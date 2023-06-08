
class UFO
{
public:
    float pos_x;
    float pos_z;
    float pos_y;

    //  UFOがどの座標番目に止まるかを保存する用の変数
    int pos_no;

    //  UFOが止まってプレイヤーをさらう時の時間
    int ufo_time;

    //  UFOが止まっている間の変数
    bool ufo_standhing;

    //  UFOに捕まった時の管理変数
    bool ufo_die;

    //  UFOのライトの大きさを編子するための変数
    float UFO_LIGHT;
    //  UFOのライトの薄さを
    int UFO_Blend;

    void Init();
    void Update();
    void Draw();
    void Exit();
};
