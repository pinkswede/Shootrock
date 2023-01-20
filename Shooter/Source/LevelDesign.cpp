#include "LevelDesign.h"

// made function for adding entity so its easier to add mutliple entities using same base code
void Level::add_entity(const Entity entities)
{
	EntityList.push_back(entities);

	tempentities.push_back(&EntityList.back());
}

//since many objects collide, function allows for code to be used with many objects
bool Level::checkcollision(Vector2i posA, int widthA, int heightA, Vector2i posB, int widthB, int heightB)
{
	if (posA.x <= posB.x + widthB && posA.x + widthA >= posB.x
		&& posA.y <= posB.y + heightB && posA.y + heightA >= posB.y)
	{
		return true;
	}
	else
		return false;
}

// ALL SPAWN FUNCTIONS were created for ease of use and organisation
void Level::spawnship()
{
	Entity ship;
	ship.position = { 400,400 };
	ship.entitytype = EntityType::ship;
	ship.height = 40;
	ship.speed = 10;
	ship.width = 40;

	ship.dead = false;

	add_entity(ship);
}

void Level::spawnrock()
{
	Entity rock;
	rock.position = { GetRandomValue(-20, GetRenderWidth()), 0 };
	rock.entitytype = EntityType::rock;
	rock.height = 30;
	rock.speed = GetRandomValue(4, 5);
	rock.width = 30;
	rock.direction = { GetRandomValue(-1, 1), 1 };

	rock.dead = false;

	add_entity(rock);
}

void Level::spawnlaser()
{
	Entity laser;
	laser.position = { GameEntities[0]->position.x + 15, GameEntities[0]->position.y };
	laser.entitytype = EntityType::laser;
	laser.height = 15;
	laser.speed = 10;
	laser.width = 5;
	laser.direction = {0,1};

	laser.dead = false;

	add_entity(laser);

}

void Level::spawncoin(Vector2i pos)
{
	Entity coin;
	for(int  i {0}; i < 5; i++)
	{
		coin.position = {pos.x + GetRandomValue(-70,70), pos.y + GetRandomValue(-70,70)};
		coin.entitytype = EntityType::coin;
		coin.height = 15;
		coin.speed = 1;
		coin.width = 15;
		coin.direction = { GetRandomValue(-1,1),1 };

		coin.dead = false;

		add_entity(coin);
	}
}

// function created in for organisational purouses
void Level::moveship()
{
	for (Entity* e : GameEntities)
	{
		if (e->entitytype == EntityType::ship)
		{
			if (IsKeyDown(KEY_LEFT) && e->position.x > 0)
			{
				e->position.x -= e->speed * 1;
			}
			if (IsKeyDown(KEY_RIGHT) && e->position.x < GetRenderWidth() - 40)
			{
				e->position.x += e->speed * 1;
			}
			if (IsKeyDown(KEY_UP) && e->position.y > 0)
			{
				e->position.y -= e->speed * 1;
			}
			if (IsKeyDown(KEY_DOWN) && e->position.y < GetRenderHeight() - 40)
			{
				e->position.y += e->speed * 1;
			}
		}
	}
}

// I created this function in order to control the spawn speed of rock and laser in relation to time/FPS, since these elements rely on this
void Level::spawntimecontrol()
{
	// rock spawn
	rock_time--;

	if (rock_time == 55)
	{
		spawnrock();
	}
	else if (rock_time == 30)
	{
		spawnrock();
	}

	if (rock_time <= 0)
	{
		rock_time = 60;
	}

	// laser spawn
	if (IsKeyDown(KEY_Z))
	{
		laser_charge_time--;
	}
	if (IsKeyReleased(KEY_Z) && laser_charge_time <= 0)
	{
		PlaySoundMulti(Media::sounds.LaserShoot);
		spawnlaser();
		laser_charge_time = 40;
	}
	if (laser_charge_time >= 0 && IsKeyReleased(KEY_Z))
	{
		laser_charge_time = 40;
	}

}

// This function was created for ease of movement, its easier to do all movement within single function
void Level::entitymovement()
{
	for (Entity* a : GameEntities)
	{
		switch (a->entitytype)
		{
		case(EntityType::rock):
		{
			a->position.y += a->speed * a->direction.y;
			a->position.x += a->direction.x;
		}
		break;
		case(EntityType::laser):
		{
			a->position.y -= a->speed * a->direction.y;
			
			if (a->position.y <= 0)
			{
				a->dead = true;
			}

		}
		break;
		case(EntityType::coin):
		{
			a->position.y += a->speed * a->direction.y;
			a->position.x += a->direction.x;
		}
		}
	}
	
}

