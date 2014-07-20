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
    
    Rect rect = Rect(0, 0, getContentSize().width, getContentSize().height);
    rect.origin.x += getPosition().x;
    rect.origin.y += getPosition().y;
    
    if(rect.intersectsRect(playerRect)){
        return true;
    }
    
    return false;
} 
