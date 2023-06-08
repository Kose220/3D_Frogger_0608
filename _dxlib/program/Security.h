
class Seculity
{
public:
    float pos_x;
    float pos_z;

    float radian;

    //  角度を足していく変数
    float radian_adding;

    float radian_max;
    float radian_min;

    //  角度を今変えていいかどうかを判定するための変数（キャラが動いているときは動かさないために）
    bool radian_move_juge;

    //  角度を回すのを待たせる時間
    float radian_wait;

    //  プロレスラーがこっちに攻撃してくるかどうかを決める変数
    bool attack;

    void Init();
    void Update();
    void Draw();
    void Exit();
};
