#include "TitleBarLayout.h"

void TitleBarLayout::Draw() {
    ImGui::SetNextWindowPos(ImVec2(x, y));
    ImGui::SetNextWindowSize(ImVec2(width, titleBarHeight));

    // Configure the window style
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, backgroundColor); // Utilise la couleur de fond personnalisée

    ImGui::Begin(title, nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

    ImGui::TextColored(textColor, title);  // Utilise la couleur du texte personnalisée

    // Boutons de contrôle
    AddMinimizeButton();
    AddCloseButton();

    ImGui::End();

    ImGui::PopStyleColor();
    ImGui::PopStyleVar(2);

    // Set the titlebar hit test callback
    SetTitlebarHitTestCallback();
}

void TitleBarLayout::SetTitlebarHitTestCallback() {
    glfwSetWindowUserPointer(m_WindowHandle, this);
    glfwSetWindowSizeLimits(m_WindowHandle, 0, 0, GLFW_DONT_CARE, GLFW_DONT_CARE);

    glfwSetTitlebarHitTestCallback(m_WindowHandle, [](GLFWwindow* window, int x, int y, int* hit) {
        TitleBarLayout* layout = static_cast<TitleBarLayout*>(glfwGetWindowUserPointer(window));
        if (layout) {
            *hit = layout->IsTitleBarHovered() ? GLFW_TRUE : GLFW_FALSE;
        } else {
            *hit = GLFW_FALSE;
        }
    });
}

bool TitleBarLayout::IsTitleBarHovered() const {
    double mouseX, mouseY;
    glfwGetCursorPos(m_WindowHandle, &mouseX, &mouseY);
    return (mouseX >= x && mouseX <= (x + width) && mouseY >= y && mouseY <= (y + titleBarHeight));
}

void TitleBarLayout::UpdateSize(int newWidth, int newHeight) {
    this->width = newWidth;
    this->height = titleBarHeight;  // Utilise la hauteur de la barre de titre personnalisée
}

void TitleBarLayout::AddCloseButton() {
    ImGui::SameLine(ImGui::GetWindowWidth() - 30); // Position du bouton à droite
    if (ImGui::Button("X")) {
        glfwSetWindowShouldClose(m_WindowHandle, GLFW_TRUE);  // Ferme la fenêtre quand on clique sur le bouton "X"
    }
}

void TitleBarLayout::AddMinimizeButton() {
    ImGui::SameLine(ImGui::GetWindowWidth() - 60); // Position du bouton "Réduire"
    if (ImGui::Button("_")) {
        glfwIconifyWindow(m_WindowHandle);  // Réduit la fenêtre
    }
}
