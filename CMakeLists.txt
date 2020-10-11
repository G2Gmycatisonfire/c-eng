cmake_minimum_required(VERSION 3.5)
project(eng1)

set(CMAKE_CXX_STANDARD 20)
set(OpenGL_GL_PREFERENCE GLVND)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(dependencies/glfw_src)
add_subdirectory(dependencies/glad)
add_subdirectory(dependencies/glm)
add_subdirectory(dependencies/assimp-5.0.1)
add_subdirectory(dependencies/JSONCpp)

include_directories(dependencies/sqlite-autoconf-3320300)
include_directories(dependencies/glm)
include_directories(dependencies/glfw_src/include)
include_directories(dependencies/glad/include)
include_directories(dependencies/stb_image)
include_directories(dependencies/JSONCpp/include)

include_directories(src/GLFW/src/engine)

find_package(OpenGL REQUIRED)
find_package(ASSIMP)

if(SQLite3_FOUND)
    include_directories(${SQLite3_INCLUDE_DIRS})
endif()

if(ASSIMP_FOUND)
    include_directories(${ASSIMP_INCLUDE_DIR})
endif()


if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
    add_compile_options(-fprofile-instr-generate -fcoverage-mapping)
    add_link_options(-fprofile-instr-generate)
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    add_compile_options(--coverage)
    link_libraries(gcov)
endif()


# VULKAN extension

find_package(Vulkan)

if(Vulkan_FOUND)
    include_directories(src/GLFW/src/engine/vulkan)
    include_directories(src/GLFW/src/engine/vulkan/vkObj/instance)
    include_directories(src/GLFW/src/engine/vulkan/vkObj/instance/device)
    include_directories(src/GLFW/src/engine/vulkan/vkObj/instance/device/queue)
    include_directories(src/GLFW/src/engine/vulkan/vkObj/instance/extension)
    include_directories(src/GLFW/src/engine/vulkan/vkObj/instance/messenger)
    include_directories(src/GLFW/src/engine/vulkan/vkObj/instance/validationLayer)
    include_directories(src/GLFW/src/engine/vulkan/vkObj/instance/pipeline)
    include_directories(src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/command)
    include_directories(src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader)
    include_directories(src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input)
    include_directories(src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/synchronization)
    include_directories(src/GLFW/src/engine/vulkan/vkObj/engine)
    include_directories(src/GLFW/src/engine/vulkan/vkObj/engine/obj)
    include_directories(src/GLFW/src/engine/vulkan/vkObj/engine/space)


    include_directories( ${Vulkan_INCLUDE_DIRS} )

    message(-- VULKAN_PATH :   ${Vulkan_LIBRARY} )

    add_executable( vkTriangle
            ${JSONCpp_SOURCE}
            src/GLFW/src/engine/vulkan/vkTests/c/vulkanTriangle.cpp
            src/GLFW/src/engine/vulkan/vkTests/obj/VulkanTriangleApplication.cpp
            src/GLFW/src/engine/vulkan/vkTests/obj/VulkanTriangleApplication.h
            src/GLFW/src/engine/vulkan/vkTests/obj/VulkanInitTests.cpp
            src/GLFW/src/engine/vulkan/vkTests/obj/VulkanInitTests.h
            src/GLFW/src/engine/vulkan/engineVulkanPreproc.h
            src/GLFW/src/engine/vulkan/vkDefs/types/vulkanExplicitTypes.h
            src/GLFW/src/engine/vulkan/vkDefs/vkDefinitions.h
            src/GLFW/src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.h
            src/GLFW/src/engine/vulkan/vkObj/instance/VInstance.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/VInstance.h
            src/GLFW/src/engine/vulkan/vkObj/instance/messenger/VMessenger.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/messenger/VMessenger.h
            src/GLFW/src/engine/vulkan/vkObj/instance/extension/VExtension.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/extension/VExtension.h
            src/GLFW/src/engine/vulkan/vkUtils/VStdUtils.cpp
            src/GLFW/src/engine/vulkan/vkUtils/VStdUtils.h
            src/GLFW/src/engine/vulkan/vkUtils/VStdUtilsDefs.h
            src/GLFW/src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.h
            src/GLFW/src/engine/vulkan/vkObj/instance/device/VPhysicalDeviceDefs.h
            src/GLFW/src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.h
            src/GLFW/src/engine/vulkan/vkObj/instance/device/VLogicalDevice.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/device/VLogicalDevice.h
            src/GLFW/src/engine/vulkan/vkObj/instance/device/queue/VQueue.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/device/queue/VQueue.h
            src/GLFW/src/engine/vulkan/vkObj/window/surface/VSurface.cpp
            src/GLFW/src/engine/vulkan/vkObj/window/surface/VSurface.h
            src/GLFW/src/engine/vulkan/vkDefs/types/vkPlatformDefs.cpp
            src/GLFW/src/engine/vulkan/vkDefs/types/vulkanShortHandTypes.h
            src/GLFW/src/engine/vulkan/vkObj/instance/device/VSwapChainDefs.h
            src/GLFW/src/engine/obj/util/settings/SettingsSharedContainer.cpp
            src/GLFW/src/engine/obj/util/settings/SettingsSharedContainer.h
            src/GLFW/src/engine/obj/util/settings/SettingOption.cpp
            src/GLFW/src/engine/obj/util/settings/SettingOption.h
            src/GLFW/src/engine/obj/util/settings/SettingOptionGraphics.cpp
            src/GLFW/src/engine/obj/util/settings/SettingOptionGraphics.h
            src/GLFW/src/engine/vulkan/vkObj/instance/device/VSwapChain.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/device/VSwapChain.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VImageView.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VImageView.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderCompiler.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderCompiler.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModule.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModule.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModuleDefs.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VPipeline.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VPipeline.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VRenderPass.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VRenderPass.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VFrameBuffer.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VFrameBuffer.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/command/VCommandBuffer.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/command/VCommandBuffer.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/command/VCommandPool.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/command/VCommandPool.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/synchronization/VSemaphore.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/synchronization/VSemaphore.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/synchronization/VFence.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/synchronization/VFence.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertex.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertex.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertexBuffer.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input/VVertexBuffer.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input/VBuffer.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input/VBuffer.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input/VStagingBuffer.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input/VStagingBuffer.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input/VIndexBuffer.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input/VIndexBuffer.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input/VUniformBuffer.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input/VUniformBuffer.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input/VDescriptorPool.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input/VDescriptorPool.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input/VDescriptorSet.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input/VDescriptorSet.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input/VTexture.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input/VTexture.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/input/VTextureDefs.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VTextureSampler.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VTextureSampler.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VDepthBuffer.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VDepthBuffer.h
            src/GLFW/src/engine/vulkan/vkObj/engine/space/VTransform.cpp
            src/GLFW/src/engine/vulkan/vkObj/engine/space/VTransform.h
            src/GLFW/src/engine/vulkan/vkObj/engine/obj/VMesh.cpp
            src/GLFW/src/engine/vulkan/vkObj/engine/obj/VMesh.h
            src/GLFW/src/engine/vulkan/vkObj/engine/obj/VShader.cpp
            src/GLFW/src/engine/vulkan/vkObj/engine/obj/VShader.h
            src/GLFW/src/engine/vulkan/vkObj/engine/obj/VMeshRenderer.cpp
            src/GLFW/src/engine/vulkan/vkObj/engine/obj/VMeshRenderer.h
            src/GLFW/src/engine/vulkan/vkObj/engine/VEntity.cpp src/GLFW/src/engine/vulkan/vkObj/engine/VEntity.h src/GLFW/src/engine/vulkan/vkObj/engine/VComponent.cpp src/GLFW/src/engine/vulkan/vkObj/engine/VComponent.h src/GLFW/src/engine/vulkan/vkObj/engine/VEntityManager.cpp src/GLFW/src/engine/vulkan/vkObj/engine/VEntityManager.h)


    target_link_libraries( vkTriangle Vulkan::Vulkan )

    target_link_libraries( vkTriangle glfw ${GLFW_LIBRARIES} )

