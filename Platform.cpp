#include "precomp.h"
#include "Platform.h"

using namespace Tmpl8;

// Global platforms vector (outside namespace)
std::vector<Platform*> platforms;

Platform::Platform(float x, float y, float width, float height)
    : x(x), y(y), width(width), height(height), platformSprite(nullptr)
{
}

Platform::~Platform()
{
    delete platformSprite;
}

void Platform::Init()
{
    Surface* platformSurface = new Surface("assets/platform.png");
    platformSprite = new Sprite(platformSurface, 1);
}

void Platform::Draw(Surface* screen)
{
    if (!platformSprite) return;

    // Draw the platform sprite scaled to fit the platform dimensions
    int spriteWidth = platformSprite->GetWidth();
    int spriteHeight = platformSprite->GetHeight();

    // Simple tiling approach - repeat the sprite to fill the platform
    int tilesX = (int)(width / spriteWidth) + 1;
    int tilesY = (int)(height / spriteHeight) + 1;

    for (int tileY = 0; tileY < tilesY; tileY++)
    {
        for (int tileX = 0; tileX < tilesX; tileX++)
        {
            int drawX = (int)x + (tileX * spriteWidth);
            int drawY = (int)y + (tileY * spriteHeight);

            // Don't draw outside platform bounds
            if (drawX < x + width && drawY < y + height)
            {
                platformSprite->Draw(screen, drawX, drawY);
            }
        }
    }
}

bool Platform::CheckCollision(float jackX, float jackY, float jackW, float jackH, float jackVelY)
{
    // Check if Jack is colliding with this platform
    return RectangleCollision(jackX, jackY, jackW, jackH, x, y, width, height);
}

bool Platform::RectangleCollision(float x1, float y1, float w1, float h1,
    float x2, float y2, float w2, float h2)
{
    return (x1 < x2 + w2 && x1 + w1 > x2 &&
        y1 < y2 + h2 && y1 + h1 > y2);
}

// Global platform management functions (outside namespace)
void InitializePlatforms()
{
    // Clear existing platforms
    CleanupPlatforms();

    // Create 6 platforms at different positions
    // Platform dimensions
    const float PLATFORM_WIDTH = 120.0f;
    const float PLATFORM_HEIGHT = 20.0f;

    // Create platforms at strategic positions
    platforms.push_back(new Platform(150, 700, PLATFORM_WIDTH, PLATFORM_HEIGHT));   // Lower left
    platforms.push_back(new Platform(620, 700, PLATFORM_WIDTH, PLATFORM_HEIGHT));   // Lower right

    platforms.push_back(new Platform(50, 550, PLATFORM_WIDTH, PLATFORM_HEIGHT));    // Mid left
    platforms.push_back(new Platform(400, 500, PLATFORM_WIDTH, PLATFORM_HEIGHT));   // Mid center
    platforms.push_back(new Platform(720, 550, PLATFORM_WIDTH, PLATFORM_HEIGHT));   // Mid right

    platforms.push_back(new Platform(300, 350, PLATFORM_WIDTH, PLATFORM_HEIGHT));   // Upper center

    // Initialize all platforms
    for (Platform* platform : platforms)
    {
        platform->Init();
    }
}

void DrawAllPlatforms(Tmpl8::Surface* screen)
{
    for (Platform* platform : platforms)
    {
        platform->Draw(screen);
    }
}

void CleanupPlatforms()
{
    for (Platform* platform : platforms)
    {
        delete platform;
    }
    platforms.clear();
}