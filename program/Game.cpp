#include <DxLib.h>
#include "Main.h"
#include "Player.h"
#include "WallClass.h"
#include "Timer.h"
#include "Score.h"
#include "Life.h"
#include "UI.h"
#include "Start_camera.h"
#include "UFO.h"
#include "Security.h"
#include "Game.h"
#include"Minimap.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include"Tutorial.h"
#include<cmath>
using namespace std;

//---------------------------------------------------------------------------
//	Doxygen　総合概要
//---------------------------------------------------------------------------
//! @mainpage Go Home
//! @li ゲーム概要 \n
//! \n
//! @image html "..\..\data\Game\GoHome.png" width = 200px height = 150px
//! \n
//! @ref section_component

//! @page section_control　ゲームの操作



Player   player;
Wall     wall;
Timer    timer;
Score    score;
Life     life;
UI       ui;
Camera   camera;
UFO      ufo;
Seculity seculity;
Minimap minimap;
Tutorial tutorial;

////////////////////////////////
// 定数
////////////////////////////////
constexpr int CAR_NUM = 5;    // 車の台数
constexpr int WOOD_NUM = 10;   // 丸太の数
constexpr int WOOD_START_Z[] = {
	-145,
	-175,
	//  3番目のものだけ不要になったため一旦見えないところに配置
	30000,
	-235,
	-265,
	300,
	-175,
	//  上記と同じ理由
	30000,
	-235,
	-265,
};

//  半分にしたことにあたってもう半分追加する
constexpr int WOOD_START_Z_Re[] = {
	-160,
	-190,
	-30000,
	-250,
	-280,
	30000,
	30000,
	300000,
	-250,
	-280,

};

constexpr int CAR_Z[] = {
	-20,
	-40,
	-60,
	-80,
	-100,

};

//  道路の白線の座標（Z座標）
constexpr float WHITE_LINE_1[] = {
	-9,
	-29,
	-49,
	-69,

};
constexpr float WHITE_LINE_2[] = {
	-11,
	-31,
	-51,
	-71,

};   //

void Respawn()
{
	life.life_count -= 1;
	ui.ui_life_count -= 1;
	//  起き上がるアニメーションを指導するための変数
	player.player_Revival = true;
	//  座標を初期位置へ
	player.move_z = 20.0f;
	//	player.move_x = 0.0f;
	player.move_y = 1.0f;
	//  プレイヤーの向きを初期化
	player.radian_y = 0.0f;
	//  座標を初期化
	player.pos_z = 20.0f;
	//	player.pos_x = 0.0f;
	player.pos_y = 1.0f;


	//  ミニマップのアイコンを青に戻す
	minimap.map_icon_switch = true;

	//  上から復活させるためにY座標を上にする
	//player.pos_y = 20.0f;
}
//void PlayCount()
//{
//	// 1. ファイルを開く
//// 1-1. fstreamクラスのコンストラクタに指定
//	fstream file("sample.txt", ios::in);
//	// 1-2. fstreamクラスのopenメンバ関数を利用
//	//fstream file;
//	//file.open("sample.txt", ios::in);
//	// 1-3. ifstreamクラスを使用
//	//ifstream file("sample.txt");
//
//	// エラー処理: ファイルが正常に開けたかどうかチェック
//	if (!file.is_open())
//	{
//		cerr << "ERROR: cannot open file." << endl;
//		system("pause");
//		return EXIT_FAILURE;
//	}
//
//	// 2. ファイルからデータを取得
//	//int num;
//	//file >> num;
//
//	//float num2;
//	//file >> num2;
//
//	// ファイル終端まで１行ずつ読み込む
//	vector<string> file_lines;
//	while (true)
//	{
//		string line;
//		getline(file, line);
//		if (file.eof())
//			break;
//
//		file_lines.emplace_back(line);
//	}
//
//	// 3. ファイルを閉じる
//	file.close();
//
//	// 4. 取得したデータを処理
//	for (const auto& line : file_lines)
//	{
//		cout << line << endl;
//		// 取得したデータをstring型からint型へ変換
//		//int num = line;	// 上手くいかない
//		//try
//		//{
//		//	int num = stoi(line);	// stoi関数(int型にしたいstring型の変数);
//		//	cout << num << endl;
//		//}
//		//catch (const std::exception&)
//		//{
//		//}
//	}
//
////	system("pause");
//	return EXIT_SUCCESS;
//
//}