#    add_executable( vkTriangleT
#            ${JSONCpp_SOURCE}
#            src/GLFW/src/engine/vulkan/_template/TemplateTriangle.cpp
#            src/GLFW/src/engine/vulkan/vkTests/obj/VulkanTriangleApplication.cpp
#            src/GLFW/src/engine/vulkan/vkTests/obj/VulkanTriangleApplication.h
#            src/GLFW/src/engine/vulkan/vkTests/obj/VulkanInitTests.cpp
#            src/GLFW/src/engine/vulkan/vkTests/obj/VulkanInitTests.h
#            src/GLFW/src/engine/vulkan/engineVulkanPreproc.h
#            src/GLFW/src/engine/vulkan/vkDefs/types/vulkanExplicitTypes.h
#            src/GLFW/src/engine/vulkan/vkDefs/vkDefinitions.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.cpp
#            src/GLFW/src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/VInstance.cpp
#            src/GLFW/src/engine/vulkan/vkObj/instance/VInstance.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/messenger/VMessenger.cpp
#            src/GLFW/src/engine/vulkan/vkObj/instance/messenger/VMessenger.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/extension/VExtension.cpp
#            src/GLFW/src/engine/vulkan/vkObj/instance/extension/VExtension.h
#            src/GLFW/src/engine/vulkan/vkUtils/VStdUtils.cpp
#            src/GLFW/src/engine/vulkan/vkUtils/VStdUtils.h
#            src/GLFW/src/engine/vulkan/vkUtils/VStdUtilsDefs.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.cpp
#            src/GLFW/src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/device/VPhysicalDeviceDefs.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.cpp
#            src/GLFW/src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/device/VLogicalDevice.cpp
#            src/GLFW/src/engine/vulkan/vkObj/instance/device/VLogicalDevice.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/device/queue/VQueue.cpp
#            src/GLFW/src/engine/vulkan/vkObj/instance/device/queue/VQueue.h
#            src/GLFW/src/engine/vulkan/vkObj/window/surface/VSurface.cpp
#            src/GLFW/src/engine/vulkan/vkObj/window/surface/VSurface.h
#            src/GLFW/src/engine/vulkan/vkDefs/types/vkPlatformDefs.cpp
#            src/GLFW/src/engine/vulkan/vkDefs/types/vulkanShortHandTypes.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/device/VSwapChainDefs.h
#            src/GLFW/src/engine/obj/util/settings/SettingsSharedContainer.cpp
#            src/GLFW/src/engine/obj/util/settings/SettingsSharedContainer.h
#            src/GLFW/src/engine/obj/util/settings/SettingOption.cpp
#            src/GLFW/src/engine/obj/util/settings/SettingOption.h
#            src/GLFW/src/engine/obj/util/settings/SettingOptionGraphics.cpp
#            src/GLFW/src/engine/obj/util/settings/SettingOptionGraphics.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/device/VSwapChain.cpp
#            src/GLFW/src/engine/vulkan/vkObj/instance/device/VSwapChain.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VImageView.cpp
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VImageView.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderCompiler.cpp
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderCompiler.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModule.cpp
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModule.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModuleDefs.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VPipeline.cpp
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VPipeline.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VRenderPass.cpp
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VRenderPass.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VFrameBuffer.cpp
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VFrameBuffer.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/command/VCommandBuffer.cpp
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/command/VCommandBuffer.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/command/VCommandPool.cpp
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/command/VCommandPool.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/synchronization/VSemaphore.cpp
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/synchronization/VSemaphore.h
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/synchronization/VFence.cpp
#            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/synchronization/VFence.h
#            )
#
#
#    target_link_libraries( vkTriangleT Vulkan::Vulkan )
#
#    target_link_libraries( vkTriangleT glfw ${GLFW_LIBRARIES} )


    add_executable( vkPrecompiler
            ${JSONCpp_SOURCE}
            src/GLFW/src/engine/vulkan/vkTests/c/vulkanPrecompilerTest.cpp
            src/GLFW/src/engine/vulkan/vkTests/obj/VulkanInitTests.cpp
            src/GLFW/src/engine/vulkan/vkTests/obj/VulkanInitTests.h
            src/GLFW/src/engine/vulkan/engineVulkanPreproc.h
            src/GLFW/src/engine/vulkan/vkDefs/types/vulkanExplicitTypes.h
            src/GLFW/src/engine/vulkan/vkDefs/vkDefinitions.h
            src/GLFW/src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/validationLayer/VValidationLayer.h
            src/GLFW/src/engine/vulkan/vkObj/instance/VInstance.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/VInstance.h
            src/GLFW/src/engine/vulkan/vkObj/instance/messenger/VMessenger.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/messenger/VMessenger.h
            src/GLFW/src/engine/vulkan/vkObj/instance/extension/VExtension.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/extension/VExtension.h
            src/GLFW/src/engine/vulkan/vkUtils/VStdUtils.cpp
            src/GLFW/src/engine/vulkan/vkUtils/VStdUtils.h
            src/GLFW/src/engine/vulkan/vkUtils/VStdUtilsDefs.h
            src/GLFW/src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.h
            src/GLFW/src/engine/vulkan/vkObj/instance/device/VPhysicalDeviceDefs.h
            src/GLFW/src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/device/queue/VQueueFamily.h
            src/GLFW/src/engine/vulkan/vkObj/instance/device/VLogicalDevice.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/device/VLogicalDevice.h
            src/GLFW/src/engine/vulkan/vkObj/instance/device/queue/VQueue.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/device/queue/VQueue.h
            src/GLFW/src/engine/vulkan/vkObj/window/surface/VSurface.cpp
            src/GLFW/src/engine/vulkan/vkObj/window/surface/VSurface.h
            src/GLFW/src/engine/vulkan/vkDefs/types/vkPlatformDefs.cpp
            src/GLFW/src/engine/vulkan/vkDefs/types/vulkanShortHandTypes.h
            src/GLFW/src/engine/vulkan/vkObj/instance/device/VSwapChainDefs.h
            src/GLFW/src/engine/obj/util/settings/SettingsSharedContainer.cpp
            src/GLFW/src/engine/obj/util/settings/SettingsSharedContainer.h
            src/GLFW/src/engine/obj/util/settings/SettingOption.cpp
            src/GLFW/src/engine/obj/util/settings/SettingOption.h
            src/GLFW/src/engine/obj/util/settings/SettingOptionGraphics.cpp
            src/GLFW/src/engine/obj/util/settings/SettingOptionGraphics.h
            src/GLFW/src/engine/vulkan/vkObj/instance/device/VSwapChain.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/device/VSwapChain.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VImageView.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/VImageView.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderCompiler.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderCompiler.h
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModule.cpp
            src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/shader/VShaderModule.h
            )


    target_link_libraries( vkPrecompiler Vulkan::Vulkan )

    target_link_libraries( vkPrecompiler glfw ${GLFW_LIBRARIES} )
