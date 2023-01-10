#include "Enemy.h"
#include <cstdlib>

Enemy::Enemy(COORD spawn)
{
	position = spawn;
}

void Enemy::PowerUpPicked()
{
	powerup_countdown = TimeManager::getInstance().time + powerup_countdown_time;
}




bool Enemy::Logic(Map* pacman_map, COORD playerPosition)
{
	
	int dir = rand() % 4; //Numero random de 0 a 4
	COORD position_new = position;
	switch (dir)
	{
	case 0:
		position_new.X++;
		break;
	case 1:
		position_new.X--;
		break;
	case 2:
		position_new.Y++;
		break;
	case 3:
		position_new.Y--;
		break;
	default:
		break;
	}

	if (position_new.X < 0)
	{
		position_new.X = pacman_map->Width - 1;
	}
	position_new.X %= pacman_map->Width;
	if (position_new.X < 0)
	{
		position_new.Y = pacman_map->Height - 1;
	}
	position_new.Y %= pacman_map->Height;

	if (pacman_map->GetTile(position_new.X, position_new.Y)!= Map::MAP_WALL)
	{
		position = position_new;
	}

	if (position.X == playerPosition.X && position.Y == playerPosition.Y)
	{
		if (powerup_countdown <= TimeManager::getInstance().time)
		{
			//muere el jugador
		}
		else
		{
			//como hacer que muera el enemigo
		}
	}
	if (powerup_countdown <= TimeManager::getInstance().time)
	{

		foreground = foreground_attack;
	}
	else
	{
		

		foreground = foreground_powerup;
	}

	return position.X == playerPosition.X && position.Y == playerPosition.Y;

}


void Enemy::Draw()
{
	ConsoleUtils::Console_SetPos(position);
	ConsoleUtils::Console_SetColor(foreground, background);
	std::cout << character;
	
}


