//
// Created by vladl on 10/2/2020.
//

#ifndef ENG1_VTRANSFORM_H
#define ENG1_VTRANSFORM_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <space/VRotor.h>
#include <VComponent.h>

namespace engine {

    class VTransform : public VComponent {
    private:
        //// private variables
        glm::vec3 _location { glm::vec3 (0.0f) };
        VRotor    _rotation { 0.0f, 0.0f, 0.0f };
        glm::vec3 _scale    { glm::vec3 (1.0f) };

        //// private functions

    public:
        //// public variable

        //// public functions
        VTransform () noexcept : VComponent( VComponent::Type::TRANSFORM ) { };

        explicit VTransform ( const glm::vec3 & location, const glm::vec3 & rotation = glm::vec3 ( 0.0f ), const glm::vec3 & scale = glm::vec3 ( 1.0f ) ) noexcept :
            VComponent( VComponent::Type::TRANSFORM ),
            _location(location),
            _rotation(rotation),
            _scale(scale){

        }

        explicit VTransform ( const glm::vec3 & location, engine::VRotor & rotor, const glm::vec3 & scale = glm::vec3 ( 1.0f ) ) noexcept :
            VComponent( VComponent::Type::TRANSFORM ),
            _location(location),
            _rotation(rotor),
            _scale(scale) {

        }

        explicit VTransform ( float locationScalar, float rotationScalar = 0.0f, float scaleScalar = 0.0f ) noexcept :
            VComponent( VComponent::Type::TRANSFORM ),
            _location ( glm::vec3 ( locationScalar ) ),
            _rotation ( glm::vec3 ( rotationScalar ) ),
            _scale ( glm::vec3 ( scaleScalar ) ){

        }

        [[nodiscard]] const glm::vec3 & getLocation () const noexcept {
            return this->_location;
        }

        [[nodiscard]] glm::vec3 & getLocation () noexcept {
            return this->_location;
        }

        [[nodiscard]] const engine::VRotor & getRotation () const noexcept {
            return this->_rotation;
        }

        [[nodiscard]] engine::VRotor & getRotation () noexcept {
            return this->_rotation;
        }

        [[nodiscard]] const glm::vec3 & getScale () const noexcept {
            return this->_scale;
        }

        [[nodiscard]] glm::vec3 & getScale () noexcept {
            return this->_scale;
        }

        void setLocation ( const glm::vec3 & location ) noexcept {
            this->_location = location;
        }

        void setRotation ( const glm::vec3 & rotation ) noexcept {
            this->_rotation = rotation;
        }

        void setRotation ( const engine::VRotor & rotation ) noexcept {
            this->_rotation = rotation;
        }

        void setScale ( const glm::vec3 & scale ) noexcept {
            this->_scale = scale;
        }
    };

}


#endif //ENG1_VTRANSFORM_H