endif()


add_executable( GLFWInitWindow
        src/GLFW/src/engine/tests/c/testInitWindow.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        src/GLFW/src/engine/enginePreproc.h
        src/GLFW/src/engine/types.h
        src/GLFW/src/engine/tests/h/lighting.h
)

target_link_libraries( GLFWInitWindow glfw ${GLFW_LIBRARIES} )

add_executable( GLFWPortOfFreeGLUT
        dependencies/glad/src/glad.c
        dependencies/glad/include/glad/glad.h
        dependencies/glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/tests/c/mainPort.cpp
        src/GLFW/src/engine/obj/window/Window.cpp
        src/GLFW/src/engine/obj/window/Window.h
        src/GLFW/src/engine/obj/util/func/KeyFunctions.cpp
        src/GLFW/src/engine/obj/util/func/KeyFunctions.h
        src/GLFW/src/engine/obj/util/geom/Size.cpp
        src/GLFW/src/engine/obj/util/geom/Size.h
        src/GLFW/src/engine/obj/util/geom/Point.cpp
        src/GLFW/src/engine/obj/util/geom/Point.h
        src/GLFW/src/engine/obj/util/geom/Vector.cpp
        src/GLFW/src/engine/obj/util/geom/Vector.h
        src/GLFW/src/engine/obj/util/geom/Vector4.cpp
        src/GLFW/src/engine/obj/util/geom/Vector4.h
        src/GLFW/src/engine/obj/util/event/InputListener.cpp
        src/GLFW/src/engine/obj/util/event/InputListener.h
        src/GLFW/src/engine/obj/util/event/KeyListener.cpp
        src/GLFW/src/engine/obj/util/event/KeyListener.h
        src/GLFW/src/engine/Engine.cpp
        src/GLFW/src/engine/Engine.h
        src/GLFW/src/engine/types.h
        src/GLFW/src/engine/enginePreproc.h
        src/GLFW/src/engine/obj/util/event/MouseListener.cpp
        src/GLFW/src/engine/obj/util/event/MouseListener.h
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.h
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.c
        src/GLFW/src/engine/obj/util/obj/Transform.cpp
        src/GLFW/src/engine/obj/util/obj/Transform.h
        src/GLFW/src/engine/obj/util/obj/GameObject.cpp
        src/GLFW/src/engine/obj/util/obj/GameObject.h
        src/GLFW/src/engine/obj/util/data/Color.cpp
        src/GLFW/src/engine/obj/util/data/Color.h
        src/GLFW/src/engine/obj/util/data/Array.cpp
        src/GLFW/src/engine/obj/util/data/Array.h
        src/GLFW/src/engine/obj/util/obj/stdObj/Camera.cpp
        src/GLFW/src/engine/obj/util/obj/stdObj/Camera.h
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        dependencies/stb_image/stb-image.h
        src/GLFW/src/engine/obj/util/geom/Vector2.cpp
        src/GLFW/src/engine/obj/util/geom/Vector2.h
        src/GLFW/src/engine/obj/util/data/Matrix.cpp
        src/GLFW/src/engine/obj/util/data/Matrix.h
)

