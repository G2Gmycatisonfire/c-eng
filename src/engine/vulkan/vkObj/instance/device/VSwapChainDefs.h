//
// Created by Vlad on 16/08/2020.
//

#ifndef ENG1_VSWAPCHAINDEFS_H
#define ENG1_VSWAPCHAINDEFS_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>

#define __VK_FORMAT_8BIT_BGRA_SRGB      VK_FORMAT_B8G8R8A8_SRGB
#define __VK_COLORSPACE_NONLINEAR_SRGB  VK_COLOR_SPACE_SRGB_NONLINEAR_KHR

#define __VK_PRESENT_MODE_NO_VSYNC                      VK_PRESENT_MODE_IMMEDIATE_KHR
#define __VK_PRESENT_MODE_VSYNC_DOUBLE_BUFFER           VK_PRESENT_MODE_FIFO_KHR
#define __VK_PRESENT_MODE_RELAXED_VSYNC_DOUBLE_BUFFER   VK_PRESENT_MODE_FIFO_RELAXED_KHR
#define __VK_PRESENT_MODE_VSYNC_TRIPLE_BUFFER           VK_PRESENT_MODE_MAILBOX_KHR

#endif //ENG1_VSWAPCHAINDEFS_H