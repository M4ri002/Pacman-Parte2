#include "Player.h"
#include "Enemy.h"
#include "GlobalResources.h"
#include <cstdlib>

Player::Player(COORD spawn)
{
   PlayerPosition = spawn;
}




void Player::Update(Map* pacman_map, GlobalResources::USER_INPUTS input, std::vector<Enemy> enemigos)
{

    COORD playerPos;
    playerPos.X = player_x;
    playerPos.Y = player_y;
    bool playerDie = false;
    for (size_t i = 0; i < enemigos.size(); i++)
    {
        if (enemigos[i].Logic(pacman_map, playerPos))
        {
            playerDie = true;
            
        }
    }
    if (playerDie)
    {
        player_x = pacman_map->spawn_player.X;
        player_y = pacman_map->spawn_player.Y;
    }
    int player_y_new = player_y;
    int player_x_new = player_x;

    switch (input)
    {
    case GlobalResources::UP:
        player_y_new--;
        break;
    case GlobalResources::DOWN:
        player_y_new++;
        break;
    case GlobalResources::RIGHT:
        player_x_new++;
        break;
    case GlobalResources::LEFT:
        player_x_new--;
        break;

    }
    if (player_x_new < 0)
    {
        player_x_new = pacman_map->Width - 1;
    }
    player_x_new %= pacman_map->Width;
    if (player_y_new < 0)
    {
        player_y_new = pacman_map->Height - 1;
    }
    player_y_new %= pacman_map->Height;

    switch (pacman_map->GetTile(player_x_new, player_y_new))
    {
    case Map::MAP_TILES::MAP_WALL:
        player_y_new = player_y;
        player_x_new = player_x;
        break;
    case Map::MAP_TILES::MAP_POINT:
        pacman_map->points--;
        player_points++;
        pacman_map->SetTile(player_x_new, player_y_new, Map::MAP_TILES::MAP_EMPTY);
        break;
    case Map::MAP_TILES::MAP_POWERUP:
        player_points += 25;
        //Como llamar a la funcion de enemigo desde aqui Enemy::PowerUpPicked();
        pacman_map->SetTile(player_x_new, player_y_new, Map::MAP_TILES::MAP_EMPTY);
        break;
    }

    player_y = player_y_new;
    player_x = player_x_new;


        

    }


void Player::Draw()
{
	ConsoleUtils::Console_SetPos(player_x, player_y);
	ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::DARK_YELLOW);
	std::cout << player_char;

}


