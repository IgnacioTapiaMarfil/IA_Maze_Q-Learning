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

	void SetController(Controller* c) { controller = c; } Controller* GetController() const { return controller; }

	void Update(Map& _map, std::vector<Entity*>& entities) override;

	MovementComponent GetMovementComponent() { return movementComponent; }

private:

};

#endif // !PLAYER_H
