#include "SelectStageScene.h"
#include "cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "ui/UIHelper.h"
#include "cocostudio/CocoStudio.h"
#include "GameScene.h"

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

    GUIReader* guiReader = GUIReader::getInstance();
    auto uiLayout = static_cast<Layout*>(guiReader->widgetFromJsonFile("StageSelect.json"));
	uiLayout->setScale(visibleSize.width / 640.0f, visibleSize.height / 960.0f);
    //uiLayout->setPosition(Vec2(0, visibleSize.height - uiLayout->getContentSize().height));
	addChild(uiLayout);

	//log("uiLayer childcount = %d ", uiLayout->getChildrenCount());
	for (int i = 1; i < 6; i++)
	{
        //アイコン用名前を作る
		char filename[50];
		sprintf(filename, "clearicon%d", i);
		auto icon = Helper::seekWidgetByName(uiLayout, filename);
		
        if(UserDefault::getInstance()->getBoolForKey(StringUtils::format("stage%d", i).c_str(), false)){
            icon->setVisible(true);
        }else{
            icon->setVisible(false);
        }

        //ボタン用名前を作る
		sprintf(filename, "StageSelect%d", i);
		auto button = Helper::seekWidgetByName(uiLayout, filename);
		button->addTouchEventListener(CC_CALLBACK_2(SelectStageScene::buttonTouchEvent, this));
	}


    return true;
}

void SelectStageScene::buttonTouchEvent(Ref *pSender, Widget::TouchEventType type){
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
        log("buttonTouchEvent BEGAN");

		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
        log("buttonTouchEvent MOVE");

		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
    {
        std::string name = static_cast<Button*>(pSender)->getName();
        for (int i = 1; i < 6; i++) {
            std::string buf = StringUtils::format("StageSelect%d", i);
            log("name = %s, buf = %s ", name.c_str(), buf.c_str());
            if (name.compare(buf) == 0) {
                //GameSceneへと遷移するロジックを作る
                auto transitionAction = TransitionFade::create(1.0f, GameScene::createScene(i), Color3B(255, 255, 255));
                Director::getInstance()->replaceScene(transitionAction);
                break;
            }
        }
    }break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
        log("buttonTouchEvent CANCELED");
		break;
	default:
		break;
	}
}