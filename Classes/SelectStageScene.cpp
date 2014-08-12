#include "SelectStageScene.h"
#include "cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

USING_NS_CC;
using namespace cocostudio;
using namespace ui;

Scene* SelectStageScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
	auto layer = SelectStageScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SelectStageScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    //UI‚Ì“Ç‚Ý•û
    GUIReader* guiReader = GUIReader::getInstance();
    auto uiLayout = static_cast<Layout*>(guiReader->widgetFromJsonFile("StageSelectScene.json"));
    uiLayout->setPosition(Vec2(0, visibleSize.height - uiLayout->getContentSize().height));
    addChild(uiLayout);
    
    return true;
}