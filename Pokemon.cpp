#include "Pokemon.h"


	Pokemon::Pokemon(float xstart, float ystart, float h, float v)
	{
		health.setHealth(100); 		// Pokemon starts with full health when it is created
		velocityX = 0.0f;
		velocityY = 0.0f;
		jumpHeight = h;
		speed = v;
		canJump = true;
		shooting = false;
		x = xstart;
		y = ystart;
		sprite.setPosition(sf::Vector2f(x, y));
		
		if (!pic.loadFromFile("Images/eevee.png")){ std::cout << "could not load" << std::endl;}
		pic.loadFromFile("Images/eevee.png");
		sprite.setTexture(pic);
		sprite.setScale(sf::Vector2f(0.4f, 0.4f));
		was_released = true;

		max_available_bullets = 15;
		available_bullets = 15; //will be regenerated with time


	}

	void Pokemon::draw(sf::RenderTarget& target) const {
    	target.draw(sprite);
		health.draw(target);

	}

	void Pokemon::update(float& deltaTime, sf::RenderWindow& window) {   // Movement is dependant on time not on frame rate
									// This means that we can have smooth movement over multiple frames, instead of static movement per each frame
		velocityX = 0.0f;
		//Left and right movement
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
			velocityX -= speed;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
			velocityX += speed;
		}
		//Jumps
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && canJump) {
			canJump = false;       //While jumping you can't jump
			velocityY = -sqrt(2.0f * 981.0f * jumpHeight);
		}
		//Testing health - will change when we have collision recognition
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
			health.setHealth(health.getHealth() - 1);
		}
		/* //One parabolic shot - use for Pokeballs?
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			ball.setPosition(x, y);     // Need to figure out where the starting x and y position are
			ball.velocityY = -sqrt(2.0f * 981.0f * ball.ballHeight); //We need to reset the ball's position and starting speed when you shoot, that's why its in this class
			shooting = true;
		}
		//Continuation of the one shot as time goes by
		if (shooting) {
			bool shoot = ball.update(deltaTime);
			if (!shoot) { shooting = false; }
		} */


		//bullets---------------------------

		//we should not be able to shoot continuously
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			if (was_released && available_bullets > 0) {

				Bullet new_bullet;
				//we want the bullet to start from the midlle right of the pokemon
				//for later: careful if we change the origin of the pokemon
				float x_bullet = x + sprite.getGlobalBounds().width;
				float y_bullet = y + sprite.getGlobalBounds().height / 2;
				sf::Vector2f initial_pos(x_bullet, y_bullet);
				new_bullet.setPosition(initial_pos); // start at the 'middle-right' of the pokemon
				//that stuff should go in the bullet class

				//Get the mouse position:
				sf::Vector2i mouse = sf::Mouse::getPosition(window);
				//sf::Mouse::getPosition returns the position of the curson in window coordinates 
				//while all the entities use world coordinates.
				//We fix this by using the mapPixelToCoords member function.
				sf::Vector2f mouse_position = window.mapPixelToCoords(mouse);
				new_bullet.set_shoot_dir(mouse_position, initial_pos);

				bullets.push_back(new_bullet);//append the new bullet to our array

				available_bullets -= 1;
				std::cout << "available bullets -1 : " << available_bullets<<std::endl;
			}

			was_released = false;

			//to do: We should not be able to shoot 'as many bullets as we want'
			//if we shoot too much too fast, we have no bullets left and have to wait a little bit
			//we should also draw a bar that shows how much bullets we have remaining


		}

		if (! sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			was_released = true;
		}

		//-----------------------------------

		health.update(); 	// Need to still react to bullets and decrease our health
							//AND NB need to make this change health.health
		 
		velocityY += 981.0f * deltaTime;
		move(deltaTime);
	}



	void Pokemon::move(float& deltaTime) {
		x += velocityX * deltaTime;
		y += velocityY * deltaTime;
		float groundY = 300.0f; //Cannot go below this height
		if (y >= groundY) {
			y = groundY;
			velocityY = 0.0f;
			canJump = true;
		}

		sprite.setPosition(x, y);
	}



	void Pokemon::update_bullets(float& deltaTime) {
		for (int  i = 0; i < bullets.size(); i++) {
			bullets[i].update(deltaTime);
			if (bullets[i].offscreen())
				bullets.erase(bullets.begin() + i);
			//we loop over the bullets and if a bullet is offscreen, remove it
			//we will also need to chack collisions
			// I think the 'erase()' this is pretty inefficient, we might need to find a better way
		}
	}
