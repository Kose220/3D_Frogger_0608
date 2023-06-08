#pragma once

class Life
{
public:
    int life_count;

    float life_x;
    float life_y;

    bool life_over;

    void Init();
    void Update();
    void Draw();
    void Exit();
    void Gui();
};