//---------------------------------------------------------------------------------
//	初期化処理
//---------------------------------------------------------------------------------
void Game::Init()
{
	//  タイトルのUIをずらすための変数
	Title_Slide = 0;
	//  タイトルのUIのX座標
	Title_Slide_x = 0;

	//  タイトルの画像用の変数の初期化
	Title_Player_x = WINDOW_W - 20;
	Title_Player_y = WINDOW_H - 80;
	Title_Ufo_x = WINDOW_W - 10;
	Title_Ufo_y = 50;
	Title_Ufo_x_plus = -0.5f;
	Title_Ufo_y_plus = 0.3f;
	Title_Ufo_rad = 0.0f;
	Title_Ufo_rad_plus = 0.005f;

	//   タイトル用の変数の初期化
	Title_Player = LoadGraph("data/Game/Title/Title_Player.png.crdownload ");
	Title_Ufo = LoadGraph("data/Game/Title/Title_Ufo.png");
	Title_Town = LoadGraph("data/Game/Title/Title_Town.jpg.crdownload");
	Title_House = LoadGraph("data/Game/Title/Title_House.png");

	//  ゲームオーバー時のイラスト変数の初期化
	//  時間切れ時の背景
	Time_Over_haikei_fire = LoadGraph("data/Game/Title/Fire.png");
	Time_Over_ilust_hansei = LoadGraph("data/Game/Title/hansei_koukai_man.png");
	Time_Over_ilust_sekkyou = LoadGraph("data/Game/Title/pose_mesen_uekara_woman.png");

	River_Over_ilust = LoadGraph("data/Game/Title/oboreru.png");
	River_Over_ilust_safe = LoadGraph("data/Game/Title/kyuujo_ukiwa_tasukaru.png");

	int goal_time = 0;

	// 仮モデルの読み込み
	//  ネズミのモデルの読み込み？
	model_ = MV1LoadModel("data/Game/Anime/model.mv1");
	//  １および２の処理
	//  ネズミの歩きモデルを読み込む
	model_anim_run = MV1LoadModel("data/Game/Anime/Walk.mv1");
	model_anim_idle = MV1LoadModel("data/Game/Anime/Idle.mv1");
	model_anim_car_clash = MV1LoadModel("data/Game/Anime/Dying.mv1");
	model_anim_river_die = MV1LoadModel("data/Game/Anime/River_Dying.mv1");
	model_anim_stand_up = MV1LoadModel("data/Game/Anime/Stand Up.mv1");
	model_anim_happy_dance = MV1LoadModel("data/Game/Anime/Happy.mv1");
	model_anim_security_stand_up = MV1LoadModel("data/Game/Anime/Security_Stand_Up.mv1");
	model_anim_dead_cry = MV1LoadModel("data/Game/Anime/Cry Idle.mv1");

	if (anim_index != -1) {
		// 現在のアニメーションのインデックスが-1（初期値）でなければ、
		// すでにアニメーションがアタッチされているということなので
		// デタッチをする
		MV1DetachAnim(model_, anim_index);
	}
	anim_index = MV1AttachAnim(model_, 1, model_anim_idle);
	anim_max_frame = MV1GetAttachAnimTotalTime(model_, anim_index);
	MV1SetAttachAnimTime(model_, anim_index, anim_max_frame);
	anim_frame = 0.0f;

	//  死んでいるか生きているかの変数の初期化
	live = true;
	dead = false;

	//    anim_time = 70.0f;
	player.anim_time = 70.0f;
	//  状態用変数
	status_ = STATUS_IDLE;

	//	プロレスラーの読みこみ
	security_model = MV1LoadModel("data/Game/Seculity/Seculity.mv1");

	//  プロレスラーのアニメーションの読み込み
	//seculity_anim_idle =
	//    MV1LoadModel("data/Game/Anime/")
	security_anim_move = MV1LoadModel("data/Game/Anime/Seculity/Seculity_Run.mv1");
	security_anim_attack = MV1LoadModel("data/Game/Anime/Seculity/Seculity_Attack.mv1");
	security_anim_idle = MV1LoadModel("data/Game/Anime/Seculity/Idle.mv1");

	//	かりめも　ファイル処理　eofがtrueになる

		if (seculity_anim_index != -1) {
		MV1DetachAnim(security_model, seculity_anim_index);
	}
	seculity_anim_index = MV1AttachAnim(security_model, 1, security_anim_idle);
	seculity_anim_max_frame = MV1GetAttachAnimTotalTime(security_model, seculity_anim_index);
	MV1SetAttachAnimTime(security_model, seculity_anim_index, seculity_anim_max_frame);

	//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－------------------------------------------------------------

	//  クラスの中身の初期化
	player.Init();
	wall.Init();
	timer.Init();
	score.Init();
	life.Init();
	ui.Init();
	camera.Init();
	ufo.Init();
	seculity.Init();
	minimap.Init();
	tutorial.Init();
	//  車の変数を初期化
	for (int i = 0; i < CAR_NUM; i++) {
		//        car_x[i] = GetRand(-200);
		car_z[i] = CAR_Z[i];
	}
	//  ランダムもいいが偏りが発生するため一つ一つばらけさせる
	car_x[0] = -50;
	car_x[1] = 30;
	car_x[2] = 90;
	car_x[3] = 60;
	car_x[4] = -100;

	//	車を動かす用の変数
	for (int i = 0; i < 6; i++) {
		car_x_plus[i] = 1.5f;
	}
	//  丸太の座標の初期化
	//for(int i = 0; i < 5; i++) {
	//    wood_x[i] = 0;
	//}
	//for(int i = 5; i <= 9; i++) {
	//    wood_x[i] = 150;
	//}
	for (int i = 0; i < WOOD_NUM; ++i) {
		//int start_pos_x = (i < 5) ? 0 : 150;
		//wood_x[i]       = start_pos_x;
		int start_pos_x = 0;
		if (i >= 5) {
			start_pos_x = 150;
		}
		wood_x[i] = start_pos_x;
		wood_z[i] = WOOD_START_Z[i];
		wood_x_re[i] = GetRand(-150);
		wood_z_re[i] = WOOD_START_Z_Re[i];
	}

	//  プレイヤーの当たり判定
	car_dead = false;

	// ゴールBGMが何度も鳴らないためにする用の変数
	goal_adjustment = 0;

	//	リスポーン地点までの距離
	Respawn_Distance_z = 0.0f;

	//  モデルの読み込み
	//  車の読み込み
	car_model[0] = MV1LoadModel("data/Game/Car/Car.mv1");
	//  UFOの読み込み
	ufo_model = MV1LoadModel("data/Game/UFO/UFO.mv1");
	//  プロレスラーの読み込み

	for (int i = 1; i < CAR_NUM; i++) {
		car_model[i] = MV1DuplicateModel(car_model[0]);
	}
	//  コインの素材を読み込む

	coin_model = MV1LoadModel("data/Game/Score/coin.mv1");
	//        coin_model = MV1LoadModel("data/Game/Score/coin.mv1");
		 // コインモデルをコピー
	for (int i = 0; i < 5; i++)
	{
		coin_models[i] = MV1DuplicateModel(coin_model);
	}

	//	コインの角度変数の初期化
	Coin_Rota_x = 90;

	//  コイン０番目をコピーし増やす
	// for(int i = 1; i < COIN_NUM; i++) {
	//    coin_model = MV1DuplicateModel(car_model[0]);
	//}
	//  川の当たり判定
	river_dead = false;

	//  丸太の判定
	//  wood_safeがファルスになった瞬間川の当たり判定がONになってしまう。
	//  乗っているうちはfalse乗っていない場合はtrue
	wood_safe = true;

	//  セーフエリアの石の座標
	safe_stone_x = -90;
	safe_stone_z = -220;


	//  ゴール座標の設定
	goal_line_x = 0;
	goal_line_z = 0;

	//  ゲームオーバー画面が遅れて出てくるための変数
	over_time = 0;

	//  川に溺れたときに上下に動くための変数
	river_out_y = 1;
	//  タイトル変数の初期化
	title = true;

	//  タイトル画面を横にずらす貯めの処理
	title_x = 0;

	title_blend = 0;
	//  タイトルの文字をぼかすために変数を減らす用のもの
	title_blend_hiku = 3;
	//  ゲームを始める用の変数
	game = false;

	//  ゴール判定変数の初期化
	goal = false;

	goal_anim = false;

	goal_count = 0;

	//	ステージを変える際のカットイン用の変数
	stage_change = false;

	//  無敵状態用の変数
	no_die = true;

	//  初期化用の変数
	init = false;

	InitTime = 0;

	//  エフェクトの初期化
	effect_congra = LoadEffekseerEffect("data/Game/Effects/Simple_Turbulence_Fireworks.efkefc");

	//	タイトルのプレイヤーの走る動きのための変数
	////  エフェクトの位置の初期化
	//SetPosPlayingEffekseer3DEffect(effect_congra_play, pos_x, pos_y, pos_z - 50);

	//  カメラの向きを変更するための変数
	camera_x = 0.0f;
	camera_z = 0.0f;
	//  カメラを上から見下ろすと起用の変数（向きもある）
	camera_y = 25.0f;
	camera_y_radian = 5.0f;
	//  BGMの初期化
	Title_BGM = LoadSoundMem("data/Game/BGM/Title.mp3");
	Game_BGM = LoadSoundMem("data/Game/BGM/GameMain.mp3");
	Over_BGM = LoadSoundMem("data/Game/BGM/GaneOver.mp3");
	Clear_BGM = LoadSoundMem("data/Game/BGM/Clear.mp3");

	//  SEの初期化
	Car_Clacshon_SE = LoadSoundMem("data/Game/SE/車のクラクション.mp3");
	River_SE = LoadSoundMem("data/Game/SE/河原.mp3");
	Car_Clash_SE = LoadSoundMem("data/Game/SE/カークラッシュ.mp3");
	Car_Slue_SE = LoadSoundMem("data/Game/SE/車通過1.mp3");
	Silen_SE = LoadSoundMem("data/Game/SE/救急車サイレン1.mp3");
	River_Die_SE = LoadSoundMem("data/Game/SE/水中で溺れる.mp3");

	//	せせらぎの音量変数
	River_SE_Volume = 0;

	//	距離図るよう変数
	River_distance = 0.0f;

	//  時計の針の変数

	//  BGMを開始させるための変数
	Title_BGM_Start = true;
	Game_BGM_Start = false;
	Over_BGM_Start = false;
	Clear_BGM_Start = false;

	//  オブジェクトカメラの作成    月曜に聞く
	//auto o = Scene::CreateObject<Object>();
	//o->SetName(u8"テストカメラ");14
	SetCameraNearFar(7.5f, 1500.0f);
	//// カメラコンポーネントを追加
	//auto camera = o->AddComponent<ComponentCamera>();
	//  カメラのポジションとどこを見るかの設定
	Title_player_y_gravity = 0.0f;

	//	空の変数の用意
	//DxLib_Init();
	//SetDrawScreen(DX_SCREEN_BACK);
	//SetUseZBuffer3D(TRUE);
	//SetWriteZBuffer3D(TRUE);

	//// Set the camera position
	//SetCameraPositionAndTarget_UpVecY(VGet(0, 0, -5), VGet(0, 0, 0));

	//// Create the skybox texture
	//skyBox = MakeBox3D(VGet(-100, -100, -100), VGet(100, 100, 100), TRUE);
	//SetMaterialUseVertNormal(FALSE); // Ignore normals
	//ChangeMaterialParam(skyBox, MATERIALPARAM_DIFFUSERED, 0);
	//ChangeMaterialParam(skyBox, MATERIALPARAM_DIFFUSEGREEN, 0);
	//ChangeMaterialParam(skyBox, MATERIALPARAM_DIFFUSEBLUE, 1);
}
//---------------------------------------------------------------------------------
//	更新処理
//---------------------------------------------------------------------------------
void Game::Update()
{
	Title_player_y_gravity += 0.25f;

	//  タイトルを横にスライドさせる
	Title_Slide_x += Title_Slide;

	if (title) {

		tutorial.Update();
		////  タイトルを横にスライドさせる
		//Title_Slide_x += Title_Slide;


		switch (bgm_status) {
		case START_BGM:
			StopSoundMem(Over_BGM);

			ChangeVolumeSoundMem(100, Title_BGM);

			PlaySoundMem(Title_BGM, DX_PLAYTYPE_LOOP);
			Title_BGM_Start = false;
			bgm_status = -1;
			break;
		}

		//if (CheckKeyInput(KEY_INPUT_A))
		//{
		//	Title_player_y_temp = -2.0f;
		//}
		//Title_Player_y += Title_player_y_temp;
		//Title_player_y_temp += 0.2f;

		//if (Title_Player_y <WINDOW_H - 200)
		//{
		//	Title_Player_y = WINDOW_H - 200;
		//}

		PlayCount_Switch = false;

		if (CheckHitKey(KEY_INPUT_I)) {
			PlayCount_Switch = true;
		}

		if (CheckHitKey(KEY_INPUT_SPACE)) {
			//  スライドのスピード
			Title_Slide = 20;
			StopSoundMem(Title_BGM);
			title_rule = true;
			bgm_status = MAIN_BGM;
			//			PlayCount();
					// 1. ファイルを開く
			// 1-1. fstreamクラスのコンストラクタに指定
						//fstream file("sample.txt", ios::in);
						//// 1-2. fstreamクラスのopenメンバ関数を利用
						////fstream file;
						////file.open("sample.txt", ios::in);
						//// 1-3. ifstreamクラスを使用
						////ifstream file("sample.txt");

						//// エラー処理: ファイルが正常に開けたかどうかチェック
						//if (!file.is_open())
						//{
						//	cerr << "ERROR: cannot open file." << endl;
						//	system("pause");
						//	return EXIT_FAILURE;
						//}

						//// 2. ファイルからデータを取得
						////int num;
						////file >> num;

						////float num2;
						////file >> num2;

						//// ファイル終端まで１行ずつ読み込む
						//vector<string> file_lines;
						//while (true)
						//{
						//	string line;
						//	getline(file, line);
						//	if (file.eof())
						//		break;

						//	file_lines.emplace_back(line);
						//}

						//// 3. ファイルを閉じる
						//file.close();

						//// 4. 取得したデータを処理
						//for (const auto& line : file_lines)
						//{
						//	cout << line << endl;
						//	// 取得したデータをstring型からint型へ変換
						//	//int num = line;	// 上手くいかない
						//	//try
						//	//{
						//	//	int num = stoi(line);	// stoi関数(int型にしたいstring型の変数);
						//	//	cout << num << endl;
						//	//}
						//	//catch (const std::exception&)
						//	//{
						//	//}
						//}

						////	system("pause");
						//return EXIT_SUCCESS;

		}
		if (Title_Slide_x >= WINDOW_W) {
			title = false;
			//	ストーリー説明のUIが止まれるようにしておく（流れていかないようにしておく）
			Title_Slide = 0;
		}

		title_blend += title_blend_hiku;
		if (title_blend >= 255) {
			title_blend_hiku *= -1;
		}
		if (title_blend <= 0) {
			title_blend_hiku *= -1;
		}

		//  タイトルのイラストを動かす用の処理
		if (Title_Ufo_y >= 55) {
			Title_Ufo_y_plus *= -1;
		}

		else if (Title_Ufo_y <= 45) {
			Title_Ufo_y_plus *= -1;
		}
		if (Title_Ufo_x <= 0) {
			Title_Ufo_x_plus *= -1;
		}
		else if (Title_Ufo_x >= WINDOW_W) {
			Title_Ufo_x_plus *= -1;
		}
		//  UFOのイラスト
		Title_Ufo_x += Title_Ufo_x_plus;
		Title_Ufo_y += Title_Ufo_y_plus;

		//	ＵＦＯの角度を変更するための処理
		Title_Ufo_rad += Title_Ufo_rad_plus;

		if (Title_Ufo_rad >= 0.25f)
		{
			Title_Ufo_rad_plus *= -1;
		}
		if (Title_Ufo_rad <= -0.25f)
		{
			Title_Ufo_rad_plus *= -1;
		}

		//  プレイヤーのイラストの処理
		if (Title_Player_x <= 300) {
			Title_Player_x = WINDOW_W + 50;
		}
		//  UFOのイラスト
		Title_Player_x -= 1.0f;
	}

	//  タイトルの次の画面
	if (title_rule) {
		if (CheckHitKey(KEY_INPUT_RETURN)) {
			title_rule = false;
			game = true;
			PlayCount++;
			stage_status = FIRST_STAGE;
			//	川のせせらぎ音を最初の段階でループ処理を作っておく
			PlaySoundMem(River_SE,DX_PLAYTYPE_LOOP);
		}

	}

	if (game) {

			ChangeVolumeSoundMem(River_SE_Volume, River_SE);



		//  エフェクトの再生
		//if(CheckHitKey(KEY_INPUT_SPACE) && IsEffekseer3DEffectPlaying(effect_congra_play) == -1) {
		//    //
		//    effect_congra_play = PlayEffekseer3DEffect(effect_congra);
		//    SetPosPlayingEffekseer3DEffect(effect_congra_play, 0, 0, -460);
		//}
		/*    if(player.pos_z <= -470) {
			effect_congra_play = PlayEffekseer3DEffect(effect_congra);
			SetPosPlayingEffekseer3DEffect(effect_congra_play, 0, 0, -460);
		}*/

		switch (bgm_status) {
		case MAIN_BGM:

			ChangeVolumeSoundMem(100, Game_BGM);
			PlaySoundMem(Game_BGM, DX_PLAYTYPE_LOOP);
			//  １回しか回さないようにする
			bgm_status = -1;
			//	ゴールした時のBGM処理
			break;
		}
		//  タイトル画面がはけたらプレイヤーが動けるようにする

		title_x -= 20;
		if (title_x < -WINDOW_W) {
			player.move_juge = true;
		}

		// 仮モデルの設定
		MV1SetPosition(model_, { player.pos_x, player.pos_y, player.pos_z });
		MV1SetRotationXYZ(model_, { 0.0f, player.radian_y, 0.0f });
		MV1SetScale(model_, { 0.05f, 0.05f, 0.05f });

		//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－------------------------------------------------------------
		//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－------------------------------------------------------------
		//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－------------------------------------------------------------
		//  アニメーションの更新
		//  アニメーションの切り替え用の時間変数
		player.anim_time++;

		//        if(live) {
		int pre_status = status_;   // ひとつ前の状態を保存
		switch (status_) {
		case STATUS_IDLE:
			//  待機状態に移ったらプレイヤーを操作できるようにする
			player.Revival_move = true;
			//  アニメーションごとにフレームスピードを変える
			anim_frame_speed = 0.5f;

			if (player.anim_juge) {
				// プレイヤーが動いたとき
				status_ = STATUS_MOVE;
				next_anim = model_anim_run;
			}
			if (car_die) {
				//  死んでしまった時のアニメーション中は操作できないようにする
				// player.player_Revival = false;
				PlaySoundFile("data/Game/SE/カークラッシュ.mp3", DX_PLAYTYPE_BACK);
				status_ = STATUS_CAR_DAMAGE;
				next_anim = model_anim_car_clash;
			}
			if (river_die) {
				//  死んでしまった時のアニメーション中は操作できないようにする
				//          player.player_Revival = false;
				PlaySoundFile("data/Game/SE/水中で溺れる.mp3", DX_PLAYTYPE_BACK);
				status_ = STATUS_RIVER_DAMAGE;
				next_anim = model_anim_river_die;
			}
			//  ゴール時のハッピーアニメーション
			if (goal) {
				player.move_juge = false;
				status_ = STATUS_HAPPY_DANCE;
				next_anim = model_anim_happy_dance;
			}

			break;
			//  上記の処理同様に今やっている処理以外の物が来た時の条件式を作って次に備える
		case STATUS_MOVE:
			//  アニメーションごとにフレームスピードを変える
			anim_frame_speed = 0.5f;

			if (player.anim_time >= 45.0f) {
				// アニメーション終了後に待機状態へ
				status_ = STATUS_IDLE;
				next_anim = model_anim_idle;
			}
			if (car_die) {
				//  死んでしまった時のアニメーション中は操作できないようにする
				//     player.player_Revival = false;
				status_ = STATUS_CAR_DAMAGE;
				next_anim = model_anim_car_clash;
				PlaySoundFile("data/Game/SE/カークラッシュ.mp3", DX_PLAYTYPE_BACK);
			}
			if (river_die) {
				//  死んでしまった時のアニメーション中は操作できないようにする
				player.move_juge = false;
				PlaySoundFile("data/Game/SE/水中で溺れる.mp3", DX_PLAYTYPE_BACK);
				//    player.player_Revival = false;
				status_ = STATUS_RIVER_DAMAGE;
				next_anim = model_anim_river_die;
			}
			//if(player.security_attack) {
			//    status_   = STATUS_CAR_DAMAGE;
			//    next_anim = model_anim_car_clash;
			//}

			if (player.security_attack) {
				//         player.move_juge       = false;
				status_ = STATUS_SECURITY_DAMEGE;
				player.Revival_move = false;
				player.security_attack = false;
				//  車にひかれたようと倒されるようアニメーションを兼用にする
				next_anim = model_anim_car_clash;
			}
			if (goal) {
				player.move_juge = false;
				status_ = STATUS_HAPPY_DANCE;
				next_anim = model_anim_happy_dance;
			}

			break;
			//  Carダメージとしているがプロレスラーに攻撃された時のダメージモーションと一時兼用とする
		case STATUS_CAR_DAMAGE:
			//  アニメーションごとにフレームスピードを変える
			anim_frame_speed = 1.0f;
			//  ゲームオーバー画面を切り替え（ライフが残っていたら画面は変わらず）
			over_status = CAR_OVER;

			//  フレームが満タンになったら（アニメーション一周）したら待機状態に戻す

			if (player.player_Revival) {
				status_ = STATUS_STAND_UP;
				next_anim = model_anim_stand_up;
			}

			break;
		case STATUS_RIVER_DAMAGE:
			//  アニメーションごとにフレームスピードを変える
			anim_frame_speed = 1.0f;
			//  ゲームオーバー画面を切り替え（ライフが残っていたら画面は変わらず）
			over_status = RIVER_OVER;

			player.move_y -= 0.1f;

			if (player.player_Revival) {
				status_ = STATUS_STAND_UP;
				next_anim = model_anim_stand_up;
			}

			break;

		case STATUS_STAND_UP:
			//  プレイヤーがリスポーンし起き上がった次のアニメーション
			if (anim_frame >= anim_max_frame - 2) {
				if (life.life_over)
				{
					status_ = STATUS_DEAD_CRY;
					next_anim = model_anim_dead_cry;
					//					player.player_Revival = false;

				}
				else {
					status_ = STATUS_IDLE;
					next_anim = model_anim_idle;
					player.player_Revival = false;
				}
			}
			break;

		case STATUS_SECURITY_DAMEGE:
			anim_frame_speed = 2.0f;

			if (anim_frame >= anim_max_frame - 2) {
				player.security_attack = false;
				status_ = STATUS_SECURITY_STAND_UP;
				next_anim = model_anim_security_stand_up;
			}
			break;

		case STATUS_SECURITY_STAND_UP:
			anim_frame_speed = 2.0f;

			//  プロレスラーに攻撃されて立ち上がる時の処理
			if (anim_frame >= anim_max_frame - 2) {
				player.security_attack = false;
				status_ = STATUS_IDLE;
				next_anim = model_anim_idle;
				//  プレイヤーから離れる
				seculity.pos_x = GetRand(320) - 150;
			}
			break;
		case STATUS_DEAD_CRY:
			//	ループさせる
			if (anim_frame >= anim_max_frame - 2) {
				anim_frame = 0;
			}
			break;
		case STATUS_HAPPY_DANCE:
			//	動けないように固定する
			player.move_x = player.pos_x;
			player.move_z = player.pos_z;
			player.move_y = player.pos_y;

			//	アニメーションを1周ほどさせたらIdleに戻す
			if (anim_frame >= anim_max_frame - 2) {
				anim_frame = 0;
			}
			if (CheckHitKey(KEY_INPUT_F)) {
				
					status_ = STATUS_IDLE;
					next_anim = model_anim_idle;
				}
		}

		if (status_ != pre_status) {
			// アニメーションが切り替わった１フレーム目
			//  1. アニメーションのDetach
			//  MV1DetachAnim(モデル, 現在のアニメインデックス);
			MV1DetachAnim(model_, anim_index);
			//  2. アニメーションのAttach
			//  MV1AttachAnim(モデル, 0/1, アニメーションモデル);
			MV1AttachAnim(model_, 1, next_anim);
			//  3. アニメーションの長さ取得
			//  MV1GetAttachAnimTotalTime(モデル, 現在のアニメインデックス);
			anim_max_frame = MV1GetAttachAnimTotalTime(model_, anim_index);
			//  4. アニメーションの再生秒数を0にする
			//  変数を初期化
			anim_frame = 0;
		}
		MV1SetAttachAnimTime(model_, anim_index, anim_frame);
		anim_frame += anim_frame_speed;
		if (anim_frame >= anim_max_frame) {
			if (car_die) {
				Respawn();
				//	止まっている車の動きを再び動き出させる
				for (int i = 0; i < 6; i++) {
					car_x_plus[i] = 1.5f;
				}
				car_die = false;
				//  ゲームオーバー用の変数　ライフが残っていたら何も起こらない
				car_dead = true;
				//status_   = STATUS_MOVE;
				//next_anim = model_anim_run;
			}
			if (river_die) {
				Respawn();
				river_die = false;
				//  ゲームオーバー用の変数　ライフが残っていたら何も起こらない
				river_dead = true;
				//status_    = STATUS_MOVE;
				//next_anim  = model_anim_run;
			}
			anim_frame = 0.0f;
		}

		//  プロレスラーのアニメ処理

		int security_pre_status = security_status;   // ひとつ前の状態を保存
		int security_next_anim = -1;                // 次のアニメーション用モデル
		if (security_move_juge) {
			security_status = SECULITY_ATTACK;
			security_next_anim = security_anim_attack;
		}

		switch (security_status) {
		case SECULITY_IDLE:
			//			Seculity_Anim_frame = 1.0f;
			Seculity_Anim_frame_speed = 1.0f;
			//if (seculity.radian >= 5.0f) {
			//	security_status = SECULITY_MOVE;
			//	security_next_anim = security_anim_move;
			//}
			//if (security_move_juge)
			//{
			//	security_status = SECULITY_MOVE;
			//	security_next_anim = security_anim_move;
			//}

			break;

			//case SECULITY_MOVE:
			//	Seculity_Anim_frame_speed = 0.25f;

			//	if (player.pos_x <= seculity.pos_x + 2 && player.pos_z < -460 || player.pos_x >= seculity.pos_x - 2 && player.pos_z < -460) {
			//		security_status = SECULITY_ATTACK;
			//		security_next_anim = security_anim_attack;
			//	}
			//	//if (security_move_juge != true)
			//	//{
			//	//	security_status = security_anim_idle;
			//	//	security_next_anim = security_anim_idle;

			//	//}
			//	if (Seculity_Anim_frame >= seculity_anim_max_frame)
			//	{
			//		security_status = security_anim_idle;
			//		security_next_anim = security_anim_idle;

			//	}

			//	break;
		case SECULITY_ATTACK:
			if (Seculity_Anim_frame >= seculity_anim_max_frame / 2)
			{
				security_status = security_anim_idle;
				security_next_anim = security_anim_idle;
				Seculity_Anim_frame = 0;

			}
			break;

		}
		if (security_status != security_pre_status) {
			// アニメーションが切り替わった１フレーム目
			//  1. アニメーションのDetach
			//  MV1DetachAnim(モデル, 現在のアニメインデックス);
			MV1DetachAnim(security_model, seculity_anim_index);
			//  2. アニメーションのAttach
			//  MV1AttachAnim(モデル, 0/1, アニメーションモデル);
			MV1AttachAnim(security_model, 1, security_next_anim);
			//  3. アニメーションの長さ取得
			//  MV1GetAttachAnimTotalTime(モデル, 現在のアニメインデックス);
			anim_max_frame = MV1GetAttachAnimTotalTime(security_model, seculity_anim_index);
			//  4. アニメーションの再生秒数を0にする
			//  変数を初期化
			Seculity_Anim_frame = 0;
		}
		MV1SetAttachAnimTime(security_model, seculity_anim_index, Seculity_Anim_frame);
		Seculity_Anim_frame += Seculity_Anim_frame_speed;


		//  プレイヤーが死んでしまったときアニメーションのフレームがmaxまで行ったら初期位置に戻す

		//  アニメーションが一定時間したら待機状態のアニメーションに戻す
		//    if(player.anim_time >= 60.0f) {
		//        idle = true;
		//        run  = false;
		//    }
		//    else if(player.anim_time <= 59.0f) {
		//        //            anim_run  = MV1AttachAnim(model_, 1, model_anim, FALSE);
		//        //    //   car_clash = false;
		//        idle = false;
		//        run  = true;
		//    }
		//    //  待機状態の処理
		//    if(idle) {
		//        //  ひかれた際のアニメーションのフレームを戻しておく
		//        MV1SetAttachAnimTime(model_, idle_index, anim_idle_frame);
		//        anim_idle_frame += 0.5f;
		//        if(anim_idle_frame >= anim_idle_max) {
		//            anim_idle_frame = 0.0f;
		//        }
		//    }
		//    //            MV1SetAttachAnimTime(model_, model_anim_idle, anim_idle_frame);
		//    //}

		//    if(run) {
		//        MV1SetAttachAnimTime(model_, run_index, anim_run_frame);

		//        anim_run_frame += 0.5f;

		//        // 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
		//        if(anim_run_frame >= anim_run_max) {
		//            anim_run_frame = 0.0f;
		//        }
		//    }
		//}
		//if(dead)   //  プレイヤーがやられてしまったときのアニメーション
		//{
		//    //  車にぶつかったときのアニメーションの処理
		//    if(car_die) {
		//        // 　ひかれたときのアニメーション以外はすべて止める
		//        idle = false;
		//        run  = false;
		//        anim_car_clash_frame += 1.0f;
		//        MV1SetAttachAnimTime(model_, car_clash_index, anim_car_clash_frame);
		//        if(anim_car_clash_frame >= anim_car_clash_max) {
		//            //  Reにより座標を初期化
		//            Respawn();
		//            live                 = true;
		//            dead                 = false;
		//            anim_car_clash_frame = 0.0f;
		//            car_dead             = true;
		//        }nfjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj
		//    }
		//    if(river_die) {
		//        idle = false;
		//        run  = false;
		//        anim_river_die_frame += 1.0f;
		//        MV1SetAttachAnimTime(model_, anim_river_die_max, anim_car_clash_frame);
		//        if(anim_river_die_frame >= anim_river_die_max) {
		//            Respawn();
		//            live                 = true;
		//            dead                 = false;
		//            anim_car_clash_frame = 0.0f;
		//        }
		//    }

		//  動いているときのアニメーションの処理
		//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－------------------------------------------------------------
		//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－------------------------------------------------------------
		//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－------------------------------------------------------------

		//  車の座標
		for (int i = 0; i < CAR_NUM; i++) {
			MV1SetPosition(car_model[i], { car_x[i], 0, car_z[i] });
			//MV1SetRotationXYZ(car_model[i], {0, 5, 0});
			MV1SetRotationXYZ(car_model[i], { 0, TO_RADIAN(-90), 0 });
			MV1SetScale(car_model[i], { 0.05f, 0.05f, 0.05f });
		}
		//        MV1SetPosition(coin_model,coin_x, 3, coin_z);
		//  コインの座標
		//	コインが回っているように見せる用の変数
		Coin_Rota_x+= 3.0f;
		for (int i = 0; i < COIN_NUM; i++) {
			MV1SetPosition(coin_models[i], { score.coin_x[i], 3, score.coin_z[i] });
			MV1SetRotationXYZ(coin_models[i], { TO_RADIAN(Coin_Rota_x), 0,TO_RADIAN(90) });
			MV1SetScale(coin_models[i], { 0.03f, 0.03f, 0.03f });
		}
		MV1SetPosition(coin_model, { score.coin_x[0], 3, score.coin_z[0] });
		MV1SetRotationXYZ(coin_model, { TO_RADIAN(90), 0,TO_RADIAN(90) });
		MV1SetScale(coin_model, { 3.0f, 3.0f, 3.0f });

		//  UFOの描画
		MV1SetPosition(ufo_model, { ufo.pos_x, ufo.pos_y - 8, ufo.pos_z });
		MV1SetScale(ufo_model, { 0.5f, 0.5f, 0.5f });

		//  プロレスラーの描画
		MV1SetPosition(security_model, { seculity.pos_x, 0, seculity.pos_z });
		MV1SetRotationXYZ(security_model, { 0.0f, seculity.radian, 0.0f });

		MV1SetScale(security_model, { 0.05f, 0.05f, 0.05f });

		//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－------------------------------------------------------------
		// SE用処理
		//－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－------------------------------------------------------------

		for (int i = 0; i < CAR_NUM; i++) {
			//  Z座標内に入ってから(縦)
			if (player.pos_z <= car_z[i] + 10 && player.pos_z >= car_z[i] - 10) {
				//  X座標内に入ったらゲームオーバー（横）
				if (player.pos_x >= car_x[i] + 99 && player.pos_x <= car_x[i] + 100) {
					PlaySoundFile("data/Game/SE/車のクラクション.mp3", DX_PLAYTYPE_BACK);
				}
			}
		}

		////  コインの位置
		//for (int i = 0; i < 5; i++) {
		//    MV1SetRotationXYZ(coin_models[i], {TO_RADIAN(90), 0, TO_RADIAN(90)});

		//    //  お試しで大きめに出力
		//    MV1SetScale(coin_models[i], {3.0f, 3.0f, 3.0f});
		//}
		//  位置はまだ決まってないのでいったん手動で場所を決める

		coin_pos[0] = { car_x[3] + 30, 3, car_z[3] };
		coin_pos[1] = { car_x[0] + 30, 3, car_z[0] };
		coin_pos[2] = { car_x[4] + 30, 3, car_z[4] };
		coin_pos[3] = { wood_x[1], 3, wood_z[1] };
		coin_pos[4] = { wood_x[3], 3, wood_x[3] };

		for (int i = 0; i < COIN_NUM; i++) {
			//MV1SetPosition(coin_model, {coin_pos[i]});
			//             MV1SetPosition(coin_model, {coin_pos[i]});
			//MV1SetPosition(coin_model[3], {0, 3, 0});
			//MV1SetPosition(coin_model[4], {0, 3, 0});*/
		}
		player.time++;

		////  スキップ機能
		if (CheckHitKey(KEY_INPUT_K)) {
			player.move_z = -400;
			player.pos_z = -400;
		}

		//  クラスの更新
		player.Update();
		wall.Update();
		timer.Update();
		score.Update();
		life.Update();
		ui.Update();
		camera.Update();
		ufo.Update();
		seculity.Update();
		minimap.Update();

		//  コインを車や丸太の上に描画するための座標変数の更新
		if (score.coin_swich[0]) {
			score.coin_x[0] = car_x[3] + 30;
			score.coin_z[0] = car_z[3];
		}
		if (score.coin_swich[1]) {
			score.coin_x[1] = car_x[0] + 30;
			score.coin_z[1] = car_z[0];
		}
		if (score.coin_swich[2]) {
			score.coin_x[2] = car_x[4] + 30;
			score.coin_z[2] = car_z[4];
		}
		if (score.coin_swich[3]) {
			score.coin_x[3] = wood_x[1];
			score.coin_z[3] = wood_z[1];
		}
		if (score.coin_swich[4]) {
			score.coin_x[4] = wood_x[3];
			score.coin_x[4] = wood_z[3];
		}

		if (player.pos_y <= 5.0f) {
			//  UFOに連れ去られてる途中にこいんをとっちゃわないようにするため
			//  コインを取った際の当たり判定の及びスコアの追加
			for (int i = 0; i < COIN_NUM; i++) {
				if (score.coin_swich[i]) {
					if (score.coin_z[i] - 3 <= player.pos_z && score.coin_z[i] + 3 >= player.pos_z &&
						score.coin_x[i] - 3 <= player.pos_x && score.coin_x[i] + 3 >= player.pos_x) {
						//  スコアを１０００増やす
						score.score += 1000;
						//  取ったコインの描画を消す
						score.coin_swich[i] = false;
					}
				}
			}
		}

		//  Z座標が前に行けば行くほどスコアが増えていくだが下がって前に出ても増えない
		if (player.move_z < score.score_pos) {
			timer.start_time = true;
			score.score_pos = player.move_z;
			//  奥に進めば進むほどスコアの上がり幅が増えていくようにする
			score.score += score.score_pos / -2;
			//            score.score += 10;
		}
		//  プレイヤーが画面端の壁まで行ったらそれ以上は横に行けないようにするための処理
		if (wall.Wall_left_x <= player.move_x) {
			player.move_x = wall.Wall_left_x - 5;
		}
		if (wall.Wall_right_x >= player.move_x) {
			player.move_x = wall.Wall_right_x + 5;
		}

		//  変数を足し続けて一定以上数値が上回ったらIdleアニメーションにしておく

		//	ステージの処理
	

		switch (stage_status)
		{
		case FIRST_STAGE:
			//  車の動きの処理
			for (int i = 0; i < CAR_NUM; i++) {
				//car_x[i] += car_x_plus[i];


				//  画面端に行ったら反対側の画面端に現れるようにしておく
				if (car_x[i] >= 200) {
					car_x[i] = -150 + GetRand(-50);

					if (i >= 5) {
						i = 0;
					}
				}
			}



			if (player.pos_y <= 5.0f) {
				//  当たり判定の処理(車の当たり判定)
				for (int i = 0; i < CAR_NUM; i++) {
					//  Z座標内に入ってから(縦)
					if (player.pos_z <= car_z[i] + 10 && player.pos_z >= car_z[i] - 10) {
						//  X座標内に入ったらゲームオーバー（横）
						if (player.pos_x >= car_x[i] - 5 && player.pos_x <= car_x[i] + 5) {
							//  プレイヤーの座標変更及びアニメーションの再生の許可変数をtrueにする
							car_x_plus[i] = 0.0f;
							//	吹っ飛ぶ演出を作る(リスポーン地点まで自然に飛ばす)
							//for (int i = 0; i < 15; i++)
							//{
							//	player.move_x++;
							//	player.pos_x = player.move_x;
							//	player.move_y++;
							//}

							//	リスポーン地点までの距離をとる
							Respawn_Distance_z = player.pos_z - 20.0f;


							for (int i = 0; i >= Respawn_Distance_z; i--)
							{
								player.move_y = i * -1;
								player.move_z -= i;
							}
							//for (int i = 0; i <= 20; i++)
							//{
							//	player.move_y = i;
							//}


	//						player.move_x += player.move_y;
							dead = true;
							live = false;
							car_die = true;
							minimap.map_icon_switch = false;
							bgm_status = OVER_BGM;
							//  プレイヤーを動けなくする
							player.Revival_move = false;
						}
					}
				}
			}

			if (player.pos_z + 15 >= goal_line_z &&player.pos_z - 15 <= goal_line_z && player.pos_x >= goal_line_x - 15 && player.pos_x <= goal_line_x + 15) {
				goal = true;
				init = true;
				timer.time_clear = false;
				InitTime++;
				goal_count=1;

				if (CheckHitKey(KEY_INPUT_F) || InitTime >= 1800) {
					if (init) {

						stage_status = SECOND_STAGE;
						//	次のステージが始まった際にアニメーションをリセットする
						status_ = STATUS_IDLE;
						next_anim = model_anim_idle;

						//Game::Init();
						player.Init();
						wall.Init();
						timer.Init();
						score.Init();
						life.Init();
						ui.Init();
						camera.Init();
						ufo.Init();
						seculity.Init();
						minimap.Init();
						camera.pos_z = -700;
						for (int i = 0; i < CAR_NUM; i++) {
							car_z[i] = CAR_Z[i];
						}
						car_x[0] = -50;
						car_x[1] = 30;
						car_x[2] = 90;
						car_x[3] = 60;
						car_x[4] = -100;
						for (int i = 0; i < 6; i++) {
							car_x_plus[i] = 1.5f;
						}
						for (int i = 0; i < WOOD_NUM; ++i) {
							int start_pos_x = 0;
							if (i >= 5) {
								start_pos_x = 150;
							}
							wood_x[i] = start_pos_x;
							wood_z[i] = WOOD_START_Z[i];
							wood_x_re[i] = GetRand(-150);
							wood_z_re[i] = WOOD_START_Z_Re[i];
						}
						car_dead = false;
						Respawn_Distance_z = 0.0f;
						river_dead = false;
						wood_safe = true;
						safe_stone_x = -90;
						safe_stone_z = -220;
						goal_line_x = 0;
						goal_line_z = 0;
						over_time = 0;
						river_out_y = 1;
						//	タイトルではなく次のステージへのカットインを差し込む
						//title = true;
						title_x = 0;
						title_blend = 0;
						title_blend_hiku = 3;
						//game = false;
						goal = false;
						goal_anim = false;
						no_die = true;
						init = false;
						camera_x = 0.0f;
						camera_z = 0.0f;
						camera_y = 10.0f;
						//				camera_y = 15.0f;
						camera_y_radian = 5.0f;

						Title_Slide = 10;

						Title_Slide_x = 0;
						stage_change = true;
						StopSoundMem(Clear_BGM);
						//	アニメーションを初期化させる
						InitTime = 0;

						//  BGMを開始させるための変数
						Title_BGM_Start = true;
						Game_BGM_Start = false;
						Over_BGM_Start = false;
						Clear_BGM_Start = false;

						bgm_status = START_BGM;
					}
				}
			}
			break;

		case SECOND_STAGE:

			//  車の動きの処理
			for (int i = 0; i < CAR_NUM; i++) {
				car_x[i] += car_x_plus[i];


				//  画面端に行ったら反対側の画面端に現れるようにしておく
				if (car_x[i] >= 200) {
					car_x[i] = -150 + GetRand(-50);

					if (i >= 5) {
						i = 0;
					}
				}
			}



			if (player.pos_y <= 5.0f) {
				//  当たり判定の処理(車の当たり判定)
				for (int i = 0; i < CAR_NUM; i++) {
					//  Z座標内に入ってから(縦)
					if (player.pos_z <= car_z[i] + 10 && player.pos_z >= car_z[i] - 10) {
						//  X座標内に入ったらゲームオーバー（横）
						if (player.pos_x >= car_x[i] - 5 && player.pos_x <= car_x[i] + 5) {
							//  プレイヤーの座標変更及びアニメーションの再生の許可変数をtrueにする
							car_x_plus[i] = 0.0f;
							//	吹っ飛ぶ演出を作る(リスポーン地点まで自然に飛ばす)
							//for (int i = 0; i < 15; i++)
							//{
							//	player.move_x++;
							//	player.pos_x = player.move_x;
							//	player.move_y++;
							//}

							//	リスポーン地点までの距離をとる
							Respawn_Distance_z = player.pos_z - 20.0f;


							for (int i = 0; i >= Respawn_Distance_z; i--)
							{
								player.move_y = i * -1;
								player.move_z -= i;
							}
							//for (int i = 0; i <= 20; i++)
							//{
							//	player.move_y = i;
							//}


	//						player.move_x += player.move_y;
							dead = true;
							live = false;
							car_die = true;
							minimap.map_icon_switch = false;
							bgm_status = OVER_BGM;
							//  プレイヤーを動けなくする
							player.Revival_move = false;
						}
					}
				}
			}


			//	川に入った瞬間のせせらぎ音の処理
			if (player.pos_z <= -115) {

			}

			River_distance = player.pos_z * -2;


			//  プレイヤーが川のエリアに入った際に移動量を減らす処理
			if (player.pos_z <= -119 && player.pos_z >= -279) {
				player.move = 15;
			}
			else
			{
				player.move = 20;
			}

			//  丸太を流す処理
			wood_x[0]--;
			wood_x[5]--;
			wood_x[1] -= 1.5f;
			wood_x[2]--;
			wood_x[7]--;
			wood_x[3] -= 1.5f;
			wood_x[4]--;
			wood_x[9]--;

			//  丸太を逆向きに流す処理
			for (int i = 0; i < 10; i++) {
				wood_x_re[i]++;
			}

			if (player.pos_y <= 5.0f) {
				if (wood_safe != true) {
					//  川のエリアに入ったか判定
					if (player.pos_z <= -130 && player.pos_z >= -279) {
						//  丸太に乗ったらプレイヤーが一緒に流れていく処理
						//   川１本目
						if (player.pos_z <= wood_z[0] + 16 && player.pos_z >= wood_z[0]) {
							player.move_x--;
						}
						else if (player.pos_z <= wood_z[5] + 16 && player.pos_z >= wood_z[5]) {
							player.move_x--;
						}
						//  川２本目
						else if (player.pos_z <= wood_z[1] + 16 && player.pos_z >= wood_z[1]) {
							player.move_x -= 2.0f;
							player.pos_x -= 1.0f;
						}
						//　川３本目
						//else if(pos_z <= wood_z[2] + 16 && pos_z >= wood_z[2] - 15) {
						//    move_x--;
						//}
						else if (player.pos_z <= wood_z[7] + 16 && player.pos_z >= wood_z[7]) {
							player.move_x--;
						}
						//  川４本目
						else if (player.pos_z <= wood_z[3] + 16 && player.pos_z >= wood_z[3]) {
							player.move_x -= 2.0f;
							player.pos_x -= 1.0f;
						}
						//  川５本目
						else if (player.pos_z <= wood_z[4] + 16 && player.pos_z >= wood_z[4] /*- 8*/) {
							player.move_x--;
						}
						else if (player.pos_z <= wood_z[9] + 8 && player.pos_z >= wood_z[9]) {
							player.move_x--;
						}

						for (int i = 0; i < 10; i++) {
							if (player.pos_z <= wood_z_re[i] + 16 && player.pos_z >= wood_z_re[i]) {
								player.move_x++;
								//                            player.pos_x = player.move_x;
								//  石のセーフエリア手前の丸太のみすぐに止まれるようにしておく
								//                            if(player.pos_z <= wood_z_re[1] + 16 && player.pos_z >= wood_z_re[1])
								//                          {
								//
								//                           }
							}
						}
					}
				}
			}

			//  画面端に行ったら戻ってくる処理	（丸太用）
			for (int i = 0; i < WOOD_NUM; i++) {
				if (wood_x[i] <= -400 - 25) {
					wood_x[i] = 400;
				}
				//  逆向きも同様に戻す
				if (wood_x_re[i] >= 400) {
					wood_x_re[i] = -150 + GetRand(-150);
				}
			}


			//  プレイヤーが地面についていた場合は判定がある
			wood_safe = false;
			if (player.pos_y <= 5.0f) {
				//  川の当たり判定はデフォルトはON
				wood_safe = true;

				//  丸太の乗っている。乗っていないの当たり判定
				for (int i = 0; i < WOOD_NUM; i++) {
					if (player.pos_z <= wood_z[i] + 16 && player.pos_z >= wood_z[i] /*- 15*/ &&
						player.pos_x <= wood_x[i] + 100 && player.pos_x >= wood_x[i] - 100) {
						//  falseが乗っているとき
						wood_safe = false;

					}
				}
				//  逆法の処理
				for (int i = 0; i < WOOD_NUM; i++) {
					if (player.pos_z <= wood_z_re[i] + 16 && player.pos_z >= wood_z_re[i] /*- 15*/ &&
						player.pos_x <= wood_x_re[i] + 100 && player.pos_x >= wood_x_re[i] - 100) {
						wood_safe = false;
						if (i >= 10) {
							i = 0;
						}
					}
				}
				//}
				//  石の上に載っているときの処理
				if (player.pos_z <= safe_stone_z + 30 && player.pos_z >= safe_stone_z && player.pos_x <= safe_stone_x + 80 &&
					player.pos_x >= safe_stone_x) {
					//move_x++;
					//  流れないようにする
					//  プレイヤーがいた場所からそれ以上進まないように一瞬固定する（それ以降しないように一回のみ）
					int i = 0;
					if (i <= 1) {
						player.move_x = player.move_x;
						i++;
					}

					//    川でしななくなる
					wood_safe = false;
				}
			}
			//  カメラの向きを変更するための処理




			//　川のステージに入ってからのカメラの変更
			/*   if(player.pos_z < -110) {
				if(CheckHitKey(KEY_INPUT_SPACE)) {
					camera_y        = 50.0f;
					camera_y_radian = -25.0f;
				}
				else {
					camera_y        = 10.0f;
					camera_y_radian = 5.0f;
				}
			}*/

			//  川の判定の処理
			if (wood_safe) {
				if (player.pos_z <= -130 && player.pos_z >= -279) {
					//  残機を減らす
					dead = true;
					river_die = true;
					minimap.map_icon_switch = false;

					//  プレイヤーを動けなくする
					player.Revival_move = false;

					if (life.life_over) {
						river_dead = true;
						//  死んでしまったので初期化（仮）
						init = true;
					}
				}
			}
			player.pos_x;
			//  一緒に流れるようにする(早い丸太用)
			if (player.pos_z <= wood_z[1] + 16 && player.pos_z >= wood_z[1]) {
				player.move_x += 0.5f;
				player.pos_x += 0.5f;
			}
			if (player.pos_z <= wood_z[3] + 16 && player.pos_z >= wood_z[3] /*- 15*/) {
				player.move_x += 0.5f;
				player.pos_x += 0.5f;
			}


			//  UFOステージの入り口にある壁の当たり判定
			if (player.pos_z <= -279.0f && player.pos_z >= -285.0f) {
				for (int i = 0; i < 17; i++) {
					if (wall.UFO_STAGE_X[i] + 5 >= player.pos_x && wall.UFO_STAGE_X[i] - 5 <= player.pos_x) {
						player.pos_x = wall.UFO_STAGE_X[i] + 10;
						player.move_x = wall.UFO_STAGE_X[i] + 10;
					}
				}
			}
			//	UFOのランダム座標は2分の1でプレイヤー座標と被るようにしておく
			//for (int i = 0; i <= 15; i++)
			//{
			//	if (ufo.pos_no <= i)
			//	{
			//		ufo.pos_x = player.pos_x;
			//	}
			//}
			if (ufo.Tracking)
			{
				if (ufo.pos_x < player.pos_x) {
					ufo.pos_x += 2;
				}
				if (ufo.pos_x > player.pos_x) {
					ufo.pos_x -= 2;
				}
			}
			if (ufo.pos_x == player.pos_x)
			{
				ufo.Tracking = false;
			}

			//  UFOとプレイヤーZ座標は同じにして追ってきてるいる感じにしておく
			if (player.pos_z <= -320 && player.pos_z >= -439) {
				ufo.pos_z = player.pos_z;
			}
			//  プレイヤーがUFOエリア内にいるときのみ当たり判定及びUFOがついてくるという処理を実行する
			if (player.pos_z <= -320 && player.pos_z >= -440) {
				//  UFOとの当たり判定の処理
				if (ufo.ufo_standhing) {
					//  UFOが止まる位置がマイナスの座標の可能性もあるので２つ用意する
					if (player.pos_x <= ufo.pos_x + 3 && player.pos_x >= ufo.pos_x - 3 ) {
						//                car_die = true;
						/* no_die = false;
							  ufo.ufo_die = true;*/
							  //car_die = true;
						ufo.ufo_die = true;
					}
				}
			}
			//  プレイヤーをリスポーン地点まで運ぶ
			if (ufo.ufo_die) {
				//if(ufo.pos_z >= 20.0f) {
				//                if(player.move_y <= 0.0f)
				if (player.move_y <= 20.0f && player.pos_z <= 303.0f) {
					player.move_y++;
				}

				if (player.pos_y >= 19.0f) {
					player.move_x = ufo.pos_x;
					player.pos_x = ufo.pos_x;

					//  UFOエリアのスタート地点まで連れていかれる
					player.move_z = -300.0f;
					//  ufo.pos_no ＝はスタート地点座標を表す
					ufo.pos_no = 0;
				}
				//  プレイヤーのZ座標がスタート地点に戻ったらUFOから降ろして死亡フラグをなくして最初から始まる。
				if (player.pos_z >= -302.0f && player.move_y >= 0.0f) {
					//  X座標をUFOによってずらされないようにするために固定する　UFOから降りきったらFALSEにして処理を止める
					player.move_x = 0.0f;
					player.pos_x = 0.0f;
					//  UFOのX座標をランダムに戻すufo_dieの処理が終わった後は元のクラスの処理に戻るようにする
					ufo.pos_no = GetRand(15);
					ufo.ufo_die = false;
				}
			}
			//	重力用の処理
			//  Z座標-460から警備員ステージへ突入
						//  画面端に行ったら戻ってくる処理
			for (int i = 0; i < WOOD_NUM; i++) {
				if (wood_x[i] <= -400 - 25) {
					wood_x[i] = 400;
				}
				//  逆向きも同様に戻す
				if (wood_x_re[i] >= 400) {
					wood_x_re[i] = -150 + GetRand(-150);
				}
			}

			//	プロレスラーの動きはデフォルトはfalseにし、動いたときのみtrueにする
			security_move_juge = false;

			if (player.pos_x >= seculity.pos_x && seculity.radian >= 4.5f) {
				//  キャラが動いているときは回転を止める
				seculity.radian_move_juge = false;
				seculity.pos_x++;
			}
			if (player.pos_x <= seculity.pos_x && seculity.radian <= 1.5f) {
				//  キャラが動いているときは回転を止める
				seculity.radian_move_juge = false;
				seculity.pos_x--;
			}

			//  Z座標-450からプロレスラーが追い始めるゴールするまで追い回される
			if (player.pos_z <= -450) {
				//  前フレームと現フレームが違った場合は実行する（動いたとき）

				if (player.pos_x != player.pos_x_copy || player.pos_z != player.pos_z_copy) {
					if (seculity.pos_x <= player.pos_x && seculity.radian >= 4.3f) {
						seculity.pos_x += 3.0f;
						security_move_juge = true;

					}
					if (seculity.pos_x >= player.pos_x && seculity.radian <= 1.8f) {
						seculity.pos_x -= 3.0f;
						security_move_juge = true;

					}
				}

				//  プロレスラーとプレイヤーの当たり判定の処理
				if (player.pos_x + 10.0f >= seculity.pos_x && player.pos_x - 10.0f <= seculity.pos_x) {
					player.security_attack = true;

					//                player.move_y = 20.0f;
				}
				//  Z座標はステージに入ったらずっと一緒
				seculity.pos_z = player.pos_z;
			}

			//}
			//if(ufo.pos_x >= 0)
			//    ufo.pos_x--;
			//player.move_x--;
			//player.pos_x--;

			//if(ufo.pos_x <= 0) {
			//    ufo.pos_x++;
			//    player.move_x++;
			//    player.pos_x++;
			//    player.pos_x--;
			//}
			//if(ufo.pos_z <= 20.0f) {
			//    ufo.pos_z++;
			//    player.move_z++;
			//    player.pos_z++;
			//}

			//if(player.pos_y == 0.0f) {
			//    no_die = false;
			//    Respawn();
			//}

			//	現段階では２ステージ目が最終ステージなのでこちらにゴールの処理を作っておく
			if (player.pos_z + 15 >= goal_line_z &&player.pos_z - 15 <= goal_line_z && player.pos_x >= goal_line_x - 15 && player.pos_x <= goal_line_x + 15) {
				//effect_congra_play = PlayEffekseer3DEffect(effect_congra);
				//SetPosPlayingEffekseer3DEffect(effect_congra_play, player.pos_x, player.pos_y, player.pos_z - 5);
				if (goal_adjustment <= 1)
				{
					bgm_status = CLEAR_BGM;
		//	何度もループしないためにする
					goal_adjustment = 2;
				}

				Clear_BGM_Start = true;
				switch (bgm_status) {
				case CLEAR_BGM:
					StopSoundMem(Game_BGM);
					PlaySoundMem(Clear_BGM, DX_PLAYTYPE_LOOP);
					bgm_status = -1;
					break;
				}
				goal = true;
				init = true;
				timer.time_clear = false;
				InitTime++;
				goal_count = 2;
				if (CheckHitKey(KEY_INPUT_F) || InitTime >= 1800) {
					if (init) {

						stage_status = 0;

						//Game::Init();
						player.Init();
						wall.Init();
						timer.Init();
						score.Init();
						life.Init();
						ui.Init();
						camera.Init();
						ufo.Init();
						seculity.Init();
						minimap.Init();
						goal_adjustment = 0;
						for (int i = 0; i < CAR_NUM; i++) {
							car_z[i] = CAR_Z[i];
						}
						car_x[0] = -50;
						car_x[1] = 30;
						car_x[2] = 90;
						car_x[3] = 60;
						car_x[4] = -100;
						for (int i = 0; i < 6; i++) {
							car_x_plus[i] = 1.5f;
						}
						for (int i = 0; i < WOOD_NUM; ++i) {
							int start_pos_x = 0;
							if (i >= 5) {
								start_pos_x = 150;
							}
							wood_x[i] = start_pos_x;
							wood_z[i] = WOOD_START_Z[i];
							wood_x_re[i] = GetRand(-150);
							wood_z_re[i] = WOOD_START_Z_Re[i];
						}
						car_dead = false;
						Respawn_Distance_z = 0.0f;
						river_dead = false;
						wood_safe = true;
						safe_stone_x = -90;
						safe_stone_z = -220;
						goal_line_x = 0;
						goal_line_z = 0;
						over_time = 0;
						river_out_y = 1;
						title = true;
						title_x = 0;
						title_blend = 0;
						title_blend_hiku = 3;
						game = false;
						goal = false;
						goal_anim = false;
						goal_count = 0;
						no_die = true;
						init = false;
						camera_x = 0.0f;
						camera_z = 0.0f;
						camera_y = 10.0f;
						//				camera_y = 15.0f;
						camera_y_radian = 5.0f;

						Title_Slide = 0;

						Title_Slide_x = 0;
						StopSoundMem(Clear_BGM);
						//	アニメーションを初期化させる
						status_ = STATUS_IDLE;
						next_anim = model_anim_idle;

						InitTime = 0;

						//  BGMを開始させるための変数
						Title_BGM_Start = true;
						Game_BGM_Start = false;
						Over_BGM_Start = false;
						Clear_BGM_Start = false;

						bgm_status = START_BGM;
					}
				}

			}



			break;

		case THIRD_STAGE:

			break;

		case FOURTH_STAGE:

			break;

		case FIFTH_STAGE:

			break;
		}
		if (player.pos_z >= -302.0f && player.move_y >= 0.0f) {
			player.move_y--;
		}


		//  時間切れでゲームオーバーになった時の処理
		if (timer.time_over) {
			//  BGMをなくす
			StopSoundMem(Game_BGM);
			Over_BGM_Start = true;
			switch (bgm_status) {
			case OVER_BGM:
				PlaySoundMem(Over_BGM, DX_PLAYTYPE_LOOP);
				bgm_status = -1;
				break;
			}

			//  このままじゃ画面裏で車に魅かれ続けてしまうので魅かれない場所に飛ばす
			player.pos_z = 80000;
			init = true;
			InitTime++;
		}


		//  道路のステージの場合の向き
		if (player.pos_z > -110) {
			if (CheckHitKey(KEY_INPUT_SPACE)) {
				/*      camera_x = -80.0f;
				camera_z = -50.0f;
		  */
				camera_y = 50.0f;
				camera_y_radian = -25.0f;
			}
			else {
				/*    camera_x = 0.0f;
				camera_z = 0.0f;
			*/
				camera_y = 10.0f;
				camera_y_radian = 5.0f;
			}
		}
		//	川ステージからはカメラを固定する
		if (player.pos_z < -110)
		{
			camera_y = 10.0f;
			camera_y_radian = 5.0f;
		}

		//	カメラがスタート位置に行くまでプレイヤーを動けなくする

		if (camera.pos_z <= player.pos_z)
		{
			player.pos_x = 0.0f;
			player.pos_z = 20.0f;
			player.move_x = 0.0f;
			player.move_z = 20.0f;
		}


		//  残機が尽きたときの処理
		if (life.life_over) {
			//  魅かれたときにBGM開始用の変数をtrueにする

			switch (bgm_status) {
			case OVER_BGM:
				StopSoundMem(Game_BGM);
				PlaySoundMem(Over_BGM, DX_PLAYTYPE_LOOP);
				bgm_status = -1;
				break;
			}

			//  このままじゃ画面裏で車に魅かれ続けてしまうので魅かれない場所に飛ばす
			//player.pos_z = 80000;
			player.radian_y = 380.0f;


			init = true;
		}


		if (CheckHitKey(KEY_INPUT_F) || InitTime >= 1800) {
			if (init) {

				//Game::Init();
				player.Init();
				wall.Init();
				timer.Init();
				score.Init();
				life.Init();
				ui.Init();
				camera.Init();
				ufo.Init();
				seculity.Init();
				minimap.Init();
				for (int i = 0; i < CAR_NUM; i++) {
					car_z[i] = CAR_Z[i];
				}
				car_x[0] = -50;
				car_x[1] = 30;
				car_x[2] = 90;
				car_x[3] = 60;
				car_x[4] = -100;
				for (int i = 0; i < 6; i++) {
					car_x_plus[i] = 1.5f;
				}
				for (int i = 0; i < WOOD_NUM; ++i) {
					int start_pos_x = 0;
					if (i >= 5) {
						start_pos_x = 150;
					}
					wood_x[i] = start_pos_x;
					wood_z[i] = WOOD_START_Z[i];
					wood_x_re[i] = GetRand(-150);
					wood_z_re[i] = WOOD_START_Z_Re[i];
				}
				car_dead = false;
				Respawn_Distance_z = 0.0f;
				river_dead = false;
				wood_safe = true;
				safe_stone_x = -90;
				safe_stone_z = -220;
				goal_line_x = 0;
				goal_line_z = 0;
				over_time = 0;
				river_out_y = 1;
				title = true;
				title_x = 0;
				title_blend = 0;
				title_blend_hiku = 3;
				game = false;
				goal = false;
				goal_anim = false;
				goal_count = 0;
				no_die = true;
				init = false;
				camera_x = 0.0f;
				camera_z = 0.0f;
				camera_y = 10.0f;
				//				camera_y = 15.0f;
				camera_y_radian = 5.0f;

				Title_Slide = 0;

				Title_Slide_x = 0;
				StopSoundMem(Clear_BGM);
				//	アニメーションを初期化させる
				status_ = STATUS_IDLE;
				next_anim = model_anim_idle;

				InitTime = 0;

				//  BGMを開始させるための変数
				Title_BGM_Start = true;
				Game_BGM_Start = false;
				Over_BGM_Start = false;
				Clear_BGM_Start = false;

				bgm_status = START_BGM;
			}
		}



		//  川で死んだときの処理
		//  +残機がなくなったとき

		if (life.life_over) {
			if (river_dead) {
				//    画面が切り替わってからBGMを切り替えるための処理
				if (over_time == 60) {
					ChangeVolumeSoundMem(200, Over_BGM);

					switch (bgm_status) {
					case OVER_BGM:
						StopSoundMem(Game_BGM);
						PlaySoundMem(Over_BGM, DX_PLAYTYPE_LOOP);
						bgm_status = -1;
						break;
					}
					//  このままじゃ溺れ続けてBGMが始まらないので座標を移動させる
					player.pos_z = 8000;
				}
				InitTime++;
				init = true;
				if (CheckHitKey(KEY_INPUT_F) || InitTime >= 1800) {
					if (init) {

						//Game::Init();
						player.Init();
						wall.Init();
						timer.Init();
						score.Init();
						life.Init();
						ui.Init();
						camera.Init();
						ufo.Init();
						seculity.Init();
						minimap.Init();
						for (int i = 0; i < CAR_NUM; i++) {
							car_z[i] = CAR_Z[i];
						}
						car_x[0] = -50;
						car_x[1] = 30;
						car_x[2] = 90;
						car_x[3] = 60;
						car_x[4] = -100;
						for (int i = 0; i < 6; i++) {
							car_x_plus[i] = 1.5f;
						}
						for (int i = 0; i < WOOD_NUM; ++i) {
							int start_pos_x = 0;
							if (i >= 5) {
								start_pos_x = 150;
							}
							wood_x[i] = start_pos_x;
							wood_z[i] = WOOD_START_Z[i];
							wood_x_re[i] = GetRand(-150);
							wood_z_re[i] = WOOD_START_Z_Re[i];
						}
						car_dead = false;
						Respawn_Distance_z = 0.0f;
						river_dead = false;
						wood_safe = true;
						safe_stone_x = -90;
						safe_stone_z = -220;
						goal_line_x = 0;
						goal_line_z = 0;
						over_time = 0;
						river_out_y = 1;
						title = true;
						title_x = 0;
						title_blend = 0;
						title_blend_hiku = 3;
						game = false;
						goal = false;
						goal_anim = false;
						goal_count = 0;
						no_die = true;
						init = false;
						camera_x = 0.0f;
						camera_z = 0.0f;
						camera_y = 10.0f;
						//				camera_y = 15.0f;
						camera_y_radian = 5.0f;

						Title_Slide = 0;

						Title_Slide_x = 0;
						StopSoundMem(Clear_BGM);
						//	アニメーションを初期化させる
						status_ = STATUS_IDLE;
						next_anim = model_anim_idle;

						InitTime = 0;

						//  BGMを開始させるための変数
						Title_BGM_Start = true;
						Game_BGM_Start = false;
						Over_BGM_Start = false;
						Clear_BGM_Start = false;

						bgm_status = START_BGM;
					}
				}
			}
		}

		//  プレイヤーを動けなくする
		player.move_juge = false;
		////  川に流されないようにする
		//player.pos_x++;
		over_time++;
		//            player.pos_y -= river_out_y;
		//  プレイヤーが溺れたときに震える
		/* if(life.life_count <= 0) {
				if(player.pos_y <= -5) {
					player.pos_y = GetRand(-3);
				}
			}*/

			//  ミニマップ用の処理
		minimap.map_player_y = 680 + player.pos_z;

		//  ライトの処理
	//    SetUseLighting(true);
		SetLightDirection({ -1.0f, -1.0f,-1.0f });
		//SetLightPosition(VGet(player.pos_x, player.pos_y + 10.0f, player.pos_z + 10.0f));


		// -----------------------------------------------------------------------------------------------------------------
		//  ゴールした時の処理
		// -----------------------------------------------------------------------------------------------------------------
		//	急ぎのためかりで　一回だけ踏んでほしいためその座標を通った瞬間のみ
		//if (player.pos_z == -599)
		//{
		//	bgm_status = CLEAR_BGM;
		//}


		//if(goal_line_x + 300 >= player.pos_x && goal_line_x - 300 <= player.pos_x && goal_line_z >= player.pos_z) {
		//    StopSoundMem(Game_BGM);
		//    //  エフェクトの再生
		//    //        if(CheckHitKey(KEY_INPUT_SPACE)) {
		//    effect_congra_play = PlayEffekseer3DEffect(effect_congra);
		//    goal_anim          = true;
		//    goal_count++;

		//    //  エフェクトの位置の初期化
		//    SetPosPlayingEffekseer3DEffect(effect_congra_play, player.pos_x, player.pos_y, player.pos_z + 15);
		//    //        }
		//    if(goal_count >= 240) {
		//        //  このままだとゴールし続けてBGMが流れないため座標を遠くにおいておく
		//        player.pos_z = 50000;
		//        switch(bgm_status) {
		//        case SceneFrogger::OVER_BGM:
		//            PlaySoundMem(Over_BGM, DX_PLAYTYPE_LOOP);
		//            bgm_status = -1;
		//            break;
		//        }

		//        goal = true;
		//        init = true;
		//    }
		//}
		////  初期化
		//  ライフがなくなったときに初期化を行う
		if (life.life_over) {
			InitTime++;
			timer.time_clear = false;

			if (CheckHitKey(KEY_INPUT_F) || InitTime >= 1800) {
				if (init) {
					//Game::Init();
					player.Init();
					wall.Init();
					timer.Init();
					score.Init();
					life.Init();
					ui.Init();
					camera.Init();
					ufo.Init();
					seculity.Init();
					minimap.Init();
					for (int i = 0; i < CAR_NUM; i++) {
						car_z[i] = CAR_Z[i];
					}
					car_x[0] = -50;
					car_x[1] = 30;
					car_x[2] = 90;
					car_x[3] = 60;
					car_x[4] = -100;
					for (int i = 0; i < 6; i++) {
						car_x_plus[i] = 1.5f;
					}
					for (int i = 0; i < WOOD_NUM; ++i) {
						int start_pos_x = 0;
						if (i >= 5) {
							start_pos_x = 150;
						}
						wood_x[i] = start_pos_x;
						wood_z[i] = WOOD_START_Z[i];
						wood_x_re[i] = GetRand(-150);
						wood_z_re[i] = WOOD_START_Z_Re[i];
					}
					car_dead = false;
					Respawn_Distance_z = 0.0f;
					river_dead = false;
					wood_safe = true;
					safe_stone_x = -90;
					safe_stone_z = -220;
					goal_line_x = 0;
					goal_line_z = 0;
					over_time = 0;
					river_out_y = 1;
					title = true;
					title_x = 0;
					title_blend = 0;
					title_blend_hiku = 3;
					game = false;
					goal = false;
					goal_anim = false;
					goal_count = 0;
					no_die = true;
					init = false;
					camera_x = 0.0f;
					camera_z = 0.0f;
					camera_y = 10.0f;
					//				camera_y = 15.0f;
					camera_y_radian = 5.0f;

					Title_Slide = 0;

					Title_Slide_x = 0;

					status_ = STATUS_IDLE;
					next_anim = model_anim_idle;
					InitTime = 0;

					//  BGMを開始させるための変数
					Title_BGM_Start = true;
					Game_BGM_Start = false;
					Over_BGM_Start = false;
					Clear_BGM_Start = false;

					bgm_status = START_BGM;



				}
			}
		}
		//	カメラがしたに埋まらないようにするための処理
		/*if (camera_y + 6.0f < 15.0f)
		{
			camera_y = 15.0f;
		}*/
		if (camera.pos_z < -600 && player.pos_z >= 0.0f)
		{
			camera_y = 20.0f;
		}

		//if (camera_y >= 10.0f)
		//{
		//	camera_y -= 0.0025f;
		//}
	//	camera_y = 25.0f;

		//Change_camera_z = camera.pos_z;
		Change_camera_z = 0.0;
		//  初期化はここまでここから下はカメラの設定
		SetCameraPositionAndTarget_UpVecY(   //  最終的なカメラのZ座標player.pos_z + 30.0f
			{ player.pos_x, 5.0f + camera_y  , player.pos_z + camera.pos_z },
			{ player.pos_x + camera_x, player.pos_y + camera_y_radian, player.pos_z + Change_camera_z });
		//  SetCameraPositionAndTarget_UpVecY({0.0f,5.0f,30.0f}, {0.0f,-180.0f,0.0f});
		SetupCamera_Perspective(60.0f * DegToRad);
	}
}
//---------------------------------------------------------------------------------
//	描画処理
//---------------------------------------------------------------------------------
void Game::Draw()
{ 
	//  道路の作成（車込み）
	if (game) {



		//MakeGraph(500, 100);
		//MakeScreen(500, 100, true);
		//  道路の白線を描画
		for (int i = 0; i < 4; i++) {
			DrawCube3D(
				{
					-300,
					-1,
					WHITE_LINE_1[i],
				},
				{ 300, 0.2f, WHITE_LINE_2[i] },
				WHITE,
				WHITE,
				TRUE);
		}
		DrawCube3D(
			{
				-300,
				-1,
				-89.0f,
			},
			{ 300, 0.2f, -91.0f },
			WHITE,
			WHITE,
			TRUE);

		// 仮モデルの描画
		//    プレイヤーモデル
		MV1DrawModel(model_);
		for (int i = 0; i < CAR_NUM; i++) {
			MV1DrawModel(car_model[i]);
		}

		//  床の描画
		//	下に書いてしまうとUIを隠してしまうことになるので上に配置
		DrawCube3D(
			{
				-300,
				-1.0f,
				500,
			},
			{ 300, -0.9f, -130 },
			GetColor(105, 105, 105),
			GetColor(105, 100, 105),
			TRUE);


		//	ステージの処理
		switch (stage_status)
		{
		case FIRST_STAGE:
		//	ゴールの場所を変更する
			goal_line_x = 0;
			goal_line_z = -130;




			//DrawCube3D({ -10, 0, -100 - 10 }, { 10, 10, -110 - 10 }, GetColor(255, 125, 125), GetColor(125, 0, 0), true);
			//DrawCone3D({ 0,25,-110 - 10 }, { 0,10,-110 - 10 }, 18, 64, GetColor(255, 255, 0), GetColor(255, 255, 0), true);
				//  ゴール画面の描画
			break;

		case SECOND_STAGE:
			goal_line_x = 0;
			goal_line_z = -600;


			//  UFOステージが始まるとわかるようにするための線
			DrawCube3D({ wall.Wall_left_x, 0, -300 }, { wall.Wall_right_x, 1, -305 }, WHITE, WHITE, true);

			//  車の描画（仮）

			//  ゴールの描画
			// DrawCube3D({goal_line_x + 300, 0, goal_line_z}, {goal_line_x - 300, 30, goal_line_z}, GREEN, GREEN, true);

			//  川の作成（仮）
			DrawCube3D({ 300, -2, -130 }, { -600, -1, -280 }, BLUE, BLUE, TRUE);

			DrawCube3D({ 300,-20,-130 }, { -600,-1,-131 }, BLUE, BLUE, TRUE);

			//  川の真ん中に置く石床の描画
			//  石の座標がｘが-10から-90　ｚが-190から-220
			DrawCube3D({ safe_stone_x + 80, 1, safe_stone_z + 30 },
				{ safe_stone_x, 0, safe_stone_z },
				GetColor(105, 105, 105),
				GetColor(105, 105, 105),
				TRUE);

			//  丸太の作成（仮）
			//  1本目
			for (int i = 0; i < 5; i++) {
				DrawCube3D({ wood_x[i] + 100, -1, wood_z[i] + 15 },
					{ wood_x[i] - 100, 0, wood_z[i] },
					GetColor(255, 125, 0),
					GetColor(255, 125, 0),
					true);
				//  逆向きの丸太も同様に流す
				DrawCube3D({ wood_x_re[i] + 100, -1, wood_z_re[i] + 15 },
					{ wood_x_re[i] - 100, 0, wood_z_re[i] },
					GetColor(255, 125, 0),
					GetColor(255, 125, 0),
					true);
			}

			//  6本目(5本目と同じ流れ)
			DrawCube3D({ wood_x[7] + 100, -1, wood_z[7] + 15 },
				{ wood_x[7] - 100, 0, wood_z[7] },
				GetColor(255, 125, 0),
				GetColor(255, 125, 0),
				true);
			//  6本目
			DrawCube3D({ wood_x[9] + 100, -1, wood_z[9] + 15 },
				{ wood_x[9] - 100, 0, wood_z[9] },
				GetColor(255, 125, 0),
				GetColor(255, 125, 0),
				true);

			//  UFOステージだとわかるように床を緑色にする
			DrawCube3D({ 200, 0, -280 }, { -170, 0.5f, -440 }, GetColor(0, 255, 0), GetColor(0, 255, 0), true);

			//    DrawSphere3D(0,0,0,50.0f)

			//  DrawPolygon3D()
					//  UFOの描画
			MV1DrawModel(ufo_model);

			//	UFO用の影を描画
			//DrawSphere3D({ ufo.pos_x,0.5f,ufo.pos_z }, 5.0f, 5.0f, BLACK, BLACK, true);
			//  Z座標-440～459はセーフエリア
			DrawCube3D({ wall.Wall_left_x, -1, -440 },
				{ wall.Wall_right_x, 0, -450 },
				GetColor(0, 0, 0),
				GetColor(0, 0, 0),
				TRUE);

			//  プロレスラーの描画
			MV1DrawModel(security_model);

			//        MV1DrawModel(coin_model);

				//  ゴール画面の描画
			if (goal&& goal_count == 2) {
				//		DrawBox(0, 0, WINDOW_W, WINDOW_H, BLACK, true);
				SetFontSize(40);
				DrawString(WINDOW_W / 3 + 110, WINDOW_H / 2 + 50, "帰宅！！", BLUE, true);
				DrawString(WINDOW_W / 3 + 110 + 3, WINDOW_H / 2 + 50, "帰宅！！", BLACK, true);

				DrawString(WINDOW_W / 3, WINDOW_H / 2 + 200, "Fを押してもう一度帰宅！", GetColor(0, 255, 0), true);
				DrawFormatStringF(WINDOW_W / 2 - 135, WINDOW_H - 115, GetColor(255, 255, 255), "今回のスコアは%d", score.score);
			}


			break;

		case THIRD_STAGE:

			break;

		case FOURTH_STAGE:

			break;

		case FIFTH_STAGE:

			break;
		}

		//  ゴールの家を描画
		DrawCube3D({ goal_line_x - 10, 0, goal_line_z + 10 }, { goal_line_x + 10, 10, goal_line_z - 10 }, GetColor(255, 125, 125), GetColor(125, 0, 0), true);
		DrawCone3D({ goal_line_x,25,goal_line_z }, { goal_line_x,10,goal_line_z }, 18, 64, GetColor(255, 255, 0), GetColor(255, 255, 0), true);




		//  コインの描画
		for (int i = 0; i < COIN_NUM; i++) {
			if (score.coin_swich[i]) {
				//                MV1DrawModel(coin_model);
				MV1DrawModel(coin_models[i]);
			}
		}
		//  コインの描画
		for (int i = 0; i < 5; i++) {
			if (score.coin_swich[i]) {
				//              DrawSphere3D({ score.coin_x[i], 3, score.coin_z[i] }, 3, 5, 5, GetColor(0, 255, 255), true);
			}
		}


		//  ゴールの家を描画
//DrawCube3D({ -10, 0, -600 - 10 }, { 10, 10, -625 - 10 }, GetColor(255, 125, 125), GetColor(125, 0, 0), true);
//DrawCone3D({ 0,25,-615 - 10}, { 0,10,-615 - 10 }, 18, 64, GetColor(255, 255, 0), GetColor(255, 255, 0), true);

//	ライトの位置の位置を確かめるために球体を出す
//	DrawSphere3D({ 1.0f, 1.0f,player.pos_z + 10.0f },5.0f,50.0f,RED,RED,true);




	//  クラスの描画

	//  wallの描画
		wall.Draw();
		score.Draw();
		ufo.Draw();
		//  タイマーの描画
		timer.Draw();
		ui.Draw();

		//if(ufo.ufo_standhing) {
		//    //  仮でUFOの座標を表示
		//    DrawFormatString(WINDOW_W / 2, WINDOW_H / 2, GetColor(255, 255, 255), "x座標は%f", ufo.pos_x);
		//}
		////  仮でプレイヤーの座標を表示
		//DrawFormatString(WINDOW_W / 2, WINDOW_H / 3, GetColor(255, 255, 255), "ラジアン座標は%f", seculity.radian);
		//DrawFormatString(WINDOW_W / 2, WINDOW_H / 4, GetColor(255, 255, 255), "z座標は%f", player.pos_z);
		//DrawFormatString(WINDOW_W / 2, WINDOW_H / 5, GetColor(255, 255, 255), "y座標は%f", player.pos_y);
		//  DrawString(WINDOW_W / 3, WINDOW_H - 100, "Kキーを押すと川ステージを飛ばせます", GetColor(255, 255, 255), true);
		if (timer.time_over) {
			DrawRotaGraph(WINDOW_W / 2, WINDOW_H / 2, 6.0f, 0, Time_Over_haikei_fire, true);
			DrawRotaGraph(WINDOW_W / 3, WINDOW_H / 2 + 50, 1.0f, 0, Time_Over_ilust_hansei, true);
			DrawRotaGraph(WINDOW_W / 2, WINDOW_H / 2, 3.0f, 0, Time_Over_ilust_sekkyou, true);

			DrawString(WINDOW_W / 3 + 5, WINDOW_H / 2, "怒られた。。。", WHITE, true);
			DrawString(WINDOW_W / 3, WINDOW_H / 2, "怒られた。。。", RED, true);
			DrawString(WINDOW_W / 3 + 5, WINDOW_H / 2 + 200, "Fを押して諦めず帰宅！", GetColor(0, 0, 0), true);
			DrawString(WINDOW_W / 3, WINDOW_H / 2 + 200, "Fを押して諦めず帰宅！", GetColor(0, 255, 0), true);

			DrawFormatStringF(WINDOW_W / 2 - 100,
				timer.result_y / 2 + 50,
				GetColor(255, 255, 255),
				"今回のスコアは%d",
				score.score);
		}

		//  残機の出力
		life.Draw();
		minimap.Draw();

		//DrawFormatStringF(50, 80, GetColor(255, 255, 255), "プレイや―X座標  %f", player.pos_x);
		//DrawFormatStringF(50, 120, GetColor(255, 255, 255), "プレイや―X座標  %f", player.pos_z);

		//if(life.life_1) {
		//    //  残り３残機
		//    DrawBox(life.life_x + 30, WINDOW_H - 10, life.life_x + 60, WINDOW_H - 40, GetColor(255, 255, 255), true);
		//    DrawBox(life.life_x + 80, WINDOW_H - 10, life.life_x + 110, WINDOW_H - 40, GetColor(255, 255, 255), true);

		//    DrawBox(life.life_x + 130, WINDOW_H - 10, life.life_x + 160, WINDOW_H - 40, GetColor(255, 255, 255), true);
		//}

		//  コイン（仮）の描画
		//for(int i = 0; i < COIN_NUM;i++) {
		//    DrawCube3D(score.coin_x)
		//}hunterhunterjf
		//        DrawCube3D(0, 0, 5, 5, GetColor(255,0,0), TRUE);

		//  タイトル画面
		DrawBox(title_x, 0, title_x + WINDOW_W, WINDOW_H, GetColor(0, 0, 0), true);
		//  ライフがすべてなくなったとき
		if (life.life_over) {
			//  ゲームオーバーの仕方によってリザルト画面を変更する
			switch (over_status) {
			case CAR_OVER:
				//		DrawBox(0, 0, WINDOW_W, WINDOW_H, GetColor(255, 0, 0), true);
				DrawString(WINDOW_W / 3 + 3, WINDOW_H / 2, "車に轢かれて帰れなかった、、、、", BLACK, true);
				DrawString(WINDOW_W / 3, WINDOW_H / 2, "車に轢かれて帰れなかった、、、", BLUE, true);
				DrawString(WINDOW_W / 3 + 5, WINDOW_H / 2 + 200, "Fを押してタイトルへ戻る", GetColor(0, 0, 0), true);
				DrawString(WINDOW_W / 3, WINDOW_H / 2 + 200, "Fを押してタイトルへ戻る", GetColor(0, 255, 0), true);

				//DrawFormatStringF(WINDOW_W / 2 - 100,
				//	WINDOW_H - 50,
				//	GetColor(255, 255, 255),
				//	"今回のスコアは%d",
				//	score.score);
				break;

			case RIVER_OVER:
				//                if(over_time >= 60) {
				DrawBox(0, 0, WINDOW_W, WINDOW_H, GetColor(0, 0, 255), true);
				DrawRotaGraph(WINDOW_W / 4, WINDOW_H / 2 + 50, 1.0f, 0, River_Over_ilust, true);
				DrawRotaGraph(WINDOW_W - 200, WINDOW_H / 2 + 50, 1.0f, 0, River_Over_ilust_safe, true);

				DrawString(WINDOW_W / 3 + 5, WINDOW_H / 2, "川に溺れてしまった。。。", BLACK, true);
				DrawString(WINDOW_W / 3, WINDOW_H / 2, "川に溺れてしまった。。。", RED, true);

				DrawString(WINDOW_W / 3 + 5, WINDOW_H / 2 + 200, "Fを押して諦めず帰宅！", GetColor(0, 0, 0), true);
				DrawString(WINDOW_W / 3, WINDOW_H / 2 + 200, "Fを押して諦めず帰宅！", GetColor(0, 255, 0), true);

				DrawFormatStringF(WINDOW_W / 2 - 100,
					WINDOW_H - 50,
					GetColor(255, 255, 255),
					"今回のスコアは%d",
					score.score);
				break;
			}
		}
		if (goal && goal_count == 1) {
			//		DrawBox(0, 0, WINDOW_W, WINDOW_H, BLACK, true);
			SetFontSize(40);
			DrawString(WINDOW_W / 3 + 110, WINDOW_H / 2 + 50, "帰宅！！", BLUE, true);
			DrawString(WINDOW_W / 3 + 110 + 3, WINDOW_H / 2 + 50, "帰宅！！", BLACK, true);

			DrawString(WINDOW_W / 3, WINDOW_H / 2 + 200, "Fを押して次のステージへ！", GREEN, true);
			DrawFormatStringF(WINDOW_W / 2 - 135, WINDOW_H - 115, BLUE, "今回のスコアは%d", score.score);
		}



		//	ステージ変更用のカットインの描画
		if (stage_change)
		{
			DrawBox(0 - Title_Slide_x, 0, WINDOW_W - Title_Slide_x, WINDOW_H, BLACK, true);
		}

	}
	//  タイトル画面の作成（仮）
	if (title) {

		
			DrawRotaGraph(WINDOW_W / 2 - Title_Slide_x, WINDOW_H / 2 - 50, 7.5f, 0, Title_Town, true);
//			DrawRotaGraph(Title_Player_x - Title_Slide_x, Title_Player_y + Title_Ufo_y, 0.5f, 0, Title_Player, true);
			//																						↓これでふり幅変更
			DrawRotaGraphF(Title_Player_x - Title_Slide_x, Title_Player_y - fabs( sinf( Title_player_y_gravity ) ) * 5.0f, 0.5f, 0, Title_Player, true);
			//DrawRotaGraph(Title_Player_x - Title_Slide_x, WINDOW_H - 120 + Title_Ufo_y, 0.5f, 0, Title_Player, true);

			DrawRotaGraph(300 - Title_Slide_x, WINDOW_H - 200, 0.7f, 0, Title_House, true);

			DrawRotaGraph(Title_Ufo_x - Title_Slide_x, Title_Ufo_y, 0.25f, Title_Ufo_rad, Title_Ufo, true);
			//        DrawBox(0, 0, WINDOW_W, WINDOW_H, GetColor(0, 0, 0), true);
			SetFontSize(100);
			DrawString(WINDOW_W / 3 + 90 - Title_Slide_x, WINDOW_H / 2 - 100, "Go Home", GetColor(0, 0, 0), true);
			DrawString(WINDOW_W / 3 + 85 - Title_Slide_x, WINDOW_H / 2 - 100, "Go Home", GetColor(255, 255, 0), true);

			SetFontSize(40);

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, title_blend);
			DrawString(WINDOW_W / 3 - Title_Slide_x + 5,
				WINDOW_H / 2 + 200,
				"SPACEキーを押して帰宅開始！",
				GetColor(0, 0, 0),
				true);

			DrawString(WINDOW_W / 3 - Title_Slide_x,
				WINDOW_H / 2 + 200,
				"SPACEキーを押して帰宅開始！",
				GetColor(255, 255, 0),
				true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
			if (PlayCount_Switch) {
				DrawFormatString(WINDOW_W - 100, WINDOW_H - 50, GetColor(0, 0, 0), "%d", PlayCount, true);
			}
			
			//
	//	tutorial.Draw();
	}
	if (title_rule) {
		int x = 1250;
		DrawString(WINDOW_W / 2 - 350 - Title_Slide_x + 5 + x,
			WINDOW_H / 2 - 100,
			"門限が後２分だ！普通に帰ったら遅刻遅刻！\n危ないけど近道を突っ切ろう！",
			GetColor(0, 0, 0),
			true);
		DrawString(WINDOW_W / 2 - 350 - Title_Slide_x + x,
			WINDOW_H / 2 - 100,
			"門限が後２分だ！普通に帰ったら遅刻遅刻！\n危ないけど近道を突っ切ろう！",
			GetColor(255, 255, 0),
			true);
		DrawString(WINDOW_W / 3 - Title_Slide_x + x,
			WINDOW_H / 2 + 200,
			"ENTERキーを押して帰宅開始！",
			GetColor(255, 255, 0),
			true);
	}

}
//---------------------------------------------------------------------------------
//	終了処理
//---------------------------------------------------------------------------------
void Game::Exit()
{
	MV1DeleteModel(model_);
	for (int i = 0; i < CAR_NUM; i++) {
		MV1DeleteModel(car_model[i]);
	}
	for (int i = 0; i < COIN_NUM; i++) {
		MV1DeleteModel(coin_models[i]);
	}
}
