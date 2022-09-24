#include "first_app.hpp"

#include "simple_render_system.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include "glm/glm.hpp"
#include "glm/gtc/constants.hpp"

// tests 
//#include "sierpinski_triangle.hpp"
//#include <iostream>
//#define CHANGE

//std
#include <stdexcept>
#include <array>
#include <iostream>

#define DEPTH_OF_SIERPINSKI_TRIANGLE 1

namespace lve {

	FirstApp::FirstApp() {
		loadGameObjects();
	}

	FirstApp::~FirstApp() {}

	void FirstApp::run() {
		SimpleRenderSystem simpleRenderSystem{ lveDevice, lveRenderer.getSwapChainRenderPass() };

		std::cout << "maxPushConstantSize = " << lveDevice.properties.limits.maxPushConstantsSize << '\n';

		while (!lveWindow.shouldClose()) {
			glfwPollEvents();

			if (auto commandBuffer = lveRenderer.beginFrame()) {
				lveRenderer.beginSwapChainRenderPass(commandBuffer);
				simpleRenderSystem.renderGameObjects(commandBuffer, gameObjects);
				lveRenderer.endSwapChainRenderPass(commandBuffer);
				lveRenderer.endFrame();
			}
		}

		vkDeviceWaitIdle(lveDevice.device());
	}

