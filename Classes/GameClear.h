//
//  GameClear.h
//  Tetris
//
//  Created by Yoshida Mitsunobu on 2014/07/20.
//
//

#ifndef __Tetris__GameClear__
#define __Tetris__GameClear__

#include "cocos2d.h"
#include "vector"
#include "list"

USING_NS_CC;


class GameClear : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameClear);

	void onExit();

	bool onTouchBegan(Touch *touch, Event *unused_event); 
    void onTouchMoved(Touch *touch, Event *unused_event); 
    void onTouchEnded(Touch *touch, Event *unused_event); 
    void onTouchCancelled(Touch *touch, Event *unused_event);
    
private:
    
};

#endif /* defined(__Tetris__GameClear__) */
