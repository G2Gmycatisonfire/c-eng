//
// Created by vladl on 10/11/2020.
//

#include "VEntityManager.h"

engine::VEntityManager engine::VEntityManager::_instance;

// TODO : implement ffs
engine::VEntityManager::~VEntityManager() noexcept {

}

void engine::VEntityManager::assign(VComponent * pComponent, VEntity * pEntity) noexcept {
    if ( pComponent == nullptr || pEntity == nullptr )
        return;

    VEntityManager::_instance._componentOwners.emplace(
            pComponent->_ID,
            pEntity
    );

    auto ownerIterator = VEntityManager::_instance._entityOwnedComponents.find( pEntity->_ID );
    if ( ownerIterator != VEntityManager::_instance._entityOwnedComponents.end() )
        ownerIterator->second.emplace( reinterpret_cast < VComponent * > ( pComponent ) );
    else
        VEntityManager::_instance._entityOwnedComponents.emplace(
                pEntity->_ID,
                std::set < engine::VComponent *, decltype( engine::VEntityManager::compareVComponent ) > ()
        ).first->second.emplace( reinterpret_cast < VComponent * > ( pComponent ) );
}

void engine::VEntityManager::free( engine::VComponent * pComponent, engine::VEntity * pEntity ) noexcept {
    if ( pComponent == nullptr || pEntity == nullptr )
        return;

    auto ownerIterator = engine::VEntityManager::_instance._componentOwners.find( pComponent->_ID );
    if ( ownerIterator != engine::VEntityManager::_instance._componentOwners.end() )
        engine::VEntityManager::_instance._componentOwners.erase( ownerIterator );

    auto ownedComponents = engine::VEntityManager::_instance._entityOwnedComponents.find( pEntity->_ID );

    ownedComponents->second.erase( pComponent );

//    auto activeComponentIterator = engine::VEntityManager::_instance._activeComponents.
    // TODO : maybe use map for active + inactive components. List does not have find ret iterator
}