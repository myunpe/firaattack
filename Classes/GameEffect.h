//
//  GameEffect.h
//  Tetris
//
//  Created by Yoshida Mitsunobu on 2014/07/20.
//
//

#ifndef __Tetris__GameEffect__
#define __Tetris__GameEffect__

#include "cocos2d.h"
/**
 * ゲームのいろいろなエフェクトを管理する
 * このクラスで行われるエフェクトが再生されている間は操作不可になる
 */

USING_NS_CC;

class GameEffect : public Sprite {
public:
    GameEffect(void);
    virtual ~GameEffect(void);
    
    virtual void onEnter() override;
    virtual void onExit() override;
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    
    Rect getRect();
    void move(float delta);
    void setDispatchTouch(bool isEnable);
    
    //Playerを生成するようのメソッド
    static GameEffect* create(const std::string &filename);
    
    
    //失敗した時のエフェクト
    void failEffect();
    //クリアした時のエフェクト
    void clearEffect();

    
private:
    Vec2 beginTouch;
    float power;
    
    bool isDispatch;
};

#endif /* defined(__Tetris__GameEffect__) */
