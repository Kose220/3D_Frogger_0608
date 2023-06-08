#include "UI.h"
#include "DxLib.h"
#include "Life.h"
#include "Game.h"
Life UI_life;

//---------------------------------------------------------------------------------
//!
//---------------------------------------------------------------------------------
void UI::Init()
{
    ui_life_count = 3;

    life_imege = LoadGraph("data/Game/UI/ネズミアイコン.png", true);

    dead_image = LoadGraph("data/Game/UI/ネズミ駆除アイコン.png", true);
}

//---------------------------------------------------------------------------------
//!	 X V
//---------------------------------------------------------------------------------
void UI::Update()
{
}

//---------------------------------------------------------------------------------
//!	 `
//---------------------------------------------------------------------------------
void UI::Draw()
{
    if(ui_life_count > 0) {
        DrawExtendGraph(70, 70, 110, 110, life_imege, true);
    }
    if(ui_life_count > 1) {
        DrawExtendGraph(130, 70, 170, 110, life_imege, true);
    }
    if(ui_life_count > 2) {
        DrawExtendGraph(190, 70, 230, 110, life_imege, true);
    }
    if(ui_life_count <= 2) {
        DrawExtendGraph(190, 70, 230, 110, dead_image, true);
    }
    if(ui_life_count <= 1) {
        DrawExtendGraph(130, 70, 170, 110, dead_image, true);
    }
    if(ui_life_count <= 0) {
        DrawExtendGraph(70, 70, 110, 110, dead_image, true);
    }
    SetFontSize(25);
        DrawString(WINDOW_W - 650, WINDOW_H - 50, "WASDキーで移動　車ステージのみスペースで視点変更", GetColor(255, 255, 255), true);
        SetFontSize(40);

    /*DrawGraph(UI_life.life_x + 45, 75, life_imege, true);

    DrawGraph(UI_life.life_x + 95, 75, life_imege, true);

    DrawGraph(UI_life.life_x + 145, 75, life_imege, true);*/
}

//---------------------------------------------------------------------------------
//!	 I
//---------------------------------------------------------------------------------
void UI::Exit()
{
}
