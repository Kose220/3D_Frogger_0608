#pragma once

//#define WINDOW_W	1500
//#define WINDOW_H	750
#define WINDOW_W	1280
#define WINDOW_H	720

#define BLACK   GetColor(0, 0, 0)
#define WHITE   GetColor(255, 255, 255)
#define RED     GetColor(255, 0, 0)
#define GREEN   GetColor(0, 255, 0)
#define BLUE    GetColor(0, 0, 255)
#define YELLOW  GetColor(255, 255, 0)
#define PINK    GetColor(255, 0, 255)
#define SKYBLUE GetColor(0, 255, 255)

constexpr int COIN_NUM = 5;   //  コインの枚数


struct Coin
{
    float x;
    float y;
    float z;
};

class Game
{
public:
    //  プレイヤーに動いてほしい位置を指定する変数
    //float move_z;
    //float move_x;
    ////  当たり判定も何もないがジャンプができるように
    //float move_y;
    ////  プレイヤーの座標
    //float pos_x;
    //float pos_y;
    //float pos_z;

    ////  キャラクターの動きを受け付けるかどうか判定する変数
    //bool move_juge;

    ////  プレイヤーの向きを変える変数
    //float radian_y;

    //  ゲームがスタートしタイトルを横にずらすための変数
    int Title_Slide;
    int Title_Slide_x;

    //  車を動かすための変数
    float car_x[6];
    float car_z[6];

    //  丸太の変数
    float wood_x[10];
    float wood_z[10];
    //  反対方向から流れてくる丸太の変数
    float wood_x_re[10];
    float wood_z_re[10];

    //  川を描画する（仮）
    float river_x;
    float river_y;

    //  連続で動けないようにする
    //    float time;

    //  プレイヤーが障害物にぶつかったとき判断する変数(車とぶつかった際)
    bool car_dead;

    //  車に

    //  川に落ちた際の処理
    bool river_dead;

    //  丸太の上に乗ってる際上記のriver_deadが発動しないようにするための変数
    bool wood_safe;

    //  真ん中のほうのセーフエリア（石の）座標
    float safe_stone_x;
    float safe_stone_z;

    //  一定以上の越したらクリアになるための座標変数
    float goal_line_x;
    float goal_line_z;

    //  ゲームオーバー画面が遅れて出てくるようにするための変数
    float over_time;

    //川に溺れたときにプレイヤーが上下に溺れているように見える処理
    float river_out_y;

    //  コイン用の変数
    float coin_z;
    float coin_x;

    int coin_models[5];

    //  コインの角度（回っているように見えるようにするようの）変数
    int Coin_Rota_x;


    //  ゴール座標をいじる用の変数
    int goal_adjustment;

    //  車を動かすための変数
    float car_x_plus[6];


    //  ゴールしたかどうか判定する変数
    bool goal;

    //  ゴール時のアニメーション用の判定用変数
    bool goal_anim;

    //  ゴールした際にプレイヤーが喜び終わってからリザルト画面に飛ぶようにするための時間をとるカウント変数
    int goal_count;

    //  タイトル画面の変数
    bool title;

    //  タイトルの次のページの物語説明用の変数
    bool title_rule;

    //  タイトルの文字をぼやかす用の変数
    int title_blend;
    int title_blend_hiku;

    //  タイトル画面が横にスライドするための変数
    float title_x;

    //  ゲーム本編を管理する変数
    bool game;

    //  死んでしまった時の初期化用の変数
    bool init;

    //  カメラの向きを変えるための変数
    float camera_x;
    float camera_z;
    //  カメラのY座標用の変数(向き)
    float camera_y;
    float camera_y_radian;

    // カメラでゴールを見る用の座標変数
    //    float goal_pos_x;
    float goal_pos_z;

    //  ゲーム本編が始まったタイミングでカメラターゲットをゴールからプレイヤーに変えるための変数
    //    float Chenge_camera_x;
    float Change_camera_z;

