#pragma once
class Wall
{
public:
    //	�ǂ̍��W�i�v���C���[���猩�č��[�j
    float Wall_right_x, Wall_right_y, Wall_right_z;
    //	�ǂ̍��W�i�v���C���[���猩�ĉE�[�j
    float Wall_left_x, Wall_left_y, Wall_left_z;

    float Ufo_start_wall_x;

    int UFO_STAGE_X[17];

    //	����
    void Init();
    void Update();
    void Draw();
    void Exit();
};
