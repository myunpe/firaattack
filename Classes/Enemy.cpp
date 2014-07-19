//
//  Enemy.cpp
//  Tetris
//
//  Created by Yoshida Mitsunobu on 2014/07/19.
//
//

#include "Enemy.h"
#include "Player.h"


Enemy::Enemy(void){
    
}

Enemy::~Enemy(void){
    
}

Enemy* Enemy::create(const std::string &filename){
    Enemy* enemy = new Enemy();
    enemy->initWithFile(filename);
    enemy->autorelease();
    return enemy;
}

void Enemy::onEnter(){
    Sprite::onEnter();
}

void Enemy::onExit(){
    Sprite::onExit();
}

bool Enemy::onCollideWithPlayer(Player* player)
{
    auto playerRect = player->getRect();
    playerRect.origin.x += player->getPosition().x;
    playerRect.origin.y += player->getPosition().y;
    
    float lowY  = playerRect.getMinY();
    float midY  = playerRect.getMidY();
    float highY = playerRect.getMaxY();
    
    float leftX  = playerRect.getMinX();
    float rightX = playerRect.getMaxX();
    
    if (getPosition().x > leftX && getPosition().x < rightX) {
        
        bool hit = false;
        
        if (getPosition().y > midY && getPosition().y <= highY)
        {
            setPosition( Vec2(getPosition().x, highY));
            hit = true;
        }
        else if (getPosition().y < midY && getPosition().y >= lowY)
        {
            setPosition( Vec2(getPosition().x, lowY));
            hit = true;
        }
        
        if (hit)
        {
            return true;
        }
    }
    return false;
} 
