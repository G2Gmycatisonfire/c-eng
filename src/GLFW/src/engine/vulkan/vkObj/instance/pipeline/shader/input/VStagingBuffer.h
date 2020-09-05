//
// Created by loghin on 9/5/20.
//

#ifndef ENG1_VSTAGINGBUFFER_H
#define ENG1_VSTAGINGBUFFER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>
#include <vkObj/instance/pipeline/shader/input/VVertex.h>
#include <vkObj/instance/pipeline/shader/input/VBuffer.h>

namespace engine {

    class VStagingBuffer : public VBuffer {
    private:
        //// private variables
//        uint32                                        _vertexCount    {0U};
        const std::vector < engine::VVertex >       * _pVertices      {nullptr};
        std::vector < engine::VVertex::SVertexPack >  _packedVertices;


        //// private functions 

    public:
        //// public variables
        VStagingBuffer () noexcept = default;

        VulkanResult setup (
            const VLogicalDevice &,
            const std::vector < VVertex > &,
            VulkanSharingMode = VulkanSharingMode::VK_SHARING_MODE_EXCLUSIVE
        ) noexcept;

        VulkanResult allocateMemory () noexcept;
//        VulkanResult allocateMemory ( VulkanMemoryPropertyFlags ) noexcept;
//        [[nodiscard]] uint32 getVertexCount () const noexcept {
//            return this->_vertexCount;
//        }

        void free () noexcept override;
        void cleanup () noexcept override;

        //// public functions

    };

}


#endif //ENG1_VSTAGINGBUFFER_H
