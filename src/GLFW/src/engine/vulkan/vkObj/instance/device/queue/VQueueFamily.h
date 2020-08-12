//
// Created by vladl on 08/08/2020.
//

#ifndef ENG1_VQUEUEFAMILY_H
#define ENG1_VQUEUEFAMILY_H
#include <engineVulkanPreproc.h>
#include <vkDefs/vkDefinitions.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VPhysicalDevice.h>
#include <map>
#include <set>

namespace engine {

    class EngineVQueueFamilyNoQueuesAvailable : public std::exception {
    private:
        std::string _message;
    public:
        EngineVQueueFamilyNoQueuesAvailable() noexcept {
            this->_message = "Could not reserve the requested queue count";
        }

        explicit EngineVQueueFamilyNoQueuesAvailable( uint32 reqQueueCount, uint32 availableQueueCount ) noexcept {
            this->_message = "Could not reserve the requested queue count. Requested : " + std::to_string(reqQueueCount) + ", Available : " + std::to_string(availableQueueCount);
        }

        [[nodiscard]] const char * what() const noexcept override {
            return this->_message.c_str();
        }
    };

    class VQueueFamilyCollection;

    class VQueueFamily {
    private:
        //// private variables
        uint32                                      _familyIndex            {0};
        VulkanQueueFamilyProperties                 _queueFamilyProperties  { };
        VQueueFamilyCollection                    * _parentCollection       { nullptr };

        //// private functions
        [[nodiscard]] constexpr static bool queueFamilyPropertiesTransferBit( const VulkanQueueFamilyProperties& properties ) noexcept {
            return (bool) ( properties.queueFlags & VQueueFamily::TRANSFER_FLAG);
        }

        [[nodiscard]] constexpr static bool queueFamilyPropertiesGraphicsBit( const VulkanQueueFamilyProperties& properties ) noexcept {
            return (bool) ( properties.queueFlags & VQueueFamily::GRAPHICS_FLAG);
        }

        [[nodiscard]] constexpr static bool queueFamilyPropertiesComputeBit( const VulkanQueueFamilyProperties& properties ) noexcept {
            return (bool) ( properties.queueFlags & VQueueFamily::COMPUTE_FLAG);
        }

        [[nodiscard]] constexpr static bool queueFamilyPropertiesProtectedBit( const VulkanQueueFamilyProperties& properties ) noexcept {
            return (bool) ( properties.queueFlags & VQueueFamily::PROTECTED_FLAG);
        }

        [[nodiscard]] constexpr static bool queueFamilyPropertiesSparseBindingBit( const VulkanQueueFamilyProperties& properties ) noexcept {
            return (bool) ( properties.queueFlags & VQueueFamily::SPARSE_BINDING_FLAG);
        }

        [[nodiscard]] constexpr static bool queueFamilyPropertiesCompatibleFlagBits( const VulkanQueueFamilyProperties& properties, VulkanQueueFlags flags ) noexcept {
            return (bool) ( ( properties.queueFlags & flags ) == flags );
        }

    public:
        //// public variables
        constexpr static VulkanQueueFlags GRAPHICS_FLAG       = VK_QUEUE_GRAPHICS_BIT;
        constexpr static VulkanQueueFlags COMPUTE_FLAG        = VK_QUEUE_COMPUTE_BIT;
        constexpr static VulkanQueueFlags TRANSFER_FLAG       = VK_QUEUE_TRANSFER_BIT;
        constexpr static VulkanQueueFlags PROTECTED_FLAG      = VK_QUEUE_PROTECTED_BIT;
        constexpr static VulkanQueueFlags SPARSE_BINDING_FLAG = VK_QUEUE_SPARSE_BINDING_BIT;

        //// public functions
        VQueueFamily() noexcept = default;
        explicit VQueueFamily (VQueueFamilyCollection * parent, const VulkanQueueFamilyProperties & properties, uint32 family) noexcept {
            this->_parentCollection = parent;
            this->_queueFamilyProperties = properties;
            this->_familyIndex = family;
        }

        VQueueFamily(const VQueueFamily& obj) noexcept {
            this->_parentCollection = obj._parentCollection;
            this->_queueFamilyProperties = obj._queueFamilyProperties;
            this->_familyIndex = obj._familyIndex;
        }

        ~VQueueFamily() noexcept = default;

        [[nodiscard]] uint32 reserveQueues          ( uint32 ) const noexcept;
        void                 freeQueues             ( uint32 ) const noexcept;

        [[nodiscard]] uint32 getAvailableQueueIndex ( )        const noexcept;
        void                 freeQueueIndex         ( uint32 ) const noexcept;

        [[nodiscard]] const VPhysicalDevice & getPhysicalDevice () const noexcept;

        [[nodiscard]] uint32 getQueueFamilyIndex ( ) const noexcept {
            return this->_familyIndex;
        }

        [[nodiscard]] uint32 getQueueCount ( ) const noexcept {
            return this->_queueFamilyProperties.queueCount;
        }

        [[nodiscard]] const VulkanQueueFamilyProperties & getQueueFamilyProperties ( ) const noexcept {
            return this->_queueFamilyProperties;
        }

        [[maybe_unused]] [[nodiscard]] constexpr bool queueFamilyTransferCapable() const noexcept {
            return VQueueFamily::queueFamilyPropertiesTransferBit(this->_queueFamilyProperties);
        }

