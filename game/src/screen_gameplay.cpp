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

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;
Texture bunkerTx;
Texture groundTx;
Texture buttonTx;
Texture rocketTx;

bool leftBtnPressed  = false;
bool rightBtnPressed = false;

bool rocketPresent = false;
long lastRender;
Vector2 rocketPos;
Vector2 rocketVel;

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
    Image groundImg = LoadImage("resources/ground_152x16.png");
    Image buttonImg = LoadImage("resources/button_48x48_f2.png");
    Image rocketImg = LoadImage("resources/button_48x48_f2.png");

    bunkerTx = LoadTextureFromImage(bunkerImg);
    groundTx = LoadTextureFromImage(groundImg);
    buttonTx = LoadTextureFromImage(buttonImg);
    rocketTx = LoadTextureFromImage(rocketImg);

    UnloadImage(bunkerImg);
    UnloadImage(groundImg);
    UnloadImage(buttonImg);
    UnloadImage(rocketImg);
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    // TODO: Update GAMEPLAY screen variables here!
    if(rocketPresent){
        float dt = GetFrameTime();
        rocketPos.x += rocketVel.x * dt/1000.0f;
        rocketPos.y += rocketVel.y * dt/1000.0f;
    }

    // Press enter or tap to change to ENDING screen
    if (IsKeyDown(KEY_ENTER)){
        rightBtnPressed = true;
    }
    else{
        rightBtnPressed = false;
    }

    if(IsKeyDown(KEY_SPACE)){
        leftBtnPressed = true;
    }
    else{
        leftBtnPressed = false;
    }

    if(IsKeyReleased(KEY_ENTER)){
        rocketPos.x = 136*4;
        rocketPos.y = 146*4;

        rocketVel.x = (rand() % 41 - 20) / 10.0f;
        rocketVel.y = (rand() % 21) / 10.0f;

        rocketPresent = true;
    }

    if(IsKeyReleased(KEY_SPACE)){
        rocketPos.x = 181*4;
        rocketPos.y = 146*4;

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

    DrawTextureEx(groundTx, Vector2{256, 576}, 0, 4, WHITE);
    DrawTextureEx(bunkerTx, Vector2{512, 512}, 0, 4, WHITE);

    float leftBtnTxStart  =  leftBtnPressed ? 48 : 0;
    float rightBtnTxStart = rightBtnPressed ? 48 : 0;
    DrawTexturePro(buttonTx, Rectangle{rightBtnTxStart, 0, 48, 48}, Rectangle{176*4, 144*4, 48*4, 48*4}, Vector2{0,0}, 0, WHITE);
    DrawTexturePro(buttonTx, Rectangle{leftBtnTxStart,  0, 48, 48}, Rectangle{96*4,  144*4, 48*4, 48*4}, Vector2{0,0}, 0, WHITE);

    DrawTexturePro(rocketTx, Rectangle{64, 0, 3, 3}, Rectangle{rocketPos.x, rocketPos.y, 3*4, 3*4}, Vector2{0,0}, 0, WHITE );

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
    UnloadTexture(buttonTx);
    UnloadTexture(rocketTx);
}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}