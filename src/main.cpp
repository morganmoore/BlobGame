#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "enemy.h"
#include "player.h"
#include<windows.h>


float randomFloat(float a, float b) {
    float random = ((float)rand()) / (float)RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

float getDistance(int x1, int y1, int x2, int y2)
{
    // Calculating distance
    return sqrt(pow(x2 - x1, 2) +
        pow(y2 - y1, 2) );
}

void updateCamera(Player player, sf::View& view, sf::RenderWindow& app, float centreX, float centreY, float mapW, float mapH, float cameraX, float cameraY)
{
    
    view.setCenter(centreX, centreY);
    app.setView(view);
    float newViewX = 1000 * pow(player.getRadius() / 20, 0.1);
    float newViewY = 700 * pow(player.getRadius() / 20, 0.1);
    if (cameraX < newViewX) { cameraX += 1; }
    if (cameraY < newViewY) { cameraY += 1; }
    view.setSize(cameraX, cameraY);
}

void updateMiniMap(sf::Sprite& sMiniMap, sf::RenderWindow& app, float centreX, float centreY, float bgW, float bgH, Player player, sf::CircleShape& miniMapDot)
{
    sMiniMap.setPosition(centreX + 230, centreY + 80);


    miniMapDot.setRadius(5);
    miniMapDot.setOrigin(5, 5);
    std::cout << "PSZ: " << player.getRadius() << std::endl;
    miniMapDot.setFillColor(sf::Color(250, 150, 0));
    miniMapDot.setPosition((centreX + 185) + (player.getPos().x / bgW) * 355, (centreY + 35) + (player.getPos().y / bgH) * 355);


    app.draw(sMiniMap);
    app.draw(miniMapDot);
	
}





int main()
{
    srand(time(0));
    const float cameraX= 1000.0f;
    const float cameraY = 700.0f;
    const int bgW = 3000;
    const int bgH = 3000;
    const float mapW = bgW-cameraX;
    const float mapH = bgH -cameraY;
    float centreX = bgW / 2;
    float centreY = bgH / 2;
    sf::RenderWindow app(sf::VideoMode(cameraX, cameraY), "Doodle Game!");
    sf::View view(sf::Vector2f(centreX, centreY), sf::Vector2f(cameraX, cameraY));
    app.setView(view);

    app.setFramerateLimit(80);
    int framecount = 0;
    

    Player player(20, { centreX, centreY }, { 255,200,0 }, 20.f, "Player 1");

    //std::vector<Enemy> enemies(20);
    int numEnemies = 20;
    std::vector<Enemy> enemies;

 
	for(int i = 0; i<= numEnemies; i++)
	{
		Vec2 pos = {rand() % (int)mapW + 500, rand() % (int)mapH + 500};
        Colour col = { rand() % 215 + 40, rand() % 215 + 40, rand() % 215 + 40 };
        float rad = randomFloat(10.f, 25.f);
        Enemy enemy(rad, pos, col);
        enemies.push_back(enemy);
	}
 
    sf::Texture t1,t2,t3;
    t1.loadFromFile("images/background5.png");
    t2.loadFromFile("images/minimap.png");
    t3.loadFromFile("images/gameOver.png");

    sf::Sprite sBackground(t1), sMiniMap(t2);

    sf::CircleShape miniMapDot(4);
    int first_time = time(NULL);
    bool bDead = false;
    while (app.isOpen())
    {
	    sf::Event e;
        while (app.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                //clock_t end = std::clock();
                int second_time = time(NULL);
                std::cout << framecount / (second_time - first_time) << std::endl;
                std::cout << "heyyy" << framecount << std::endl;
                std::cout << CLOCKS_PER_SEC << std::endl;
                //std::cin.ignore();
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
            std::cout << "Distance: " << distFromPlayer << std::endl;
            if (distFromPlayer < (enemies[i].getRadius() + player.getRadius() +20))
            {
                std::cout << "Index1: " << i << std::endl;
                if (enemies[i].getRadius() > player.getRadius())
                {
                	if(distFromPlayer <(enemies[i].getRadius() + player.getRadius()))
                	{
                      
                        bDead = true;
                        //Sleep(100);
                        app.close();
                        break;
                		
                	}
                    
                    if (enemies[i].getPos().x < player.getPos().x - enemies[i].getSpeedIncrement()) { enemies[i].updateVelX(1); }
                    else if (enemies[i].getPos().x > player.getPos().x + enemies[i].getSpeedIncrement()) { enemies[i].updateVelX(-1); }
                    if (enemies[i].getPos().y < player.getPos().y - enemies[i].getSpeedIncrement()) { enemies[i].updateVelY(1); }
                    else if (enemies[i].getPos().y > player.getPos().y + enemies[i].getSpeedIncrement()) { enemies[i].updateVelY(-1); }
                }
                
                else
                {
                    
                    if (distFromPlayer < (enemies[i].getRadius() + player.getRadius()))
                    {
                        std::cout << "erase1" << std::endl;
                        player.updateSize(enemies[i].getRadius());
                        enemies.erase(enemies.begin() + i);
                        std::cout << "erase2" << std::endl;
                        
                        --i;
                        
                    }
                	
                    else
                    {
                        if (enemies[i].getPos().x < player.getPos().x - 2) { enemies[i].updateVelX(-1); }
                        else if (enemies[i].getPos().x > player.getPos().x + 2) { enemies[i].updateVelX(1); }
                        if (enemies[i].getPos().y < player.getPos().y - 2) { enemies[i].updateVelY(-1); }
                        else if (enemies[i].getPos().y > player.getPos().y + 2) { enemies[i].updateVelY(1); }
                    }
                     
                }		
            }
            else
            {
                std::cout << "check outside" << std::endl;
                enemies[i].checkOutsideMap();

            }
        	
            enemies[i].updatePos();
            enemies[i].draw(app);
        }

        centreX = std::max(cameraX / 2, std::min(player.getPos().x, mapW + cameraX / 2));
        centreY = std::max(cameraY / 2, std::min(player.getPos().y, mapH + cameraY / 2));

        updateCamera(player, view, app, centreX, centreY,  mapW, mapH, cameraX, cameraY);

        updateMiniMap(sMiniMap, app, centreX, centreY, bgW, bgH, player, miniMapDot);

    app.display();
}

    return 0;
}
