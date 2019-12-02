#pragma once
#include "Bullet.h"
#include "Artillery.h"
#include "Pokeball.h"
#include "Health.h"
#include <SFML/Graphics.hpp>
#include <string>


class Pokemon {
public:
	float rarity;

	sf::Sprite sprite;
	float x;                //x and y store current position
	float y;
	float speed;            //Determines how far pokemon moves each time you press l/r
	float velocityX;
	float velocityY;    	//will be needed to jump
	float accY;
	float jumpHeight;       // how high this pokemon can jump
	bool canJump;           // If you're on the ground, you can jump
	bool shooting;          // If you're shooting, we want to draw the pokeball
	Healthbar health;				// Health between 1 and 100
	Artillery bullets; 		// This is where all bullets are stored
							// If we want bullets to depend on Pokemon, bullets must have a constructor
	Pokemon()=default;
	Pokemon(float xstart, float ystart, float h, float v, float hp, std::string path, float pokemon_rarity);
	
protected:
	sf::Texture pic;
};
