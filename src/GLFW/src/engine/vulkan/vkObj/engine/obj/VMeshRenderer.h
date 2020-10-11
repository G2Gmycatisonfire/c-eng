//
// Created by vladl on 10/10/2020.
//

#ifndef ENG1_VMESHRENDERER_H
#define ENG1_VMESHRENDERER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <VLogicalDevice.h>
#include <VDescriptorSet.h>
#include <VShader.h>
#include <VCommandPool.h>
#include <VComponent.h>

namespace engine {

    class VMeshRenderer : public VComponent {
    private:
        //// private variables
        const VLogicalDevice                                          * _pLogicalDevice       {nullptr};
        const VTextureSampler                                         * _pTextureSampler      {nullptr};
        const VShader                                                 * _pShader              {nullptr};
        const VDescriptorPool                                         * _pDescriptorPool      {nullptr};
        const VCommandPool                                            * _pCommandPool         {nullptr};

        VTexture                                                        _texture;

//        VulkanDescriptorSetLayout                                       _descriptorSetLayout   {VK_NULL_HANDLE};
        VDescriptorSetCollection < engine::SUniformBufferObject >       _descriptorSets;     // NOLINT(bugprone-reserved-identifier)
        std::vector < VUniformBuffer < engine::SUniformBufferObject > > _MVPDescriptorBuffers;  // NOLINT(bugprone-reserved-identifier)

        //// private functions

    public:
        //// public variables

        //// public functions
        VMeshRenderer () noexcept : VComponent( VComponent::Type::MESH_RENDERER ) { }

        [[nodiscard]] const VLogicalDevice * getLogicalDevicePtr () const noexcept {
            return this->_pLogicalDevice;
        }

        [[nodiscard]] const VTextureSampler * getTextureSamplerPtr () const noexcept {
            return this->_pTextureSampler;
        }

        [[nodiscard]] const VTexture & getTexture () const noexcept {
            return this->_texture;
        }

        [[nodiscard]] VTexture & getTexture () noexcept {
            return this->_texture;
        }

//        [[nodiscard]] const VulkanDescriptorSetLayout & getDescriptorSetLayout () const noexcept {
//            return this->_descriptorSetLayout;
//        }
//
//        [[nodiscard]] VulkanDescriptorSetLayout & getDescriptorSetLayout () noexcept {
//            return this->_descriptorSetLayout;
//        }

        [[nodiscard]] const VDescriptorSetCollection < engine::SUniformBufferObject > & getDescriptorSets () const noexcept {
            return this->_descriptorSets;
        }

        [[nodiscard]] VDescriptorSetCollection < engine::SUniformBufferObject > & getDescriptorSets () noexcept {
            return this->_descriptorSets;
        }

        [[nodiscard]] const std::vector < VUniformBuffer < engine::SUniformBufferObject >> & getMVPDescriptorBuffers () const noexcept {
            return this->_MVPDescriptorBuffers;
        }

        [[nodiscard]] std::vector < VUniformBuffer < engine::SUniformBufferObject >> & getMVPDescriptorBuffers () noexcept {
            return this->_MVPDescriptorBuffers;
        }

        void cleanup() noexcept;

        void cleanupUniformBuffers () noexcept;
        VulkanResult recreateUniformBuffers () noexcept;
        VulkanResult recreateDescriptorSets () noexcept;
        VulkanResult recreate() noexcept;

        VulkanResult setup (
                const VCommandPool &,
                const VDescriptorPool &,
                const VShader &,
                const std::string &,
                const VTextureSampler &,
                const VQueueFamilyCollection &
        ) noexcept;
    };

}


#endif //ENG1_VMESHRENDERER_H
