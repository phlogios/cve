#pragma once

#include "vulkan/vulkan.h"
#include <vector>
#include <string>

namespace CVE {
	class Pipeline {
	public:
		Pipeline();
		~Pipeline();

		VkShaderModule createShaderModule(const std::vector<char>& code);
		void createGraphicsPipeline(
			const VkDevice& device,
			const VkViewport& viewport,
			const VkRect2D& scissor,
			VkSampleCountFlagBits msaaSamples,
			const VkRenderPass& renderPass,
			const std::string& name,
			std::vector<VkVertexInputBindingDescription> inputBindings,
			std::vector<VkVertexInputAttributeDescription> inputAttributes);

		void destroy();

		const VkPipeline& GetVkPipeline() const noexcept;
		const VkPipelineLayout& GetVkPipelineLayout() const noexcept;

		const VkDescriptorSetLayout& GetDescriptorSetLayout() const noexcept;

	private:
		VkDevice device;
		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;

		std::vector<VkVertexInputBindingDescription> inputBindings;
		std::vector<VkVertexInputAttributeDescription> inputAttributes;

		VkDescriptorSetLayout descriptorSetLayout;

		void createDescriptorSetLayout();
	};
}