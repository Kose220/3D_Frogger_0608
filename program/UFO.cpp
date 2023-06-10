#include "UFO.h"
#include"DxLib.h"
#include "Random.h"
#include"Player.h"

Player Ufo_player;

constexpr int UFO_POS_X[] = {
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	0,
	180,
	160,
	140,
	120,
	100,
	80,
	60,
	40,
	20,

	-20,
	-40,
	-60,
	-80,
	-100,
	-120,
};

void UFO::Init()
{
	pos_x = 0.0f;
	pos_y = 20.0f;
	pos_z = -300.0f;
	pos_no = GetRandomF(30);
	ufo_time = 0;
	ufo_standhing = false;
	ufo_die = false;

	UFO_LIGHT = 15;
	UFO_Blend = 150;

	//	TRUEの時はプレイヤーを追跡
	Tracking = false;

}

void UFO::Update()
{


	ufo_standhing = false;
	//	trueの時は追跡それ以外縦横無尽に移動
	if (Tracking == false)
	{
		if (pos_x < UFO_POS_X[pos_no]) {
			pos_x += 2;
		}
		if (pos_x > UFO_POS_X[pos_no]) {
			pos_x -= 2;
		}
	}
	//if(pos_x <= -124 || pos_x >= 178)
	//    int iii = 0;

	//  座標がマイナスの場合もあるのでパターンが2個
	if (pos_x <= UFO_POS_X[pos_no] + 2 && pos_x >= UFO_POS_X[pos_no] - 2 ||
		pos_x <= UFO_POS_X[pos_no] - 2 && pos_x >= UFO_POS_X[pos_no] + 2) {
		ufo_time++;
		ufo_standhing = true;
		//	プレイヤー座標以外の時のUFOの座標

		if (pos_no >= 16)
		{
			pos_x = UFO_POS_X[pos_no];
			Tracking = false;
		}
		else
		{
			Tracking = true;
		}
	}
	//	プレイヤー追跡が終わってから
		if (ufo_time >= 7 && Tracking == false) {

		pos_no = GetRandomF(30 /*9*/);
		ufo_time = 0;
	}
}

void UFO::Draw()
{
	//  UFOのライトの薄くする
//MV1SetMeshDrawBlendMode(125,)
//    DrawPolygonIndexed3D({ pos_x,pos_y,pos_z },)

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, UFO_Blend);
	//  UFOのライトを描画する
	DrawCone3D({ pos_x,pos_y,pos_z }, { pos_x,0,pos_z }, UFO_LIGHT, 10, GetColor(255, 255, 0), GetColor(255, 255, 0), true);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);

	/*   DrawCube3D({pos_x - 5.0f, pos_y + 5.0f, pos_z},
				  {pos_x + 5.0f, pos_y, pos_z},
				  GetColor(125, 0, 0),
				  GetColor(125, 125, 125),
				  true);
   */
}

void UFO::Exit()
{
}