target_link_libraries( GLFWPortOfFreeGLUT glfw ${GLFW_LIBRARIES} )

add_executable( drawTests src/GLFW/src/engine/tests/c/drawTests.cpp
        dependencies/glad/src/glad.c
        dependencies/glad/include/glad/glad.h
        dependencies/glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        dependencies/stb_image/stb-image.h
        src/GLFW/src/engine/obj/util/geom/Vector2.cpp
        src/GLFW/src/engine/obj/util/geom/Vector2.h
        src/GLFW/src/engine/obj/util/data/Matrix.cpp
        src/GLFW/src/engine/obj/util/data/Matrix.h
)

target_link_libraries( drawTests glfw ${GLFW_LIBRARIES} )

add_executable( glfwSandbox
        src/GLFW/src/engine/tests/c/glfwSandbox.cpp
        src/GLFW/src/engine/obj/util/data/Matrix.h
        src/GLFW/src/engine/obj/util/data/Matrix.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        dependencies/stb_image/stb-image.h
    )

add_executable( glfwSandbox2
        dependencies/glad/src/glad.c
        dependencies/glad/include/glad/glad.h
        dependencies/glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/tests/sandbox/glfwSandbox2.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        dependencies/stb_image/stb-image.h
)

target_link_libraries( glfwSandbox2 glfw ${GLFW_LIBRARIES} )

add_executable( glfwWhiteboard1
        dependencies/glad/src/glad.c
        dependencies/glad/include/glad/glad.h
        dependencies/glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/tests/sandbox/whiteboard1.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        src/GLFW/src/engine/obj/util/obj/GameObject.cpp
        src/GLFW/src/engine/obj/util/obj/GameObject.h
        src/GLFW/src/engine/obj/util/obj/Transform.cpp
        src/GLFW/src/engine/obj/util/obj/Transform.h
        src/GLFW/src/engine/obj/util/geom/Vector.cpp
        src/GLFW/src/engine/obj/util/geom/Vector.h
        src/GLFW/src/engine/Engine.cpp
        src/GLFW/src/engine/Engine.h
        src/GLFW/src/engine/obj/window/Window.cpp
        src/GLFW/src/engine/obj/window/Window.h
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.c
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.h
        src/GLFW/src/engine/obj/util/data/String.cpp
        src/GLFW/src/engine/obj/util/data/String.h
        src/GLFW/src/engine/obj/util/data/Array.cpp
        src/GLFW/src/engine/obj/util/data/Array.h
        src/GLFW/src/engine/obj/util/data/Pair.cpp
        src/GLFW/src/engine/obj/util/data/Pair.h
        src/GLFW/src/engine/obj/util/data/Map.cpp
        src/GLFW/src/engine/obj/util/data/Map.h
        dependencies/stb_image/stb-image.h
)

target_link_libraries( glfwWhiteboard1 glfw ${GLFW_LIBRARIES} )