    //  リスポーン地点との距離を図るための変数
    float Respawn_Distance_z;

    //  BGM用の変数
    int Title_BGM;
    int Game_BGM;
    int Over_BGM;
    int Clear_BGM;

    //  SE用の変数
    //  せせらぎSE
    int River_SE;
    //  せせらぎの音量変更用の変数;
    int River_SE_Volume;
    //  プレイヤーと川の距離を測るための変数
    float River_distance;
    //  車にひかれた時のSE
    int Car_Clash_SE;
    //  車のクラクションのSE
    int Car_Clacshon_SE;
    //  車の通過のSE
    int Car_Slue_SE;
    //  車にひかれた後のサイレンのSE
    int Silen_SE;
    //  川でおぼれた時のSE
    int River_Die_SE;

    //  アニメーションの変更の貯めの変数
    float anim_time;

    ////  動いているときの変数
    //bool run;
    ////  止まっているときの変数
    //bool idle;
    ////  車にぶつかったときのアニメーション
    //bool car_clash;
    ////  川に溺れたときのアニメーションの判定変数
    bool river_die;

    bool car_die;

    //  UFOにさらわれたさいにリスポーン地点まで帰ってる途中は無敵状態にしたいのでそれ用の変数
    bool no_die;

    //  ステージ変更用の画面を出すための変数
    bool stage_change;


    //　BGM開始用の変数
    bool Title_BGM_Start;
    bool Game_BGM_Start;
    bool Over_BGM_Start;
    bool Clear_BGM_Start;

    //  タイトル用のイラスト（画像）の変数
    int Title_Player;
    int Title_Ufo;
    int Title_Town;
    int Title_House;

    //  タイトルのイラスト用の変数
    float Title_Player_x;
    float Title_Player_y;
    float Title_Ufo_x;
    float Title_Ufo_y;
    //  画像の座標を足す用の変数
    float Title_Ufo_x_plus;
    float Title_Ufo_y_plus;

    //  UFOの角度を変更するための変数
    float Title_Ufo_rad;
    float Title_Ufo_rad_plus;


    //  ゲームオーバー時のいらうと用の変数
    int Time_Over_ilust_hansei;
    int Time_Over_ilust_sekkyou;
    int Time_Over_haikei_fire;

    int River_Over_ilust;
    int River_Over_ilust_safe;


    int next_anim = -1;        // 次のアニメーション用モデル

    //  一定以上でタイトルへ戻るようにしておく
    int InitTime;

    //  プレイ数をカウントするための変数
    int PlayCount;
    bool PlayCount_Switch;


    void Init();                //!< 初期化
    void Update();   //!< 更新
    void Draw();                //!< 描画
    void Exit();                //!< 終了
    void GUI();                 //!< GUI表示

private:
    int model_ = -1;   //!< MV1モデルハンドル
    int model_anim_run = -1;   //!< MV1モデルハンドル
    int model_anim_idle = -1;
    int model_anim_car_clash = -1;
    int model_anim_river_die = -1;
    int model_anim_stand_up = -1;   //  プレイヤーがリスポーンした際にするアニメーション
    int model_anim_happy_dance = -1;
    int model_anim_security_dameg = -1;
    int model_anim_security_stand_up = -1;
    int model_anim_dead_cry = -1;


    //  プロレスラーのアニメーションの初期化
    //  警備員（プロレスラー）のモデル
    int security_model;
    int security_anim_idle = -1;
    int security_anim_move = -1;
    int security_anim_attack = -1;

    //  プロレスラーが動いているか判定するための変数
    bool security_move_juge;

    //  アニメーションモデルを統括する用の変数
    // int anim_managemen;

