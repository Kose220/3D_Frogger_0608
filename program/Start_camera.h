#pragma once

class Camera
{
public:
	//  基本X座標はプレイヤーの真後ろなので消す
	//    float pos_x;
	float pos_z;
	//    Y座標の高さも基本的にはいじらないので消す
	//    float pos_y;

	//  カメラがプレイヤー方向に向かっているかどうか判定する変数
	bool camera_juge;

	void Init();
	void Update();
	void Draw();
	void Exit();
	void GUI();
};
