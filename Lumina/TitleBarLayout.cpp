#include "TitleBarLayout.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION

void TitleBar::Draw(VkDevice device) {
    ImGui::SetNextWindowPos(ImVec2(x, y));
    ImGui::SetNextWindowSize(ImVec2(width, titleBarHeight));

    // Configure the window style
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);  // Coins légèrement arrondis
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.15f, 0.15f, 0.20f, 1.0f)); // Couleur sombre professionnelle pour la barre de titre

    ImGui::Begin(title, nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar );

    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));  // Texte blanc

    {
        // Calcul de la taille du texte
        ImVec2 textSize = ImGui::CalcTextSize(title);

        // Calcul de l'espace disponible horizontalement et verticalement
        float availableWidth = ImGui::GetWindowWidth() - textSize.x;
        float availableHeight = titleBarHeight - textSize.y;

        // Calcul de la position pour centrer le texte horizontalement et verticalement
        float textPosX = availableWidth * 0.5f;
        float textPosY = availableHeight * 0.5f;

        // Applique la position du texte pour le centrer
        ImGui::SetCursorPos(ImVec2(textPosX, textPosY));
        ImGui::Text("%s", title); // Dessine le titre
    }

    ImGui::PopStyleColor();

    // Boutons de contrôle avec style moderne
    float buttonWidth = 44.0f;  // Largeur des boutons
    ImGui::SameLine(ImGui::GetWindowWidth() - (3 * buttonWidth));  // Position des boutons de contrôle à droite

    AddMinimizeButton(buttonWidth);
    AddMaximizeButton(buttonWidth);
    AddCloseButton(buttonWidth, device);

    ImGui::End();

    ImGui::PopStyleColor();
    ImGui::PopStyleVar(2);

    // Set the titlebar hit test callback
    SetTitlebarHitTestCallback();
}

void TitleBar::SetTitlebarHitTestCallback() {
    glfwSetWindowUserPointer(m_WindowHandle, this);
    glfwSetWindowSizeLimits(m_WindowHandle, 0, 0, GLFW_DONT_CARE, GLFW_DONT_CARE);

    glfwSetTitlebarHitTestCallback(m_WindowHandle, [](GLFWwindow* window, int x, int y, int* hit) {
        TitleBar* layout = static_cast<TitleBar*>(glfwGetWindowUserPointer(window));
        if (layout) {
            *hit = layout->IsTitleBarHovered() ? GLFW_TRUE : GLFW_FALSE;
        } else {
            *hit = GLFW_FALSE;
        }
    });
}

bool TitleBar::IsTitleBarHovered() const {
    double mouseX, mouseY;
    glfwGetCursorPos(m_WindowHandle, &mouseX, &mouseY);
    return (mouseX >= x && mouseX <= (x + width) && mouseY >= y && mouseY <= (y + titleBarHeight));
}

void TitleBar::UpdateSize(int newWidth, int newHeight) {
    this->width = newWidth;
    this->height = titleBarHeight;
}


void TitleBar::AddCloseButton(float buttonWidth, VkDevice device) {
    ImGui::SetCursorPosX(ImGui::GetWindowWidth() - buttonWidth);
    ImGui::SetCursorPosY(0.0f);

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f)); // Transparent background
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 1.0f, 1.0f, 0.05f)); // White with some opacity on hover
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 1.0f, 1.0f, 0.3f)); // White with more opacity on click
    if (ImGui::Button("°", ImVec2(buttonWidth, titleBarHeight))) {  // Taille des boutons remplissant la hauteur de la barre de titre
        glfwIconifyWindow(m_WindowHandle);  // Réduit la fenêtre
    }

    // Create a close button with the texture
    ImGui::PopStyleColor(3);
}

void TitleBar::AddMinimizeButton(float buttonWidth) {
    ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 2 * buttonWidth);
    ImGui::SetCursorPosY(0.0f);

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));  // Pas de couleur de fond
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 1.0f, 1.0f, 0.05f));  // Blanc avec peu d'opacité pour le survol
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 1.0f, 1.0f, 0.3f));  // Blanc avec un peu plus d'opacité pour l'action

    if (ImGui::Button("_", ImVec2(buttonWidth, titleBarHeight))) {  // Taille des boutons remplissant la hauteur de la barre de titre
        glfwIconifyWindow(m_WindowHandle);  // Réduit la fenêtre
    }

    ImGui::PopStyleColor(3);
}

void TitleBar::AddMaximizeButton(float buttonWidth) {
    ImGui::SetCursorPosX(ImGui::GetWindowWidth() - 3 * buttonWidth);
    ImGui::SetCursorPosY(0.0f);

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));  // Pas de couleur de fond
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.0f, 1.0f, 1.0f, 0.05f));  // Blanc avec peu d'opacité pour le survol
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4(1.0f, 1.0f, 1.0f, 0.3f));  // Blanc avec un peu plus d'opacité pour l'action

    if (ImGui::Button("□", ImVec2(buttonWidth, titleBarHeight))) {  // Taille des boutons remplissant la hauteur de la barre de titre
        // Code pour basculer entre maximiser et restaurer
    }

    ImGui::PopStyleColor(3);
}