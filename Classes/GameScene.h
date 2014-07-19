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
#include "vector"
#include "list"

class Player;
class Enemy;

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    //当たり判定チェック用
    void onCollisionCheck(float detla);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
private:
    Player* mPlayer;
    std::list<Enemy*> enemyList;

};


#endif /* defined(__Tetris__GameScene__) */
