//
// Created by vladl on 07/08/2020.
//

#ifndef ENG1_VSTDUTILS_H
#define ENG1_VSTDUTILS_H
#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <string>

namespace engine {

    class VStandardUtils {
    private:
        //// private variables

        //// private functions

    public:
        //// public variables

        //// public functions
        VStandardUtils() = delete;

        static std::string to_string ( VulkanResult ) noexcept;
    };

}


#endif //ENG1_VSTDUTILS_H
