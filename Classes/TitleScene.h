//
//  TitleScene.h
//  Tetris
//
//  Created by Yoshida Mitsunobu on 2014/07/26.
//
//

#ifndef __Tetris__TitleScene__
#define __Tetris__TitleScene__

#include "cocos2d.h"

class GameClear : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameClear);
    
private:
    
};

#endif /* defined(__Tetris__TitleScene__) */
