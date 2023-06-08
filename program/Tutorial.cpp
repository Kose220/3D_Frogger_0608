#include"Tutorial.h"
#include"DxLib.h"
#include"Hit.h"
#include"Main.h"
#include"Game.h"
#define PLAYER_MOV_SPEED	6.0f
#define PLAYER_ROT_SPEED	6.0f

void Tutorial::Init()
{
	//	プレイヤーの座標の初期化
	Player_pos.x = WINDOW_W / 2;
	Player_pos.y = WINDOW_H + 50;
	//	大きさの初期化
	//(当たり判定の大きさ)
	Player_size = 5;
	//	プレイヤーの画像の読み込み
	Player_image = LoadGraph("data/Game/2D/Flog.png");

	//	プレイヤーがどこまで進むかを保存する変数
	Player_move.x = WINDOW_W / 2;
	Player_move.y = WINDOW_H + 50;
	//	プレイヤーが何機あるかのカウント
	Player_count = 0;
	//	プレイヤーが同時に動けなくするための変数の初期化
	move_time = 0;
	//	動いていいか判定する変数
	move = true;
	//	プレイヤーのゴール判定
	goal = false;

	//	一度使ったゴールは使えなくするための変数
	for (int i = 0; i <= 4; i++)
	{
		goal_dead_count[i] = 0;
		//	ゴールした際にゴールの色を変える
		goal_juge_color[i] = 255;
	}

	//	ゴールカウントの初期化
	goal_count = 0;

	goal_count_check = 5;

	//	プレイヤーが敵にぶつかったときの処理
	dead = false;

	wood_out = false;

	//	川に入ったときの変数の初期化
	river_in = false;
	Player_flow = -5.0f;

	//	制限時間の変数の初期化
	time = 1800;
	time_start = false;


		for (int i = 0; i <= 8; i++)
	{
		//	右から出てくるよう
		Enemy_pos_Right[i].x = WINDOW_W;
		Enemy_pos_Right[i].y = WINDOW_W / 2;
		//	左から出てくるよう
		Enemy_pos_Left[i].x = WINDOW_W;
		Enemy_pos_Left[i].y = WINDOW_W / 2;

	}

	//	Enemyの画像
	Car_red = LoadGraph("data/Game/2D/car_red.png");
	Car_green = LoadGraph("data/Game/2D/car_green.png");
	Car_blue = LoadGraph("data/Game/2D/car_skyblue.png");
	Car_black = LoadGraph("data/Game/2D/car_black.png");
	//	逆向き
	Car_red_oppose = LoadGraph("data/Game/2D/car_red_gyaku.png");
	Car_green_oppose = LoadGraph("data/Game/2D/car_green_gyaku.png");
	Car_blue_oppose = LoadGraph("data/Game/2D/car_skyblue_gyaku.png");
	Car_black_oppose = LoadGraph("data/Game/2D/car_black_gyaku.png");


	//	Enemyの大きさの初期化
	Enemy_size = 10;

	//	重なってる敵をずらす処理
	//	右から出てくる敵
	Enemy_pos_Right[1].x =+200;
	Enemy_pos_Right[4].x = +200;
	Enemy_pos_Right[7].x = +250;

	Enemy_pos_Right[2].x = +400;
	Enemy_pos_Right[5].x = +400;
	Enemy_pos_Right[8].x = +450;

	//	左から出てくる敵
	Enemy_pos_Left[1].x = +200;
	Enemy_pos_Left[4].x = +200;
	Enemy_pos_Left[7].x = +250;

	Enemy_pos_Left[2].x = +400;
	Enemy_pos_Left[5].x = +400;
	Enemy_pos_Left[8].x = +450;

	//	X座標をずらすための処理　これがないと車が二列で走っているように見えるので
	Enemy_pos_Left[0].x += 50;
	Enemy_pos_Left[1].x += 50;
	Enemy_pos_Left[2].x += 50;

	//	川の座標の変数を初期化
	//	右流れの川
	Enemy_pos_River_Right[0].x = 900;
	Enemy_pos_River_Right[1].x = 0;

	//	左流れの初期化
	Enemy_pos_River_Left[0].x = 900;
	Enemy_pos_River_Left[1].x = 100;
	//	右流れの川
	Enemy_pos_River_Right[2].x = 1400;
	Enemy_pos_River_Right[3].x = 500;

	//	画像を読み込み
	River_image = LoadGraph("data/Game/2D/River.jpg");

	Wood_image = LoadGraph("data/Game/2D/wood.png");
	Wood_image2 = LoadGraph("data/Game/2D/wood_hantai.png");

}
void Tutorial::Update()
{
	//goal_count_check = 5 - goal_count;

	//if (time_start) {
	//	time--;
	//}
	move_time++;
	//	連打で動けないようにカウントをとる
	if (move_time >= 10)
	{
		move = true;
	}

	if (move)
	{
		//	プレイヤー操作処理
		if (PushHitKey(KEY_INPUT_LEFT))
		{
			Player_move.x -= 50;
			move_time = 0;
			move = false;
			//	動き出したら制限時間も動き出す
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_RIGHT))
		{
			Player_move.x += 50;
			move_time = 0;
			move = false;
			//	動き出したら制限時間も動き出す
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_UP))
		{
			Player_move.y -= 50;
			move_time = 0;
			move = false;
			//	動き出したら制限時間も動き出す
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_DOWN))
		{
			Player_move.y += 50;
			move_time = 0;
			move = false;
			//	動き出したら制限時間も動き出す
			time_start = true;
		}
		//	プレイヤー操作処理 WASDキー用
		if (PushHitKey(KEY_INPUT_A))
		{
			Player_move.x -= 50;
			move_time = 0;
			move = false;
			//	動き出したら制限時間も動き出す
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_D))
		{
			Player_move.x += 50;
			move_time = 0;
			move = false;
			//	動き出したら制限時間も動き出す
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_W))
		{
			Player_move.y -= 50;
			move_time = 0;
			move = false;
			//	動き出したら制限時間も動き出す
			time_start = true;
		}
		if (PushHitKey(KEY_INPUT_S))
		{
			Player_move.y += 50;
			move_time = 0;
			move = false;
			//	動き出したら制限時間も動き出す
			time_start = true;
		}

		//	画面外に行かないようにする処理
		if (Player_move.x >= WINDOW_W - 50)
		{
			Player_move.x = WINDOW_H - 50;

		}
		if (Player_move.x <= 50)
		{
			Player_move.x = 50;
		}
		if (Player_move.y >= WINDOW_H - 25)
		{
			Player_move.y = WINDOW_H - 25;
		}
	}
	if (Player_move.x >= Player_pos.x)
	{
		Player_pos.x += 5;
	}
	if (Player_move.y <= Player_pos.y)
	{
		Player_pos.y -= 5;
	}
	if (Player_move.x <= Player_pos.x)
	{
		Player_pos.x -= 5;
	}
	if (Player_move.y >= Player_pos.y)
	{
		Player_pos.y += 5;
	}


	//	川に入ったときの処理

	/*if (Player_pos.y <= 100)
	{
		Player_pos.y = 50;
	}*/

	//	ゴールした時の処理
	if (Player_pos.y <= 50)
	{

		if (Player_pos.x >= WINDOW_W / 2 + 300 && Player_pos.x <= WINDOW_W / 2 + 375)
		{

			//	一度ゴールしたら使えなくする
			goal_count++;
			//	プレイヤーを初期位置に戻す
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_H + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	ゴールしたら制限時間を初期化
			time = 1800;
			//	ゴールしたら制限時間を止める
			time_start = false;
			goal_dead_count[0]++;
			goal_juge_color[0] = 0;

		}

		else if (Player_pos.x >= WINDOW_W / 2 + 50 && Player_pos.x <= WINDOW_W / 2 + 125)
		{
			//	一度ゴールしたら使えなくする

			goal_count++;
			//	プレイヤーを初期位置に戻す
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_W + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	ゴールしたら制限時間を初期化
			time = 1800;
			//	ゴールしたら制限時間を止める
			time_start = false;

			goal_dead_count[1]++;
			goal_juge_color[1] = 0;
		}

		else if (Player_pos.x >= WINDOW_W / 2 - 175 && Player_pos.x <= WINDOW_W / 2 - 100)
		{
			//	一度ゴールしたら使えなくする

			goal_count++;
			//	プレイヤーを初期位置に戻す
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_H + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	ゴールしたら制限時間を初期化
			time = 1800;
			//	ゴールしたら制限時間を止める
			time_start = false;

			goal_dead_count[2]++;
			goal_juge_color[2] = 0;
		}


		else if (Player_pos.x >= WINDOW_W / 4 && Player_pos.x <= WINDOW_W / 4 + 75)
		{
			//	一度ゴールしたら使えなくする

			goal_count++;
			//	プレイヤーを初期位置に戻す
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_H + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	ゴールしたら制限時間を初期化
			time = 1800;
			//	ゴールしたら制限時間を止める
			time_start = false;

			goal_dead_count[3]++;
			goal_juge_color[3] = 0;
		}

		else if (Player_pos.x >= WINDOW_W / 10 && Player_pos.x <= WINDOW_W / 10 + 75)
		{

			goal_count++;
			//	プレイヤーを初期位置に戻す
			Player_pos.x = WINDOW_W / 2;
			Player_pos.y = WINDOW_H + 50;
			Player_move.x = WINDOW_W / 2;
			Player_move.y = WINDOW_H + 50;
			//	ゴールしたら制限時間を初期化
			time = 1800;
			//	ゴールしたら制限時間を止める
			time_start = false;

			goal_dead_count[4]++;
			goal_juge_color[4] = 0;
		}




		else
		{
			dead = true;
		}

	}

	//	時間切れでゲームオーバー　
	if (time <= -1)
	{
		dead = true;
	}
	if (goal_dead_count[0] >= 2)
	{
		dead = true;

	}

	if (goal_dead_count[1] >= 2)
	{
		dead = true;

	}
	if (goal_dead_count[2] >= 2)
	{
		dead = true;

	}
	if (goal_dead_count[3] >= 2)
	{
		dead = true;

	}
	if (goal_dead_count[4] >= 2)
	{
		dead = true;

	}

	if (goal_count >= 5)
	{
		goal = true;
	}
	//	敵の座標(Y座標)
	for (int i = 0; i <= 2; i++) {
		Enemy_pos_Right[i].y = 675;
		Enemy_pos_Left[i].y = 625;
	}
	for (int i = 3; i <= 5; i++)
	{
		Enemy_pos_Right[i].y = 525;
		Enemy_pos_Left[i].y = 575;
	}
	for (int i = 6; i <= 8; i++)
	{
		Enemy_pos_Right[i].y = 425;
		Enemy_pos_Left[i].y = 475;
	}

	//	敵の座標（X座標）
	for (int i = 0; i <= 8; i++)
	{
		//	車のスピードを調整する
		Enemy_pos_Right[i].x -= 5;
		Enemy_pos_Left[i].x += 5;
	}

	//	敵が画面外に行ったら反対方向から出てくる処理
	for (int i = 0; i <= 8; i++)
	{
		if (Enemy_pos_Right[i].x <= -50)
		{
			Enemy_pos_Right[i].x = WINDOW_W;
		}
		if (Enemy_pos_Left[i].x >= WINDOW_W + 50)
		{
			Enemy_pos_Left[i].x = -50;
		}
	}

	//	川の処理
	for (int i = 0; i <= 3; i++)
	{
		Enemy_pos_River_Right[i].x -= 5;
		if (Enemy_pos_River_Right[i].x <= -20)
		{
			Enemy_pos_River_Right[i].x = WINDOW_W + 500;
		}
	}
	for (int i = 0; i <= 1; i++)
	{
		Enemy_pos_River_Left[i].x += 5;
		if (Enemy_pos_River_Left[i].x >= WINDOW_W + 200)
		{
			Enemy_pos_River_Left[i].x = -500;
		}
	}

	//	当たり判定の処理
	for (int i = 0; i <= 8; i++)
	{
		if (CheckCircleHit(Player_pos, Player_size, Enemy_pos_Right[i], Enemy_size))
		{
			dead = true;
		}
		if (CheckCircleHit(Player_pos, Player_size, Enemy_pos_Left[i], Enemy_size))
		{
			dead = true;
		}
	}

	if (river_in)
	{
		Player_move.x += Player_flow;
	}

	//	川にいる時以外は流れないようにしておく
	{
		river_in = false;
	}


	//	川の当たり判定

	//	プレイヤーが丸太の上に乗っているときの処理
	//	1本目の川
	if (Player_pos.y <= 350 && Player_pos.y >= 250)
	{
		//	プレイヤーが川に流れる処理
		river_in = true;
		Player_flow = -5.0f;


		//	丸太の当たり判定
		if (Player_pos.x >= Enemy_pos_River_Right[0].x - 400 && Player_pos.x <= Enemy_pos_River_Right[0].x + 25)
		{
			wood_out = false;
		}

		if (Player_pos.y <= 350 && Player_pos.y >= 250)
		{
			if (Player_pos.x >= Enemy_pos_River_Right[1].x - 500 && Player_pos.x <= Enemy_pos_River_Right[1].x + 25)
			{
				wood_out = false;
			}
			else if (Player_pos.x >= Enemy_pos_River_Right[0].x - 400 && Player_pos.x <= Enemy_pos_River_Right[0].x + 25)
			{
				wood_out = false;
			}
			else
			{
				wood_out = true;
			}
		}
		//	一本目の川ここまで

	}
	//	二本目の川
	if (Player_pos.y <= 250 && Player_pos.y >= 150)
	{
		Player_flow = 5.0f;

		if (Player_pos.x <= Enemy_pos_River_Left[0].x + 500 && Player_pos.x >= Enemy_pos_River_Left[0].x - 25)
		{
			wood_out = false;

		}
		else if (Player_pos.x <= Enemy_pos_River_Left[1].x + 300 && Player_pos.x >= Enemy_pos_River_Left[1].x - 25)
		{
	wood_out = false;

		}
		else
		{
			wood_out = true;
		}

	}

	//	三本目の川
	if (Player_pos.y <= 150 && Player_pos.y >= 50)
	{
		Player_flow = -5.0f;

		if (Player_pos.x >= Enemy_pos_River_Right[2].x - 400 && Player_pos.x <= Enemy_pos_River_Right[2].x + 25)
		{
			wood_out = false;
		}
		else if (Player_pos.x >= Enemy_pos_River_Right[3].x - 500 && Player_pos.x <= Enemy_pos_River_Right[3].x + 25)
		{
			wood_out = false;
		}
		else
		{
			wood_out = true;
		}
	}


	//	木から墜ちたときの処理
	if (wood_out)
	{
		dead = true;
	}

	//	プレイヤーが死んだ際にリスポーン地点に戻すための処理
	if (dead)
	{
		//	一度ゴールしたら使えなくする
		//goal_count++;
		//	プレイヤーを初期位置に戻す
		Player_pos.x = WINDOW_W / 2;
		Player_pos.y = WINDOW_H - 25;
		Player_move.x = WINDOW_W / 2;
		Player_move.y = WINDOW_H +50;
		//	ゴールしたら制限時間を初期化
		//time = 1800;
		////	ゴールしたら制限時間を止める
		//time_start = false;
		//goal_dead_count[0]++;
		//goal_juge_color[0] = 0;
		dead = false;

		wood_out = false;

	}

}
void Tutorial::Draw()
{
	//	一番下
	DrawBox(0, 650, WINDOW_W, 700, GetColor(0, 0, 155), TRUE);
	//	下から2番目
	DrawBox(0, 600, WINDOW_W, 650, GetColor(155, 0, 0), TRUE);
	//	下から三番目
	DrawBox(0, 550, WINDOW_W, 600, GetColor(0, 155, 0), TRUE);
	//	上から三番目
	DrawBox(0, 500, WINDOW_W, 550, GetColor(0, 155, 155), TRUE);
	//	上から二番目
	DrawBox(0, 450, WINDOW_W, 500, GetColor(155, 155, 155), TRUE);
	//	一番上
	DrawBox(0, 400, WINDOW_W, 450, GetColor(0, 0, 0), TRUE);
	//---------------------------------------------------------------------------------
	//---------------------------------------------------------------------------------

	//	川の描画
	DrawRotaGraphF(WINDOW_W / 2, 350 / 2, 2.5f, TO_RADIAN(0), River_image, TRUE);

	////	丸太の描画
	//DrawRotaGraphF(enemy.Enemy_pos_River_Right[0].x, enemy.Enemy_pos_River_Right[0].y, 0.1f, TO_RADIAN(0), wood_image, TRUE);



	//	ゴール
	DrawLine(0, -50, WINDOW_W, 50, GetColor(0, 0, 255), TRUE);
	DrawLine(0, 50, WINDOW_W, 50, GetColor(0, 0, 255), TRUE);
	DrawBox(0, -50, WINDOW_W, 50, GetColor(0, 0, 255), TRUE);

	//	ゴールの場所を描画

	DrawBox(WINDOW_W / 2 + 375, 25, WINDOW_W / 2 + 300, 50, GetColor(goal_juge_color[0], 255, 255), TRUE);
	DrawBox(WINDOW_W / 2 + 125, 25, WINDOW_W / 2 + 50, 50, GetColor(goal_juge_color[1], 255, 255), TRUE);
	DrawBox(WINDOW_W / 2 - 175, 25, WINDOW_W / 2 - 100, 50, GetColor(goal_juge_color[2], 255, 255), TRUE);
	DrawBox(WINDOW_W / 4, 25, WINDOW_W / 4 + 75, 50, GetColor(goal_juge_color[3], 255, 255), TRUE);
	DrawBox(WINDOW_W / 10, 25, WINDOW_W / 10 + 75, 50, GetColor(goal_juge_color[4], 255, 255), TRUE);


	DrawString(WINDOW_W / 2, 50, "ゴール", GetColor(0, 255, 0), TRUE);


	for (int i = 0; i <= 8; i++)
	{
		DrawCircle(Enemy_pos_Right[i].x, Enemy_pos_Right[i].y, Enemy_size, GetColor(255, 255, 0), TRUE);
		DrawCircle(Enemy_pos_Left[i].x, Enemy_pos_Left[i].y, Enemy_size, GetColor(255, 255, 0), TRUE);

	}



	//	車の描画（右から出てくるもの）
	for (int i = 0; i < 8; i++) {
		DrawRotaGraphF(Enemy_pos_Right[i].x, Enemy_pos_Right[i].y, 0.25f, TO_RADIAN(0), Car_red, TRUE);

	}
	//DrawRotaGraphF(Enemy_pos_Right[0].x, Enemy_pos_Right[0].y, 0.25f, TO_RADIAN(0), Car_red, TRUE);
	//DrawRotaGraphF(Enemy_pos_Right[1].x, Enemy_pos_Right[1].y, 0.25f, TO_RADIAN(0), Car_black, TRUE);
	//DrawRotaGraphF(Enemy_pos_Right[2].x, Enemy_pos_Right[2].y, 0.25f, TO_RADIAN(0), Car_blue, TRUE);
	//DrawRotaGraphF(Enemy_pos_Right[3].x, Enemy_pos_Right[3].y, 0.25f, TO_RADIAN(0), Car_green, TRUE);
	//DrawRotaGraphF(Enemy_pos_Right[7].x, Enemy_pos_Right[7].y, 0.25f, TO_RADIAN(0), Car_red, TRUE);
	//DrawRotaGraphF(Enemy_pos_Right[4].x, Enemy_pos_Right[4].y, 0.25f, TO_RADIAN(0), Car_black, TRUE);
	//DrawRotaGraphF(Enemy_pos_Right[6].x, Enemy_pos_Right[6].y, 0.25f, TO_RADIAN(0), Car_blue, TRUE);
	//DrawRotaGraphF(Enemy_pos_Right[5].x, Enemy_pos_Right[5].y, 0.25f, TO_RADIAN(0), Car_green, TRUE);
	//DrawRotaGraphF(Enemy_pos_Right[8].x, Enemy_pos_Right[8].y, 0.25f, TO_RADIAN(0), Car_green, TRUE);

	////	車の描画（左から出てくるもの）
	//DrawRotaGraphF(Enemy_pos_Left[0].x, Enemy_pos_Left[0].y, 0.25f, TO_RADIAN(0), Car_red_gyaku, TRUE);
	//DrawRotaGraphF(Enemy_pos_Left[1].x, Enemy_pos_Left[1].y, 0.25f, TO_RADIAN(0), Car_black_gyaku, TRUE);
	//DrawRotaGraphF(Enemy_pos_Left[2].x, Enemy_pos_Left[2].y, 0.25f, TO_RADIAN(0), Car_blue_gyaku, TRUE);
	//DrawRotaGraphF(Enemy_pos_Left[3].x, Enemy_pos_Left[3].y, 0.25f, TO_RADIAN(0), Car_green_gyaku, TRUE);
	//DrawRotaGraphF(Enemy_pos_Left[7].x, Enemy_pos_Left[7].y, 0.25f, TO_RADIAN(0), Car_red_gyaku, TRUE);
	//DrawRotaGraphF(Enemy_pos_Left[4].x, Enemy_pos_Left[4].y, 0.25f, TO_RADIAN(0), Car_black_gyaku, TRUE);
	//DrawRotaGraphF(Enemy_pos_Left[6].x, Enemy_pos_Left[6].y, 0.25f, TO_RADIAN(0), Car_blue_gyaku, TRUE);
	//DrawRotaGraphF(Enemy_pos_Left[5].x, Enemy_pos_Left[5].y, 0.25f, TO_RADIAN(0), Car_green_gyaku, TRUE);
	//DrawRotaGraphF(Enemy_pos_Left[8].x, Enemy_pos_Left[8].y, 0.25f, TO_RADIAN(0), Car_green_gyaku, TRUE);

	//	丸太の描画
	DrawRotaGraphF(Enemy_pos_River_Right[0].x - 200, 300, 0.25f, TO_RADIAN(0), Wood_image, TRUE);
	DrawRotaGraphF(Enemy_pos_River_Right[1].x - 250, 300, 0.3f, TO_RADIAN(0), Wood_image, TRUE);

	DrawRotaGraphF(Enemy_pos_River_Left[0].x + 250, 200, 0.3f, TO_RADIAN(0), Wood_image2, TRUE);
	DrawRotaGraphF(Enemy_pos_River_Left[1].x + 150, 210, 0.25f, TO_RADIAN(0), Wood_image2, TRUE);

	DrawRotaGraphF(Enemy_pos_River_Right[2].x - 200, 100, 0.25f, TO_RADIAN(0), Wood_image, TRUE);
	DrawRotaGraphF(Enemy_pos_River_Right[3].x - 250, 100, 0.3f, TO_RADIAN(0), Wood_image, TRUE);

	DrawCircle(Player_pos.x, Player_pos.y, Player_size, GetColor(0, 0, 255), TRUE);
	DrawRotaGraphF(Player_pos.x, Player_pos.y, 0.035f, TO_RADIAN(0), Player_image, TRUE);
	SetFontSize(20);
	DrawFormatString(WINDOW_W - 350, WINDOW_H - 30, GetColor(0, 0, 255), "クリアまで必要なゴール回数あと%d", goal_count_check, true);
	DrawFormatString(0, WINDOW_H - 30, GetColor(0, 0, 255), "残り時間%d", time / 60, true);


}
void Tutorial::Exit()
{

}