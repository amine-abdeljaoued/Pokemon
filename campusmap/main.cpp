#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include "tilemap.hpp"


int main()
{
    sf::Texture texturePlayer;
    if (!texturePlayer.loadFromFile(/* resourcePath() + */ "Sprites/fullch.png")) {
        return EXIT_FAILURE;
    }
    sf::Sprite spritePlayer(texturePlayer);

    spritePlayer.setTextureRect(sf::IntRect(0,0,64,64));
    spritePlayer.setScale(sf::Vector2f(0.5f, 0.5f));
    
    //Variables for the character
    float playerMovementSpeed = 4;

    int counterWalk = 0;
    
    sf::View view(sf::Vector2f(272, 272), sf::Vector2f(544, 544));
    view.zoom(0.5f);
    
    
//    sf::View minimapView(sf::Vector2f(272, 272), sf::Vector2f(544, 544));
//    minimapView.setViewport(sf::FloatRect(0.75f, 0, 0.25f, 0.25f));
    
    spritePlayer.setPosition(262, 272);
    

    sf::RenderWindow window(sf::VideoMode(544, 544), "Tilemap");

    const int level[] =
    {
        3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,
        3,60, 01, 01, 01, 01, 01, 01, 01, 01, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,61,3,
        3,8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,9, 9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,10,3,
        3,8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,9, 9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,10,3,
        3,8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9,9, 9,9,9,4,5,5,6,9,9,9,9,9,9,9,9,9,10,3,
        3,68, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 17, 6, 9,9,9,12,13,13,14,9,9,4,17,17,17,17,17,17,69,3,
        3,3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 68, 6,9,9,12,13,13,14,9,9,10,3,3,3,3,3,3,3,3,
        3,3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 68,6,9,20,21,21,22,9,9,10,3,3,3,3,3,3,3,3,
        3,3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,8,9,9,9,9,9,9,9,10,3,3,3,3,3,3,3,3,
        3,3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,8,9,9,9,9,9,9,9,10,3,3,3,3,3,3,3,3,
        3,3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,68,17,17,17,17,17,17,17,69,3,3,3,3,3,3,3,3,
    };


    TileMap map;
    
    if (!map.load("Sprites/eau_trouble.png", sf::Vector2u(16, 16), level, 34, 11)) return -1;

    const int level2[] =
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,
        1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
        
    };

    TileMap bigmap;
    
    if (!bigmap.load("Sprites/herbe.png", sf::Vector2u(16, 16), level2, 34,34 )) return -1;
    
    while (window.isOpen())
    {
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            if(event.type == sf::Event::Closed) window.close();
            
            if (event.type == sf::Event::KeyPressed){
                sf::Vector2f position = spritePlayer.getPosition();
                std::cout<<(position.x+10)/16<<","<<(position.y/16)+1<<std::endl;
                
            
                if (event.key.code == sf::Keyboard::Left) {
                    spritePlayer.move(-playerMovementSpeed, 0);
                    spritePlayer.setTextureRect(sf::IntRect(counterWalk * 64,64,64,64));
                    view.move(-playerMovementSpeed, 0);
                    
                }
                if (event.key.code == sf::Keyboard::Right) {
                    spritePlayer.move(playerMovementSpeed, 0);
                    spritePlayer.setTextureRect(sf::IntRect(counterWalk * 64,2*64,64,64));
                    view.move(playerMovementSpeed, 0);
                   
                }
                if (event.key.code == sf::Keyboard::Up) {
                    spritePlayer.move(0, -playerMovementSpeed);
                    spritePlayer.setTextureRect(sf::IntRect(counterWalk * 64,3*64,64,64));
                    view.move(0, -playerMovementSpeed);
                    
                }
                if (event.key.code == sf::Keyboard::Down) {
                    spritePlayer.move(0, playerMovementSpeed);
                    spritePlayer.setTextureRect(sf::IntRect(counterWalk * 64,0,64,64));
                    view.move(0,playerMovementSpeed);
                    
                }
                counterWalk++;
                if(counterWalk==3){
                    counterWalk=0;
                }
            }
        }
        
        
        window.clear();
        
        window.draw(bigmap);
        
        window.draw(map);
        
        window.draw(spritePlayer);

        window.setView(view);
        
        window.display();
    }

    return 0;
}

