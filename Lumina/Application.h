#ifndef APPLICATION_H
#define APPLICATION_H
#define GLFW_INCLUDE_NONE
#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

class Application {
public:
    // Constructeurs
    Application(int largeur, int hauteur);
    Application() : Application(1600, 900) {}  // Constructeur par défaut

    // Destructeur
    ~Application();

    // Méthodes publiques
    void Run(int width, int height, bool customTitlebar = true);
    bool IsTitleBarHovered() const { return m_TitleBarHovered; }

private:
    // Méthodes privées
    static void UpdateFrame();

    // Variables membres
    int largeurFenetre;
    int hauteurFenetre;

    bool IsHoveredTitleBar;
    bool CustomTitlebar;
    bool m_TitleBarHovered = false;
    bool isDragging = false; // Variable pour suivre l'état de glissement

    GLFWwindow* m_WindowHandle;
};

#endif // APPLICATION_H
