/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include <random>

#include "raylib.h"
#include "screens.h"
#include "game_logic.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
Texture bunkerTx;
Texture groundTx;
Texture rocketTx;

bool rocketPresent = false;
long lastRender;
Vector2 rocketPos;
Vector2 rocketVel;

Button   leftBtn;
Button rightBtn;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    // TODO: Initialize GAMEPLAY screen variables here!
    framesCounter = 0;
    finishScreen = 0;

    Image bunkerImg = LoadImage("resources/base_silos_64x32.png");
    Image groundImg = LoadImage("resources/ground_192x16.png");
    Image rocketImg = LoadImage("resources/rocket_16x16_f16.png");

     leftBtn.init("resources/button_48x48_f2.png");
    rightBtn.init("resources/button_48x48_f2.png");

     leftBtn.pos = Vector2{  96*4, 144*4 };
    rightBtn.pos = Vector2{ 176*4, 144*4 };

    bunkerTx = LoadTextureFromImage(bunkerImg);
    groundTx = LoadTextureFromImage(groundImg);
    rocketTx = LoadTextureFromImage(rocketImg);

    UnloadImage(bunkerImg);
    UnloadImage(groundImg);
    UnloadImage(rocketImg);
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!
    if(rocketPresent){
        float dt = GetFrameTime();
        rocketPos.x += rocketVel.x;
        rocketPos.y += rocketVel.y;
    }

    // Press enter or tap to change to ENDING screen
    if (IsKeyDown(KEY_ENTER)){
        rightBtn.currentFrame = 1;
    }
    else{
        rightBtn.currentFrame = 0;
    }

    if(IsKeyDown(KEY_SPACE)){
        leftBtn.currentFrame = 1;
    }
    else{
        leftBtn.currentFrame = 0;
    }

    if(IsKeyReleased(KEY_ENTER)){
        rocketPos.x = 181 * 4;
        rocketPos.y = 149 * 4;

        rightBtn.currentFrame = 0;

        rocketVel.x = (rand() % 41 - 20) / 10.0f;
        rocketVel.y = (rand() % 21) / -10.0f;

        rocketPresent = true;
    }

    if(IsKeyReleased(KEY_SPACE)){
        rocketPos.x = 136 * 4;
        rocketPos.y = 149 * 4;

        leftBtn.currentFrame = 0;

        rocketVel.x = (rand() % 41 - 20) / 10.0f;
        rocketVel.y = (rand() % 21) / -10.0f;

        rocketPresent = true;
    }
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    // TODO: Draw GAMEPLAY screen here!
    DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), Color{141, 105, 122, 255});

    DrawTextureEx(groundTx, Vector2{64*4, 144*4}, 0, 4, WHITE);
    DrawTextureEx(bunkerTx, Vector2{128*4, 128*4}, 0, 4, WHITE);

    DrawTexturePro(rocketTx, Rectangle{64, 0, 3, 3}, Rectangle{rocketPos.x, rocketPos.y, 3*4, 3*4}, Vector2{0,0}, 0, WHITE );

    leftBtn.render();
    rightBtn.render();

    //DrawRectangleLines(512, 512, 256, 128, GREEN)
    //DrawRectangleLines(0, 0, 1280, 768, GREEN);

    //Vector2 pos = { 20, 10 };
    //DrawTextEx(font, "GAMEPLAY SCREEN", pos, font.baseSize*3.0f, 4, MAROON);
    //DrawText("PRESS ENTER or TAP to JUMP to ENDING SCREEN", 130, 220, 20, MAROON);
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{
    // TODO: Unload GAMEPLAY screen variables here!
    UnloadTexture(bunkerTx);
    UnloadTexture(groundTx);
    UnloadTexture(rocketTx);

    leftBtn.unload();
    rightBtn.unload();
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}