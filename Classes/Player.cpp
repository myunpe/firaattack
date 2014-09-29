//
//  Player.cpp
//  Tetris
//
//  Created by Yoshida Mitsunobu on 2014/07/18.
//
//

#include "Player.h"

static const char fire[] = "fire.png";

Player::Player() : Sprite(){
    isUserAct = true;
    power = 0.0f;
    reflectMax = UserDefault::getInstance()->getIntegerForKey("reflectMax", 3);
}

Player::~Player(){
    
}

Player* Player::create(const std::string &filename){
    Player* player = new Player();
	player->initWithTexture(Director::getInstance()->getTextureCache()->addImage(filename));
    //player->initWithFile(filename);
    player->autorelease();
    auto particle = ParticleFire::createWithTotalParticles(20);
    particle->retain();
    player->addChild(particle, 10);
    
    particle->setTexture( Director::getInstance()->getTextureCache()->addImage(fire) );
	particle->setPosition(Vec2(player->getRect().getMidX(),0));
    
    return player;
}

void Player::onEnter(){
    log("Player::onEnter");
    Sprite::onEnter();
    
    //touchListener->setSwallowTouches(true);
    touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(Player::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(Player::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(Player::onTouchEnded, this);
    
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void Player::onExit(){
    Sprite::onExit();
    Director::getInstance()->getEventDispatcher()->removeEventListener(touchListener);
}


bool Player::onTouchBegan(Touch* touch, Event* event){
    log("player onTouchbegan");
    if (!isUserAct || power > 0.0f) { //移動中はタッチとれないようにしてみた
        return false;
    }
    reflectCount = 0;
    unschedule(schedule_selector(Player::move));
    beginTouch = touch->getLocation();
    return true;
}
void Player::onTouchMoved(Touch* touch, Event* event){
//    log("player onTouchMoved");
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
    
    //power -= 5.0f;
    Vec2 temp = beginTouch * delta * power + getPosition();
//    log("Player Move + delta %f, x = %f, y = %f, power = %f",delta, temp.x, temp.y, power);
    
//    log("setPosition power = %f, x, y = %f, %f",power, temp.x, temp.y);
    this->setPosition(temp);
    if (reflectCount >= reflectMax) {
        Rect r = Rect(0, 0, Director::getInstance()->getVisibleSize().width, Director::getInstance()->getVisibleSize().height);
        if(!r.containsPoint(getPosition()+getContentSize()/2) && !r.containsPoint(getPosition()-getContentSize()/2)
           ){
            if (onMoveEnd) {
                onMoveEnd();
            }
            power = 0.0f;
            log("getPosition = x, y = %f, %f", getPosition().x, getPosition().y);
            unschedule(schedule_selector(Player::move));
        }
        return;
    }
   
    Size winSize = Director::getInstance()->getWinSize();
    Rect r = getRect();
    r.origin.x += getPosition().x - getContentSize().width / 2;
    r.origin.y += getPosition().y - getContentSize().height / 2;
    if (0.0f > r.getMinX()){
        float len = - r.getMinX();
        beginTouch.x = -beginTouch.x;
        setPosition(getPosition().x + len , getPosition().y);
        reflectCount++;
    }else if(r.getMaxX() >= winSize.width) {
        float len =  -(r.getMaxX() - winSize.width);
        beginTouch.x = -beginTouch.x;
        setPosition(getPosition().x + len , getPosition().y);
        reflectCount++;
    }
    if (0.0f > r.getMinY() || r.getMaxY() >= winSize.height) {
        beginTouch.y = -beginTouch.y;
        reflectCount++;
    }
    
}

Rect Player::getRect()
{
    auto s = getTexture()->getContentSize();
    return Rect(0, 0, s.width, s.height);
}

Rect Player::getRect(Sprite* sprite)
{
    auto s = sprite->getTexture()->getContentSize();
    Rect r = Rect(0, 0, s.width, s.height);
    r.origin.x += sprite->getPosition().x;
    r.origin.y += sprite->getPosition().y;
    return r;
}


bool Player::onCollideWithSprite(Sprite* other)
{
    auto spriteRect = this->getRect(other);
    
    Rect rect = this->getRect(this);
    
    if(rect.intersectsRect(spriteRect)){
        return true;
    }
    
    return false;
}