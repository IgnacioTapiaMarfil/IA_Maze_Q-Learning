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

	int StartPosX, StarPosY;

	bool dead;

	bool kill;

	bool arrive;

	bool treasureCatched;

	int enemiesKilled, treasuresCaught, deaths;
	int totalEnemiesKilled, totalTreasuresCaught;


public:
	Player(Map& _map);

	void SetController(Controller* c) { controller = c; } Controller* GetController() const { return controller; }

	void Update(Map& _map, std::vector<Entity*>& entities) override;

	void Reset();

	MovementComponent GetMovementComponent() { return movementComponent; }

	void SetArrive(bool _arrive) { arrive = _arrive; }
	bool GetArrive() const { return arrive; }

	void SetDead(bool _dead) { dead = _dead; }
	bool GetDead() const { return dead; }

	void SetKill(bool _kill) { kill = _kill; }
	bool GetKill() const { return kill; }

	void SetTreasureCached(bool _treasureCached) { treasureCatched = _treasureCached; }
	bool GetTreasureCached() const { return treasureCatched; }

	int GetEnemiesKilled()  const { return enemiesKilled; }
	int GetTotalEnemiesKilled()  const { return totalEnemiesKilled; }
	int GetTreasuresCaught() const { return treasuresCaught; }
	int GetTotalTreasuresCaught() const { return totalTreasuresCaught; }
	int GetDeaths() const { return deaths; }

private:
	void Fight(Entity* _enemy);
};

#endif // !PLAYER_H
