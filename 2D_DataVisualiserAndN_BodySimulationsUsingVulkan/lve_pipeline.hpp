#pragma once

#include "lve_device.hpp"

// std
#include <string>
#include <vector>
#include <stdexcept>

namespace lve {

	struct PipelineConfigInfo {
		PipelineConfigInfo() = default;
		PipelineConfigInfo(const PipelineConfigInfo&) = delete;
		PipelineConfigInfo& operator=(const PipelineConfigInfo&) = delete;

		//the ones commented are out of date
		//std::vector<VkVertexInputBindingDescription> bindingDescriptions{};
		//std::vector<VkVertexInputAttributeDescription> attributeDescriptions{};
		//VkViewport viewport;
		//VkRect2D scissor;
		VkPipelineViewportStateCreateInfo viewportInfo;
		VkPipelineInputAssemblyStateCreateInfo inputAssemblyInfo;
		VkPipelineRasterizationStateCreateInfo rasterizationInfo;
		VkPipelineMultisampleStateCreateInfo multisampleInfo;
		VkPipelineColorBlendAttachmentState colorBlendAttachment;
		VkPipelineColorBlendStateCreateInfo colorBlendInfo;
		VkPipelineDepthStencilStateCreateInfo depthStencilInfo;
		std::vector<VkDynamicState> dynamicStateEnables;
		VkPipelineDynamicStateCreateInfo dynamicStateInfo;
		VkPipelineLayout pipelineLayout = nullptr;
		VkRenderPass renderPass = nullptr;
		uint32_t subpass = 0;
	};

	class LvePipeline {
	public:
		LvePipeline(
				LveDevice &device,
				const std ::string & vertFilePath, 
				const std::string & fragFilePath, 
				const PipelineConfigInfo&  configInfo);
		~LvePipeline();

		//to avoid accicentally duplicate
		LvePipeline(const LvePipeline&) = delete;
		LvePipeline& operator=(const LvePipeline&) = delete;

		//static PipelineConfigInfo defaultPipelineConfigInfo(uint32_t width, uint32_t height);
		
		void bind(VkCommandBuffer commandBuffer);
		static void defaultPipelineConfigInfo(
			PipelineConfigInfo& configInfo);//, uint32_t width, uint32_t height);

	private:
		static std::vector<char> readFile(const std::string& filepath);

		void createGraphicsPipeline(
				const std::string& vertFilePath, 
				const std::string& fragFilePath, 
				const PipelineConfigInfo& configInfo);

		void createShaderModule(const std::vector<char>& code, VkShaderModule* shaderModule);

		LveDevice& lveDevice;
		VkPipeline graphicsPipeline;
		VkShaderModule vertShaderModule;
		VkShaderModule fragShaderModule;
	};
} //namespace lve