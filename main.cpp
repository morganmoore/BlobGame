#include <SFML/Graphics.hpp>
#include <time.h>
#include <iostream>
#include "enemy.h"
#include "player.h"
#include<windows.h>
using namespace sf;

float RandomFloat(float a, float b) {
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






struct point
{ int x,y;};

void drawEnemy(RenderWindow& app, Enemy& e)
{
    CircleShape enemyShape(e.size);
    enemyShape.setOrigin(e.size, e.size);
    enemyShape.setFillColor(sf::Color(e.colour.r, e.colour.g, e.colour.b));
    //enemyShape.setOutlineColor(sf::Color::Red);
    enemyShape.setPosition(e.pos.x, e.pos.y);
    app.draw(enemyShape);
}

int main()
{
    srand(time(0));
    float cameraX= 1000.0f;
    float cameraY = 700.0f;
    int bgW = 3000;
    int bgH = 3000;
    float mapW = bgW-cameraX;
    float mapH = bgH -cameraY;
    float centreX = bgW / 2;
    float centreY = bgH / 2;
    RenderWindow app(VideoMode(cameraX, cameraY), "Doodle Game!");
    View view(Vector2f(centreX, centreY), sf::Vector2f(cameraX, cameraY));
    app.setView(view);

    
	
    app.setFramerateLimit(80);
    int framecount = 0;
    

    Player player(20, { centreX, centreY }, { 0.0f, 0.0f }, { 255,200,0 });

	

    std::vector<Enemy> enemies(20);

    for (auto& e : enemies)
    {
        e.pos.x = rand() % (int)mapW+500;
        e.pos.y = rand() % (int)mapH+500;
        e.size = rand() % 25 + 10;
        e.colour.r = rand() % 240 + 40;
        e.colour.g = rand() % 240 + 40;
        e.colour.b = rand() % 240 + 40;

        //std::cout << "X: " << e.pos.x << "   Y: " << e.pos.y << std::endl;

    }

    
    // map a 100x100 textured rectangle to the shape
    //shape.setTexture(&texture); // texture is a sf::Texture
    //shape.setTextureRect(sf::IntRect(10, 10, 100, 100));
    

    std::cout << "0000000000000" << std::endl;
    
    Texture t1,t2,t3;
    t1.loadFromFile("images/background5.png");
    t2.loadFromFile("images/minimap.png");
    t3.loadFromFile("images/gameOver.png");
	

    Sprite sBackground(t1), sMiniMap(t2);

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
    CircleShape playerShape(20);
    CircleShape miniMapDot(4);
    //clock_t start = std::clock();
    int first_time = time(NULL);
    bool bDead = false;
    while (app.isOpen())
    {
        Event e;
        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
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
        if (Keyboard::isKeyPressed(Keyboard::Right)) { playerSpeedX = 0.2; }
        else if (Keyboard::isKeyPressed(Keyboard::Left)) { playerSpeedX = -0.2; }
        else { playerSpeedX = 0; }
        if (Keyboard::isKeyPressed(Keyboard::Up)) playerSpeedY = -0.2;
        else if (Keyboard::isKeyPressed(Keyboard::Down)) playerSpeedY = 0.2;
        else { playerSpeedY = 0; }

        const Vector2i mousePosition{ Mouse::getPosition(app) };
        const Vector2f mouseCoord{ app.mapPixelToCoords(mousePosition) };
        player.updatePos(mouseCoord.x, mouseCoord.y);
       
        framecount++;
    	
        app.draw(sBackground);

    	
        //player.updateVel(playerSpeedX, playerSpeedY);

        
        std::cout << "1111111111" << std::endl;
    	
        Position pp = player.getPos();
        float psz = player.getSize();

        

    
        
        playerShape.setRadius(psz);
        playerShape.setOrigin(psz, psz);
        std::cout << "PSZ: " << psz << std::endl;
        playerShape.setFillColor(sf::Color(250, 150, 0));
        playerShape.setPosition(pp.x, pp.y);
        app.draw(playerShape);
    	
        for (int i = 0; i<enemies.size(); i++)
        {
            
            std::cout << "2222222222" << std::endl;
            float dst = getDistance(enemies[i].pos.x, enemies[i].pos.y, pp.x, pp.y);
            std::cout << "Distance: " << dst << std::endl;
            if ( dst  < (enemies[i].size + psz+20))
            {
                std::cout << "Index1: " << i << std::endl;
                if (enemies[i].size > psz)
                {
                	if(dst<(enemies[i].size+psz))
                	{
                        //delete &player; 
                        
                        bDead = true;
                        //Sprite sBackground(t3);
                        //Sleep(100);
                        app.close();
                        break;
                		
                	}
                    std::cout << "Test: " << dst << std::endl;
                    if (enemies[i].pos.x < pp.x - enemySpeed) { enemies[i].vel.x += enemySpeed; }
                    else if (enemies[i].pos.x > pp.x + enemySpeed) { enemies[i].vel.x -= enemySpeed; }
                    if (enemies[i].pos.y < pp.y - enemySpeed) { enemies[i].vel.y += enemySpeed; }
                    else if (enemies[i].pos.y > pp.y + enemySpeed) { enemies[i].vel.x -= enemySpeed; }
                }
                
                else
                {
                    
                    if (dst < (enemies[i].size + psz))
                    {
                        std::cout << "erase1" << std::endl;
                        player.updateSize(enemies[i].size);
                        enemies.erase(enemies.begin() + i);
                        std::cout << "erase2" << std::endl;
                        
                        --i;
                        std::cout << enemies.size() << " enemies left" << std::endl;
                        std::cout << "I: " << i <<std::endl;
                        
                        continue;

                    }
                	
                    else
                    {
                        if (enemies[i].pos.x < pp.x - 2) { enemies[i].vel.x -= enemySpeed; }
                        else if (enemies[i].pos.x > pp.x + 2) { enemies[i].vel.x += enemySpeed; }
                        if (enemies[i].pos.y < pp.y - 2) { enemies[i].vel.y -= enemySpeed; }
                        else if (enemies[i].pos.y > pp.y + 2) { enemies[i].vel.x += enemySpeed; }
                    }
                    
                    
                    
                }
            		
            }
            else
            {
                std::cout << "Index2: " << i << std::endl;
            	if((enemies[i].pos.x<500 || enemies[i].pos.x>mapW+500)|| (enemies[i].pos.y < 500 || enemies[i].pos.y>mapH+500))
            	{
                    
                    if (enemies[i].pos.x < 500) { enemies[i].vel.x += rand() % (int)(enemySpeed * 2 + 1); }
                    else if(enemies[i].pos.x > mapW-500) { enemies[i].vel.x += (rand() % (int)(enemySpeed * 2 + 1) *-1); }
            		if (enemies[i].pos.y < 500) { enemies[i].vel.y += rand() % (int)(enemySpeed * 2 + 1); }
                    else if (enemies[i].pos.y > mapH-500) { enemies[i].vel.y += (rand() % (int)(enemySpeed * 2 + 1) * -1); }
            	}
                else
                {
                    
                    enemies[i].vel.x += rand() % (int)(enemySpeed*2+1) + (-enemySpeed);
                    enemies[i].vel.y += rand() % (int)(enemySpeed * 2 + 1) + (-enemySpeed);
                   
                }
            }
            std::cout << "Index3: " << i << std::endl;
            enemies[i].vel.x = std::max(-5.0f, std::min(enemies[i].vel.x, 5.0f));
            enemies[i].vel.y = std::max(-5.0f, std::min(enemies[i].vel.y, 5.0f));
            //std::cout << enemies[1].vel.x << " yep" << std::endl;
            std::cout << "Index3: " << i << std::endl;
            enemies[i].pos.x += (enemies[i].vel.x); //-offsetX);
            enemies[i].pos.y += (enemies[i].vel.y); //-offsetY);
            
            drawEnemy(app, enemies[i]);
	        
        }
        tmpX = cameraX / 2;
        tmpY = cameraY / 2;
        centreX = std::max(tmpX, std::min(pp.x, mapW+tmpX));
        centreY = std::max(tmpY, std::min(pp.y, mapH+tmpY));
        view.setCenter(centreX, centreY);
        app.setView(view);
        float newViewX = 1000 * pow(psz / 20, 0.1);
        float newViewY = 700 * pow(psz / 20, 0.1);
        if (cameraX < newViewX) { cameraX += 1; }
        if (cameraY < newViewY) { cameraY += 1; }
        view.setSize(cameraX, cameraY);

    	
        sMiniMap.setPosition(centreX + 230, centreY + 80);

        
        miniMapDot.setRadius(5);
        miniMapDot.setOrigin(5, 5);
        std::cout << "PSZ: " << psz << std::endl;
        miniMapDot.setFillColor(sf::Color(250, 150, 0));
        miniMapDot.setPosition((centreX + 185)+(pp.x/bgW)*355, (centreY + 35)+(pp.y / bgH) * 355);
        
    	
        app.draw(sMiniMap);
        app.draw(miniMapDot);
        std::cout << "CENTRE x" << centreX << std::endl;


    app.display();
}

    return 0;
}
