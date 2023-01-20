#include "entity.h"
#include<vector>
#include <list>
#include "Media.h"	

class Level 
{
	std::list<Entity> EntityList;

	std::vector<Entity*> tempentities {};
	std::vector<Entity*> GameEntities = {};


	public:

		int rock_time = 60;
		int laser_charge_time = 40;
		int score;
		int combo_time = 100;
		int coinvalue = 50;
		int text_timer = 20;
		bool ship_death = false;
		bool combo_collision = true;
		bool text_bool = false;

		void add_entity(const Entity entities);
		void spawnship();
		void spawnrock();
		void spawnlaser();
		void spawncoin(Vector2i pos);
		void spawntimecontrol();
		void moveship();
		void entitymovement();
		void destroy_add_ents();
		bool checkcollision(Vector2i posA, int widthA, int heightA, Vector2i posB, int widthB, int heightB);
		void entitycollisions();
		void resetlevel();

		void render();
		void update();

};

