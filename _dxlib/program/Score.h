#pragma once

class Score
{
public:
    int score;

    float score_pos;

    //  コイン用の変数
    float coin_x[5];
    //    float coin_y[5];
    float coin_z[5];
    //  コインを取った際　消えるようにON　OFのスイッチ変数
    bool coin_swich[5];

    void Init();
    void Update();
    void Draw();
    void Exit();
    void Gui();
};

