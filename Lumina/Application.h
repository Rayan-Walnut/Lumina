#ifndef APPLICATION_H
#define APPLICATION_H
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>
#include "TitleBarLayout.h"
#include <vector>

class Application {
public:
    // Constructeurs
    Application(int largeur, int hauteur);
    Application() : Application(1600, 900) {}  // Constructeur par défaut

    // Destructeur
    ~Application();
    // Méthodes publiques
    void Run();
    void RenderLayouts();
    bool IsTitleBarHovered() const { return m_TitleBarHovered; }
    void AddLayout(Layout* layout); // Méthode pour ajouter un layout
    GLFWwindow *GetWindowHandle() const;

    void InitializeWindow(int width, int height, bool customTitlebar);

private:
    // Variables membres
    int largeurFenetre;
    int hauteurFenetre;

    bool IsHoveredTitleBar;
    bool CustomTitlebar;
    bool m_TitleBarHovered = false;
    bool isDragging = false; // Variable pour suivre l'état de glissement

    GLFWwindow* m_WindowHandle;
    std::vector<Layout*> layouts;

};

#endif // APPLICATION_H