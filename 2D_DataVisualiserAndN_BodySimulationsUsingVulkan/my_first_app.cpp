#include "my_first_app.hpp"

#include "simple_render_system.hpp"

// libs
#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

// std
#include <array>
#include <cassert>
#include <stdexcept>

//#include "lve_defines.hpp"
//constexpr float DT = 1.f / 10000;
constexpr float DT = 1.f / 100000;

namespace lve {

    // Note: also would need to add RigidBody2dComponent to game object
    // struct RigidBody2dComponent {
    //   glm::vec2 velocity;
    //   float mass{1.0f};
    // };
///////////////////////////////////////////////////////////////////////
/////////////////////////PHYSICS SYSTEM////////////////////////////////
///////////////////////////////////////////////////////////////////////
    class MyGravityPhysicsSystem {
    public:
        MyGravityPhysicsSystem(float strength) : strengthGravity{ strength } {}

        const float strengthGravity;

        // dt stands for delta time, and specifies the amount of time to advance the simulation
        // substeps is how many intervals to divide the forward time step in. More substeps result in a
        // more stable simulation, but takes longer to compute
        void update(std::vector<LveGameObject>& objs, float dt, unsigned int substeps = 1) {
            const float stepDelta = dt / substeps;
            for (int i = 0; i < substeps; i++) {
                stepSimulation(objs, stepDelta);
            }
        }

        glm::vec2 computeForce(LveGameObject& fromObj, LveGameObject& toObj) const {
            auto offset = fromObj.transform2d.translation - toObj.transform2d.translation;
            float distanceSquared = glm::dot(offset, offset);

            // clown town - just going to return 0 if objects are too close together...
            if (glm::abs(distanceSquared) < 1e-10f) {
                return { .0f, .0f };
            }

            float force =
                strengthGravity * toObj.rigidBody2d.mass * fromObj.rigidBody2d.mass / distanceSquared;
            return force * offset / glm::sqrt(distanceSquared);
        }

    private:
        void stepSimulation(std::vector<LveGameObject>& physicsObjs, float dt) {
            // Loops through all pairs of objects and applies attractive force between them
            for (auto iterA = physicsObjs.begin(); iterA != physicsObjs.end(); ++iterA) {
                auto& objA = *iterA;
                for (auto iterB = iterA; iterB != physicsObjs.end(); ++iterB) {
                    if (iterA == iterB) continue;
                    auto& objB = *iterB;

                    auto force = computeForce(objA, objB);
                    objA.rigidBody2d.velocity += dt * -force / objA.rigidBody2d.mass;
                    objB.rigidBody2d.velocity += dt * force / objB.rigidBody2d.mass;
                }
            }

            // update each objects position based on its final velocity
            for (auto& obj : physicsObjs) {
                obj.transform2d.translation += dt * obj.rigidBody2d.velocity;
            }
        }
    };

    std::unique_ptr<LveModel> myCreateCircleModel(LveDevice& device, unsigned int numSides) {
        std::vector<LveModel::Vertex> uniqueVertices{};
        for (int i = 0; i < numSides; i++) {
            float angle = i * glm::two_pi<float>() / numSides;
            uniqueVertices.push_back({ {glm::cos(angle), glm::sin(angle)} });
        }
        uniqueVertices.push_back({});  // adds center vertex at 0, 0

        std::vector<LveModel::Vertex> vertices{};
        for (int i = 0; i < numSides; i++) {
            vertices.push_back(uniqueVertices[i]);
            vertices.push_back(uniqueVertices[(i + 1) % numSides]);
            vertices.push_back(uniqueVertices[numSides]);
        }
        return std::make_unique<LveModel>(device, vertices);
    }

    MyFirstApp::MyFirstApp() { /*loadGameObjects();*/ }

    MyFirstApp::~MyFirstApp() {}

