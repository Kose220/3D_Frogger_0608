﻿#include "Start_camera.h"
//#include "GameMain.h"

void Camera::Init()
{
    //  設定値は５００
    pos_z = -800.0f;
    camera_juge = true;
}
void Camera::Update()
{
    if(pos_z <= 30.0f) {
        pos_z += 2.0f;
    }
    if (pos_z >= 28.0f)
    {
        camera_juge = false;
    }
}

void Camera::Draw()
{
}

void Camera::Exit()
{
}
