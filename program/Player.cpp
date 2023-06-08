#include "DxLib.h"
#include "Player.h"
#include "Score.h"
#include "Timer.h"

Score player_score;
Timer player_time;

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void Player::Init()
{
    move_x = 10.0f;
    move_y = 1.0f;
    move_z = 20.0f;
    //    -２８０以降がUFO後で消す

    //  川の直前
    // move_z = -460.0f;

    //    move_z = -120.0f;
    pos_x = 10.0f;
    pos_y = 1.0f;
    //    pos_z = 20.0f;
    //  ゴール直前
    pos_z = 20.0f;
    //pos_z = -460.0f;

    //  プレイヤーの移動量の変数
    move = 20.0f;

    //  動いていいか判定する
    move_juge = false;
    //  アニメの判定をする
    anim_juge = false;

    radian_y = 0;

    time = 0.0f;

    player_Revival = false;
    //  復活中に動けないようにするための変数
    Revival_move   = true;
    //  プロレスラーに攻撃された直後すぐに攻撃されないようにするための変数
    security_attack = false;

    vel = 0;
    acc = -0.5;
}

//---------------------------------------------------------------------------------
//---------------------------------------------------------------------------------
void Player::Update()
{
    pos_x_copy = pos_x;
    pos_z_copy = pos_z;
    //  キーを押した瞬間一瞬で動いてしまわないようにmove変数を挟む
    if(move_z >= pos_z) {
        pos_z++;
    }
    if(move_z <= pos_z) {
        pos_z--;
    }
    if(move_x >= pos_x) {
        pos_x++;
    }
    if(move_x <= pos_x) {
        pos_x--;
    }
    if(move_y > pos_y) {
        pos_y++;
    }
    if(move_y < pos_y) {
        pos_y -= 1.0f;
    }

    //  デフォルトはtrue復活中の上から降ってきているときは動けなくする
    //if(pos_z == 20.0f) {
    //    player_Revival = true;
    //}
    //if(pos_y >= 0.5f) {
    //    pos_y -= 0.1f;
    //    player_Revival = false;
    //}

    //  動いた時のアニメーションを動かす変数
    //  常にオフにして置き動いた瞬間の一コマのみtrueにする
    anim_juge = false;

    if (pos_z <= -740)
    {
        pos_z = -739;
    }

    //  プレイヤーは復活しきったら動けるようにする
    if(Revival_move) {
        
        if(move_juge) {
            if(time >= 30) {
                if(CheckHitKey(KEY_INPUT_S)) {
                    move_z += move;
                    time      = 0;
                    radian_y  = 380.0f;
                    anim_time = 0;
                    anim_juge = true;
                }
                if(CheckHitKey(KEY_INPUT_W)) {
                    move_z -= move;
                    time      = 0;
                    radian_y  = 0.0f;
                    anim_time = 0;
                    anim_juge = true;
                }
                if(CheckHitKey(KEY_INPUT_A)) {
                    move_x += 20;
                    time      = 0;
                    radian_y  = 80.0f;
                    anim_time = 0;
                    anim_juge = true;
                }
                if(CheckHitKey(KEY_INPUT_D)) {
                    move_x -= 20;
                    time      = 0;
                    radian_y  = 190.0f;
                    anim_time = 0;
                    anim_juge = true;
                }
            }
        }
    }
    //  タイトルから始まった瞬間に待機アニメーションに入るためにする
    if (CheckHitKey(KEY_INPUT_RETURN)) {
        anim_juge = true;
    }
    //  プレイヤーが一定以上後ろに行かないようにするための処理
    if (pos_z >= 20.0f)
    {
        pos_z = 20.0f;
    }


}

//---------------------------------------------------------------------------------
//!　描画
//---------------------------------------------------------------------------------
void Player::Draw()
{
}

//---------------------------------------------------------------------------------
//!	終了処理
//---------------------------------------------------------------------------------
void Player::Exit()
{
}
