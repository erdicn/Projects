#pragma once

#include "lve_window.hpp"
#include "lve_device.hpp"
#include "lve_game_object.hpp"
#include "lve_renderer.hpp"



//std
#include <memory>
#include <vector>

constexpr int DOMAIN_WIDTH = 1800;
constexpr int DOMAIN_HEIGHT = 1000;

namespace lve {
	class MyFirstApp {
	public:
		static constexpr bool RIGHT_SIZE = (DOMAIN_HEIGHT <= 1000 && DOMAIN_WIDTH <= 1800);
		static constexpr int WIDTH  = (RIGHT_SIZE) ? DOMAIN_HEIGHT : DOMAIN_WIDTH / 10;
		static constexpr int HEIGHT = (RIGHT_SIZE) ? DOMAIN_HEIGHT : DOMAIN_WIDTH / 10;

		MyFirstApp();
		~MyFirstApp();

		MyFirstApp(const MyFirstApp&) = delete;
		MyFirstApp& operator=(const MyFirstApp&) = delete;

		void run();

	private:
		//void loadGameObjects();

		LveWindow lveWindow{ WIDTH, HEIGHT, "Hello Vulkan!" };
		LveDevice lveDevice{ lveWindow };
		LveRenderer lveRenderer{ lveWindow, lveDevice };

		std::vector<LveGameObject> gameObjects;
	};
}	//namespace lve