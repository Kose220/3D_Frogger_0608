#include "WallClass.h"
#include "DxLib.h"
constexpr int UFO_STAGE_WALL[] = {
    170,
    150,
    130,
    110,
    90,
    70,
    50,
    30,
    10,
    -10,
    -30,
    -50,
    -70,
    -90,
    -110,
    -130,
    -150,
};
void Wall::Init()
{
    //	���[�̕ǂ̍��W��ݒ�
    Wall_left_x = 186;
    Wall_left_y = 0;
    Wall_left_z = 200;
    //	�E�[�̕ǂ̍��W��ݒ�
    Wall_right_x = -125;
    Wall_right_y = 0;
    Wall_right_z = 200;

    for(int i = 0; i < 17; i++) {
        UFO_STAGE_X[i] = UFO_STAGE_WALL[i];
    }

    //  UFOStageのいりぐち
    float Ufo_start_wall_x;
}
void Wall::Update()
{
}
void Wall::Draw()
{
    DrawCube3D({Wall_left_x + 5, Wall_left_y, Wall_left_z + 200},
               {Wall_left_x + 5, Wall_left_y + 500, Wall_left_z - 1500},
               GetColor(255,255,255),
        GetColor(255, 255, 255),
               TRUE);
    DrawCube3D({Wall_right_x - 5, Wall_right_y, Wall_right_z},
               {Wall_right_x - 5, Wall_right_y + 500, Wall_right_z - 1500},
        GetColor(255, 255, 255),
               GetColor(255, 255, 255),
               TRUE);
    DrawCube3D({ Wall_right_x, Wall_right_y, -745 },
        { Wall_left_x, Wall_right_y + 500, -750 },
        GetColor(125, 125, 125),
        GetColor(125, 125, 125),
        TRUE);

    for(int i = 0; i < 17; i++) {
        DrawCube3D({UFO_STAGE_WALL[i] + 5.0f, 0, -279},
                   {UFO_STAGE_WALL[i] - 5.0f, 5, -281},
                   GetColor(255, 255, 0),
                   GetColor(255, 255, 0),
                   true);
    }
}
void Wall::Exit()
{
}
