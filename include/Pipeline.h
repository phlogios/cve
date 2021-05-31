#pragma once

#include "vulkan/vulkan.h"
#include <vector>

namespace CVE {
	class Pipeline {
	public:
		Pipeline();
		~Pipeline();

		VkDevice device;

		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;

		VkShaderModule createShaderModule(const std::vector<char>& code);
		void createGraphicsPipeline(
			const VkDevice& device,
			const VkViewport& viewport,
			const VkRect2D& scissor,
			VkSampleCountFlagBits msaaSamples,
			const VkDescriptorSetLayout& descriptorSetLayout,
			const VkRenderPass& renderPass);

		void destroy();
	};
}