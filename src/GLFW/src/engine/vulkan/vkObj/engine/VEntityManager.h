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
#include <set>

namespace engine {

    class VEntityManager {
    private:
        //// private variables

        constexpr static auto compareVComponent = []( const engine::VComponent * pObj1, const engine::VComponent * pObj2 ) constexpr noexcept -> bool { return pObj1->_ID < pObj2->_ID; };
        std::map        < VEntity::VEntityID, std::set < engine::VComponent *, decltype( engine::VEntityManager::compareVComponent ) > > _entityOwnedComponents;
        std::map        < VComponent::VComponentID, VEntity * > _componentOwners;

        std::list < VComponent * > _activeComponents;
        std::list < VComponent * > _inactiveComponents;

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
        [[nodiscard]] static T * getNewComponent ( const VEntity * = nullptr ) noexcept;

        static void assign ( VComponent *, VEntity * ) noexcept;
        static void free ( VComponent *, VEntity * ) noexcept;
        static void destroy ( VComponent * ) noexcept;

    };

}

template <class T>
[[nodiscard]] T * engine::VEntityManager::getNewComponent (const VEntity * pParentEntity) noexcept {
    if constexpr ( ! std::is_base_of_v < engine::VComponent , T > )
        return nullptr;

    T * pComponent = new T ();

    if ( pParentEntity == nullptr )
        VEntityManager::_instance._inactiveComponents.push_back(pComponent );
    else {
        VEntityManager::_instance._activeComponents.push_back(pComponent );
        VEntityManager::_instance._componentOwners.emplace(
                reinterpret_cast < VComponent * > ( pComponent )->_ID,
                pParentEntity
        );

        auto ownerIterator = VEntityManager::_instance._entityOwnedComponents.find( pParentEntity->_ID );
        if ( ownerIterator != VEntityManager::_instance._entityOwnedComponents.end() )
            ownerIterator->second.emplace( reinterpret_cast < VComponent * > ( pComponent ) );
        else
            VEntityManager::_instance._entityOwnedComponents.emplace(
                pParentEntity->_ID,
                std::set < engine::VComponent *, decltype( engine::VEntityManager::compareVComponent ) > ()
            ).first->second.emplace( reinterpret_cast < VComponent * > ( pComponent ) );
    }

    return pComponent;
}


#endif //ENG1_VENTITYMANAGER_H
