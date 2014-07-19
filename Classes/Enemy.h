//
//  Enemy.h
//  Tetris
//
//  Created by Yoshida Mitsunobu on 2014/07/19.
//
//

#ifndef __Tetris__Enemy__
#define __Tetris__Enemy__

#include "cocos2d.h"

USING_NS_CC;

class Player;

class Enemy : public Sprite {
public:
    Enemy(void);
    virtual ~Enemy(void);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    
    bool onCollideWithPlayer(Player* player);
    
    //Playerを生成するようのメソッド
    static Enemy* create(const std::string &filename);
    
private:
    Vec2 beginTouch;
    float power;
};


#endif /* defined(__Tetris__Enemy__) */
