//
// Created by vladl on 10/11/2020.
//

#ifndef ENG1_VENTITYMANAGER_H
#define ENG1_VENTITYMANAGER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <VEntity.h>
#include <map>
#include <list>
#include <type_traits>

namespace engine {

    class VEntityManager {
    private:
        //// private variables
        std::list < VComponent * > _activeComponents;
        std::list < VComponent * > _inactiveComponents;

        std::map  < VEntity::VEntityID, VComponent * > _entityOwnedComponents;
        std::map  < VComponent::VComponentID, VEntity * > _componentOwners;

        static VEntityManager _instance;

        //// private functions
        VEntityManager () noexcept = default;
        ~VEntityManager() noexcept;

    public:
        //// public variables

        //// public functions
//        [[nodiscard]] static VEntityManager & getInstance() { return VEntityManager::_instance; }

//        void clearActiveComponents() noexcept;
//        void clearInactiveComponents() noexcept;

        static void clearActiveComponents ( ) noexcept;
        static void clearInactiveComponents ( ) noexcept;

        template <class T>
        [[nodiscard]] static T * getComponent ( const VEntity * = nullptr ) noexcept;

        static void assign ( const VComponent *, const VEntity * ) noexcept;

    };

}

template <class T>
[[nodiscard]] T * engine::VEntityManager::getComponent (const VEntity * pParentEntity) noexcept {
    if constexpr ( ! std::is_base_of_v < engine::VComponent , T > )
        return nullptr;

    T * component = new T ();

    if ( pParentEntity == nullptr )
        VEntityManager::_instance._inactiveComponents.push_back( component );
    else {
        VEntityManager::_instance._activeComponents.push_back( component );
        VEntityManager::_instance._componentOwners.emplace(
                dynamic_cast < VComponent * > ( component )->_ID,
                pParentEntity
        );
        VEntityManager::_instance._entityOwnedComponents.emplace(
                pParentEntity->_ID,
                reinterpret_cast < VComponent * > ( component )
        );
    }

    return component;
}


#endif //ENG1_VENTITYMANAGER_H
