//
//  GameScene.h
//  Tetris
//
//  Created by Yoshida Mitsunobu on 2014/07/18.
//
//

#ifndef __Tetris__GameScene__
#define __Tetris__GameScene__

#include "cocos2d.h"
#include <vector>
#include <list>
#include "ui/CocosGUI.h"
#include "json/document.h"

class Player;
class Enemy;

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(int stageId);

	virtual bool init();

	void onEnter();
	void onExit();
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

private:
	//Jsonからゲームデータを読み込む
	void readGameData();

	//当たり判定チェック用
	void onCollisionCheck(float detla);

	//点数追加
	void addScore(int addCount);
	//プレイヤーの移動が終了した時呼ばれる
	void onPlayerMoveEnd();
	//コインを表示する関数
	void coinAdd(Enemy* enemy);
	//移動後コインを消す関数
	void coinRemove(cocos2d::Node* sprite);
    //敵を生成する関数
	void enemyCreate(rapidjson::Value& enemyData);
    //失敗した時の処理
    void fail();

private:
	Player* mPlayer;
    MotionStreak* streak;
    
	std::list<Enemy*> enemyList;
	std::list<cocos2d::Sprite*> itemList;
	cocos2d::ui::Layout* uiLayout;

	int enemyNum;
	int gameCoin;
    int stageId;
    EventListenerTouchOneByOne* touchListener;
};


#endif /* defined(__Tetris__GameScene__) */
