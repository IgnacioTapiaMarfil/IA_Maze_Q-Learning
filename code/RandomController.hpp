#ifndef RANDOMCONTROLLER_H
#define RANDOMCONTROLLER_H

#include "Controller.hpp"
#include "Player.hpp"
#include <random>
#include "iostream"

enum class Movments
{
    Up = 0,
    Down = 1,
    Left = 2,
    Right = 3,
    None = 4
};

class RandomController : public Controller 
{
public:
    void DoAction(Player& player, Map& _map) override
    {
        bool actionDone = false;

        Movments dir = Movments::None;

        while (!actionDone)
        {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_int_distribution<> dis(0, 3);

            dir = static_cast<Movments>(dis(gen));

            switch (dir) 
            {
                case Movments::Up:
                    actionDone = player.GetMovementComponent().MoveUp();
                    std::cout << "UP" << "\n";
                    break;
                case Movments::Down:
                    actionDone = player.GetMovementComponent().MoveDown();
                    std::cout << "DOWN" << "\n";
                    break;
                case Movments::Left:
                    actionDone = player.GetMovementComponent().MoveLeft();
                    std::cout << "LEFT" << "\n";
                    break;
                case Movments::Right:
                    actionDone = player.GetMovementComponent().MoveRight();
                    std::cout << "RIGHT" << "\n";
                    break;
                default:
                    actionDone = false;
                    break;
            }
        }

        dir = Movments::None;
    }
};

#endif
