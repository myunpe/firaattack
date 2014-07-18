//
//  Player.h
//  Tetris
//
//  Created by Yoshida Mitsunobu on 2014/07/18.
//
//

#ifndef __Tetris__Player__
#define __Tetris__Player__

#include "cocos2d.h"

USING_NS_CC;

class Player : public Sprite {
public:
    Player(void);
    virtual ~Player(void);
    
    virtual void onEnter() override;
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    
    //Playerを生成するようのメソッド
    static Player* create(const std::string &filename);
};



#endif /* defined(__Tetris__Player__) */
