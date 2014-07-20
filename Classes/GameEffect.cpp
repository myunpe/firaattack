//
//  GameEffect.cpp
//  Tetris
//
//  Created by Yoshida Mitsunobu on 2014/07/20.
//
//

#include "GameEffect.h"


//
//  Player.cpp
//  Tetris
//
//  Created by Yoshida Mitsunobu on 2014/07/18.
//
//

#include "Player.h"

GameEffect::GameEffect() : Sprite(){
    
}

GameEffect::~GameEffect(){
    
}

GameEffect* GameEffect::create(const std::string &filename){
    GameEffect* gameEffect = new GameEffect();
    gameEffect->init();
    gameEffect->autorelease();
    gameEffect->setTextureRect(Rect(0, 0, Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height));
    gameEffect->setColor(Color3B(20, 20, 20));
    gameEffect->setOpacity(166);
    gameEffect->setContentSize(Director::getInstance()->getWinSize());
    gameEffect->setPosition(Vec2(0,0));
    gameEffect->setAnchorPoint(Vec2(0.0f, 0.0f));
    gameEffect->setVisible(false);
    
    return gameEffect;
}

void GameEffect::onEnter(){
    log("GameEffect::onEnter");
    Sprite::onEnter();
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    
    touchListener->onTouchBegan = CC_CALLBACK_2(GameEffect::onTouchBegan, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameEffect::onTouchMoved, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameEffect::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
}

void GameEffect::onExit(){
    Sprite::onExit();
}

void GameEffect::setDispatchTouch(bool isEnable){
    isDispatch = isEnable;
}


bool GameEffect::onTouchBegan(Touch* touch, Event* event){
//    log("player onTouchbegan");
//    unschedule(schedule_selector(Player::move));
//    beginTouch = touch->getLocation();
    //    thistouch->getLocation();
    
    bool is = isDispatch;
    log("is? = %d", is);
    return is;
}
void GameEffect::onTouchMoved(Touch* touch, Event* event){
    log("GameEffect onTouchMoved");
}
void GameEffect::onTouchEnded(Touch* touch, Event* event){
//    Vec2 endTouch = touch->getLocation();
//    endTouch.subtract(beginTouch);
//    beginTouch = endTouch;
//    power = beginTouch.length();
//    if (power > 100.0f) {
//        schedule(schedule_selector(Player::move));
//    }
//    power = 1000.0f;
//    log("player onTouchEnded len = %f", power);
//    beginTouch.normalize();
//    _eventDispatcher->setEnabled(false);
}


void GameEffect::move(float delta){
    
//    power -= 5.0f;
//    if (power <= 0.0f) {
//        log("getPosition = x, y = %f, %f", getPosition().x, getPosition().y);
//        _eventDispatcher->setEnabled(true);
//        unschedule(schedule_selector(Player::move));
//    }
//    Vec2 temp = beginTouch * delta * power + getPosition();
//    //    log("Player Move + delta %f, x = %f, y = %f, power = %f",delta, temp.x, temp.y, power);
//    
//    //    log("setPosition power = %f, x, y = %f, %f",power, temp.x, temp.y);
//    this->setPosition(temp);
//    
//    Size winSize = Director::getInstance()->getWinSize();
//    Rect r = getRect();
//    r.origin.x += getPosition().x;
//    r.origin.y += getPosition().y;
//    if (0.0f > r.getMinX()){
//        float len = - r.getMinX();
//        beginTouch.x = -beginTouch.x;
//        setPosition(getPosition().x + len , getPosition().y);
//    }else if(r.getMaxX() >= winSize.width) {
//        float len =  -(r.getMaxX() - winSize.width);
//        beginTouch.x = -beginTouch.x;
//        setPosition(getPosition().x + len , getPosition().y);
//    }
//    if (0.0f > r.getMinY() || r.getMaxY() >= winSize.height) {
//        beginTouch.y = -beginTouch.y;
//    }
}

Rect GameEffect::getRect()
{
    auto s = getTexture()->getContentSize();
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}