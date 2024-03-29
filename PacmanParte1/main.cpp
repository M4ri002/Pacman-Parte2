#include "Enemy.h"
#include "Player.h"
#include "TimeManager.h"
#include <vector>
#include "GlobalResources.h"

/// <summary>
/// Sets the needed variables
/// </summary>
void Setup();
/// <summary>
/// Handles the inputs
/// </summary>
void Input();
/// <summary>
/// Handles the logic of the game
/// </summary>
void Logic();
/// <summary>
/// Draws the screen
/// </summary>
void Draw();

GlobalResources globalResources;
Player player = Player(globalResources.pacman_map.spawn_player);
bool run = true;
bool win = false;
bool lose = false;

int main()
{
    Setup();
    while (run)
    {
        Input();
        Logic();
        Draw();
    }
}

void Setup()
{
    std::cout.sync_with_stdio(false);

    srand(time(NULL));

    

    std::cout << "Cuantos enemigos quieres?" << std::endl;
    std::cin >> globalResources.enemy_count;

    /*for (size_t i = 0; i < enemy_count; i++)
    {
        globalResources.enemigos.push_back(Enemy(globalResources.pacman_map.spawn_enemy));
    }*/
    player.player_x = globalResources.pacman_map.spawn_player.X;
    player.player_y = globalResources.pacman_map.spawn_player.Y;
}

void Input()
{
    globalResources.input = globalResources.USER_INPUTS::NONE;
    if (ConsoleUtils::KeyPressed(VK_UP) || ConsoleUtils::KeyPressed('W'))
    {
        globalResources.input = globalResources.USER_INPUTS::UP;
    }
    if (ConsoleUtils::KeyPressed(VK_DOWN) || ConsoleUtils::KeyPressed('S'))
    {
        globalResources.input = globalResources.USER_INPUTS::DOWN;
    }
    if (ConsoleUtils::KeyPressed(VK_RIGHT) || ConsoleUtils::KeyPressed('D'))
    {
        globalResources.input = globalResources.USER_INPUTS::RIGHT;
    }
    if (ConsoleUtils::KeyPressed(VK_LEFT) || ConsoleUtils::KeyPressed('A'))
    {
        globalResources.input = globalResources.USER_INPUTS::LEFT;
    }
    if (ConsoleUtils::KeyPressed(VK_ESCAPE) || ConsoleUtils::KeyPressed('Q'))
    {
        globalResources.input = globalResources.USER_INPUTS::QUIT;
    }
}

void Logic()
{
    if (globalResources.enemigos.size() < globalResources.enemy_count && TimeManager::getInstance().Contador())
    {
        globalResources.enemigos.push_back(Enemy(globalResources.pacman_map.spawn_enemy));
    }
    
    if (globalResources.input == GlobalResources::QUIT)
    {
        run = false;
    }
    if (win || lose)
    {
        switch (globalResources.input)
        {
        case GlobalResources::QUIT:
            run = false;
            break;
        }
    }
    if (player.vidas <= 0)
    {
        lose = true;
        run = false;
    }
    if (globalResources.pacman_map.points <= 0)
    {
        win = true;
        run = false;
    }

    for (size_t i = 0; i < globalResources.enemigos.size(); i++)
    {
       globalResources.enemigos[i].Logic(&globalResources.pacman_map, player.PlayerPosition);
    }
    player.Update(&globalResources.pacman_map, globalResources.input, globalResources.enemigos);
}

void Draw()
{
    ConsoleUtils::Console_SetPos(0,0);
    globalResources.pacman_map.Draw();


    for (size_t i = 0; i < globalResources.enemigos.size(); i++)
    {
        globalResources.enemigos[i].Draw();   
    }

    player.Draw();
    ConsoleUtils::Console_ClearCharacter({ 0,(short)globalResources.pacman_map.Height });
    ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::CYAN);
    std::cout << "Puntuacion actual: " << player.player_points << " Puntuacion pendiente: " << globalResources.pacman_map.points << std::endl;
    std::cout << "Fotogramas: " << TimeManager::getInstance().frameCount << std::endl;
    std::cout << "DeltaTime: " << TimeManager::getInstance().deltaTime << std::endl;
    std::cout << "Tiempo: " << TimeManager::getInstance().time << std::endl;
    //std::cout << "Tiempo Contador: " << TimeManager::getInstance().ContTime << std::endl;
    std::cout << "Enemigos: " << globalResources.enemigos.size() << std::endl;
    std::cout << "Vidas: " << player.vidas << std::endl;
    std::cout << "Contador: " << TimeManager::getInstance().contador << std::endl;


    /*if (TimeManager::getInstance().spawn)
    {
        i += 1;
        
    }*/


    
    if (win)
    {
        ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::GREEN);
        std::cout << "Has ganado!" << std::endl;
        std::cout << "Pulsa Q para salir." << std::endl;
    }
    if (lose)
    {
        ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::DARK_RED);
        std::cout << "Has perdido!" << std::endl;
        std::cout << "Pulsa Q para salir." << std::endl;

    }

    TimeManager::getInstance().nextFrame();
    //TimeManager::getInstance().EnemySpawn();

}