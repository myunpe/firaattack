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
    //touchListener->setSwallowTouches(true);
    
    touchListener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Player::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Player::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void Player::onExit(){
    Sprite::onExit();
}


bool Player::onTouchBegan(Touch* touch, Event* event){
    log("player onTouchbegan");
    unschedule(schedule_selector(Player::move));
    beginTouch = touch->getLocation();
//    thistouch->getLocation();
    return true;
}
void Player::onTouchMoved(Touch* touch, Event* event){
    log("player onTouchMoved");
}
void Player::onTouchEnded(Touch* touch, Event* event){
    Vec2 endTouch = touch->getLocation();
    endTouch.subtract(beginTouch);
    beginTouch = endTouch;
    power = beginTouch.length();
    if (power > 100.0f) {
        schedule(schedule_selector(Player::move));
    }
    power = 1000.0f;
    log("player onTouchEnded len = %f", power);
    beginTouch.normalize();
}


void Player::move(float delta){
    
    power -= 5.0f;
    if (power <= 0.0f) {
        log("getPosition = x, y = %f, %f", getPosition().x, getPosition().y);
        unschedule(schedule_selector(Player::move));
    }
    Vec2 temp = beginTouch * delta * power + getPosition();
//    log("Player Move + delta %f, x = %f, y = %f, power = %f",delta, temp.x, temp.y, power);
    
    log("setPosition power = %f, x, y = %f, %f",power, temp.x, temp.y);
    this->setPosition(temp);
   
    Size winSize = Director::getInstance()->getWinSize();
    Rect r = getRect();
    r.origin.x += getPosition().x;
    r.origin.y += getPosition().y;
    if (0.0f > r.getMinX()){
        float len = - r.getMinX();
        beginTouch.x = -beginTouch.x;
        setPosition(getPosition().x + len , getPosition().y);
    }else if(r.getMaxX() >= winSize.width) {
        float len =  -(r.getMaxX() - winSize.width);
        beginTouch.x = -beginTouch.x;
        setPosition(getPosition().x + len , getPosition().y);
    }
    if (0.0f > r.getMinY() || r.getMaxY() >= winSize.height) {
        beginTouch.y = -beginTouch.y;
    }
    
}

Rect Player::getRect()
{
    auto s = getTexture()->getContentSize();
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}