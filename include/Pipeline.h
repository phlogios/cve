#pragma once

#include "vulkan/vulkan.h"
#include <vector>

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
			const VkDescriptorSetLayout& descriptorSetLayout,
			const VkRenderPass& renderPass);

		void destroy();

		const VkPipeline& GetVkPipeline() const noexcept;
		const VkPipelineLayout& GetVkPipelineLayout() const noexcept;
	private:
		VkDevice device;
		VkPipelineLayout pipelineLayout;
		VkPipeline graphicsPipeline;
	};
}