//
// Created by vladl on 10/5/2020.
//

#ifndef ENG1_VMESH_H
#define ENG1_VMESH_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/pipeline/command/VCommandPool.h>
#include <vkObj/instance/pipeline/shader/input/VVertexBuffer.h>
#include <vkObj/instance/pipeline/shader/input/VIndexBuffer.h>
#include <VComponent.h>

namespace engine {

    class VMesh : public VComponent {
    private:
        //// private variables
        const VCommandPool            * _pCommandPool           {nullptr};
        const VQueueFamilyCollection  * _pQueueFamilyCollection {nullptr};
        VVertexBuffer                   _vertexBuffer;
        VIndexBuffer                    _indexBuffer;

        //// private functions

    public:
        //// public variables

        //// public functions
        VMesh() noexcept : VComponent( VComponent::Type::MESH ) { }

        [[nodiscard]] VulkanResult setup(
                const VCommandPool &,
                const VQueueFamilyCollection &,
                const std::vector < engine::VVertex > &,
                const std::vector < uint16 > &
        ) noexcept;

        void free();
        void cleanup();

        [[nodiscard]] const VVertexBuffer & getVertexBuffer () const noexcept {
            return this->_vertexBuffer;
        }

        [[nodiscard]] VVertexBuffer & getVertexBuffer () noexcept {
            return this->_vertexBuffer;
        }

        [[nodiscard]] const VIndexBuffer & getIndexBuffer () const noexcept {
            return this->_indexBuffer;
        }

        [[nodiscard]] VIndexBuffer & getIndexBuffer () noexcept {
            return this->_indexBuffer;
        }

        [[nodiscard]] const VLogicalDevice * getLogicalDevicePtr () const noexcept {
            if ( this->_pCommandPool == nullptr )
                return nullptr;
            return this->_pCommandPool->getLogicalDevicePtr();
        }
    };

}


#endif //ENG1_VMESH_H
