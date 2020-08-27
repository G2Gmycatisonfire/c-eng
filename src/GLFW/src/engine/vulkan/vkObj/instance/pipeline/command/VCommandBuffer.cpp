//
// Created by Vlad on 19/08/2020.
//

#include "VCommandBuffer.h"

inline static void populateCommandBufferAllocateInfo (
    VulkanCommandBufferAllocateInfo * allocateInfo,
    const engine::VCommandPool      & commandPool,
    uint32                            commandBufferCount,
    VulkanCommandBufferLevel          level
) noexcept {
    if ( allocateInfo == nullptr )
        return;

    * allocateInfo = { };

    allocateInfo->sType                 = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocateInfo->commandPool           = commandPool.data();
    allocateInfo->commandBufferCount    = commandBufferCount;
    allocateInfo->level                 = level;
}

inline static void populateCommandBufferBeginInfo (
    VulkanCommandBufferBeginInfo * beginInfo
) noexcept {
    if ( beginInfo == nullptr )
        return;

    * beginInfo = { };

    beginInfo->sType            = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
    beginInfo->flags            = 0U;
    beginInfo->pInheritanceInfo = nullptr;
}

inline static void populateRenderPassBeginInfo (
    VulkanRenderPassBeginInfo   * renderPassBeginInfo,
    const engine::VFrameBuffer  * frameBuffer,
    VulkanClearValue            * pClearValues,
    uint32                        clearValueCount
) noexcept {
    if ( renderPassBeginInfo == nullptr || frameBuffer == nullptr )
        return;

    * renderPassBeginInfo = { };

    renderPassBeginInfo->sType                  = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
    renderPassBeginInfo->renderPass             = frameBuffer->getRenderPassPtr()->data();
    renderPassBeginInfo->framebuffer            = frameBuffer->data();
    renderPassBeginInfo->renderArea.offset      = {0, 0};
    renderPassBeginInfo->renderArea.extent      = frameBuffer->getRenderPassPtr()->getLogicalDevicePtr()->getSwapChain()->getImagesInfo().extent;

    renderPassBeginInfo->clearValueCount        = clearValueCount;
    renderPassBeginInfo->pClearValues           = pClearValues;
}

inline static void populateSubmitInfo (
    VulkanSubmitInfo                  * submitInfo,
    const VulkanPipelineStageFlags    * pWaitStages,
    const VulkanSemaphore             * pWaitSemaphores,
    uint32                              waitSemaphoreCount,
    const VulkanSemaphore             * pSignalSemaphores,
    uint32                              signalSemaphoreCount,
    const VulkanCommandBuffer         * pCommandBuffers,
    uint32                              commandBufferCount
) noexcept {
    if (
        submitInfo          == nullptr ||
        pWaitStages         == nullptr ||
        pWaitSemaphores     == nullptr ||
        pSignalSemaphores   == nullptr ||
        pCommandBuffers     == nullptr
    )
        return;

    * submitInfo = { };

    submitInfo->sType                   = VK_STRUCTURE_TYPE_SUBMIT_INFO;
    submitInfo->waitSemaphoreCount      = waitSemaphoreCount;
    submitInfo->pWaitDstStageMask       = pWaitStages;
    submitInfo->pWaitSemaphores         = pWaitSemaphores;

    submitInfo->commandBufferCount      = commandBufferCount;
    submitInfo->pCommandBuffers         = pCommandBuffers;

    submitInfo->signalSemaphoreCount    = signalSemaphoreCount;
    submitInfo->pSignalSemaphores       = pSignalSemaphores;
}

VulkanResult engine::VCommandBufferCollection::allocate(const engine::VCommandPool & commandPool, const engine::VFrameBufferCollection & frameBufferCollection) {
    this->_pCommandPool = & commandPool;
    VulkanCommandBufferAllocateInfo allocateInfo { };
    std::vector < VulkanCommandBuffer > handles (frameBufferCollection.size());

    populateCommandBufferAllocateInfo( & allocateInfo, commandPool, handles.size(), VCommandBuffer::PRIMARY_LEVEL );

    VulkanResult allocateResult = vkAllocateCommandBuffers( commandPool.getLogicalDevicePtr()->data(), & allocateInfo, handles.data() );

    if ( allocateResult != VK_SUCCESS )
        return allocateResult;

    uint32 frameBufferIndex = 0U;

    for ( const auto & handle : handles ) {
        this->_commandBuffers.emplace_back( handle, & frameBufferCollection.getFrameBuffers()[frameBufferIndex++] );
    }

    return allocateResult;
}

