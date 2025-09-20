// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#include "precomp.h"
#include "game.h"
#include "BombJack.h"
#include "Background.h"
#include "Platform.h"

using namespace Tmpl8;

// Game objects
BombJack* jack = nullptr;
Background* background = nullptr;
bool gameInitialized = false;

// -----------------------------------------------------------
// Initialize the application
// -----------------------------------------------------------
void Game::Init()
{
    // Create game objects
    background = new Background();
    jack = new BombJack();

    // Initialize objects
    background->Init();
    InitializePlatforms();
    jack->Init();

    gameInitialized = true;
}

// -----------------------------------------------------------
// Main application tick function - Executed once per frame
// -----------------------------------------------------------
void Game::Tick(float deltaTime)
{
    if (!gameInitialized) return;

    // Clear screen
    screen->Clear(0);

    // Draw background (scaled from 224x224 to 896x896)
    background->Draw(screen);

    // Draw platforms
    DrawAllPlatforms(screen);

    // Update and draw Jack
    jack->Update(deltaTime);
    jack->Draw(screen);
}

// -----------------------------------------------------------
// Shutdown - Clean up game objects
// -----------------------------------------------------------
void Game::Shutdown()
{
    delete jack;
    delete background;
    CleanupPlatforms();
}