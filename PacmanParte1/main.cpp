#include "Map.h"
#include "Player.h"
#include "TimeManager.h"


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

Map pacman_map = Map();
std::vector<Enemy> enemigos;
Player player = Player(pacman_map.spawn_player);
USER_INPUTS input = USER_INPUTS::NONE;
bool run = true;
bool win = false;

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
   
    unsigned short enemyNumber = 0;
    std::cout << "Cuantos enemigos quieres?";
    std::cin >> enemyNumber;
    for (size_t i = 0; i < enemyNumber; i++)
    {
        enemigos.push_back(Enemy(pacman_map.spawn_enemy));
    }
}

void Input()
{
    input = USER_INPUTS::NONE;
    if (ConsoleUtils::KeyPressed(VK_UP) || ConsoleUtils::KeyPressed('W'))
    {
        input = USER_INPUTS::UP;
    }
    if (ConsoleUtils::KeyPressed(VK_DOWN) || ConsoleUtils::KeyPressed('S'))
    {
        input = USER_INPUTS::DOWN;
    }
    if (ConsoleUtils::KeyPressed(VK_RIGHT) || ConsoleUtils::KeyPressed('D'))
    {
        input = USER_INPUTS::RIGHT;
    }
    if (ConsoleUtils::KeyPressed(VK_LEFT) || ConsoleUtils::KeyPressed('A'))
    {
        input = USER_INPUTS::LEFT;
    }
    if (ConsoleUtils::KeyPressed(VK_ESCAPE) || ConsoleUtils::KeyPressed('Q'))
    {
        input = USER_INPUTS::QUIT;
    }
}

void Logic()
{
    if (win)
    {
        switch (input)
        {
        case QUIT:
            run = false;
            break;
        }
    }
    else
    {
        if (input == USER_INPUTS::QUIT)
            run = false;
        player.Update(&pacman_map, input,  &enemigos);

        for (size_t i = 0; i < enemigos.size(); i++)
        {
            Enemy::ENEMY_STATE enemystate = enemigos[i].Update(&pacman_map, player.position);
            switch (enemystate)
            {
            case Enemy::ENEMY_KILLED:
                break;
            case Enemy::ENEMY_DEAD:
               pacman_map.spawn_player.X;
               pacman_map.spawn_player.Y;
                break;
            }
        }

        if (pacman_map.points <= 0)
        {
            win = true;
        }
        /*Enemy::ENEMY_STATE enemy1state = enemy1.Update(&pacman_map, {(short)player_x, (short)player_y});
        switch (enemy1state)
        {
        case Enemy::ENEMY_KILLED:
            player_points += 50;
            break;
        case Enemy::ENEMY_DEAD:
            player_x = pacman_map.spawn_player.X;
            player_y = pacman_map.spawn_player.Y;
            break;
        }*/
    }
}

void Draw()
{
    ConsoleUtils::Console_SetPos(0,0);
    pacman_map.Draw();
   // ConsoleUtils::Console_SetPos(player_x, player_y);
   // ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::DARK_YELLOW);
   // std::cout << player_char;
    player.Draw();
    
    //enemy1.Draw();
    
    for (size_t i = 0; i < enemigos.size(); i++)
    {
        enemigos[i].Draw();
    }

    ConsoleUtils::Console_ClearCharacter({ 0,(short)pacman_map.Height });
    ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::CYAN);
    std::cout << "Puntuacion actual: " <<player.points << " Puntuacion pendiente: " << pacman_map.points << std::endl;
    if (win)
    {
        ConsoleUtils::Console_SetColor(ConsoleUtils::CONSOLE_COLOR::GREEN);
        std::cout << "Has ganado!" << std::endl;
    }
    std::cout <<"Fotogramas: " << TimeManager::getInstance().frameCount << std::endl;
    std::cout << "Time: " << TimeManager::getInstance().time << std::endl;
    std::cout << "DeltaTime: " << TimeManager::getInstance().deltaTime << std::endl;
    TimeManager::getInstance().NextFrame();
}