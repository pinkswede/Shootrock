Assignment - 2 

Game - Shoot Rock

Name : Adarsh Kumar

Instruction:
Welcome to my game Shoot Rock. The game is arcade based game and the goals is to shoot down the asteroids and dodge them. 

In order to win the game. Player has to score 10000 points.

Controls : The game has few controls. The arrow keys are used to control ship and move it. The Z key is pressed and hold in order to charge the laser and release to fire it when it is charged. Escape keep to pause the game.


Documents: 

// CPP Files

Level.cpp : It contains all the logic for the game level. It contains the entites vector, list of entities and all the functions related to the game.

LevelGraphics.cpp : This cpp files contains the render function for the game. It renders all the texture in game screen.

Game.cpp : It is used to create the menu system for the game. 

myMath.cpp : It contains all the mathematical functions for the other part of codes.

ResourceManager.cpp : This is used to load all the textures and sounds.

main.cpp : It initialize the game window and loads resources and runs the game. at the end of it deinitializes the resources.


//HEADER

CONSTANTS.h : This header contains the constant values like speed of entities.

Entity.h : It defines the entities and the different types of entities.

Level.h : It defines the storage for the entities and logical functions of the game like movement,spawn and update.

Game.h : It defines the menu states and menu gui functions. Also Handles the level as it goes through it to the main.

ResourceManager.h : It defines the struct for texture and sounds and loadre and Unload functions for the resources.

// FILE SYSTEM

There is resources folder that contails :

Sounds folder : It contains all the sounds for the game.

Textures folder : This files contains all the texture for the game.



WHAT HAPPENS IN THE CODE?

In Main.cpp, It use switch for different states of the window which can be seen in Game.h file, It initializes raylib stuff, loads the resources from ResourceManager.h, spawn the player and starts the game loop when it is in GAME state. It runs the render and update function(Level.h). Later it unloads the resources(In ResourceManager.cpp before closing the window.

In Level.cpp, It has all the functions running. In update function, It spawns all the entities and push back to the vector through add_entity functions. It creates movement for player and update other object movements. It keep check for the collision between objects too. Also, At the end of each frame. It adds the entities to the list by refreshentities() function.
