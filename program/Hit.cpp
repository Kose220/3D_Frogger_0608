#include "Main.h"
#include "Game.h"
#include "Hit.h"

//---------------------------------------------------------------------------------
//	‰~“¯Žm‚Ì“–‚½‚è”»’è
//---------------------------------------------------------------------------------
bool CheckCircleHit(Vector2& center1, float radius1, Vector2& center2, float radius2)
{
	float length = GetVector2Distance(center1, center2);
	float radius = radius1 + radius2;
	if (length <= radius) {
		return true;
	}
	return false;
}
