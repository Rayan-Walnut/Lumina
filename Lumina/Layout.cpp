#include "Layout.h"

void Layout::UpdateSize(int fb_width, int fb_height) {
    this->width = fb_width;
    this->height = 32; // Hauteur fixe pour la barre de titre, ajustez selon vos besoins
}