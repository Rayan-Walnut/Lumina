#include "Lumina/Application.h"
#include "Lumina/TitleBarLayout.h"

int main(int, char**) {
    const int width = 1600;
    const int height = 900;

    // Créer l'application
    Application app;

    // Initializer
    app.InitializeWindow(width, height, true);

    // Créer et personnaliser la barre de titre
    auto* titleBar = new TitleBar(0, 0, width, 32, "Window Title", app.GetWindowHandle());

    // titleBar->SetBackgroundColor(ImVec4(0.2f, 0.3f, 0.4f, 1.0f));  // Changer la couleur de fond
    // titleBar->SetTextColor(ImVec4(1.0f, 0.8f, 0.6f, 1.0f));        // Changer la couleur du texte
    // titleBar->SetTitleBarHeight(50.0f);                            // Ajuster la hauteur de la barre de titre

    // Ajouter la barre de titre à l'application
    app.AddLayout(titleBar);

    // Lancer l'application
    app.Run();

    return 0;
}