    LveGameObject createParicle(std::shared_ptr<LveModel> model, 
                                glm::vec2 translation, glm::vec3 color, 
                                glm::vec2 velocity = { 0,0 }, float mass = 1.0f, 
                                glm::vec2 scale = glm::vec2{ .01f }) {
        auto obj= LveGameObject::createGameObject();
        obj.transform2d.scale = scale;
        obj.transform2d.translation = translation;
        obj.color = color;
        obj.rigidBody2d.velocity = velocity;
        obj.rigidBody2d.mass = mass;
        obj.model = model;
        return obj;
    }

    void MyFirstApp::run() {
        // create some models

        std::shared_ptr<LveModel> circleModel = myCreateCircleModel(lveDevice, 64);

        // create physics objects
        std::vector<LveGameObject> physicsObjects{};
        auto red = LveGameObject::createGameObject();
        red.transform2d.scale = glm::vec2{ .05f };
        red.transform2d.translation = { .0f, .45f };
        red.color = { 1.f, 0.f, 0.f };
        red.rigidBody2d.velocity = { -.5f, .0f };
        //red.rigidBody2d.mass = 0.1f;
        red.model = circleModel;
        physicsObjects.push_back(std::move(red));
        auto blue = LveGameObject::createGameObject();
        blue.transform2d.scale = glm::vec2{ .01f };
        blue.transform2d.translation = { -.45f, -.25f };
        blue.color = { 0.f, 0.f, 1.f };
        blue.rigidBody2d.velocity = { .5f, .0f };
        blue.rigidBody2d.mass = 1000.0f;
        blue.model = circleModel;
        physicsObjects.push_back(std::move(blue));
        auto green = LveGameObject::createGameObject();
        green.transform2d.scale = glm::vec2{ .05f };
        green.transform2d.translation = { .45f, -.25f };
        green.color = { 0.f, 1.f, 0.f };
        green.rigidBody2d.velocity = { .5f, .0f };
        //green.rigidBody2d.mass = 0.1f;
        green.model = circleModel;
        physicsObjects.push_back(std::move(green));

        for (auto x = -10; x <= 10; x++) {
            for (auto y = -10; y <= 10; y++) {
                auto newObj = createParicle(circleModel, { x / 50.0, y / 50.0 },
                    { 1.f,1.f,1.f }, { 0.f, 0.f }, 0.1);
                physicsObjects.push_back(std::move(newObj));
            }
        }

        MyGravityPhysicsSystem gravitySystem{ 0.81f };

        SimpleRenderSystem simpleRenderSystem{ lveDevice, lveRenderer.getSwapChainRenderPass() };

        while (!lveWindow.shouldClose()) {
            glfwPollEvents();

            if (auto commandBuffer = lveRenderer.beginFrame()) {
                // update systems
                gravitySystem.update(physicsObjects, DT, 5);

                // render system
                lveRenderer.beginSwapChainRenderPass(commandBuffer);
                simpleRenderSystem.renderGameObjects(commandBuffer, physicsObjects);
                lveRenderer.endSwapChainRenderPass(commandBuffer);
                lveRenderer.endFrame();
            }
        }

        vkDeviceWaitIdle(lveDevice.device());
    }

    //void MyFirstApp::loadGameObjects() {
    //    std::vector<LveModel::Vertex> vertices{
    //        {{0.0f, -0.5f}, {1.0f, 0.0f, 0.0f}},
    //        {{0.5f, 0.5f}, {0.0f, 1.0f, 0.0f}},
    //        {{-0.5f, 0.5f}, {0.0f, 0.0f, 1.0f}} };
    //    auto lveModel = std::make_shared<LveModel>(lveDevice, vertices);

    //    auto triangle = LveGameObject::createGameObject();
    //    triangle.model = lveModel;
    //    triangle.color = { .1f, .8f, .1f };
    //    triangle.transform2d.translation.x = .2f;
    //    triangle.transform2d.scale = { 2.f, .5f };
    //    triangle.transform2d.rotation = .25f * glm::two_pi<float>();

    //    gameObjects.push_back(std::move(triangle));
    //}

}  // namespace lve