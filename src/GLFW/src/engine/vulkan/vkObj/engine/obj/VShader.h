//
// Created by vladl on 10/9/2020.
//

#ifndef ENG1_VSHADER_H
#define ENG1_VSHADER_H

#include <engineVulkanPreproc.h>
#include <vkDefs/types/vulkanExplicitTypes.h>
#include <vkObj/instance/device/VLogicalDevice.h>
#include <vkObj/instance/pipeline/VPipeline.h>
#include <vkObj/instance/pipeline/shader/VShaderModule.h>
#include <vkObj/instance/pipeline/shader/VShaderCompiler.h>
#include <VComponent.h>

namespace engine {

    class VShader : public VComponent {
    private:
        //// private variables
        const VLogicalDevice                              * _pLogicalDevice         {nullptr};
        VPipeline                                           _pipeline;

        VShaderModule                                       _vertexShader;
        VShaderModule                                       _fragmentShader;

        std::vector < VulkanPipelineShaderStageCreateInfo > _shaderStages;
        VulkanDescriptorSetLayout                           _descriptorSetLayout    {VK_NULL_HANDLE};

        std::vector < VulkanDescriptorSetLayoutBinding >    _descriptorSetLayoutBindings;

        //// private functions

    public:
        //// public variables

        //// public functions
        VShader() noexcept : VComponent( VComponent::Type::SHADER ) { }

        [[nodiscard]] const VPipeline & getPipeline () const noexcept {
            return this->_pipeline;
        }

        [[nodiscard]] VPipeline & getPipeline () noexcept {
            return this->_pipeline;
        }

        [[nodiscard]] const VShaderModule & getVertexShaderModule () const noexcept {
            return this->_vertexShader;
        }

        [[nodiscard]] VShaderModule & getVertexShaderModule () noexcept {
            return this->_vertexShader;
        }

        [[nodiscard]] const VShaderModule & getFragmentShaderModule () const noexcept {
            return this->_fragmentShader;
        }

        [[nodiscard]] VShaderModule & getFragmentShaderModule () noexcept {
            return this->_fragmentShader;
        }

        [[nodiscard]] const VRenderPass * getRenderPassPtr () const noexcept {
            return this->_pipeline.getRenderPassPtr();
        }

        [[nodiscard]] const VulkanDescriptorSetLayout & getDescriptorSetLayout () const noexcept {
            return this->_descriptorSetLayout;
        }

        [[nodiscard]] VulkanDescriptorSetLayout & getDescriptorSetLayout () noexcept {
            return this->_descriptorSetLayout;
        }

        [[nodiscard]] const std::vector < VulkanDescriptorSetLayoutBinding > & getDescriptorSetLayoutBindings () const noexcept {
            return this->_descriptorSetLayoutBindings;
        }

        [[nodiscard]] std::vector < VulkanDescriptorSetLayoutBinding > & getDescriptorSetLayoutBindings () noexcept {
            return this->_descriptorSetLayoutBindings;
        }

        [[nodiscard]] std::vector < VulkanDescriptorType > getDescriptorTypeLayout () const noexcept {
            std::vector < VulkanDescriptorType > descriptorTypes;

            for ( const auto & binding : this->_descriptorSetLayoutBindings ) {
                descriptorTypes.push_back( binding.descriptorType );
            }

            return descriptorTypes;
        }

        VulkanResult setup (
            const VLogicalDevice &,
            const VShaderCompiler &,
            const std::string &
        ) noexcept;

        VulkanResult recreateShader () noexcept;

        void cleanup() noexcept;

    };

}


#endif //ENG1_VSHADER_H
