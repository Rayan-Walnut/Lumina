#ifndef LAYOUT_H
#define LAYOUT_H

#include <imgui.h>
#include <vulkan/vulkan_core.h>

class Layout {
public:
    Layout(float x, float y, float width, float height)
        : x(x), y(y), width(width), height(height) {}

    virtual void UpdateSize(int fb_width, int fb_height); // Méthode pour mettre à jour la taille
    virtual void Draw(VkDevice vk_device) = 0; // Méthode virtuelle pure pour dessiner le layout
protected:
    float x, y, width, height;
};

#endif // LAYOUT_H