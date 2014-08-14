#include "SelectStageScene.h"
#include "cocostudio/CCSGUIReader.h"
#include "ui/CocosGUI.h"
#include "ui/UIHelper.h"
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
    auto uiLayout = static_cast<Layout*>(guiReader->widgetFromJsonFile("StageSelectScene.ExportJson"));
    uiLayout->setPosition(Vec2(0, visibleSize.height - uiLayout->getContentSize().height));
    addChild(uiLayout);

	log("uiLayer childcount = %l", uiLayout->getChildrenCount());
	//log("uiLayer childcount = %d ", uiLayout->);
	//ImageView* icon1 = static_cast<ImageView*>(uiLayout->getChildByName("clearicon1"));
	//if(!icon1){
	//	icon1->setVisible(false);
	//}
	for (int i = 0; i < 5; i++)
	{
        //アイコン用名前を作る
		char filename[50];
		sprintf(filename, "clearicon%d", i+1);
		auto icon = Helper::seekWidgetByName(uiLayout, filename);
		icon->setVisible(false);

        //ボタン用名前を作る
		sprintf(filename, "SelectButton%d", i+1);
		auto button = Helper::seekWidgetByName(uiLayout, filename);
		button->addTouchEventListener(CC_CALLBACK_2(SelectStageScene::buttonTouchEvent, this));
	}


    return true;
}

void SelectStageScene::buttonTouchEvent(Ref *pSender, Widget::TouchEventType type){
	log("buttonTouchEvent");

	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
		log("name = %s",static_cast<Button*>(pSender)->getName().c_str());
        //GameSceneへと遷移するロジックを作る
		break;
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}