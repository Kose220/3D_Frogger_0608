#include"Minimap.h"
#include"DxLib.h"
#include"Player.h"

Player miniPlayer;

void Minimap::Init()
{
	map_y = 700 ;

	map_player_y = 680;

	map_icon_player = LoadGraph("data/Game/Map/ÇÀÇ∏Ç›ê∂ë∂.png");
	map_icon_dead = LoadGraph("data/Game/Map/ÇÀÇ∏Ç›éÄñS.png");

	map_icon_switch = true;
}
void Minimap::Update()
{
	map_player_y = 680 + miniPlayer.pos_z;
}
void Minimap::Draw()
{
	DrawBox(30, 80, 40, map_y, GetColor(255, 255, 255), TRUE);

	DrawBox(45, 80, 25, 85, GetColor(255, 255, 255), true);
	DrawBox(45, map_y, 25, map_y - 5, GetColor(255, 255, 255), true);


	//	DrawBox(45, map_player_y + 5, 25, map_player_y - 5, GetColor(0, 0, 0), true);
	if (map_icon_switch) {
		DrawRotaGraph(37.5f, map_player_y, 0.125f, 0.0f, map_icon_player, true);
	}
	else{
	DrawRotaGraph(37.5f, map_player_y, 0.125f, 0.0f, map_icon_dead, true);
	}
}
void Minimap::Exit()
{

}