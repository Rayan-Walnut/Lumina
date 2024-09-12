#ifndef LAYOUT_H
#define LAYOUT_H

#include <imgui.h>

class Layout {
public:
    Layout(float x, float y, float width, float height)
        : x(x), y(y), width(width), height(height) {}

    virtual void Draw() = 0; // Méthode virtuelle pure pour dessiner le layout
    virtual void UpdateSize(int fb_width, int fb_height); // Méthode pour mettre à jour la taille

protected:
    float x, y, width, height;
};

#endif // LAYOUT_H
