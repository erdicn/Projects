//#define TWO_BODY_GRAVITY
#define MY_FIRST_APP


#ifdef MY_FIRST_APP 

	#include "my_first_app.hpp"

	// std
	#include <cstdlib>
	#include <iostream>
	#include <stdexcept>

	int main() {
		lve::MyFirstApp app{};

		try {
			app.run();
		}
		catch (const std::exception& e) {
			std::cerr << e.what() << '\n';
			return EXIT_FAILURE;
		}
		return EXIT_SUCCESS;
	}

#else
	#ifdef TWO_BODY_GRAVITY

		#include "gravity_vec_field_app.hpp"

		// std
		#include <cstdlib>
		#include <iostream>
		#include <stdexcept>

		int main() {
			lve::GravityVecFieldApp app{};

			try {
				app.run();
			}
			catch (const std::exception& e) {
				std::cerr << e.what() << '\n';
				return EXIT_FAILURE;
			}
			return EXIT_SUCCESS;	
		}

	#else
		#include "first_app.hpp"

		// std
		#include <cstdlib>
		#include <iostream>
		#include <stdexcept>

		int main() {
			lve::FirstApp app{};

			try {
				app.run();
			} catch (const std::exception &e) {
				std::cerr << e.what() << '\n';
				return EXIT_FAILURE;
			}
			return EXIT_SUCCESS;
		}

	#endif // TWO_BODY_GRAVITY
#endif // MY_FIRST_APP


//to test vulkan

/*#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define FLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <iostream>

int main() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	GLFWwindow* window = glfwCreateWindow(800, 600, "Vulkan window", nullptr, nullptr);

	uint32_t extensionCount = 0;
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);

	std::cout << extensionCount << " extensions supported\n";

	glm::mat4 matrix;
	glm::vec4 vec;
	auto test = matrix * vec;

	while (!glfwWindowShouldClose(window)) {
		glfwPollEvents();
	}

	glfwDestroyWindow(window);

	glfwTerminate();

	return 0;
}
*/