add_executable( glfwWhiteboard2
        dependencies/glad/src/glad.c
        dependencies/glad/include/glad/glad.h
        dependencies/glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/tests/sandbox/whiteboard2.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        dependencies/stb_image/stb-image.h
        src/GLFW/src/engine/obj/util/data/Array.cpp
        src/GLFW/src/engine/obj/util/data/Array.h
        src/GLFW/src/engine/obj/util/data/String.cpp
        src/GLFW/src/engine/obj/util/data/String.h
)

target_link_libraries( glfwWhiteboard2 glfw ${GLFW_LIBRARIES} )


add_executable( glfwLightning
        src/GLFW/src/engine/tests/c/lightingTest.cpp
        dependencies/glad/src/glad.c
        dependencies/glad/include/glad/glad.h
        dependencies/glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        src/GLFW/src/engine/obj/util/obj/GameObject.cpp
        src/GLFW/src/engine/obj/util/obj/GameObject.h
        src/GLFW/src/engine/obj/util/obj/Transform.cpp
        src/GLFW/src/engine/obj/util/obj/Transform.h
        src/GLFW/src/engine/obj/util/geom/Vector.cpp
        src/GLFW/src/engine/obj/util/geom/Vector.h
        src/GLFW/src/engine/Engine.cpp
        src/GLFW/src/engine/Engine.h
        src/GLFW/src/engine/obj/window/Window.cpp
        src/GLFW/src/engine/obj/window/Window.h
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.c
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.h
        dependencies/stb_image/stb-image.h
)

target_link_libraries( glfwLightning glfw ${GLFW_LIBRARIES} )

add_executable( glfwDiffuseMaps
        src/GLFW/src/engine/tests/c/diffuseMaps.cpp
        dependencies/glad/src/glad.c
        dependencies/glad/include/glad/glad.h
        dependencies/glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        src/GLFW/src/engine/obj/util/obj/GameObject.cpp
        src/GLFW/src/engine/obj/util/obj/GameObject.h
        src/GLFW/src/engine/obj/util/obj/Transform.cpp
        src/GLFW/src/engine/obj/util/obj/Transform.h
        src/GLFW/src/engine/obj/util/geom/Vector.cpp
        src/GLFW/src/engine/obj/util/geom/Vector.h
        src/GLFW/src/engine/Engine.cpp
        src/GLFW/src/engine/Engine.h
        src/GLFW/src/engine/obj/window/Window.cpp
        src/GLFW/src/engine/obj/window/Window.h
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.c
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.h
        dependencies/stb_image/stb-image.h
        src/GLFW/src/engine/dataTypes.h)

target_link_libraries( glfwDiffuseMaps glfw ${GLFW_LIBRARIES} )

#set_target_properties(
#        drawTests
#        GLFWPortOfFreeGLUT
#
#        PROPERTIES
#
#        RUNTIME_OUTPUT_DIRECTORY "/build/bin/"
#        ARCHIVE_OUTPUT_DIRECTORY "/build/lib/"
#        LIBRARY_OUTPUT_DIRECTORY "/build/lib/"
#)


add_executable( glfwLightcasting
        src/GLFW/src/engine/tests/c/lightCasting.cpp
        dependencies/glad/src/glad.c
        dependencies/glad/include/glad/glad.h
        dependencies/glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        src/GLFW/src/engine/obj/util/obj/GameObject.cpp
        src/GLFW/src/engine/obj/util/obj/GameObject.h
        src/GLFW/src/engine/obj/util/obj/Transform.cpp
        src/GLFW/src/engine/obj/util/obj/Transform.h
        src/GLFW/src/engine/obj/util/geom/Vector.cpp
        src/GLFW/src/engine/obj/util/geom/Vector.h
        src/GLFW/src/engine/Engine.cpp
        src/GLFW/src/engine/Engine.h
        src/GLFW/src/engine/obj/window/Window.cpp
        src/GLFW/src/engine/obj/window/Window.h
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.c
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.h
        dependencies/stb_image/stb-image.h
        )

target_link_libraries( glfwLightcasting glfw ${GLFW_LIBRARIES} )


add_executable( glfwSpotlights
        src/GLFW/src/engine/tests/c/spotlightTest.cpp
        dependencies/glad/src/glad.c
        dependencies/glad/include/glad/glad.h
        dependencies/glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        src/GLFW/src/engine/obj/util/obj/GameObject.cpp
        src/GLFW/src/engine/obj/util/obj/GameObject.h
        src/GLFW/src/engine/obj/util/obj/Transform.cpp
        src/GLFW/src/engine/obj/util/obj/Transform.h
        src/GLFW/src/engine/obj/util/geom/Vector.cpp
        src/GLFW/src/engine/obj/util/geom/Vector.h
        src/GLFW/src/engine/Engine.cpp
        src/GLFW/src/engine/Engine.h
        src/GLFW/src/engine/obj/window/Window.cpp
        src/GLFW/src/engine/obj/window/Window.h
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.c
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.h
        dependencies/stb_image/stb-image.h
        )

target_link_libraries( glfwSpotlights glfw ${GLFW_LIBRARIES} )

