#include "Player.h"
bool Player::CheckCollision(Solid* other)
{
	return CollisionHandler.CheckCollision(other);
}