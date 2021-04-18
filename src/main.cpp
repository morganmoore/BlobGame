#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "enemy.h"
#include "player.h"
#include<windows.h>

//get random float between two values
float randomFloat(float a, float b) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

//get distance between two points
float getDistance(int x1, int y1, int x2, int y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) +
        pow(y2 - y1, 2) );
}

//to do: create class for both camera and User Interface

//update camera viewing plane in repsonse to player movment or increase in size
void updateCamera(Player player, sf::View& view, sf::RenderWindow& app, float centreX, float centreY, float mapW, float mapH, float cameraW, float cameraH)
{
    
    view.setCenter(centreX, centreY);
    app.setView(view);

	//adjusting camera view to the size of the player e.g. larger view as player size increases
    float newViewX = cameraW * pow(player.getRadius() / 20, 0.1);
    float newViewY = cameraH * pow(player.getRadius() / 20, 0.1);

	//gradually increment to new value
    if (cameraW < newViewX) { cameraW += 1; }
    if (cameraH < newViewY) { cameraH += 1; }
	
    view.setSize(cameraW, cameraH);
}

//draw 'mini player' to mini map and move map with player movement
void updateMiniMap(sf::Sprite& sMiniMap, sf::RenderWindow& app, float centreX, float centreY, float bgW, float bgH, Player player, sf::CircleShape& miniMapDot)
{
    sMiniMap.setPosition(centreX + 230, centreY + 80);
    miniMapDot.setPosition((centreX + 185) + (player.getPos().x / bgW) * 355, (centreY + 35) + (player.getPos().y / bgH) * 355);
    app.draw(sMiniMap);
    app.draw(miniMapDot);
	
}

int main()
{
    srand(time(0));
	
	//size of camera viewing plane
    const float cameraW= 1000.0f;
    const float cameraH = 700.0f;

	//full background image width and height
    const int bgW = 3000;
    const int bgH = 3000;

	//the width and height of the playable area,
    const float mapW = bgW- cameraW;
    const float mapH = bgH -cameraH;

	//position of camera viewing plane
    float centreX = bgW / 2;
    float centreY = bgH / 2;

	//creating window and setting viewing plane
    sf::RenderWindow app(sf::VideoMode(cameraW, cameraH), "Doodle Game!");
    sf::View view(sf::Vector2f(centreX, centreY), sf::Vector2f(cameraW, cameraH));
    app.setView(view);

    app.setFramerateLimit(80);
    int framecount = 0;
    

    Player player(20, { centreX, centreY }, { 255,200,0 }, 20.f, "Player 1");

    int numEnemies = 20;
    std::vector<Enemy> enemies;

	//creating and intialising the number of Enemies
	for(int i = 0; i<= numEnemies; i++)
	{
		Vec2 pos = {rand() % (int)mapW + 500, rand() % (int)mapH + 500};
        Colour col = { rand() % 215 + 40, rand() % 215 + 40, rand() % 215 + 40 };
        float rad = randomFloat(10.f, 25.f);
        Enemy enemy(rad, pos, col);
        enemies.push_back(enemy);
	}

	//loading texture needed for game
    sf::Texture t1,t2,t3;
    t1.loadFromFile("images/background5.png");
    t2.loadFromFile("images/minimap.png");

	//creating sprites with textures
    sf::Sprite sBackground(t1), sMiniMap(t2);

    sf::CircleShape miniMapDot(4);
    miniMapDot.setRadius(5);
    miniMapDot.setOrigin(5, 5);
    miniMapDot.setFillColor(sf::Color(250, 150, 0));
	
    int first_time = time(NULL);
    bool bDead = false;

	//the distance from which enemies will become aware of player
    float awareDistance = 20.f;

    //program main loop
    while (app.isOpen())
    {
	    sf::Event e;
        while (app.pollEvent(e))
        {
        	//if the window is closed
            if (e.type == sf::Event::Closed)
            {
                //print frames per second and close window
                int second_time = time(NULL);
                std::cout << framecount / (second_time - first_time) << std::endl;
                app.close(); 
            }
        }
        
        framecount++;
    	
        app.draw(sBackground);

        const sf::Vector2i mousePosition{ sf::Mouse::getPosition(app) };
        const sf::Vector2f mouseCoord{ app.mapPixelToCoords(mousePosition) };
        player.updatePos(mouseCoord.x, mouseCoord.y);
        player.draw(app);

    	
        for (int i = 0; i<enemies.size(); i++)
        {
            float distFromPlayer = getDistance(enemies[i].getPos().x, enemies[i].getPos().y, player.getPos().x, player.getPos().y);
            

        	//if the player and enemy are within 'aware distance' units of each other
            if (distFromPlayer < (enemies[i].getRadius() + player.getRadius() + awareDistance))
            {
                //if enemy bigger than player
                if (enemies[i].getRadius() > player.getRadius())
                {
                    //if enemy and player overlapping 
                	if(distFromPlayer <(enemies[i].getRadius() + player.getRadius()))
                	{
                        //print frames per second and close window
                        int second_time = time(NULL);
                        std::cout << framecount / (second_time - first_time) << std::endl;
                        app.close();
                        break;
                	}
                    //else move enemy towards player
                    if (enemies[i].getPos().x < player.getPos().x - enemies[i].getSpeedIncrement()) { enemies[i].updateVelX(1); }
                    else if (enemies[i].getPos().x > player.getPos().x + enemies[i].getSpeedIncrement()) { enemies[i].updateVelX(-1); }
                    if (enemies[i].getPos().y < player.getPos().y - enemies[i].getSpeedIncrement()) { enemies[i].updateVelY(1); }
                    else if (enemies[i].getPos().y > player.getPos().y + enemies[i].getSpeedIncrement()) { enemies[i].updateVelY(-1); }
                }
                //if player bigger than enemy
                else
                {
                    //if enemy and player overlapping 
                    if (distFromPlayer < (enemies[i].getRadius() + player.getRadius()))
                    {
                    	//remove enemy from vector and ajust increment (--i)
                        player.updateSize(enemies[i].getRadius());
                        enemies.erase(enemies.begin() + i);
                        --i;
                    }
                    else
                    {
                    	//move enemy away from player
                        if (enemies[i].getPos().x < player.getPos().x - 2) { enemies[i].updateVelX(-1); }
                        else if (enemies[i].getPos().x > player.getPos().x + 2) { enemies[i].updateVelX(1); }
                        if (enemies[i].getPos().y < player.getPos().y - 2) { enemies[i].updateVelY(-1); }
                        else if (enemies[i].getPos().y > player.getPos().y + 2) { enemies[i].updateVelY(1); }
                    }  
                }		
            }
        	
            else
            {
                //check if enemy is outside map
                enemies[i].checkOutsideMap();
            }
        	
        	//update enemy position and draw to screen
            enemies[i].updatePos();
            enemies[i].draw(app);
        }

    	//setting the position of the camera viewing plane
        centreX = std::max(cameraW / 2, std::min(player.getPos().x, mapW + cameraW / 2));
        centreY = std::max(cameraH / 2, std::min(player.getPos().y, mapH + cameraH / 2));

        updateCamera(player, view, app, centreX, centreY,  mapW, mapH, cameraW, cameraH);
        updateMiniMap(sMiniMap, app, centreX, centreY, bgW, bgH, player, miniMapDot);

    app.display();
}

    return 0;
}