add_executable( glfwMultLights
        src/GLFW/src/engine/tests/c/multipleLights.cpp
        dependencies/glad/src/glad.c
        dependencies/glad/include/glad/glad.h
        dependencies/glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        src/GLFW/src/engine/obj/util/obj/GameObject.cpp
        src/GLFW/src/engine/obj/util/obj/GameObject.h
        src/GLFW/src/engine/obj/util/obj/Transform.cpp
        src/GLFW/src/engine/obj/util/obj/Transform.h
        src/GLFW/src/engine/obj/util/geom/Vector.cpp
        src/GLFW/src/engine/obj/util/geom/Vector.h
        src/GLFW/src/engine/obj/util/data/String.cpp
        src/GLFW/src/engine/obj/util/data/String.h
        src/GLFW/src/engine/obj/util/data/Array.cpp
        src/GLFW/src/engine/obj/util/data/Array.h
        src/GLFW/src/engine/Engine.cpp
        src/GLFW/src/engine/Engine.h
        src/GLFW/src/engine/obj/window/Window.cpp
        src/GLFW/src/engine/obj/window/Window.h
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.c
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.h
        dependencies/stb_image/stb-image.h
        )

target_link_libraries( glfwMultLights glfw ${GLFW_LIBRARIES} )

add_executable( glfwModels
        src/GLFW/src/engine/tests/c/glfwModels.cpp
        dependencies/glad/src/glad.c
        dependencies/glad/include/glad/glad.h
        dependencies/glad/include/KHR/khrplatform.h
        src/GLFW/src/engine/obj/util/shader/Shader.cpp
        src/GLFW/src/engine/obj/util/shader/Shader.h
        src/GLFW/src/engine/obj/util/diag/Diagnostic.cpp
        src/GLFW/src/engine/obj/util/diag/Diagnostic.h
        src/GLFW/src/engine/obj/util/obj/GameObject.cpp
        src/GLFW/src/engine/obj/util/obj/GameObject.h
        src/GLFW/src/engine/obj/util/obj/Transform.cpp
        src/GLFW/src/engine/obj/util/obj/Transform.h
        src/GLFW/src/engine/obj/util/geom/Vector.cpp
        src/GLFW/src/engine/obj/util/geom/Vector.h
        src/GLFW/src/engine/Engine.cpp
        src/GLFW/src/engine/Engine.h
        src/GLFW/src/engine/obj/window/Window.cpp
        src/GLFW/src/engine/obj/window/Window.h
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.c
        src/GLFW/src/engine/obj/util/struct/inputAxisFunc.h
        dependencies/stb_image/stb-image.h
        src/GLFW/src/engine/obj/util/struct/meshStructs.h
        src/GLFW/src/engine/obj/util/model/Mesh.cpp
        src/GLFW/src/engine/obj/util/model/Mesh.h
        src/GLFW/src/engine/obj/util/data/String.cpp
        src/GLFW/src/engine/obj/util/data/String.h
        src/GLFW/src/engine/obj/util/data/Array.cpp
        src/GLFW/src/engine/obj/util/data/Array.h
        src/GLFW/src/engine/obj/util/data/Set.cpp src/GLFW/src/engine/obj/util/data/Set.h src/GLFW/src/engine/obj/util/data/Map.cpp src/GLFW/src/engine/obj/util/data/Map.h src/GLFW/src/engine/obj/util/model/Model.cpp src/GLFW/src/engine/obj/util/model/Model.h src/GLFW/src/engine/obj/util/func/TextureManager.cpp src/GLFW/src/engine/obj/util/func/TextureManager.h)

target_link_libraries( glfwModels glfw ${GLFW_LIBRARIES} )


add_executable( Sandbox3
        src/GLFW/src/engine/tests/sandbox/sandbox3.cpp
        src/GLFW/src/engine/obj/util/data/Array.cpp
        src/GLFW/src/engine/obj/util/data/Array.h
        src/GLFW/src/engine/obj/util/data/String.cpp
        src/GLFW/src/engine/obj/util/data/String.h
        src/GLFW/src/engine/obj/util/data/Set.cpp
        src/GLFW/src/engine/obj/util/data/Set.h
        src/GLFW/src/engine/obj/util/data/Pair.cpp src/GLFW/src/engine/obj/util/data/Pair.h)

add_executable( whiteboard3
        src/GLFW/src/engine/tests/sandbox/whiteboard3.cpp
)

add_executable( whiteboard4
        src/GLFW/src/engine/tests/sandbox/whiteboard4.cpp
#        dependencies/glad/src/glad.c
#        dependencies/glad/include/glad/glad.h
#        dependencies/glad/include/KHR/khrplatform.h
#        dependencies/stb_image/stb-image.h
        )

target_link_libraries( whiteboard4) #glfw assimp ${GLFW_LIBRARIES} ${ASSIMP_LIBRARIES} )
#target_link_libraries( whiteboard4 assimp ${ASSIMP_LIBRARIES} )


add_executable(
        sandbox src/exec/sandbox.cpp
        src/GLFW/src/engine/obj/util/data/Array.cpp
        src/GLFW/src/engine/obj/util/data/Array.h
)

