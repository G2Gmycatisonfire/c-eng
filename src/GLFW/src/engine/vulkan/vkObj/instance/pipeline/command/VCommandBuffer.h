//
// Created by Vlad on 19/08/2020.
//

#ifndef ENG1_VCOMMANDBUFFER_H
#define ENG1_VCOMMANDBUFFER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include "VCommandPool.h"
#include <vkObj/instance/pipeline/VFrameBuffer.h>
#include <src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VPipeline.h>
#include <src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/synchronization/VSemaphore.h>

namespace engine {

    class VCommandBuffer {
    private:
        friend class VCommandBufferCollection;
        //// private variables
        VulkanCommandBuffer     _handle         {nullptr};
        const VFrameBuffer    * _pFrameBuffer   {nullptr};

        //// private functions

    public:
        //// public variables
        constexpr static VulkanCommandBufferLevel PRIMARY_LEVEL     = VulkanCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_PRIMARY;
        constexpr static VulkanCommandBufferLevel SECONDARY_LEVEL   = VulkanCommandBufferLevel::VK_COMMAND_BUFFER_LEVEL_SECONDARY;

        //// public functions
        VCommandBuffer() noexcept = delete;
        explicit VCommandBuffer ( const VulkanCommandBuffer & handle, const VFrameBuffer * pFrameBuffer ) noexcept :
            _handle ( handle ),
            _pFrameBuffer ( pFrameBuffer ){

        }

        VulkanResult submit ( VulkanPipelineStageFlags *, VSemaphore *, uint32, VSemaphore *, uint32 ) const noexcept;

        VulkanResult startRecord ( const VPipeline& ) noexcept;
    };

    class VCommandBufferCollection {
    private:
        //// private variables
        std::vector < VCommandBuffer > _commandBuffers;

        //// private functions

    public:
        //// public variables

        //// public functions
        VCommandBufferCollection() noexcept = default;

        VulkanResult allocate ( const engine::VCommandPool &, const engine::VFrameBufferCollection & );
        VulkanResult startRecord ( const VPipeline& ) noexcept;

        [[nodiscard]] const std::vector < VCommandBuffer > & getCommandBuffers () const noexcept {
            return this->_commandBuffers;
        }
    };

}


#endif //ENG1_VCOMMANDBUFFER_H
