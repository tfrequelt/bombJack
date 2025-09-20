#include "precomp.h"
#include "BombJack.h"
#include "Platform.h"

using namespace Tmpl8;

// Constants
const float BombJack::GRAVITY = 800.0f;
const float BombJack::JUMP_FORCE = -400.0f;
const float BombJack::MOVE_SPEED = 0.1f;
const float BombJack::GROUND_Y = 896.0f - 64.0f; // Screen height - jack height
const float BombJack::ANIMATION_SPEED = 10.0f;

extern std::vector<Platform*> platforms; // Declared in Platform.cpp

BombJack::BombJack()
    : x(100.0f), y(GROUND_Y), velocityX(0.0f), velocityY(0.0f)
    , width(32.0f), height(64.0f)
    , currentState(STANDING), previousState(STANDING)
    , isJumping(false), isOnGround(true)
    , standingSprite(nullptr), movingLeftSprite(nullptr), movingRightSprite(nullptr)
    , animationTimer(0.0f), currentFrame(0)
{
}

BombJack::~BombJack()
{
    delete standingSprite;
    delete movingLeftSprite;
    delete movingRightSprite;
}

void BombJack::Init()
{
    // Load sprites
    Surface* standingSurface = new Surface("assets/standing_jack.png");
    standingSprite = new Sprite(standingSurface, 1);

    Surface* movingLeftSurface = new Surface("assets/moving_left_jack.png");
    movingLeftSprite = new Sprite(movingLeftSurface, 4);

    Surface* movingRightSurface = new Surface("assets/moving_right_jack.png");
    movingRightSprite = new Sprite(movingRightSurface, 4);

    // Set initial dimensions based on sprite
    width = (float)standingSprite->GetWidth();
    height = (float)standingSprite->GetHeight();
}

void BombJack::Update(float deltaTime)
{
    HandleInput();
    UpdatePhysics(deltaTime);
    CheckCollisions();
    UpdateState();
    UpdateAnimation(deltaTime);
}

void BombJack::HandleInput()
{
    velocityX = 0.0f;

    // Get the window handle for input
    GLFWwindow* window = glfwGetCurrentContext();

    // Left/Right movement
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
    {
        velocityX = -MOVE_SPEED;
        if (currentState != JUMPING)
            currentState = MOVING_LEFT;
    }
    else if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
    {
        velocityX = MOVE_SPEED;
        if (currentState != JUMPING)
            currentState = MOVING_RIGHT;
    }
    else if (currentState != JUMPING)
    {
        currentState = STANDING;
    }

    // Jump
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && isOnGround && !isJumping)
    {
        velocityY = JUMP_FORCE;
        isJumping = true;
        isOnGround = false;
        currentState = JUMPING;
    }
}

void BombJack::UpdatePhysics(float deltaTime)
{
    // Update horizontal position
    x += velocityX * deltaTime;

    // Apply gravity if not on ground
    if (!isOnGround)
    {
        velocityY += GRAVITY * deltaTime;
    }

    // Update vertical position
    y += velocityY * deltaTime;

    // Screen boundaries (horizontal)
    if (x < 0) x = 0;
    if (x > 896 - width) x = 896 - width;
}

void BombJack::CheckCollisions()
{
    isOnGround = false;

    // Check ground collision
    if (y >= GROUND_Y)
    {
        y = GROUND_Y;
        velocityY = 0.0f;
        isOnGround = true;
        isJumping = false;
    }

    // Check platform collisions
    for (Platform* platform : platforms)
    {
        if (platform->CheckCollision(x, y, width, height, velocityY))
        {
            if (velocityY > 0) // Only land if falling
            {
                y = platform->GetY() - height;
                velocityY = 0.0f;
                isOnGround = true;
                isJumping = false;
            }
        }
    }
}

void BombJack::UpdateState()
{
    if (isJumping && isOnGround)
    {
        // Just landed
        if (velocityX < 0) currentState = MOVING_LEFT;
        else if (velocityX > 0) currentState = MOVING_RIGHT;
        else currentState = STANDING;
    }
}

void BombJack::UpdateAnimation(float deltaTime)
{
    if (currentState == MOVING_LEFT || currentState == MOVING_RIGHT)
    {
        animationTimer += deltaTime * ANIMATION_SPEED;
        if (animationTimer >= 1.0f)
        {
            currentFrame = (currentFrame + 1) % 4;
            animationTimer = 0.0f;
        }
    }
    else
    {
        currentFrame = 0;
        animationTimer = 0.0f;
    }
}

void BombJack::Draw(Surface* screen)
{
    Sprite* spriteToUse = standingSprite;

    switch (currentState)
    {
    case STANDING:
    case JUMPING:
        spriteToUse = standingSprite;
        spriteToUse->SetFrame(0);
        break;
    case MOVING_LEFT:
        spriteToUse = movingLeftSprite;
        spriteToUse->SetFrame(currentFrame);
        break;
    case MOVING_RIGHT:
        spriteToUse = movingRightSprite;
        spriteToUse->SetFrame(currentFrame);
        break;
    }

    if (spriteToUse)
    {
        spriteToUse->Draw(screen, (int)x, (int)y);
    }
}

bool BombJack::IsOnGround()
{
    return isOnGround;
}

bool BombJack::IsOnPlatform()
{
    for (Platform* platform : platforms)
    {
        if (platform->CheckCollision(x, y, width, height, 0))
        {
            return true;
        }
    }
    return false;
}