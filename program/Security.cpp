#include "Security.h"
#include "Random.h"
void Seculity::Init()
{
    pos_x = 20.0f;
    pos_z = -460.0f;

    radian = 1.6f;

    radian_adding = 0.025f;

    //  角度の最大値と最小値を設定
    radian_max       = 4.5f;
    radian_min       = 1.5f;
    radian_move_juge = true;

    radian_wait = 0.0f;
}

void Seculity::Update()
{
    //  基本はtrueにしておいてキャラが動いた瞬間のみfalseにする

    //  1.5で９０度向きを変える(右方向を見る4.5で270度左方向を見る)
    if(/*radian_move_juge*/ radian_wait >= 1200.0f) {
        if(radian >= radian_max) {
            radian_adding *= -1;
            radian_wait = 0.0f;
        }
        else if(radian <= radian_min) {
            radian_adding *= -1;
            radian_wait = 0.0f;
        }
        radian += radian_adding;
    }

    radian_wait += GetRandomF(10);
}
void Seculity::Draw()
{
}

void Seculity::Exit()
{
}
