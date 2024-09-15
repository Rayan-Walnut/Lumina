#ifndef TITLEBAR_H
#define TITLEBAR_H

#include "Layout.h"
#include <imgui.h>
#include <GLFW/glfw3.h>
#include <vulkan/vulkan_core.h>

class TitleBar : public Layout {

public:
    TitleBar(float x, float y, float width, float height, const char* title, GLFWwindow* windowHandle)
      : Layout(x, y, width, height),
        title(title),
        m_WindowHandle(windowHandle),
        backgroundColor(ImVec4{0.1f, 0.1f, 0.1f, 0.2f}),
        textColor(ImVec4{1.0f, 1.0f, 1.0f, 1.0f}),
        titleBarHeight(44.0f)
    {}

    void SetBackgroundColor(const ImVec4& color) { backgroundColor = color; }
    void SetTextColor(const ImVec4& color) { textColor = color; }
    void SetTitleBarHeight(float height) { titleBarHeight = height; }
    void UpdateSize(int newWidth, int newHeight) override;

    // Méthodes pour ajouter les boutons avec une largeur spécifiée
    void AddCloseButton(float buttonWidth, VkDevice device);
    void AddMinimizeButton(float buttonWidth);
    void AddMaximizeButton(float buttonWidth);

    static void InitializeVulkanResources(VkDevice device, VkPhysicalDevice physicalDevice, VkCommandPool commandPool, VkQueue queue, VkAllocationCallbacks* allocator);

    // Ressources Vulkan non-statiques
    VkPhysicalDevice physicalDevice;
    VkCommandPool commandPool;
    VkQueue queue;
    VkAllocationCallbacks* allocator;

private:
    const char* title;
    GLFWwindow* m_WindowHandle;
    ImVec4 backgroundColor;
    ImVec4 textColor;
    float titleBarHeight;

    void Draw(VkDevice device);

    void SetTitlebarHitTestCallback();
    bool IsTitleBarHovered() const;
};

#endif // TITLEBARLAYOUT_H