#pragma once

class Life
{
public:
    //  �c�@��J�E���g����p�̕ϐ�
    int life_count;

    //  �c�@�̕`��p�̍��W�ϐ�
    float life_x;
    float life_y;

    //  ���C�t���S�Ďg���؂����ۂ̔���p�ϐ�
    bool life_over;

    void Init();
    void Update();
    void Draw();
    void Exit();
    void Gui();
};
