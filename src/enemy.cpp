#include "enemy.h"

void Enemy::updateVelX(int posNeg)
{
    vel.x += (rand() % (int)(speedIncrement * 2 + 1))*posNeg;
}

void Enemy::updateVelY(int posNeg)
{
    vel.y += (rand() % (int)(speedIncrement * 2 + 1)) * posNeg;
}

float Enemy::getSpeedIncrement()
{
    return speedIncrement;
}

//limit the velocity to the max and min values and then add it to the position x,y vector
void Enemy::updatePos()
{
    vel.x = std::max(-5.0f, std::min(vel.x, 5.0f));
    vel.y = std::max(-5.0f, std::min(vel.y, 5.0f));
    pos.x += vel.x; //-offsetX);
    pos.y += vel.y;

}

//check to see if the enemy sphere is approaching of past the boundary of the map
//if so, move away from edge
//if not randomly move
void Enemy::checkOutsideMap()
{
    if ((pos.x<500 || pos.x>mapW + 500) || (pos.y < 500 || pos.y>mapH + 500))
    {
        if (pos.x < 500) { updateVelX(1); }
        else if (pos.x > mapW + 500) { updateVelX(-1); }
        if (pos.y < 500) { updateVelY(1); }
        else if (pos.y > mapH + 500) { updateVelY(-1); }
    }
    else
    {
        
        vel.x += rand() % (int)(speedIncrement * 2 + 1) + (-speedIncrement);
        vel.y += rand() % (int)(speedIncrement * 2 + 1) + (-speedIncrement);

    }
}

//update the enemy sphere position and draw it
void Enemy::draw(sf::RenderWindow& app)
{
    enemyShape.setPosition(pos.x, pos.y);
    app.draw(enemyShape);
}
