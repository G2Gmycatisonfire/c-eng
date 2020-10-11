//
// Created by vladl on 10/11/2020.
//

#ifndef ENG1_VENTITY_H
#define ENG1_VENTITY_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <VComponent.h>
#include <map>

namespace engine {

    class VEntity {
        friend class VEntityManager;
    private:
        typedef uint32 VEntityID;

        //// private variables
        std::map < VComponent::Type, VComponent * > _components;
        VEntity::VEntityID                          _ID                 { VEntity::_internalIDCounter++ }; // NOLINT(bugprone-reserved-identifier)

        static VEntity::VEntityID                   _internalIDCounter;
        constexpr static VEntity::VEntityID         _entityIDStart = 1U;

        //// private functions

    public:
        //// public variables

        //// public functions

    };

}


#endif //ENG1_VENTITY_H
