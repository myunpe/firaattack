//
//  GameScene.cpp
//  Tetris
//
//  Created by Yoshida Mitsunobu on 2014/07/18.
//
//

#include "GameScene.h"
#include "Player.h"
#include "Enemy.h"

#include "library/json11.hpp"

USING_NS_CC;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");
    
    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    mPlayer = Player::create("tileset.png");
    mPlayer->setPosition(Vec2(100, 100));
    this->addChild(mPlayer, 1);
    readGameData();
    
    enemyList = std::list<Enemy*>();
    for (int i = 0; i < enemyNum; i++) {
        Enemy* enemy = Enemy::create("enemy.png");
        Vec2 enemyPos = Vec2();
        enemyPos.x = rand() % (int)visibleSize.width;
        enemyPos.y = rand() % (int)visibleSize.height;
        enemy->setPosition(enemyPos);
        addChild(enemy);
        enemyList.push_back(enemy);
    }
    
    schedule(schedule_selector(GameScene::onCollisionCheck));
    
    return true;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameScene::onCollisionCheck(float detla){
    for (auto it = enemyList.begin(); it != enemyList.end(); ++it) {
        if((*it)->onCollideWithPlayer(mPlayer)){
            (*it)->removeFromParentAndCleanup(true);
            it = enemyList.erase(it);
        }
    }

    if (enemyList.empty()) {
        unschedule(schedule_selector(GameScene::onCollisionCheck));
    }
}

void GameScene::readGameData(){
    auto jsonStringFile = FileUtils::getInstance()->getStringFromFile("data.json");
    std::string err;
    auto json = json11::Json::parse(jsonStringFile, err);
    auto scene = json["scene"];
    log("jsonName = %s", scene["name"].string_value().c_str());
    enemyNum = scene["enemy"].int_value();
    log("enemyNum = %d", enemyNum);
    
}



