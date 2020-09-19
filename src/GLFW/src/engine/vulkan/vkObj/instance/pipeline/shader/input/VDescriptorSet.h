//
// Created by Vlad on 07/09/2020.
//

#ifndef ENG1_VDESCRIPTORSET_H
#define ENG1_VDESCRIPTORSET_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/pipeline/shader/input/VDescriptorPool.h>
#include <vkObj/instance/pipeline/shader/input/VUniformBuffer.h>
#include <vector>

namespace engine {

    template <class T>
    class VDescriptorSetCollection;

    template <class T>
    class VDescriptorSet {
        friend class VDescriptorSetCollection<T>;
    private:
        //// private variables
        VulkanDescriptorSet     _handle;
        const VLogicalDevice  * _pLogicalDevice {nullptr};

        //// private functions

    public:
        //// public variables

        //// public functions
        VDescriptorSet ( ) noexcept = delete;
        explicit VDescriptorSet ( VulkanDescriptorSet handle, const VLogicalDevice * pLogicalDevice ) noexcept :
            _handle ( handle ),
            _pLogicalDevice ( pLogicalDevice ) {

        }

        [[nodiscard]] const VulkanDescriptorSet & data() const noexcept {
            return this->_handle;
        }

        void configure ( const VUniformBuffer <T> & ) noexcept;
    };

    template <class T>
    class VDescriptorSetCollection {
    private:
        //// private variables
        const VLogicalDevice                * _pLogicalDevice {nullptr};
        std::vector < VDescriptorSet <T> >    _descriptorSets;

        //// private functions
    public:
        //// public variables

        //// public functions
        VDescriptorSetCollection () noexcept = default;
        VulkanResult allocate ( const VDescriptorPool & , const VulkanDescriptorSetLayout & ) noexcept;

        [[nodiscard]] const std::vector < VDescriptorSet <T> > & getDescriptorSets () const noexcept {
            return this->_descriptorSets;
        }

        [[nodiscard]] std::vector < VulkanDescriptorSet > getDescriptorSetHandles () const noexcept;

        [[nodiscard]] const VLogicalDevice * getLogicalDevicePtr () const noexcept {
            return this->_pLogicalDevice;
        }

        void configure ( const std::vector < VUniformBuffer <T> > & ) noexcept;
    };

}

template <class T>
[[nodiscard]] std::vector < VulkanDescriptorSet > engine::VDescriptorSetCollection<T>::getDescriptorSetHandles () const noexcept {
    std::vector < VulkanDescriptorSet > handles;

    for ( auto & descriptorSet : this->_descriptorSets )
        handles.push_back( descriptorSet.data() );

    return handles;
}

inline static void populateDescriptorSetAllocateInfo (
        VulkanDescriptorSetAllocateInfo * pAllocateInfo,
        VulkanDescriptorPool              descriptorPool,
        uint32                            descriptorSetCount,
        const VulkanDescriptorSetLayout * pSetLayouts
) noexcept {
    if ( pAllocateInfo == nullptr || pSetLayouts == nullptr )
        return;

    * pAllocateInfo = VulkanDescriptorSetAllocateInfo {
            .sType              = VulkanStructureType::VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO,
            .pNext              = nullptr,
            .descriptorPool     = descriptorPool,
            .descriptorSetCount = descriptorSetCount,
            .pSetLayouts        = pSetLayouts,
    };
}

template <class T>
VulkanResult engine::VDescriptorSetCollection<T>::allocate(
        const VDescriptorPool & descriptorPool,
        const VulkanDescriptorSetLayout & descriptorSetBaseLayout
) noexcept {
    this->_pLogicalDevice = descriptorPool.getLogicalDevicePtr();
    auto swapChainImageCount = static_cast < uint32 > ( this->_pLogicalDevice->getSwapChain()->getImages().size() );

    std::vector < VulkanDescriptorSet >         descriptorSetHandles ( swapChainImageCount );
    std::vector < VulkanDescriptorSetLayout >   layouts ( swapChainImageCount, descriptorSetBaseLayout );

    VulkanDescriptorSetAllocateInfo             allocateInfo {};
    populateDescriptorSetAllocateInfo(
            & allocateInfo,
            descriptorPool.data(),
            swapChainImageCount,
            layouts.data()
    );

    VulkanResult allocateResult = vkAllocateDescriptorSets(
            this->_pLogicalDevice->data(),
            & allocateInfo,
            descriptorSetHandles.data()
    );

    if ( allocateResult != VulkanResult::VK_SUCCESS )
        return allocateResult;

    this->_descriptorSets.clear();
    for ( const auto & descriptorSetHandle : descriptorSetHandles )
        this->_descriptorSets.emplace_back( descriptorSetHandle, this->_pLogicalDevice );

    return VulkanResult::VK_SUCCESS;
}

static inline void populateDescriptorBufferInfo (
    VulkanDescriptorBufferInfo * pBufferInfo,
    VulkanBuffer                 uniformBufferHandle,
    uint32                       offset,
    uint32                       size
) noexcept {
    if ( pBufferInfo == nullptr )
        return;

    * pBufferInfo = VulkanDescriptorBufferInfo {
        .buffer = uniformBufferHandle,
        .offset = offset,
        .range  = size
    };
}

static inline void populateWriteDescriptorSet (
    VulkanWriteDescriptorSet          * pWriteDescriptorSet,
    VulkanDescriptorSet                 destinationDescriptorSetHandle,
    uint32                              destinationBinding,
    uint32                              destinationArrayElementIndex,
    const VulkanDescriptorBufferInfo  * pDescriptorBufferInfo
) noexcept {
    if ( pWriteDescriptorSet == nullptr )
        return;

    * pWriteDescriptorSet = VulkanWriteDescriptorSet {
        .sType              = VulkanStructureType::VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET,
        .pNext              = nullptr,
        .dstSet             = destinationDescriptorSetHandle,
        .dstBinding         = destinationBinding,
        .dstArrayElement    = destinationArrayElementIndex,
        .descriptorCount    = 1U,
        .descriptorType     = VulkanDescriptorType::VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER,
        .pImageInfo         = nullptr,
        .pBufferInfo        = pDescriptorBufferInfo,
        .pTexelBufferView   = nullptr
    };
}

template <class T>
void engine::VDescriptorSetCollection<T>::configure(const std::vector<VUniformBuffer<T>> & uniformBuffers) noexcept {
    for ( uint32 it = 0; it < this->_descriptorSets.size(); it++ )
        this->_descriptorSets[it].configure ( uniformBuffers[ it ] );
}

template <class T>
void engine::VDescriptorSet<T>::configure(const VUniformBuffer<T> & uniformBuffer) noexcept {
    VulkanDescriptorBufferInfo bufferInfo {};
    populateDescriptorBufferInfo(
        & bufferInfo,
        uniformBuffer.data(),
        0U,
        sizeof ( T )
    );

    VulkanWriteDescriptorSet writeDescriptorSet{ };
    populateWriteDescriptorSet(
        & writeDescriptorSet,
        this->_handle,
        0U,
        0U,
        & bufferInfo
    );

    vkUpdateDescriptorSets( this->_pLogicalDevice->data() , 1U, & writeDescriptorSet, 0U, nullptr );
}

#endif //ENG1_VDESCRIPTORSET_H