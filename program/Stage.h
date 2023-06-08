#pragma once

//  ステージ作成用のヘッダー
class Stage
{
public:
    //  車を動かすための変数
    float car_x[6];
    float car_z[6];

    //  丸太の変数
    float wood_x[10];
    float wood_z[10];
    //  反対方向から流れてくる丸太の変数
    float wood_x_re[10];
    float wood_z_re[10];

    //  川を描画する（仮）
    float river_x;
    float river_y;

    //  連続で動けないようにする

        //  真ん中のほうのセーフエリア（石の）座標
    float safe_stone_x;
    float safe_stone_z;

    //  一定以上の越したらクリアになるための座標変数
    float goal_line_x;
    float goal_line_z;


    //  ステージ変更用の変数
    enum STAGE_STATUS
    {
        FIRST_STAGE = 0,    //  ステージの変数
        SECOND_STAGE,
        THIRD_STAGE,
        FOURTH_STAGE,
        FIFTH_STAGE



    };
    //  ステージ操作の変数
    int stage_status = FIRST_STAGE;

    void Init();
    void Update();
    void Draw();
    void Exit();

};