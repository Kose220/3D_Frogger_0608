#pragma once

class Timer
{
public:
	float time;

	//  色を変えるよう飲変数
	float time_max;

	//  プレイヤーが動いてから制限時間が動き出すようにしておくための変数
	bool start_time;

	int color1;
	int color2;
	int color3;
	//  一定時間に達したときにゲームオーバーにする変数
	bool time_over;
	//  リザルト画面が上から降りてくるような感じにしたいのでY座標用の変数を用意
	float result_y;

	//  時間のバーが点滅するようにするための変数
	bool  time_pinch;
	float time_pinch_count;

	//  制限時間の時計用の変数
	//　針の画像用の変数
	int Time_Wach;
	//	秒針の角度
	float Rad;

	//	クリア後に制限時間が来た際にはタイトルに戻るようにしておく貯めの変数
	bool time_clear;

	void Init();     //������
	void Update();   //�X�V
	void Draw();     //�`��
	void Exit();     //�I������
	void GUI();      //!< GUI
};
