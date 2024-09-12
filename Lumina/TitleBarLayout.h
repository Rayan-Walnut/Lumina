#ifndef TITLEBARLAYOUT_H
#define TITLEBARLAYOUT_H

#include "Layout.h"
#include <imgui.h>
#include <GLFW/glfw3.h>

class TitleBarLayout : public Layout {
public:
    TitleBarLayout(float x, float y, float width, float height, const char* title, GLFWwindow* windowHandle)
        : Layout(x, y, width, height), title(title), m_WindowHandle(windowHandle),
          backgroundColor(ImVec4{0.1f, 0.1f, 0.1f, 1.0f}), textColor(ImVec4{1.0f, 1.0f, 1.0f, 1.0f}),
          titleBarHeight(32.0f) {}

    void Draw() override;
    void SetBackgroundColor(const ImVec4& color) { backgroundColor = color; }
    void SetTextColor(const ImVec4& color) { textColor = color; }
    void SetTitleBarHeight(float height) { titleBarHeight = height; }
    void AddCloseButton();   // Méthode pour ajouter un bouton "Fermer"
    void AddMinimizeButton(); // Méthode pour ajouter un bouton "Réduire"

private:
    const char* title;
    GLFWwindow* m_WindowHandle;
    ImVec4 backgroundColor;
    ImVec4 textColor;
    float titleBarHeight;

    void SetTitlebarHitTestCallback();
    bool IsTitleBarHovered() const;
    void UpdateSize(int newWidth, int newHeight) override;
};

#endif // TITLEBARLAYOUT_H
