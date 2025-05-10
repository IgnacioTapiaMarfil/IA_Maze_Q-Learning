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

	bool dead;

	bool arrive;

public:
	Player(Map& _map);

	void SetController(Controller* c) { controller = c; } Controller* GetController() const { return controller; }

	void Update(Map& _map, std::vector<Entity*>& entities) override;

	MovementComponent GetMovementComponent() { return movementComponent; }

	void SetArrive(bool _arrive) { arrive = _arrive; }
	bool GetArrive() { return arrive; }

	void SetDead(bool _dead) { dead = _dead; }
	bool GetDead() { return dead; }

};

#endif // !PLAYER_H
