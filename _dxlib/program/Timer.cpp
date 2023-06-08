#include "Timer.h"
#include "Game.h"
#include "DxLib.h"
#include "Score.h"

Score Timer_score;
void  Timer::Init()
{
    time_max  = 1080.0f;
    time      = time_max;
    time_over = false;

    //  タイムバーの色の変数
    color1 = 255;
    color2 = 0;
    color3 = 0;

    start_time = false;
    time_clear = true;

    //  リザルト画面が上から降りてくるような感じにしたいのでY座標用の変数を用意
    result_y = 0.0f;

    //  余裕があるときはtrueピンチになるとfalseにする
    time_pinch       = false;
    time_pinch_count = 61.0f;
    //  画像用の変数
    Time_Wach = LoadGraph("data/Game/Time/Woach.png");

    //  タイマーの初期化
    Rad = 0.0f;
}

void Timer::Update()
{

    //  クリアした際にはタイマーを止める    
    //  falseになったらクリア

    if (time_clear) {

        //  プレイヤーが動いてから制限時間が動き出すようにしておく
        if (start_time) {
            //  �^�C�}�[����炵�����܂�
    //        Rad += 0.0017361111f;
            Rad += 0.0017361111f / 2;

        }


        // 色変更用処理

        //if(time_max / 2 >= time) {
        //    color1 = 0;
        //    color2 = 255;
        //    color3 = 255;
        //}
        //if(time_max / 4 >= time) {
        //    color1 = 0;
        //    color2 = 0;
        //    color3 = 255;
        //}

        if (Rad >= 11) {
            time_pinch_count += 2;
        }
        if (time_pinch_count <= 60) {
            time_pinch = false;
        }
        if (time_pinch_count >= 61) {
            time_pinch = true;
        }
        if (time_pinch_count >= 120) {
            time_pinch_count = 0;
        }

        if (Rad >= 6.25f) {
            time = 0.0f;
            time_over = true;
            result_y += 10.0f;
            if (result_y >= WINDOW_H) {
                result_y = WINDOW_H;
            }
        }
    }
}
void Timer::Draw()
{
    if (time_pinch) {
    DrawCircle(WINDOW_W - 120, 110, 85, GetColor(128, 128, 128), 1, 1);
    DrawCircle(WINDOW_W - 120, 110, 80, WHITE, 1, 1);
    //  秒針は6.25で約一周
    DrawRotaGraph(WINDOW_W - 120, 110, 0.4, Rad, Time_Wach, TRUE);
    DrawRotaGraph(WINDOW_W - 120, 110, 0.2, 3.1 / 100, Time_Wach, TRUE);


//        DrawBox(WINDOW_W / 2 + 80, 50, WINDOW_W / 2 + 80 + time, 20, GetColor(color3, color2, color1), TRUE);
    }
    if(time_over) {
        //  時間切れになった際のリザルト画面の出力
       DrawBox(0, 0, WINDOW_W, result_y, GetColor(0, 0, 0), true);
        DrawString(WINDOW_W / 2, result_y / 2, "時間切れ、、、だ", GetColor(255, 255, 255), true);


        DrawFormatStringF(WINDOW_W / 2 - 100,
                          result_y / 2 + 50,
                          GetColor(255, 255, 255),
                         "今回のスコアは%d",
                         Timer_score.score);
    }
}

void Timer::Exit()
{
}
