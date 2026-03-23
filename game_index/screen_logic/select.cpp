#include <raylib.h>
#include <iostream>
#include "../include/game/player_stats.hpp"
#include "../include/screen_load/screen_constants.hpp"
#include <cstdint>
#include <vector>
#include <cmath>
#include "../include/screen_load/home_screen.hpp"
// Can communicate with main.cpp:
#include "../include/screen_load/select_main.hpp"
// Gives easy access to all standard ui features:
#include "../include/standardUI/manager.hpp"
// The files' local ui manager:
ui::Manager selectManager;
using DP = ui::Button::DisplayDependency;
Race currentRace;
Prof currentProf;
bool raceSelect=false;
bool profSelect=false;

using AlignmentX = ui::Button::AlignmentX;
using AlignmentY = ui::Button::AlignmentY;

void placeButton(std::string label, AlignmentX alignmentX, AlignmentY alignmentY, Vector2 offset, Texture2D tex, std::function<void()> action) {
    ui::Button button(Vector2 { 0, 0 }, tex, action);

    button.label = label;
    button.alignmentX = alignmentX;
    button.alignmentY = alignmentY;
    button.alignmentOffsetX = offset.x;
    button.alignmentOffsetY = offset.y;

    selectManager.addButton(button);
}

void selectPreLoadTasks(float screenWidth, float screenHeight){
    static Texture2D buttonTexture = LoadTexture("assets/UI/screen_interface/buttons/blueButton.png");
    // Race select buttons
    // selectManager.placeButton( "SpLz", Vector2 { 0, 0 }, buttonTexture, []{ currentRace = Race::Spacelizard; raceSelect = true; });
    // selectManager.placeButton( "VdCr", Vector2 { 50, 0 }, buttonTexture, []{ currentRace = Race::Voidcrawler; raceSelect = true; });
    // selectManager.placeButton( "McSp", Vector2 { 100, 0 }, buttonTexture, []{ currentRace = Race::Mecha_sapien; raceSelect = true; });
    // selectManager.placeButton( "Human", Vector2 { 150, 0 }, buttonTexture, []{ currentRace = Race::Human; raceSelect = true; });
    placeButton("SpLz", AlignmentX::Left, AlignmentY::Top, Vector2 { 0, 0 }, buttonTexture, []{ currentRace = Race::Spacelizard; raceSelect = true; });
    placeButton( "VdCr", AlignmentX::Left, AlignmentY::Top, Vector2 { 50, 0 }, buttonTexture, []{ currentRace = Race::Voidcrawler; raceSelect = true; });
    placeButton( "McSp", AlignmentX::Left, AlignmentY::Top, Vector2 { 100, 0 }, buttonTexture, []{ currentRace = Race::Mecha_sapien; raceSelect = true; });
    placeButton( "Human", AlignmentX::Left, AlignmentY::Top, Vector2 { 150, 0 }, buttonTexture, []{ currentRace = Race::Human; raceSelect = true; });

    // Proffesion select buttons
    // selectManager.placeButton("NcrMnc", Vector2 { 0, 50 }, buttonTexture, []{ currentProf = Prof::Necromancer; profSelect = true; });
    // selectManager.placeButton("CrftMn", Vector2 { 50, 50 }, buttonTexture, []{ currentProf = Prof::Craftsman; profSelect = true; });
    // selectManager.placeButton("Wizard", Vector2 { 100, 50 }, buttonTexture, []{ currentProf = Prof::Wizard; profSelect = true; });
    // selectManager.placeButton("Dualist", Vector2 { 150, 50 }, buttonTexture, []{ currentProf = Prof::Dualist; profSelect = true; });
    placeButton("NcrMnc", AlignmentX::Left, AlignmentY::Top, Vector2 { 0, 50 }, buttonTexture, []{ currentProf = Prof::Necromancer; profSelect = true; });
    placeButton("CrftMn", AlignmentX::Left, AlignmentY::Top, Vector2 { 50, 50 }, buttonTexture, []{ currentProf = Prof::Craftsman; profSelect = true; });
    placeButton("Wizard", AlignmentX::Left, AlignmentY::Top, Vector2 { 100, 50 }, buttonTexture, []{ currentProf = Prof::Wizard; profSelect = true; });
    placeButton("Dualist", AlignmentX::Left, AlignmentY::Top, Vector2 { 150, 50 }, buttonTexture, []{ currentProf = Prof::Dualist; profSelect = true; });

    // Button progresses to level select
    // const float btnX = screenWidth/2.f;
    // const float btnY = screenHeight/2.f;
    // selectManager.placeButton("Choose", Vector2 { btnX, btnY }, buttonTexture, []{ if(raceSelect && profSelect) currentScreen = screen::LevelSelect; });
    placeButton("Choose", AlignmentX::Center, AlignmentY::Center, Vector2 { 0, 0 }, buttonTexture, []{ if(raceSelect && profSelect) currentScreen = screen::LevelSelect; });

    // Create background:
    selectManager.setupHelper(buttonTexture);
    selectManager.Helper.setupScale(screenWidth, screenHeight);
}
void loadSelectScreen(Vector2 mousePos, float screenWidth, float screenHeight){
    static bool loaded = false;
    if(!loaded){
        selectPreLoadTasks(screenWidth, screenHeight);
        loaded = true;
    }
    selectManager.updateAll(mousePos);
    selectManager.drawAll();
    selectManager.Helper.draw();
}
