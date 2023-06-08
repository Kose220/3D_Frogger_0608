#pragma once
class Wall
{
public:
    float Wall_right_x, Wall_right_y, Wall_right_z;
    float Wall_left_x, Wall_left_y, Wall_left_z;

    float Ufo_start_wall_x;

    float Ufo_start_wall_y;

    int UFO_STAGE_X[17];

    void Init();
    void Update();
    void Draw();
    void Exit();
};
