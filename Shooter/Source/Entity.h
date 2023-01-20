#include "raylib.h"
#include "myMath.h"

enum struct EntityType
{
	rock, ship, laser, coin
};

class Entity {

public:
	EntityType entitytype;
	int speed;
	Vector2i position = {};
	int height;
	int width;
	Vector2i direction {0,0};

	bool dead = false;

};