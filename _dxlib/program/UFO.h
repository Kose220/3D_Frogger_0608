
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

    void Init();
    void Update();
    void Draw();
    void Exit();
};
