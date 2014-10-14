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
    virtual void onExit() override;
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    Rect getRect();
    Rect getRect(Sprite* sprite);
    void move(float delta);
    
    //Playerを生成するようのメソッド
    static Player* create(const std::string &filename);
    
    //Spriteとの当たり判定
    bool onCollideWithSprite(Sprite* other);

	//強制的に移動を終了させる
	void forceMoveEnd();

	//reflectMaxを設定
	inline void setReflectMax(int max){ reflectMax = max; }
	inline int getReflectMax() { return reflectMax - reflectCount; }
    
public:
    std::function<void()> onMoveEnd;
    bool isUserAct; //ユーザーが操作出来るか
    
private:
    Vec2 beginTouch;
    float power;
    int reflectCount;
    int reflectMax;
};



#endif /* defined(__Tetris__Player__) */