	void FirstApp::loadGameObjects() {
#ifdef CHANGE
		std::vector<LveModel::Vertex> vertices{
			{{ 0.25f ,   0.0f}},
			{{-0.25f ,   0.0f}},
			{{ 0.0f    ,   0.25f}},
			/*{{0.0f, -0.5f}},
			{{0.5f, 0.5f}},
			{{-0.5f, 0.5f}},
			{{ 0.0f    ,   1.0f}},
			{{0.5f,  1.0f}}*/
		};
#else // do the standart
		std::vector<LveModel::Vertex> vertices{
			{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
			{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
			{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
			//{{-1,1}}
		};
#endif

		////for (int i = 0; i < DEPTH_OF_SIERPINSKI_TRIANGLE; i++) {}
		//vertices = SierpinskiTriangle::solution(vertices);
		//for (int i = 0; i < vertices.size(); i++) {
		//	std::cout << vertices.at(i).position.x << '\t' << vertices.at(i).position.y << std::endl;
		//}


		auto  lveModel = std::make_shared<LveModel>(lveDevice, vertices);
		auto triangle = LveGameObject::createGameObject();
		triangle.model = lveModel;
		triangle.color = { .1f, .8f, .1f };
		triangle.transform2d.translation.x = .2f; // moves triangle slightly to the right
		triangle.transform2d.scale = { 2.f, .5f };
		triangle.transform2d.rotation = .25f * glm::two_pi<float>();

		gameObjects.push_back(std::move(triangle));
	}

} // namespace lve


//// before renderer 
//
//#include "first_app.hpp"
//
//// libs
//#define GLM_FORCE_RADIANS
//#define GLM_FORCE_DEPTH_ZERO_TO_ONE
//#include "glm/glm.hpp"
//#include "glm/gtc/constants.hpp"
//
//// tests 
////#include "sierpinski_triangle.hpp"
////#include <iostream>
////#define CHANGE
//
////std
//#include <stdexcept>
//#include <array>
//#include <iostream>
//
//#define DEPTH_OF_SIERPINSKI_TRIANGLE 1
//
//namespace lve {
//
//	struct SimplePushConstantData {
//		glm::mat2 transform{1.f};
//		glm::vec2 offset;
//		alignas(16) glm::vec3 color;
//	};
//
//	FirstApp::FirstApp() {
//		loadGameObjects();
//		createPipelineLayout();
//		recreateSwapChain();// now createPipeline(); is in this 
//		createCommandBuffers();
//	}
//
//	FirstApp::~FirstApp() {
//		vkDestroyPipelineLayout(lveDevice.device(), pipelineLayout, nullptr);
//	}
//
//	void FirstApp::run() {
//		std::cout << "maxPushConstantSize = " << lveDevice.properties.limits.maxPushConstantsSize << '\n';
//
//		while (!lveWindow.shouldClose()) {
//			glfwPollEvents();
//			drawFrame();
//		}
//
//		vkDeviceWaitIdle(lveDevice.device());
//	}
//
//	void FirstApp::loadGameObjects() {
//#ifdef CHANGE
//		std::vector<LveModel::Vertex> vertices{
//			{{ 0.25f ,   0.0f}},
//			{{-0.25f ,   0.0f}},
//			{{ 0.0f    ,   0.25f}},
//			/*{{0.0f, -0.5f}},
//			{{0.5f, 0.5f}},
//			{{-0.5f, 0.5f}},
//			{{ 0.0f    ,   1.0f}},
//			{{0.5f,  1.0f}}*/
//		};
//#else // do the standart
//		std::vector<LveModel::Vertex> vertices{
//			{{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
//			{{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
//			{{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}},
//			//{{-1,1}}
//		};
//#endif
//
//		////for (int i = 0; i < DEPTH_OF_SIERPINSKI_TRIANGLE; i++) {}
//		//vertices = SierpinskiTriangle::solution(vertices);
//		//for (int i = 0; i < vertices.size(); i++) {
//		//	std::cout << vertices.at(i).position.x << '\t' << vertices.at(i).position.y << std::endl;
//		//}
//		
//		
//		auto  lveModel = std::make_shared<LveModel>(lveDevice, vertices);
//		auto triangle = LveGameObject::createGameObject();
//		triangle.model = lveModel;
//		triangle.color = { .1f, .8f, .1f }; 
//		triangle.transform2d.translation.x = .2f; // moves triangle slightly to the right
//		triangle.transform2d.scale = { 2.f, .5f };
//		triangle.transform2d.rotation = .25f * glm::two_pi<float>();
//
//		gameObjects.push_back(std::move(triangle));
//	}
//
//	void FirstApp::createPipelineLayout() {
//
//		VkPushConstantRange pushConstantRange{};
//		pushConstantRange.stageFlags = VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT;
//		pushConstantRange.offset = 0; // the offset is used if we are using separate ranges for the vertex and fragment shaders
//		pushConstantRange.size = sizeof(SimplePushConstantData);
//
//		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
//		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
//		pipelineLayoutInfo.setLayoutCount = 0;
//		pipelineLayoutInfo.pSetLayouts = nullptr;
//		pipelineLayoutInfo.pushConstantRangeCount = 1;
//		pipelineLayoutInfo.pPushConstantRanges = &pushConstantRange; 
//	
//		if (vkCreatePipelineLayout(lveDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
//			throw std::runtime_error("failed to create pipeline layout!");
//		}
//	}
//
//	void FirstApp::createPipeline() {
//		assert(lveSwapChain != nullptr && "Cannot create pipeline before swap chain");
//		assert(pipelineLayout != nullptr && "Cannot create pipeline before pipeline layout");
//
//		PipelineConfigInfo pipelineConfig{};
//		LvePipeline::defaultPipelineConfigInfo(pipelineConfig);
//		pipelineConfig.renderPass = lveSwapChain->getRenderPass();
//		pipelineConfig.pipelineLayout = pipelineLayout;
//		lvePipeline = std::make_unique<LvePipeline>(
//			lveDevice,
//			"shaders/simple_shader.vert.spv",
//			"shaders/simple_shader.frag.spv",
//			pipelineConfig);
//	}
//
//	void FirstApp::recreateSwapChain() {
//		auto extent = lveWindow.getExtent();
//		while (extent.width == 0 || extent.height == 0) {
//			extent = lveWindow.getExtent();
//			glfwWaitEvents();
//		}
//		vkDeviceWaitIdle(lveDevice.device()); // wait the current swapchain to recreate the new swap chin
//		
//		if (lveSwapChain == nullptr) {
//			lveSwapChain = std::make_unique<LveSwapChain>(lveDevice, extent);
//		} else {
//			lveSwapChain = std::make_unique<LveSwapChain>(lveDevice, extent, std::move(lveSwapChain));
//			if (lveSwapChain->imageCount() != commandBuffers.size()) {
//				freeCommandBuffers();
//				createCommandBuffers();
//			}
//		}
//		
//		//FUTURE if the render pass is compatible do nothing else 
//		createPipeline();
//	}
//
//	void FirstApp::createCommandBuffers() {
//		commandBuffers.resize(lveSwapChain->imageCount());
//
//		VkCommandBufferAllocateInfo allocInfo{};
//		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
//		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
//		allocInfo.commandPool = lveDevice.getCommandPool();
//		allocInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());
//
//		if (vkAllocateCommandBuffers(lveDevice.device(), &allocInfo, commandBuffers.data()) != VK_SUCCESS) {
//			throw std::runtime_error("failed to allocate command buffers");
//		}
//	}
//
//	void FirstApp::freeCommandBuffers() {
//		vkFreeCommandBuffers(lveDevice.device(),
//			lveDevice.getCommandPool(), 
//			static_cast<uint32_t>(commandBuffers.size()),
//			commandBuffers.data());
//		commandBuffers.clear();
//	}
//
//	void FirstApp::recordCommandBuffer(int imageIndex) {
//		VkCommandBufferBeginInfo beginInfo{};
//		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
//
//		if (vkBeginCommandBuffer(commandBuffers[imageIndex], &beginInfo) != VK_SUCCESS) {
//			throw std::runtime_error("failed to begin recording command buffer");
//		}
//
//		VkRenderPassBeginInfo renderPassInfo{};
//		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
//		renderPassInfo.renderPass = lveSwapChain->getRenderPass();
//		renderPassInfo.framebuffer = lveSwapChain->getFrameBuffer(imageIndex);
//
//		renderPassInfo.renderArea.offset = { 0,0 };
//		renderPassInfo.renderArea.extent = lveSwapChain->getSwapChainExtent();
//
//		std::array<VkClearValue, 2> clearValues{};
//		clearValues[0].color = { 0.01f, 0.01f, 0.01f, 1.0f };
//		clearValues[1].depthStencil = { 1.0f, 0 };
//		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
//		renderPassInfo.pClearValues = clearValues.data();
//
//		vkCmdBeginRenderPass(commandBuffers[imageIndex], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);
//
//		VkViewport viewport{};
//		viewport.x = 0.0f;
//		viewport.y = 0.0f;
//		viewport.width = static_cast<float>(lveSwapChain->getSwapChainExtent().width);
//		viewport.height = static_cast<float>(lveSwapChain->getSwapChainExtent().height);
//		viewport.minDepth = 0.0f;
//		viewport.maxDepth = 1.0f;
//		VkRect2D scissor{ {0, 0}, lveSwapChain->getSwapChainExtent() };
//		vkCmdSetViewport(commandBuffers[imageIndex], 0, 1, &viewport);
//		vkCmdSetScissor(commandBuffers[imageIndex], 0, 1, &scissor);
//
//		renderGameObjects(commandBuffers[imageIndex]);
//
//		vkCmdEndRenderPass(commandBuffers[imageIndex]);
//		if (vkEndCommandBuffer(commandBuffers[imageIndex]) != VK_SUCCESS) {
//			throw std::runtime_error("failed to recored command buffer!");
//		}
//	}
//
//	void FirstApp::renderGameObjects(VkCommandBuffer commandBuffer) {
//		lvePipeline->bind(commandBuffer);
//
//		for (auto& obj : gameObjects){
//			obj.transform2d.rotation = glm::mod(obj.transform2d.rotation + 0.01f, glm::two_pi<float>());
//
//			SimplePushConstantData push{};
//			push.offset = obj.transform2d.translation;
//			push.color = obj.color;
//			push.transform = obj.transform2d.mat2();
//
//			vkCmdPushConstants(
//				commandBuffer,
//				pipelineLayout,
//				VK_SHADER_STAGE_VERTEX_BIT | VK_SHADER_STAGE_FRAGMENT_BIT,
//				0,
//				sizeof(SimplePushConstantData),
//				&push);
//			obj.model->bind(commandBuffer);
//			obj.model->draw(commandBuffer);
//		}
//	}
//	
//	void FirstApp::drawFrame(){
//		uint32_t imageIndex;
//		auto result = lveSwapChain->acquireNextImage(&imageIndex);
//
//		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
//			recreateSwapChain();
//			return;
//		}
//
//		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
//			throw std::runtime_error("failed to aquire swap chain image!");
//		}
//
//		recordCommandBuffer(imageIndex);
//		result = lveSwapChain->submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
//		if (result == VK_ERROR_OUT_OF_DATE_KHR
//			|| result == VK_SUBOPTIMAL_KHR || lveWindow.wasWindowResized()) {
//			lveWindow.resetWindowResizedFlag(); 
//			recreateSwapChain();
//			return;
//		}
//
//		if (result != VK_SUCCESS) {
//			throw std::runtime_error("failed to present swap chain image!");
//		}
//	}
//} // namespace lve