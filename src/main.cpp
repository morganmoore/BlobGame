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

void updateCamera(Player player, sf::View& view, sf::RenderWindow& app, float mapW, float mapH, float cameraX, float cameraY)
{
    float tmpX = cameraX / 2;
    float tmpY = cameraY / 2;
    float centreX = std::max(tmpX, std::min(player.getPos().x, mapW + tmpX));
    float centreY = std::max(tmpY, std::min(player.getPos().y, mapH + tmpY));
    view.setCenter(centreX, centreY);
    app.setView(view);
    float newViewX = 1000 * pow(player.getRadius() / 20, 0.1);
    float newViewY = 700 * pow(player.getRadius() / 20, 0.1);
    if (cameraX < newViewX) { cameraX += 1; }
    if (cameraY < newViewY) { cameraY += 1; }
    view.setSize(cameraX, cameraY);
}

void updateMiniMap(sf::Sprite& sMiniMap, sf::RenderWindow& app, const float centreX, const float centreY, float bgW, float bgH, Player player, sf::CircleShape& miniMapDot)
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




float Entity::mapH = mapW;
float Entity::mapW = mapW;


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
    /*
    std::vector<Enemy> enemies(20);

    for (auto& e : enemies)
    {
        e.pos.x = rand() % (int)mapW+500;
        e.pos.y = rand() % (int)mapH+500;
        e.size = rand() % 25 + 10;
        e.colour.r = rand() % 240 + 40;
        e.colour.g = rand() % 240 + 40;
        e.colour.b = rand() % 240 + 40;

    }
    */

    sf::Texture t1,t2,t3;
    t1.loadFromFile("images/background5.png");
    t2.loadFromFile("images/minimap.png");
    t3.loadFromFile("images/gameOver.png");


    sf::Sprite sBackground(t1), sMiniMap(t2);

    //sMiniMap.setPosition(centreX+220, centreY+100);

    float enemySpeed = 1.0f;
    float playerSpeedX = 0.8f;
    float playerSpeedY = 0.8f;
	
	//int x=100,y=100,h=200;
    //float dx=0,dy=0;
    
    int offsetX = 0;
    int offsetY = 0;
    int prevX = cameraX / 2;
    int prevY = cameraY / 2;
    float tmpX;
    float tmpY;
    sf::CircleShape playerShape(20);
    sf::CircleShape miniMapDot(4);
    //clock_t start = std::clock();
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

        
        std::cout << "1111111111" << std::endl;
    	
        //Vec2 pp = player.getPos();
        //float psz = player.getRadius();

        

		
        /*
        playerShape.setRadius(player.getRadius());
        playerShape.setOrigin(player.getRadius(), player.getRadius());
        //std::cout << "PSZ: " << psz << std::endl;
        playerShape.setFillColor(sf::Color(250, 150, 0));
        playerShape.setPosition(player.getPos().x, player.getPos().y);
        app.draw(playerShape);

        */
    	
        for (int i = 0; i<enemies.size(); i++)
        {
            //enemies[i].updatePos(player.getPos(), player.getRadius(), app);
            
            float dst = getDistance(enemies[i].getPos().x, enemies[i].getPos().y, player.getPos().x, player.getPos().y);
            std::cout << "Distance: " << dst << std::endl;
            if ( dst  < (enemies[i].getRadius() + player.getRadius() +20))
            {
                std::cout << "Index1: " << i << std::endl;
                if (enemies[i].getRadius() > player.getRadius())
                {
                	if(dst<(enemies[i].getRadius() + player.getRadius()))
                	{
                      
                        bDead = true;
                        //Sleep(100);
                        app.close();
                        break;
                		
                	}
                    std::cout << "Test: " << dst << std::endl;
                    if (enemies[i].getPos().x < player.getPos().x - enemySpeed) { enemies[i].updateVelX(1); }
                    else if (enemies[i].getPos().x > player.getPos().x + enemySpeed) { enemies[i].updateVelX(-1); }
                    if (enemies[i].getPos().y < player.getPos().y - enemySpeed) { enemies[i].updateVelY(1); }
                    else if (enemies[i].getPos().y > player.getPos().y + enemySpeed) { enemies[i].updateVelY(-1); }
                }
                
                else
                {
                    
                    if (dst < (enemies[i].getRadius() + player.getRadius()))
                    {
                        std::cout << "erase1" << std::endl;
                        player.updateSize(enemies[i].getRadius());
                        enemies.erase(enemies.begin() + i);
                        std::cout << "erase2" << std::endl;
                        
                        --i;
                        std::cout << enemies.size() << " enemies left" << std::endl;

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
                enemies[i].checkOutsideMap();

            }
        	
            enemies[i].updatePos();
            enemies[i].draw(app);
        }

        updateCamera(player, view, app, mapW, mapH, cameraX, cameraY);

        updateMiniMap(sMiniMap, app, centreX, centreY, bgW, bgH, player, miniMapDot);

    app.display();
}

    return 0;
}
