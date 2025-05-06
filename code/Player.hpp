#ifndef PLAYER_H

#define PLAYER_H

#include "Entity.hpp"
#include "MovementComponent.hpp"
#include "Controller.hpp"

class Player : public Entity
{

private:
	MovementComponent movementComponent;

	Controller* controller = nullptr;

public:
	Player(Map& _map);

	void SetController(Controller* c) { controller = c; }

	void Update(Map& _map) override;

	MovementComponent GetMovementComponent() { return movementComponent; }

private:

};

#endif // !PLAYER_H
