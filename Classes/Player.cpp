//
//  Player.cpp
//  Tetris
//
//  Created by Yoshida Mitsunobu on 2014/07/18.
//
//

#include "Player.h"

Player::Player() : Sprite(){
    
}

Player::~Player(){
    
}

Player* Player::create(const std::string &filename){
    Player* player = new Player();
    player->initWithFile(filename);
    player->autorelease();
    return player;
}

void Player::onEnter(){
    log("Player::onEnter");
    Sprite::onEnter();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    
    touchListener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Player::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Player::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}


bool Player::onTouchBegan(Touch* touch, Event* event){
    log("player onTouchbegan");
    return true;
}
void Player::onTouchMoved(Touch* touch, Event* event){
    log("player onTouchMoved");
}
void Player::onTouchEnded(Touch* touch, Event* event){
    log("player onTouchEnded");
}