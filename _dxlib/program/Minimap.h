#pragma once
class Minimap
{
public:

    //  ミニマップのY座標用変数
    float map_y;
    //  ミニマッププレイヤー用の変数
    float map_player_y;

    //  ネズミのアイコン用の変数
    int map_icon_player;
    int map_icon_dead;

    //  ミニマップのアイコンの色を変えるための変数
    bool map_icon_switch;

    void Init();
    void Update();
    void Draw();
    void Exit();

};