    //  状態の変数
    //const int STATE_IDLE         = 0;
    //const int STATE_RUN          = 1;
    //const int STATE_CAR_DAMEGE   = 2;
    //const int STATE_RIVER_DAMEGE = 3;
    enum BGM_STATUS
    {
        START_BGM = 0,   //  タイトルBGM
        MAIN_BGM,        //  ゲーム本編BGM
        OVER_BGM,        //  ゲームオーバーBGM
        CLEAR_BGM        //  クリアBGM

    };
    enum STAGE_STATUS
    {
        FIRST_STAGE = 0,    //  ステージの変数
        SECOND_STAGE,
        THIRD_STAGE,
        FOURTH_STAGE,
        FIFTH_STAGE



    };
    int bgm_status = START_BGM;
    int stage_status = FIRST_STAGE;
    enum STATUS
    {
        STATUS_IDLE = 0,       // 待機
        STATUS_MOVE,           // 移動（走り）
        STATUS_CAR_DAMAGE,     // ダメージ（車）
        STATUS_RIVER_DAMAGE,   // ダメージ（川）
        STATUS_STAND_UP,       //  起き上がるよう
        STATUS_HAPPY_DANCE,
        STATUS_SECURITY_DAMEGE,
        STATUS_SECURITY_STAND_UP,
        STATUS_DEAD_CRY        //  ゲームオーバーにより悲しむアニメーション
    };
    int status_ = STATUS_IDLE;   // 状態を管理する

    //  川でおぼれたか車で引かれたか死因を判定する用
    enum GAMEOVER
    {
        CAR_OVER = 0,   //  車で引かれた時用
        RIVER_OVER      //  川でおぼれた時用

    };
    int over_status = 0;   //  管理用
                           //  複製するための変数

    int security_status = SECULITY_IDLE;

    enum SECULITY_ACTION_JUGE
    {
        SECULITY_IDLE = 0,
        SECULITY_MOVE,
        SECULITY_ATTACK

    };
    //  int seculity_status_ = SECULITY_IDLE;

    int Seculity_Action_status = SECULITY_IDLE;

    int   seculity_anim_index = -1;
    float seculity_anim_max_frame = -1;   // アニメーションの最大フレーム数

    float Seculity_Anim_frame = -1;
    float Seculity_Anim_frame_speed = 1.0f;

    //  生きているか死んでいるか判定するような変数
    bool live;
    bool dead;
    //  アニメーション用の変数
    int   anim_index = -1;   // 現在のアニメーションのインデックス
    float anim_max_frame = -1;   // アニメーションの最大フレーム数
    float anim_frame = -1;   // 現在のアニメーションの再生フレーム
    float anim_frame_speed = 1.0f;

    //  プロレスラー用のアニメーション変数

    float security_anim_time;

    //  タイトルキャラクターが走っている感じの動きを付け足すための変数

    float Title_player_y_gravity;

    //  空を描画するような変数
    int skyBox;

    //int   anim_run = 0;   //  走るアニメーション
    //float anim_run_frame;
    //int   anim_run_max;
    ////  アニメーションの戻り値用の変数
    //int run_index;
    ////  立ち止まっているときのアニメーション変数
    //int   anim_idle = 0;
    //float anim_idle_frame;
    //int   anim_idle_max;
    ////  idleの戻り値
    //int idle_index;

    ////  車にぶつかった際のアニメーションの戻り値
    //int car_clash_index;

    ////  車にぶつかったときのアニメーション変数
    //int   anim_car_clash = 0;
    //float anim_car_clash_frame;
    //int   anim_car_clash_max;

    ////  川に溺れたときのアニメーション変数

    //int   river_die_index;
    //int   anim_river_die = 0;
    //float anim_river_die_frame;
    //int   anim_river_die_max;

    //  UFO用のモデル
    int ufo_model;

    //  車のモデル用変数
    int car_model[5];

    //  スコアのコイン用の画像変数
    int  coin_model;
    Coin coin_pos[COIN_NUM];

    //  エフェクト
    //  ゴールした際の花火のエフェクト
    int effect_congra;

    //  エフェクトの再生ハンドル
    int effect_congra_play = -1;
};