        [[maybe_unused]] [[nodiscard]] constexpr bool queueFamilyGraphicsCapable() const noexcept {
            return VQueueFamily::queueFamilyPropertiesGraphicsBit(this->_queueFamilyProperties);
        }

        [[maybe_unused]] [[nodiscard]] constexpr bool queueFamilyComputeCapable() const noexcept {
            return VQueueFamily::queueFamilyPropertiesComputeBit(this->_queueFamilyProperties);
        }

        [[maybe_unused]] [[nodiscard]] constexpr bool queueFamilyProtectedCapable() const noexcept {
            return VQueueFamily::queueFamilyPropertiesProtectedBit(this->_queueFamilyProperties);
        }

        [[maybe_unused]] [[nodiscard]] constexpr bool queueFamilySparseBindingCapable() const noexcept {
            return VQueueFamily::queueFamilyPropertiesSparseBindingBit(this->_queueFamilyProperties);
        }

        [[nodiscard]] constexpr bool queueFamilyIsCapableOf ( VulkanQueueFlags flags ) const noexcept {
            return VQueueFamily::queueFamilyPropertiesCompatibleFlagBits( this->_queueFamilyProperties, flags );
        }

#ifndef NDEBUG
        void debugPrintQueueFamily ( std::ostream&, const char * = "" ) const noexcept;
        void debugPrintQueueFamilyReservation( std::ostream&, const char* = "" ) const noexcept;
        static void debugPrintQueueFamilyPropertiesStructureQueueFlags ( const VulkanQueueFamilyProperties & ,std::ostream&, const char * = "" ) noexcept;
        static void debugPrintQueueFamilyPropertiesStructure ( const VulkanQueueFamilyProperties &, std::ostream&, const char * = "" ) noexcept;
#endif
    };

    class VQueueFamilyCollection {
    private:
        //// private variables
        const VPhysicalDevice         * _physicalDevice { nullptr };
        std::vector < VQueueFamily >    _queueFamilies;
        std::map < uint32, uint32 >     _reservedQueuesForFamilies;
        std::map < uint32, std::set < uint32 > > _reservedQueueIndicesForFamilies;
        //// private functions
        void unReserveAllQueueFamilies ( ) noexcept (false);
        void queryAvailableQueueFamilies ( ) noexcept (false);
    public:
        //// public variables

        //// public functions
        VQueueFamilyCollection () noexcept = delete;
        explicit VQueueFamilyCollection ( const VPhysicalDevice & physicalDevice ) noexcept (false) {
            this->_physicalDevice = (& physicalDevice);
            this->queryAvailableQueueFamilies();
            this->unReserveAllQueueFamilies();
        }

        [[nodiscard]] uint32 reserveQueues( const VQueueFamily&, uint32 ) noexcept;
        void                 freeQueues(    const VQueueFamily&, uint32 ) noexcept;
        uint32               getAvailableQueueIndex ( const VQueueFamily& ) noexcept;
        void                 freeQueueIndex ( const VQueueFamily& ,uint32 ) noexcept;

        [[nodiscard]] const std::map < uint32, uint32 > & getReservedQueueFamiliesMap () const noexcept {
            return this->_reservedQueuesForFamilies;
        }

        [[nodiscard]] const VPhysicalDevice & getPhysicalDevice ( ) const noexcept {
            return * this->_physicalDevice;
        }

        [[nodiscard]] const std::vector < VQueueFamily > & getQueueFamilies () const noexcept {
            return this->_queueFamilies;
        }

        /// fix:0002 . Have to return *, otherwise duplicates that will destroy logical devices and queues will appear
        [[nodiscard]] std::vector < const VQueueFamily* > getGraphicsCapableQueueFamilies () const noexcept {
            return this->getFlagsCapableQueueFamilies( VQueueFamily::GRAPHICS_FLAG );
        }

        [[nodiscard]] std::vector < const VQueueFamily* > getComputeCapableQueueFamilies () const noexcept {
            return this->getFlagsCapableQueueFamilies( VQueueFamily::COMPUTE_FLAG );
        }

        [[nodiscard]] std::vector < const VQueueFamily* > getTransferCapableQueueFamilies () const noexcept {
            return this->getFlagsCapableQueueFamilies( VQueueFamily::TRANSFER_FLAG );
        }

        [[nodiscard]] std::vector < const VQueueFamily* > getProtectedCapableQueueFamilies () const noexcept {
            return this->getFlagsCapableQueueFamilies( VQueueFamily::PROTECTED_FLAG );
        }

        [[nodiscard]] std::vector < const VQueueFamily* > getSparseBindingCapableQueueFamilies () const noexcept {
            return this->getFlagsCapableQueueFamilies( VQueueFamily::SPARSE_BINDING_FLAG );
        }

        [[nodiscard]] std::vector < const VQueueFamily* > getFlagsCapableQueueFamilies ( VulkanQueueFlags ) const noexcept;

#ifndef NDEBUG
        void debugPrintQueueFamilies ( std::ostream&, const char* = "" ) const noexcept;
        void debugPrintQueueFamiliesReservations ( std::ostream&, const char * = "" ) const noexcept;
#endif
    };

}


#endif //ENG1_VQUEUEFAMILY_H
