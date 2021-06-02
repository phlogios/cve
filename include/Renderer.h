#pragma once

#include "CVEConfig.h"

#include "Pipeline.h"

#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#define GLM_FORCE_RADIANS
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


#include <iostream>
#include <string>
#include <string_view>
#include <stdexcept>
#include <cstdlib>
#include <vector>
#include <optional>
#include <algorithm>
#include <set>
#include <fstream>
#include <array>
#include <chrono>
#include <unordered_map>

#include "Vertex.h"


//#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

const std::string MODEL_PATH = "resources/models/viking_room.obj";
const std::string TEXTURE_PATH = "resources/textures/viking_room.png";

struct UniformBufferObject {
    glm::mat4 model;
    glm::mat4 view;
    glm::mat4 proj;
};

const std::vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};

const std::vector<const char*> deviceExtensions = {
    VK_KHR_SWAPCHAIN_EXTENSION_NAME
};

const int MAX_FRAMES_IN_FLIGHT = 2;

#ifdef NDEBUG
const bool enableValidationLayers = false;
#else
const bool enableValidationLayers = true;
#endif

VkResult CreateDebugUtilsMessengerEXT(
    VkInstance instance,
    const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
    const VkAllocationCallbacks* pAllocator,
    VkDebugUtilsMessengerEXT* pDebugMessenger);

void DestroyDebugUtilsMessengerEXT(
    VkInstance instance,
    VkDebugUtilsMessengerEXT debugMessenger,
    const VkAllocationCallbacks* pAllocator);

namespace CVE {
    class Renderer {
    public:
        Renderer();
        ~Renderer();
        void run() {
            mainLoop();
            cleanup();
        }

        void init(uint32_t width, uint32_t height) {
            initWindow(width, height);
            initVulkan();
            initImgui();
        }

    private:
        VkInstance instance;
        VkDebugUtilsMessengerEXT debugMessenger;
        VkSurfaceKHR surface;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;
        VkDevice device;
        VkQueue graphicsQueue;
        VkQueue presentQueue;
        VkSwapchainKHR swapChain;
        std::vector<VkImage> swapChainImages;
        VkFormat swapChainImageFormat;
        VkExtent2D swapChainExtent;
        std::vector<VkImageView> swapChainImageViews;
        VkRenderPass renderPass;
        VkRenderPass renderPassGui;
        VkDescriptorSetLayout descriptorSetLayout;

        Pipeline pipeline;

        std::vector<VkFramebuffer> swapChainFramebuffers;
        std::vector<VkFramebuffer> framebuffersGUI;
        VkCommandPool commandPool;
        std::vector<VkCommandBuffer> commandBuffers;
        VkCommandPool commandPoolGUI;
        std::vector<VkCommandBuffer> commandBuffersForGUI;
        std::vector<VkSemaphore> imageAvailableSemaphores; // one for each concurrent frame
        std::vector<VkSemaphore> renderFinishedSemaphores;
        std::vector<VkFence> inFlightFences;
        std::vector<VkFence> imagesInFlight;
        size_t currentFrame = 0;
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        VkBuffer vertexBuffer;
        VkDeviceMemory vertexBufferMemory;
        VkBuffer indexBuffer;
        VkDeviceMemory indexBufferMemory;

        std::vector<VkBuffer> uniformBuffers;
        std::vector<VkDeviceMemory> uniformBuffersMemory;

        VkDescriptorPool descriptorPool;
        std::vector<VkDescriptorSet> descriptorSets;

        VkDescriptorPool descriptorPoolGUI;

        uint32_t mipLevels;
        VkImage textureImage;
        VkDeviceMemory textureImageMemory;
        VkImageView textureImageView;
        VkSampler textureSampler;

        VkImage depthImage;
        VkDeviceMemory depthImageMemory;
        VkImageView depthImageView;

        VkSampleCountFlagBits msaaSamples;
        VkImage colorImage;
        VkDeviceMemory colorImageMemory;
        VkImageView colorImageView;

        VkViewport viewport;
        VkRect2D scissor;

        bool framebufferResized = false;

        GLFWwindow* window;

        void initWindow(uint32_t width, uint32_t height);
        static void framebufferResizeCallback(GLFWwindow* window, int width, int height);
        void initVulkan();
        void initImgui();
        VkSampleCountFlagBits getMaxUsableSampleCount();
        void loadModel();
        VkFormat findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features);
        VkFormat findDepthFormat();
        bool hasStencilComponent(VkFormat format);
        void createDepthResources();
        void createColorResources();
        void createTextureSampler();
        VkImageView createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, uint32_t mipLevels);
        void createTextureImageView();
        void generateMipmaps(VkImage image, VkFormat imageFormat, int32_t texWidth, int32_t texHeight, uint32_t mipLevels);
        void createTextureImage();
        void createImage(uint32_t width, uint32_t height, uint32_t mipLevels, VkSampleCountFlagBits numSamples, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage& image, VkDeviceMemory& imageMemory);
        void transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout, uint32_t mipLevels);
        void copyBufferToImage(VkBuffer buffer, VkImage image, uint32_t width, uint32_t height);
        void createSyncObjects();
        void createCommandPool(VkCommandPool* _commandPool, VkCommandPoolCreateFlags flags = 0);
        void createCommandBuffers(VkCommandBuffer* commandBuffer, uint32_t commandBufferCount, VkCommandPool& commandPool);
        void recordCommandBuffersForModel();
        uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
        void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
        void createVertexBuffer();
        void createIndexBuffer();
        void createUniformBuffers();
        VkCommandBuffer beginSingleTimeCommands();
        void endSingleTimeCommands(VkCommandBuffer commandBuffer);
        void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
        void createDescriptorPool();
        void createDescriptorSets();
        void createFramebuffers();
        void createRenderPass();
        void createDescriptorSetLayout();
        
        VkShaderModule createShaderModule(const std::vector<char>& code);
        void createImageViews();
        void createSurface();
        void createLogicalDevice();
        void pickPhysicalDevice();
        bool isDeviceSuitable(VkPhysicalDevice device);
        VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
        VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
        VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
        void createSwapChain();

        struct SwapChainSupportDetails {
            VkSurfaceCapabilitiesKHR capabilities;
            std::vector<VkSurfaceFormatKHR> formats;
            std::vector<VkPresentModeKHR> presentModes;
        };
        
        SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

        struct QueueFamilyIndices {
            std::optional<uint32_t> graphicsFamily;
            std::optional<uint32_t> presentFamily;

            bool isComplete() {
                return graphicsFamily.has_value() && presentFamily.has_value();
            }
        };

        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        bool checkDeviceExtensionSupport(VkPhysicalDevice device);
        void createInstance();
        void setupDebugMessenger();
        void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo);
        void mainLoop();
        void drawFrame();
        void drawGUI(uint32_t imageIndex);
        void updateUniformBuffer(uint32_t imageIndex);
        void recreateSwapChain();
        void cleanupSwapChain();
        void cleanup();
        bool checkValidationLayerSupport();
        std::vector<const char*> getRequiredExtensions();
        std::vector<VkExtensionProperties> getAvailableExtensions();
    };
}