// created to control all collisions within one place, as collisions happen a lot in game (organisational)
void Level::entitycollisions()
{
	if (combo_collision)
	{
		combo_time--;
	}
	if (combo_time <= 0)
	{
		combo_collision = false;
		combo_time = 100;
		coinvalue = 50;
	}

	if (text_bool == true)
	{
		text_timer--;
		if (text_timer > 0)
		{
			DrawText(TextFormat("+%i", coinvalue), GameEntities[0]->position.x+40, GameEntities[0]->position.y -30, 20, WHITE);
		}
		if (text_timer <= 0)
		{
			text_timer = 20;
			text_bool = false;
		}
	}

	for (Entity* a : GameEntities)
	{
		switch (a->entitytype)
		{
		case(EntityType::ship):
		{
			for (Entity* z : GameEntities)
			{
				switch (z->entitytype)
				{
				case(EntityType::rock):
				{
					bool collision = checkcollision(a->position, a->width, a->height, z->position, z->width, z->height);
					if (collision == true)
					{
						a->dead = true;
						ship_death = true;
					}
				}
				break;
				}
			}
		}
		break;
		case(EntityType::laser):
		{
			for (Entity* z : GameEntities)
			{
				switch (z->entitytype)
				{
				case(EntityType::rock):
				{
					bool collision = checkcollision(a->position, a->width, a->height, z->position, z->width, z->height);
					if (collision == true)
					{
						z->dead = true;
						spawncoin(z->position);
					}
				}
				break;
				}
			}
		}
		break;
		case(EntityType::coin):
		{
			for(Entity* x : GameEntities)

				switch (x->entitytype)
				{
				case(EntityType::ship):
				{
					bool collision = checkcollision(x->position, x->width, x->height, a->position, a->width, a->height);
					if (collision == true)
					{

						text_bool = true;
						
						if (combo_time < 100)
						{
							coinvalue += 10;
						}
						score += coinvalue;
						a->dead = true;
						combo_collision = true;
							
					}
				}
				}
		}

		}
	}
}

// created to remove and add by calling it at the start of each frame in update function, so that pointers in vector dont become invalid
void Level::destroy_add_ents() {
	auto new_last_entity = std::remove_if(GameEntities.begin(), GameEntities.end(), [](const Entity* e) -> bool { return e->dead; });

	GameEntities.erase(new_last_entity, GameEntities.end());

	EntityList.remove_if([](const Entity& e) -> bool { return e.dead; });

	while (tempentities.size() != 0)
	{
		GameEntities.push_back(tempentities.back());
		tempentities.pop_back();
	}
}
// basic render function, draws elements
void Level::render()
{
	DrawText(TextFormat("%i", score), 380, 20, 30, WHITE);

	for (Entity* e : GameEntities)
	{
		switch (e->entitytype)
		{
		case(EntityType::ship):
		{
			if (IsKeyDown(KEY_Z) && laser_charge_time > 20)
			{
				DrawTexture(Media::textures.charge, e->position.x+5, e->position.y - 20, WHITE);
			}
			if (IsKeyDown(KEY_Z) && laser_charge_time <= 20)
			{
				DrawTexture(Media::textures.chargep2, e->position.x + 12, e->position.y - 20, WHITE);
			}
			DrawTexture(Media::textures.ship, e->position.x, e->position.y, WHITE);
		}
		break;

		case(EntityType::rock):
		{
			DrawTexture(Media::textures.asteroid, e->position.x, e->position.y, WHITE);
		}
		break;

		case(EntityType::laser):
		{
			DrawTexture(Media::textures.laser, e->position.x, e->position.y, WHITE);;
		}
		break;

		case(EntityType::coin):
		{
			DrawTexture(Media::textures.coin, e->position.x, e->position.y, WHITE);
		}
		break;
		}
	}
}

// resets all parameters
void Level::resetlevel()
{
	ship_death = false;
	GameEntities.clear();
	EntityList.clear();
	spawnship();
	score = 0;
}

void Level::update()
{
	destroy_add_ents();
	moveship();
	spawntimecontrol();
	entitymovement();
	entitycollisions();
}