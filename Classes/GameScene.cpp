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
#include "SelectStageScene.h"



USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;


Scene* GameScene::createScene(int stageId)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    log("stageId = %d", stageId);
    layer->stageId = stageId;
    layer->readGameData();
    layer->enemyNum = stageId;
    layer->enemyCreate();
    
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
	gameCoin = 0;
    
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
    mPlayer->setPosition(Vec2(visibleSize.width / 2, 100));
	mPlayer->onMoveEnd = std::bind(std::mem_fn(&GameScene::onPlayerMoveEnd), this);
    this->addChild(mPlayer, 1);
    
    
    enemyList = std::list<Enemy*>();
    
    GameEffect* gameEffect = GameEffect::create("");
    gameEffect->setDispatchTouch(false);
    //一番上に来るようにindexOrderを上げる
    addChild(gameEffect, 1000, 1000);

#ifdef __MINGW32__
    auto userNotifyText = Label::createWithSystemFont("Flik", "Arial", 24);
#else
    auto userNotifyText = Label::createWithSystemFont("フリックしてプレイヤーを飛ばしてね！", "Arial", 24);
#endif
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
    uiLayout->setPosition(Vec2(0, visibleSize.height - uiLayout->getContentSize().height));
    addChild(uiLayout);
    
    //
    itemList = std::list<Sprite*>();
    
    return true;
}

void GameScene::enemyCreate(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    for (int i = 0; i < enemyNum; i++) {
        Enemy* enemy = Enemy::create("enemy.png");
        Vec2 enemyPos = Vec2();
        enemyPos.x = rand() % (int)(visibleSize.width - enemy->getContentSize().width) + enemy->getContentSize().width / 2;
        enemyPos.y = rand() % (int)(visibleSize.height / 2 - enemy->getContentSize().height) + enemy->getContentSize().height / 2 + visibleSize.height / 2;
        enemy->setPosition(enemyPos);
        addChild(enemy);
        enemyList.push_back(enemy);
    }
    schedule(schedule_selector(GameScene::onCollisionCheck));
}

void GameScene::onEnter(){
    log("GameScene:onEnter");
    Layer::onEnter();
	gameCoin = UserDefault::getInstance()->getIntegerForKey("gameCoin",100);
	addScore(0);	//ゲーム画面に反映するため
}

void GameScene::onExit(){
    log("GameScene:onExit");
	Layer::onExit();
    enemyList.clear();
    itemList.clear();
	this->removeAllChildrenWithCleanup(true);
	UserDefault* ud = UserDefault::getInstance();
	ud->setIntegerForKey("gameCoin", gameCoin);
	ud->flush();
}

void GameScene::onPlayerMoveEnd(){
	log("onMoveEnd");
    mPlayer->isUserAct = false;
    if (itemList.empty()){
        fail();
        return;
    }
    log("isUSerAct = false");
	Text* coinLabel = dynamic_cast<Text*>(uiLayout->getChildByName("Score"));
	
	for (auto it = itemList.begin(); it != itemList.end();) {
		auto move = MoveTo::create(1.0f, uiLayout->getPosition() + coinLabel->getPosition() + coinLabel->getContentSize() / 2);
		auto func = CallFuncN::create(CC_CALLBACK_1(GameScene::coinRemove, this));
		auto action = Sequence::create(move, func, nullptr);
		(*it)->runAction(action);
		++it;
    }

	itemList.clear();
    
}

void GameScene::coinRemove(Node* sprite){
	addScore(15);
	removeChild(sprite);
    
    if (itemList.empty()) {
        mPlayer->isUserAct = true;
    }
    
    if (enemyList.empty() && itemList.empty()) {
        //数が0になった場合はゲームクリア
        //クリア保存
        std::string clearKey = StringUtils::format("stage%d", stageId);
        log("clearKey = %s", clearKey.c_str());
        UserDefault::getInstance()->setBoolForKey(clearKey.c_str(), true);
        mPlayer->unscheduleAllSelectors();
        unschedule(schedule_selector(GameScene::onCollisionCheck));
        GameEffect* effect = static_cast<GameEffect*>(getChildByTag(1000));
        effect->clearEffect([] {
            auto transitionAction = TransitionFade::create(1.0f, SelectStageScene::createScene(), Color3B(255, 255, 255));
            Director::getInstance()->replaceScene(transitionAction);
        });
    }else{
        fail();
    }
}

void GameScene::coinAdd(Enemy* enemy){
	TextureCache* texCache = Director::getInstance()->getTextureCache();
	Sprite* coin = Sprite::createWithTexture(texCache->addImage("coin.png"));
	coin->setPosition(enemy->getPosition());
	coin->setScale(0.5f);
	coin->setAnchorPoint(Vec2(1.0f, 0.5f));
	auto action = RepeatForever::create(RotateBy::create(0.5f, Vec3(0.0f, 360.0f, 0.0f)));
	coin->runAction(action);
	itemList.push_back(coin);
	
	addChild(coin);
}

void GameScene::fail()
{
    //失敗
    GameEffect* effect = static_cast<GameEffect*>(getChildByTag(1000));
    effect->failEffect([] {
        auto transitionAction = TransitionFade::create(1.0f, SelectStageScene::createScene(), Color3B(255, 255, 255));
        Director::getInstance()->replaceScene(transitionAction);
    });
    log("game fail");    
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
//    GameEffect* effect = static_cast<GameEffect*>(getChildByTag(1000));
//    effect->failEffect();
//    effect->clearEffect();
    
}

void GameScene::onCollisionCheck(float detla){
    for (auto it = enemyList.begin(); it != enemyList.end();) {
        if((*it)->onCollideWithPlayer(mPlayer)){
            //当たった時の処理を行いたい
			coinAdd(*it);
			(*it)->removeFromParentAndCleanup(true);
            it = enemyList.erase(it);
			continue;
        }
		++it;
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

void GameScene::addScore(int addCount){
	gameCoin += addCount;
	log("addScore gameScore = %05d", gameCoin);
	char format[] = "コイン : %05d";
	char buf[50];
	sprintf(buf, format, gameCoin);
    Text* back_label = dynamic_cast<Text*>(uiLayout->getChildByName("Score"));
	std::string text = std::string(buf);
    log("score = %s", text.c_str());
    back_label->setString(text);
}
