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

class Player;
class Enemy;



class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void onEnter();
    
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
    void addScore();
    
private:
    Player* mPlayer;
    std::list<Enemy*> enemyList;
    cocos2d::ui::Layout* uiLayout;
    
    int enemyNum;
    int gameScore;
};


#endif /* defined(__Tetris__GameScene__) */
