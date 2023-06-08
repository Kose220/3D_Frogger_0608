#pragma once

class Player
{
public:
    float move_z;
    float move_x;

    float move_y;

    float pos_x;
    float pos_y;
    float pos_z;

    float pos_x_copy;
    float pos_z_copy;

    //  プレイヤーの動く大きさを管理する用の変数
    float move;

    bool anim_juge;

    bool move_juge;

    float radian_y;

    float time;

    //  プレイヤーが死んで復活する判定
    bool player_Revival;

    //  プレイヤーが復活しきったら動くことを許可する変数
    bool Revival_move;

    float anim_time;

    bool security_attack;

    float vel;

    float acc;

    void Init(); 
    void Update(); 
    void Draw();  
    void Exit();
};
