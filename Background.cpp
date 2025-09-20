#include "precomp.h"
#include "Background.h"

using namespace Tmpl8;

Background::Background() : backgroundSurface(nullptr)
{
}

Background::~Background()
{
    delete backgroundSurface;
}

void Background::Init()
{
    backgroundSurface = new Surface("assets/background_1.png");
}

void Background::Draw(Surface* screen)
{
    if (!backgroundSurface) return;

    // Scale factor from 224x224 to 896x896 (4x scaling)
    const int scaleX = SCREEN_SIZE / ORIGINAL_SIZE;
    const int scaleY = SCREEN_SIZE / ORIGINAL_SIZE;

    // Get source pixels
    uint* srcPixels = backgroundSurface->pixels;
    uint* destPixels = screen->pixels;

    // Simple nearest neighbor scaling
    for (int y = 0; y < SCREEN_SIZE; y++)
    {
        for (int x = 0; x < SCREEN_SIZE; x++)
        {
            // Map screen coordinates to source coordinates
            int srcX = x / scaleX;
            int srcY = y / scaleY;

            // Ensure we don't go out of bounds
            if (srcX >= ORIGINAL_SIZE) srcX = ORIGINAL_SIZE - 1;
            if (srcY >= ORIGINAL_SIZE) srcY = ORIGINAL_SIZE - 1;

            // Copy pixel
            uint sourcePixel = srcPixels[srcX + srcY * ORIGINAL_SIZE];
            destPixels[x + y * SCREEN_SIZE] = sourcePixel;
        }
    }
}