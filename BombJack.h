#pragma once

namespace Tmpl8
{
    class BombJack
    {
    public:
        enum State {
            STANDING,
            MOVING_LEFT,
            MOVING_RIGHT,
            JUMPING
        };

        // Constructor/Destructor
        BombJack();
        ~BombJack();

        // Methods
        void Init();
        void Update(float deltaTime);
        void Draw(Surface* screen);
        void HandleInput();

        // Collision
        bool IsOnGround();
        bool IsOnPlatform();
        void CheckCollisions();

        // Getters
        float GetX() const { return x; }
        float GetY() const { return y; }
        float GetWidth() const { return width; }
        float GetHeight() const { return height; }


        // Position and movement
        float x, y;
        float velocityX, velocityY;
        float width, height;

        // Physics
        static const float GRAVITY;
        static const float JUMP_FORCE;
        static const float MOVE_SPEED;
        static const float GROUND_Y;

        // State management
        State currentState;
        State previousState;
        bool isJumping;
        bool isOnGround;

        // Sprites
        Sprite* standingSprite;
        Sprite* movingLeftSprite;
        Sprite* movingRightSprite;

        // Animation
        float animationTimer;
        int currentFrame;
        static const float ANIMATION_SPEED;

        // Helper methods
        void UpdateAnimation(float deltaTime);
        void UpdatePhysics(float deltaTime);
        void UpdateState();
    };
}