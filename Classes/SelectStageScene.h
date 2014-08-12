//
//  SelectStageScene.h
//  Tetris
//
//  Created by Yoshida Mitsunobu on 2014/08/13.
//
//
#ifndef __Tetris__SelectStageScene__
#define __Tetris__SelectStageScene__
#include "cocos2d.h"


class SelectStageScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(SelectStageScene);
};


#endif /* defined(__Tetris__GameScene__) */