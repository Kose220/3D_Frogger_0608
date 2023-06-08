#include "DxLib.h"
#include "Player.h"
#include "Score.h"

Player Score_Player;

void Score::Init()
{
    score = 0;

    score_pos = 20.0f;

    //  コイン用の座標変数
    for(int i = 0; i < 5; i++) {
        coin_x[i]     = 0.0f;
        coin_z[i]     = 0.0f;
        coin_swich[i] = true;
    }
}
void Score::Update()
{
    if(Score_Player.move_z < score_pos) {
        // score += 100;
        score_pos = Score_Player.move_z;
    }
}
void Score::Draw()
{
    ////  コインの描画
    //for(int i = 0; i < 5; i++) {
    //    if(coin_swich[i]) {
    //        DrawSphere3D({coin_x[i], 3, coin_z[i]}, 3, 5, 5, GetColor(0, 255, 255), true);
    //    }
    //}


    // DrawCube3D(coin_x[0])

    //    DrawSphere3D(0.0f, 0, 0, 5, 5, GetColor(0,255,0));
    DrawFormatStringF(50, 30, GetColor(255, 255, 255), "SCORE%d", score);
}
void Score::Exit()
{
}
void Score::Gui()
{
}
