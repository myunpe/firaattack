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
#include "GameEffect.h"
#include "GameClear.h"

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
    
    //変数初期化
    gameScore = 0;
    
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
    
	closeItem->setPosition(Vec2(closeItem->getContentSize().width/2 ,
                                closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    mPlayer = Player::create("tileset.png");
    mPlayer->setPosition(Vec2(100, 100));
    mPlayer->onMoveEnd = []{
        log("onMoveEnd");
    };
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
    
    GameEffect* gameEffect = GameEffect::create("");
    gameEffect->setDispatchTouch(false);
    //一番上に来るようにindexOrderを上げる
    addChild(gameEffect, 1000);
    
    auto userNotifyText = LabelTTF::create("フリックでプレイヤーを飛ばしてね！", "Arial", 24);
    userNotifyText->setPosition(visibleSize.width - (userNotifyText->getContentSize().width / 2), userNotifyText->getContentSize().height / 2);
    
    auto action2 = FadeOut::create(1.0f);
    auto action2Back = action2->reverse();
    auto action2BackReverse = action2Back->reverse();
    auto action2BackReverseReverse = action2BackReverse->reverse();
    auto actionForever = RepeatForever::create(Sequence::create( action2, action2Back,action2BackReverse,action2BackReverseReverse, nullptr));
    userNotifyText->runAction(actionForever);
    
    this->addChild(userNotifyText, 3, 100);
    
    return true;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
//    return;
//#endif
//    
//    Director::getInstance()->end();
//    
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//    exit(0);
//#endif
    
}

void GameScene::onCollisionCheck(float detla){
    for (auto it = enemyList.begin(); it != enemyList.end(); ++it) {
        if((*it)->onCollideWithPlayer(mPlayer)){
            //当たった時の処理を行いたい
            addScore();
            (*it)->removeFromParentAndCleanup(true);
            it = enemyList.erase(it);
        }
    }

    if (enemyList.empty()) {
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameClear::createScene(), Color3B::BLACK));
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

void GameScene::addScore(){
    gameScore++;
    log("addScore gameScore = %d", gameScore);
}
