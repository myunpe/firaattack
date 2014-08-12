//
//  GameEffect.cpp
//  Tetris
//
//  Created by Yoshida Mitsunobu on 2014/07/20.
//
//

#include "GameEffect.h"

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
//    gameEffect->setColor(Color3B(255, 255, 0));
//    gameEffect->setTextureRect(Rect(0,0,Director::getInstance()->getWinSize().width, Director::getInstance()->getWinSize().height));
//    
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

void GameEffect::failEffect(){
    this->setVisible(true);
    Sprite* fail = Sprite::create("failed.png");
    Size winSize = Director::getInstance()->getWinSize();
    fail->setPosition(winSize.width / 2.0f, winSize.height);
    auto moveAction = MoveTo::create(1.2f, Vec2(winSize.width / 2.0f, winSize.height / 2.0f));
    fail->runAction(moveAction);
//    fail->setPosition(Vec2(100, 100));
    addChild(fail);
    
//    MenuItem* item1 = MenuItem::create([](Ref* sender){
//        log("item1 callback");
//    });
}

void GameEffect::clearEffect(){
    this->setVisible(true);
    Sprite* clear = Sprite::create("clear.png");
    Size winSize = Director::getInstance()->getWinSize();
    clear->setPosition(Vec2(winSize.width / 2.0f, winSize.height / 2.0f));
    clear->setScale(0.0f, 0.0f);
    clear->setAnchorPoint(Vec2(0.5f, 0.5f));
    auto rotateAction = RotateBy::create(0.6f, Vec3(0.0f, 360.0f, 0.0f));
    auto alphaAction = FadeIn::create(1.5f);
    auto scaleAction = ScaleTo::create(1.5f, 1.0f);
    auto setAction = Spawn::create(Repeat::create(rotateAction, 3),alphaAction, scaleAction, NULL);
    clear->runAction(setAction);
//    clear->runAction(alphaAction);
//    clear->runAction(scaleAction);
    addChild(clear);
}

void GameEffect::setDispatchTouch(bool isEnable){
    isDispatch = isEnable;
}


bool GameEffect::onTouchBegan(Touch* touch, Event* event){
    bool is = isDispatch;
    log("is? = %d", is);
    return is;
}
void GameEffect::onTouchMoved(Touch* touch, Event* event){
    log("GameEffect onTouchMoved");
}
void GameEffect::onTouchEnded(Touch* touch, Event* event){
}

Rect GameEffect::getRect()
{
    auto s = getTexture()->getContentSize();
    return Rect(-s.width / 2, -s.height / 2, s.width, s.height);
}