add_executable( drawReshapeTest
        src/exec/tests/drawReshapeTest.cpp
        src/obj/engine/window/Window.cpp
        src/obj/engine/window/Window.h
        src/obj/engine/util/Size.cpp
        src/obj/engine/util/Size.h
        src/obj/engine/util/geom/Point.cpp
        src/obj/engine/util/geom/Point.h
        src/obj/engine/util/defs/types.h
        src/obj/engine/Engine.cpp
        src/obj/engine/Engine.h
        src/obj/engine/preCompiledHeaders.h
        )

target_link_libraries(drawReshapeTest -lOpenGL32 -lfreeGLUT -lglu32)

add_executable( animateTest
        src/exec/tests/animateTest.cpp
        src/obj/engine/window/Window.cpp
        src/obj/engine/window/Window.h
        src/obj/engine/util/Size.cpp
        src/obj/engine/util/Size.h
        src/obj/engine/util/geom/Point.cpp
        src/obj/engine/util/geom/Point.h
        src/obj/engine/util/defs/types.h
        src/obj/engine/Engine.cpp
        src/obj/engine/Engine.h
        src/obj/engine/util/event/KeyListener.cpp
        src/obj/engine/util/event/KeyListener.h
        src/obj/engine/util/obj/standardObj/Camera.cpp
        src/obj/engine/util/obj/standardObj/Camera.h
        src/obj/engine/util/obj/standardObj/Sphere.cpp
        src/obj/engine/util/obj/standardObj/Sphere.h
        src/obj/engine/util/dataStructures/Array.cpp
        src/obj/engine/util/dataStructures/Array.h
        src/obj/engine/preCompiledHeaders.h
        src/GLFW/src/engine/enginePreproc.h src/GLFW/src/engine/obj/util/func/KeyFunctions.cpp src/GLFW/src/engine/obj/util/func/KeyFunctions.h src/GLFW/src/engine/vulkan/vkTests/obj/VulkanTriangleApplication.cpp src/GLFW/src/engine/vulkan/vkTests/obj/VulkanTriangleApplication.h src/GLFW/src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.cpp src/GLFW/src/engine/vulkan/vkObj/instance/device/VPhysicalDevice.h src/GLFW/src/engine/vulkan/vkDefs/VInstanceDefinitions.h src/GLFW/src/engine/vulkan/vkDefs/vkPlatformDefs.h src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/command/VCommandPool.cpp src/GLFW/src/engine/vulkan/vkObj/instance/pipeline/command/VCommandPool.h src/GLFW/src/engine/vulkan/vkObj/engine/space/VTransform.cpp src/GLFW/src/engine/vulkan/vkObj/engine/space/VTransform.h src/GLFW/src/engine/vulkan/vkObj/engine/space/VRotor.cpp src/GLFW/src/engine/vulkan/vkObj/engine/space/VRotor.h)

target_link_libraries(animateTest -lOpenGL32 -lfreeGLUT -lglu32)

add_executable( inputTest
        src/exec/tests/inputTest.cpp
        src/obj/engine/window/Window.cpp
        src/obj/engine/window/Window.h
        src/obj/engine/util/Size.cpp
        src/obj/engine/util/Size.h
        src/obj/engine/util/geom/Point.cpp
        src/obj/engine/util/geom/Point.h
        src/obj/engine/util/defs/types.h
        src/obj/engine/Engine.cpp
        src/obj/engine/Engine.h
        src/obj/engine/util/event/KeyListener.cpp
        src/obj/engine/util/event/KeyListener.h
        src/obj/engine/preCompiledHeaders.h
        src/obj/engine/util/dataStructures/Color.cpp
        src/obj/engine/util/dataStructures/Color.h
        )

target_link_libraries(inputTest -lOpenGL32 -lfreeGLUT -lglu32)

add_executable( cameraMovement
        src/exec/tests/cameraMovement.cpp
        src/obj/engine/window/Window.cpp
        src/obj/engine/window/Window.h
        src/obj/engine/util/geom/Vector.cpp
        src/obj/engine/util/geom/Vector.h
        src/obj/engine/util/Size.cpp
        src/obj/engine/util/Size.h
        src/obj/engine/util/geom/Point.cpp
        src/obj/engine/util/geom/Point.h
        src/obj/engine/util/defs/types.h
        src/obj/engine/Engine.cpp
        src/obj/engine/Engine.h
        src/obj/engine/util/event/KeyListener.cpp
        src/obj/engine/util/event/KeyListener.h
        src/obj/engine/util/obj/Transform.cpp
        src/obj/engine/util/obj/Transform.h
        src/obj/engine/util/obj/GameObject.cpp
        src/obj/engine/util/obj/GameObject.h
        src/obj/engine/preCompiledHeaders.h
        src/obj/engine/util/obj/standardObj/Camera.cpp
        src/obj/engine/util/obj/standardObj/Camera.h
        )

target_link_libraries(cameraMovement -lOpenGL32 -lfreeGLUT -lglu32)


