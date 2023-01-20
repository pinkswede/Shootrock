#include"raylib.h"

// organised all tecxtures under one structure
struct Textures
{
	Texture2D ship;
	Texture2D asteroid;
	Texture2D coin;
	Texture2D laser;
	Texture2D charge;
	Texture2D chargep2;
};

struct Sounds
{
	Sound LaserShoot;
};

// grouping media
struct Media
{
	static Textures textures;
	static Sounds sounds;

	static void LoadMedia();
	static void UnloadMedia();
};