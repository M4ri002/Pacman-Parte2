#pragma once
#include "Map.h"
#include <time.h>
#include <vector>

#include "TimeManager.h"

class Enemy
{
public:
	COORD position;



private:
	char character = 'E';
	float powerup_countdown = 0;
	const float powerup_countdown_time = 15;
	ConsoleUtils::CONSOLE_COLOR foreground = ConsoleUtils::CONSOLE_COLOR::DARK_RED;
	ConsoleUtils::CONSOLE_COLOR background = ConsoleUtils::CONSOLE_COLOR::BLACK;

	ConsoleUtils::CONSOLE_COLOR foreground_attack = ConsoleUtils::CONSOLE_COLOR::DARK_RED;
	ConsoleUtils::CONSOLE_COLOR foreground_powerup = ConsoleUtils::CONSOLE_COLOR::CYAN;

public:
	//enum ENEMY_STATE {ENEMY_NONE, ENEMY_KILLED, ENEMY_DEAD};
	Enemy(COORD spawn);
	void PowerUpPicked();
	bool Logic(Map* pacman_map, COORD playerPosition);
	void Draw();
	



};

