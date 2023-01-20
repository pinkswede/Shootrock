#include "Media.h"

Textures Media::textures;
Sounds Media::sounds;

// putting all media in same location
void Media::LoadMedia()
{
	textures.ship = LoadTexture("./Resources/Textures/ship.png");
	textures.asteroid = LoadTexture("./Resources/Textures/Asteroid.png");
	textures.coin = LoadTexture("./Resources/Textures/coin.png");
	textures.laser = LoadTexture("./Resources/Textures/laser.png");
	textures.charge = LoadTexture("./Resources/Textures/charge.png");
	textures.chargep2 = LoadTexture("./Resources/Textures/chargep2.png");

	sounds.LaserShoot = LoadSound("./Resources/Sounds/Lasersound.wav");
}

void Media::UnloadMedia()
{
	UnloadTexture(textures.ship);

	UnloadSound(sounds.LaserShoot);
}