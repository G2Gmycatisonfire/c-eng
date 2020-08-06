//
// Created by vladl on 05/08/2020.
//

#ifndef ENG1_VKDEFINITIONS_H
#define ENG1_VKDEFINITIONS_H

#define VULKAN_LAYERS_NONE 0

#define __VULKAN_LAYER_NVIDIA_OPTIMUS             "VK_LAYER_NV_optimus"
#define __VULKAN_LAYER_OBS_HOOK                   "VK_LAYER_OBS_HOOK"
#define __VULKAN_LAYER_GOG_GALAXY_OVERLAY         "GalaxyOverlayVkLayer"
#define __VULKAN_LAYER_GOG_GALAXY_OVERLAY_VERBOSE "GalaxyOverlayVkLayer_VERBOSE"
#define __VULKAN_LAYER_GOG_GALAXY_OVERLAY_DEBUG   "GalaxyOverlayVkLayer_DEBUG"
#define __VULKAN_LAYER_VALVE_STEAM_OVERLAY        "VK_LAYER_VALVE_steam_overlay"
#define __VULKAN_LAYER_VALVE_STEAM_PIPELINE       "VK_LAYER_VALVE_steam_fossilize"
#define __VULKAN_LAYER_EPIC_ONLINE_SERVICES       "VK_LAYER_EOS_Overlay"
#define __VULKAN_LAYER_ROCKSTAR_GAMES_SOCIAL_CLUB "VK_LAYER_ROCKSTAR_GAMES_social_club"
#define __VULKAN_LAYER_LUNARG_API_DUMP            "VK_LAYER_LUNARG_api_dump"
#define __VULKAN_LAYER_DEVICE_SIMULATION          "VK_LAYER_LUNARG_device_simulation"
#define __VULKAN_LAYER_GFX_RECONSTRUCT_CAPTURE    "VK_LAYER_LUNARG_gfxreconstruct"
#define __VULKAN_LAYER_KHRONOS_GROUP_VALIDATION   "VK_LAYER_KHRONOS_validation"
#define __VULKAN_LAYER_LUNARG_EXECUTION_MONITOR   "VK_LAYER_LUNARG_monitor"
#define __VULKAN_LAYER_LUNARG_IMAGE_CAPTURE       "VK_LAYER_LUNARG_screenshot"
#define __VULKAN_LAYER_LUNARG_STANDARD_VALIDATION "VK_LAYER_LUNARG_standard_validation"

#define __VULKAN_LAYER_UNDEFINED                  "__UNDEFINED__VK__LAYER__"

#define VULKAN_API_ATTRIBUTE                      VKAPI_ATTR
#define VULKAN_API_CALL                           VKAPI_CALL

#define VULKAN_TRUE                               VK_TRUE
#define VULKAN_FALSE                              VK_FALSE

#define __VULKAN_INSTANCE_PROC_ADDRESS_CREATE_DEBUG_UTIL_MESSENGER_EXT    "vkCreateDebugUtilsMessengerEXT"
#define __VULKAN_INSTANCE_PROC_ADDRESS_DESTROY_DEBUG_UTIL_MESSENGER_EXT   "vkDestroyDebugUtilsMessengerEXT"

#define __VULKAN_INSTANCE_DEFAULT_TITLE                                   "Vulkan Application"

#define __VULKAN_INSTANCE_APP_INFO_ENGINE_NO_ENGINE                       "No Engine"

#endif //ENG1_VKDEFINITIONS_H