VulkanResult engine::VCommandBuffer::startRecord(
    const engine::VPipeline & pipeline,
    const VVertexBuffer * pVertexBuffers,
    const VulkanDeviceSize * pOffsets,
    uint32 vertexBufferCount
) noexcept {
    VulkanCommandBufferBeginInfo beginInfo { };

    populateCommandBufferBeginInfo( & beginInfo );

    VulkanResult recordResult = vkBeginCommandBuffer( this->_handle, & beginInfo );

    if ( recordResult != VulkanResult::VK_SUCCESS )
        return recordResult;

    VulkanRenderPassBeginInfo renderPassBeginInfo { };
    VulkanClearValue          clearColor          { 0.0f, 0.0f, 0.0f, 1.0f };

    populateRenderPassBeginInfo( & renderPassBeginInfo, this->_pFrameBuffer, & clearColor, 1U );

    vkCmdBeginRenderPass( this->_handle, & renderPassBeginInfo, VK_SUBPASS_CONTENTS_INLINE );
    vkCmdBindPipeline   ( this->_handle, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline.data() );

    if ( pVertexBuffers != nullptr ) {
        VulkanBuffer vertexBufferHandles [ vertexBufferCount ];
        for ( uint32 vertexBufferIndex = 0U; vertexBufferIndex < vertexBufferCount; vertexBufferIndex ++ )
            vertexBufferHandles [ vertexBufferIndex ] = pVertexBuffers [ vertexBufferIndex ].data();

        vkCmdBindVertexBuffers( this->_handle, 0, vertexBufferCount, vertexBufferHandles, pOffsets );
    }

    vkCmdDraw           ( this->_handle, 3, 1, 0, 0 );
    vkCmdEndRenderPass  ( this->_handle );

    return vkEndCommandBuffer( this->_handle );
}

VulkanResult engine::VCommandBufferCollection::startRecord(
    const engine::VPipeline & pipeline,
    const engine::VVertexBuffer * pVertexBuffers,
    const VulkanDeviceSize * pOffsets,
    uint32 vertexBufferCount
) noexcept {
    for ( auto & commandBuffer : this->_commandBuffers ) {
        VulkanResult startRecordResult = commandBuffer.startRecord(pipeline, pVertexBuffers, pOffsets, vertexBufferCount);
        if( startRecordResult != VulkanResult::VK_SUCCESS )
            return startRecordResult;
    }
    return VulkanResult::VK_SUCCESS;
}

void engine::VCommandBufferCollection::free() noexcept {
    std::vector < VulkanCommandBuffer > commandBufferHandles;
    for( const auto & commandBuffer : this->_commandBuffers )
        commandBufferHandles.emplace_back( commandBuffer.data() );

    vkFreeCommandBuffers (
        this->_pCommandPool->getLogicalDevicePtr()->data(),
        this->_pCommandPool->data(),
        static_cast < uint32 > ( commandBufferHandles.size() ),
        commandBufferHandles.data()
    );

    this->_commandBuffers.clear();
    this->_pCommandPool = nullptr;
}

VulkanResult engine::VCommandBuffer::submit(
    const VulkanPipelineStageFlags * pWaitStages,
    const VSemaphore * pWaitSemaphores,
    uint32 waitSemaphoreCount,
    const VSemaphore * pSignalSemaphores,
    uint32 signalSemaphoreCount,
    const VFence * pFence
) const noexcept {
    VulkanSubmitInfo    submitInfo { };
    VulkanSemaphore     waitHandles[waitSemaphoreCount];
    VulkanSemaphore     signalHandles[signalSemaphoreCount];

    for ( uint32 i = 0; i < waitSemaphoreCount; i++ )
        waitHandles[i] = pWaitSemaphores[i].data();

    for ( uint32 i = 0; i < signalSemaphoreCount; i++ )
        signalHandles[i] = pSignalSemaphores[i].data();

    populateSubmitInfo (
        & submitInfo,
        pWaitStages,
        waitHandles,
        waitSemaphoreCount,
        signalHandles,
        signalSemaphoreCount,
        & this->_handle,
        1U
    );

    const auto * pGraphicsQueue = this->_pFrameBuffer->getRenderPassPtr()->getLogicalDevicePtr()->getFirstGraphicsQueuePtr();

    if ( pGraphicsQueue == nullptr )
        return VulkanResult::VK_ERROR_INITIALIZATION_FAILED;

    if ( pFence == nullptr )
        return vkQueueSubmit( pGraphicsQueue->data(), 1U, & submitInfo, VK_NULL_HANDLE );
    else {
        vkResetFences(
            this->_pFrameBuffer->getRenderPassPtr()->getLogicalDevicePtr()->data(),
            1U,
            & pFence->data()
        );

        return vkQueueSubmit(pGraphicsQueue->data(), 1U, &submitInfo, pFence->data());
    }
}