add_executable( libTests
        src/obj/engine/util/Size.cpp
        src/obj/engine/util/Size.h
        src/obj/engine/util/geom/Point.cpp
        src/obj/engine/util/geom/Point.h
        src/obj/engine/window/Window.cpp
        src/obj/engine/window/Window.h
        src/obj/engine/util/defs/types.h
        src/obj/engine/Engine.cpp
        src/obj/engine/Engine.h
        src/obj/engine/util/event/KeyListener.cpp
        src/obj/engine/util/event/KeyListener.h
        src/obj/engine/util/geom/Vector.cpp
        src/obj/engine/util/geom/Vector.h
        src/obj/engine/util/obj/Transform.cpp
        src/obj/engine/util/obj/Transform.h
        src/obj/engine/util/obj/GameObject.cpp
        src/obj/engine/util/obj/GameObject.h
        src/obj/engine/util/dataStructures/Array.h
        src/obj/engine/util/dataStructures/Array.cpp
        src/exec/tests/libTest.cpp
        src/obj/engine/preCompiledHeaders.h
        src/exec/tests/objectTests.cpp
        src/exec/tests/UITests.cpp)

target_link_libraries(libTests -lOpenGL32 -lfreeGLUT -lglu32)

add_executable( cameraMovement2
        src/exec/tests/cameraMovementTypeTwo.cpp
        src/obj/engine/window/Window.cpp
        src/obj/engine/window/Window.h
        src/obj/engine/util/geom/Vector.cpp
        src/obj/engine/util/geom/Vector.h
        src/obj/engine/util/Size.cpp
        src/obj/engine/util/Size.h
        src/obj/engine/util/geom/Point.cpp
        src/obj/engine/util/geom/Point.h
        src/obj/engine/util/defs/types.h
        src/obj/engine/Engine.cpp
        src/obj/engine/Engine.h
        src/obj/engine/util/event/KeyListener.cpp
        src/obj/engine/util/event/KeyListener.h
        src/obj/engine/util/obj/Transform.cpp
        src/obj/engine/util/obj/Transform.h
        src/obj/engine/util/obj/GameObject.cpp
        src/obj/engine/util/obj/GameObject.h
        src/obj/engine/preCompiledHeaders.h
        src/obj/engine/util/obj/standardObj/Camera.cpp
        src/obj/engine/util/obj/standardObj/Camera.h
        )

target_link_libraries(cameraMovement2 -lOpenGL32 -lfreeGLUT -lglu32)

add_executable( objectTests
        src/exec/tests/objectTests.cpp
        src/obj/engine/window/Window.cpp
        src/obj/engine/window/Window.h
        src/obj/engine/util/geom/Vector.cpp
        src/obj/engine/util/geom/Vector.h
        src/obj/engine/util/Size.cpp
        src/obj/engine/util/Size.h
        src/obj/engine/util/geom/Point.cpp
        src/obj/engine/util/geom/Point.h
        src/obj/engine/util/defs/types.h
        src/obj/engine/Engine.cpp
        src/obj/engine/Engine.h
        src/obj/engine/util/event/KeyListener.cpp
        src/obj/engine/util/event/KeyListener.h
        src/obj/engine/util/obj/Transform.cpp
        src/obj/engine/util/obj/Transform.h
        src/obj/engine/util/obj/GameObject.cpp
        src/obj/engine/util/obj/GameObject.h
        src/obj/engine/preCompiledHeaders.h
        src/obj/engine/util/obj/standardObj/Camera.cpp
        src/obj/engine/util/obj/standardObj/Camera.h
        src/obj/engine/util/dataStructures/Color.cpp
        src/obj/engine/util/dataStructures/Color.h
        src/obj/engine/util/obj/standardObj/Sphere.cpp
        src/obj/engine/util/obj/standardObj/Sphere.h
        src/obj/engine/util/event/MouseListener.cpp
        src/obj/engine/util/event/MouseListener.h
        src/obj/engine/util/event/InputListener.cpp
        src/obj/engine/util/event/InputListener.h
        )

target_link_libraries(objectTests -lOpenGL32 -lfreeGLUT -lglu32)

add_executable( UITests
        src/exec/tests/UITests.cpp
        src/obj/engine/window/Window.cpp
        src/obj/engine/window/Window.h
        src/obj/engine/util/geom/Vector.cpp
        src/obj/engine/util/geom/Vector.h
        src/obj/engine/util/Size.cpp
        src/obj/engine/util/Size.h
        src/obj/engine/util/geom/Point.cpp
        src/obj/engine/util/geom/Point.h
        src/obj/engine/util/defs/types.h
        src/obj/engine/Engine.cpp
        src/obj/engine/Engine.h
        src/obj/engine/util/event/KeyListener.cpp
        src/obj/engine/util/event/KeyListener.h
        src/obj/engine/util/obj/Transform.cpp
        src/obj/engine/util/obj/Transform.h
        src/obj/engine/util/obj/GameObject.cpp
        src/obj/engine/util/obj/GameObject.h
        src/obj/engine/preCompiledHeaders.h
        src/obj/engine/util/obj/standardObj/Camera.cpp
        src/obj/engine/util/obj/standardObj/Camera.h
        src/obj/engine/util/dataStructures/Color.cpp
        src/obj/engine/util/dataStructures/Color.h
        src/obj/engine/util/obj/standardObj/Sphere.cpp
        src/obj/engine/util/obj/standardObj/Sphere.h
        src/obj/engine/util/event/MouseListener.cpp
        src/obj/engine/util/event/MouseListener.h
        src/obj/engine/util/event/InputListener.cpp
        src/obj/engine/util/event/InputListener.h
        )

target_link_libraries(UITests -lOpenGL32 -lfreeGLUT -lglu32)
