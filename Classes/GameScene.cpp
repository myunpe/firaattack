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
#include "json/document.h"
#include "cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"



USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;


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
    
    auto userNotifyText = LabelTTF::create("フリックして", "Arial", 24);
    userNotifyText->setPosition(visibleSize.width - (userNotifyText->getContentSize().width / 2), userNotifyText->getContentSize().height / 2);
    
    auto action2 = FadeOut::create(1.0f);
    auto action2Back = action2->reverse();
    auto action2BackReverse = action2Back->reverse();
    auto action2BackReverseReverse = action2BackReverse->reverse();
    auto actionForever = RepeatForever::create(Sequence::create( action2, action2Back,action2BackReverse,action2BackReverseReverse, nullptr));
    userNotifyText->runAction(actionForever);
    
    this->addChild(userNotifyText, 3, 100);
    
    
    //UIの読み方
    GUIReader* guiReader = GUIReader::getInstance();
    uiLayout = static_cast<Layout*>(guiReader->widgetFromJsonFile("UIGame.ExportJson"));
    addChild(uiLayout);
    
    return true;
}

void GameScene::onEnter(){
    Layer::onEnter();
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
    for (auto it = enemyList.begin(); it != enemyList.end();) {
        if((*it)->onCollideWithPlayer(mPlayer)){
            //当たった時の処理を行いたい
            addScore();
			(*it)->removeFromParentAndCleanup(true);
            it = enemyList.erase(it);
			continue;
        }
		++it;
    }

    if (enemyList.empty()) {
        Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameClear::createScene(), Color3B::BLACK));
        unschedule(schedule_selector(GameScene::onCollisionCheck));
    }
}

void GameScene::readGameData(){
    //rapidjsonに書き換え
    auto data = FileUtils::getInstance()->getStringFromFile("data.json");
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
    rapidjson::Value &val = doc["scene"];
    log( "name = %s, enemy = %d", val["name"].GetString(), val["enemy"].GetInt());
    enemyNum = val["enemy"].GetInt();
    
//    auto jsonStringFile = FileUtils::getInstance()->getStringFromFile("data.json");
//    std::string err;
//    auto json = json11::Json::parse(jsonStringFile, err);
//    auto scene = json["scene"];
//    log("jsonName = %s", scene["name"].string_value().c_str());
//    enemyNum = scene["enemy"].int_value();
//    log("enemyNum = %d", enemyNum);
    
}

void GameScene::addScore(){
    gameScore++;
    log("addScore gameScore = %05d", gameScore);
	char format[] = "スコア : %05d";
	char buf[50];
	sprintf(buf, format, gameScore);
    Text* back_label = dynamic_cast<Text*>(uiLayout->getChildByName("Score"));
	std::string text = std::string(buf);
    log("score = %s", text.c_str());
    back_label->setString(text);
}
