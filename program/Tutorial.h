#pragma once
#include"Main.h"
#include "Base.h"

class Tutorial : public Base
{
public:
	//	プレイヤーの座標変数
	Vector2 Player_pos;


	//	プレイヤーの大きさ
	int Player_size;

	//	プレイヤーの画像
	int Player_image;

	//	プレイヤーがどこまで進むかを保存する変数
	Vector2 Player_move;

	//	プレイヤーの残機カウント
	int Player_count;

	//	プレイヤーの操作を同時に行えなくするための変数
	int move_time;
	//	プレイヤーの操作を同時に行えなくするための変数
	bool move;

	//	一定回数クリアするとゲームクリアとなるようにするための変数
	int goal_count;

	//	プレイヤーにあと何回ゴールすればいいか教えるための変数
	int goal_count_check;

	//	ゴールした場所を何度も使えないようにするための変数

	//	それぞれのゴールでゴールカウントが2回になったらゲームオーバーとする（同じゴールに行くとゲームオーバーとなる）
	int goal_dead_count[5];

	//	その際にわかりやすくするため色を変える
	int goal_juge_color[5];

	//	ゴール判定の変数
	bool goal;

	//	死んだときの変数
	//	残機が3個なので3個用意
	bool dead;

	//	プレイヤーが川に入ったら流される用の変数
		//	川に入ったかどうかの判定の変数
	bool river_in;
	//	流れるための変数
	float Player_flow;


	//	制限時間の変数
	int time;

	//	動き出したら制限時間が始まるための変数
	bool time_start;

	//	プレイヤーが川の上で丸太に乗っているときの変数
	bool wood_out;


	//	障害物
		//	右から出てくる用の変数
	Vector2 Enemy_pos_Right[9];
	//	左から出てくる敵の変数
	Vector2 Enemy_pos_Left[9];
	//	川の当たり判定（基本的には当たり判定は広くして一部だけ当たらなくしてそこをマルタとして通らせる）
	//	右から左へ流れていく川
	Vector2 Enemy_pos_River_Right[4];
	//	左から右へ流れていく川
	Vector2 Enemy_pos_River_Left[2];

	//	丸太（川の中でゲームオーバーとならない座標）
	//	右から左へ流れていく丸太
	Vector2 Enemy_pos_Safe_Right[2];
	//	左から右へ流れていく丸太
	Vector2 Enemy_pos_Safe_Left;


		//	Enemyの画像用変数
	int Car_red;
	int Car_black;
	int Car_green;
	int Car_blue;
	//	逆向きのものを作る
	int Car_red_oppose;
	int Car_black_oppose;
	int Car_green_oppose;
	int Car_blue_oppose;

	//	チュートリアル用の画像を読み込むための変数
	
	int Wood_image;
	int Wood_image2;

	int River_image;


	//	Ememyの大きさを設定
	int Enemy_size;



	void Init();
	void Update();
	void Draw();
	void Exit();
};