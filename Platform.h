#pragma once

namespace Tmpl8
{
    class Platform
    {
    public:
        Platform(float x, float y, float width, float height);
        ~Platform();

        void Init();
        void Draw(Surface* screen);
        bool CheckCollision(float jackX, float jackY, float jackW, float jackH, float jackVelY);

        // Getters
        float GetX() const { return x; }
        float GetY() const { return y; }
        float GetWidth() const { return width; }
        float GetHeight() const { return height; }

    private:
        float x, y, width, height;
        Sprite* platformSprite;

        // Helper methods
        bool RectangleCollision(float x1, float y1, float w1, float h1,
            float x2, float y2, float w2, float h2);
    };

} // End namespace Tmpl8

// Global functions for platform management (outside namespace to avoid conflicts)
void InitializePlatforms();
void DrawAllPlatforms(Tmpl8::Surface* screen);
void CleanupPlatforms();
