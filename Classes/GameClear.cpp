//
//  GameClear.cpp
//  Tetris
//
//  Created by Yoshida Mitsunobu on 2014/07/20.
//
//

#include "GameClear.h"
#include "GameScene.h"


USING_NS_CC;

Scene* GameClear::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameClear::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool GameClear::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    Sprite* bg = Sprite::create();
    bg->setTextureRect(Rect(0, 0, visibleSize.width, visibleSize.height));
    bg->setColor(Color3B::GRAY);
    bg->setAnchorPoint(Vec2(0.0f, 0.0f));
    addChild(bg, -1);
    
    Label* label = Label::createWithSystemFont("GameClear", "", 30.0f);
    label->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    addChild(label);
    

	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();
	EventListenerTouchOneByOne* touch = EventListenerTouchOneByOne::create();
	touch->onTouchBegan = CC_CALLBACK_2(GameClear::onTouchBegan, this);
	eventDispatcher->addEventListenerWithFixedPriority(touch,1);
    
	return true;
}

void GameClear::onExit(){
	Layer::onExit();
	this->removeAllChildrenWithCleanup(true);
	Director::getInstance()->getEventDispatcher()->removeAllEventListeners();
}

bool GameClear::onTouchBegan(Touch *touch, Event *unused_event){
	log("onTouchBegan");
	Director::getInstance()->replaceScene(GameScene::createScene());
	return true;
}
void GameClear::onTouchMoved(Touch *touch, Event *unused_event){}
void GameClear::onTouchEnded(Touch *touch, Event *unused_event){}
void GameClear::onTouchCancelled(Touch *touch, Event *unused_event){}