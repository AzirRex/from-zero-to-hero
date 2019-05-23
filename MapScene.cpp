#include "proj.win32/MapScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

float x, y;
Scene *MapScene::createScene()
{
	Scene *scene = Scene::create();
	MapScene *layer = MapScene::create();
	scene->addChild(layer);
	return scene;
}
/*void MapScene::view_move()
{
	Size visableSize = CCSizeMake(1920, 1080); //��Ļ��С
	Size mysize = CCSizeMake(3*1920/2, 3*1080/2);       //������С

//�������������ô�С
	LayerColor* scrollLayer = LayerColor::create(ccc4(255, 255, 255, 255));
	scrollLayer->setContentSize(mysize);

	//�����еĶ���
	Sprite* MAP = Sprite::create("map.jpg");
	MAP->setScale(3.0f);
	MAP->setPosition(ccp(3*1920 / 2.0, 3*1080 / 2.0));
	scrollLayer->addChild(MAP);


	//����������ͼCCScrollView
	ScrollView * scrollView = ScrollView::create();
	this->addChild(scrollView, 0, 2);

	//��������
	scrollView->setContainer(scrollLayer);  //��������
	scrollView->setViewSize(visableSize); //���������С
	scrollView->setBounceable(false);        //�Ƿ���е���
	scrollView->setDelegate(this);
}*/
bool MapScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//��ͼ
	auto MAP = Sprite::create("map.jpg");
	MAP->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	MAP->setScale(1.0f);
	auto* layer1 = Layer::create();
	layer1->setAnchorPoint(Vec2(0, 0));
	layer1->setPosition((Vec2(0, 0)));
	layer1->addChild(MAP);
	this->addChild(layer1,0, 1);

	//���԰�ť
	auto pBackButtonItem = MenuItemImage::create("Backbutton.png", "Backbutton.png", CC_CALLBACK_1(MapScene::EnterHelloWorldScene, this));
	auto BackButton = Menu::create(pBackButtonItem,NULL);
	BackButton->setPosition(Vec2(80,visibleSize.height-30));
	addChild(BackButton, 1);
	hero = new heroPrint();
	hero->initHeroSprite( 8, Vec2(860,540));
	addChild(hero, 2, 3);

	
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto myKeyListener = EventListenerKeyboard::create();	//�����̱�����ʱ��Ӧ	
	/*myKeyListener->onKeyPressed = [](EventKeyboard::KeyCode keycode, cocos2d::Event *event)	
	{		CCLOG("key is pressed,keycode is %d", keycode);	};*/
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	myKeyListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	//scheduleUpdate();
	dispatcher->addEventListenerWithSceneGraphPriority(myKeyListener, this);
	return true;
}
void MapScene::onKeyPressed(EventKeyboard::KeyCode keycode, Event* event) {
	Vec2 hero_position = hero->herosPosition();
	//Sprite* MAP = (Sprite*)getChildByTag(1);
	Layer* layer1 = (Layer*)getChildByTag(1);
	Vec2 layer_position = layer1->getPosition();
	CCLOG("%f %f", hero_position.x, hero_position.y);
	if (keycode == EventKeyboard::KeyCode::KEY_UP_ARROW) {
		CCLOG("�����ˣ��Ϸ����");
		hero->heroSprite->setPosition(Vec2(hero_position.x, hero_position.y-100));
		layer1->setPosition(Vec2(layer_position.x, layer_position.y-100));
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_LEFT_ARROW) {
		CCLOG("�����ˣ������");
		hero->heroSprite->setPosition(Vec2(hero_position.x+100, hero_position.y ));
		layer1->setPosition(Vec2(layer_position.x+100, layer_position.y ));
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW) {
		CCLOG("�����ˣ��ҷ����");
		hero->heroSprite->setPosition(Vec2(hero_position.x-100, hero_position.y));
		layer1->setPosition(Vec2(layer_position.x-100, layer_position.y ));
	}
	else if (keycode == EventKeyboard::KeyCode::KEY_DOWN_ARROW) {
		hero->heroSprite->setPosition(Vec2(hero_position.x , hero_position.y+100));
		layer1->setPosition(Vec2(layer_position.x , layer_position.y+100));
		CCLOG("�����ˣ��·����");
	}
}
bool MapScene::onTouchBegan(Touch *touch, Event *unused_event)
{
	float Position_x=hero->getDistance_x(hero->currentPosition, touch->getLocation());
	float Position_y = hero->getDistance_x(hero->currentPosition, touch->getLocation());
	CCLOG("%f %f", Position_x, Position_y);
	float distance = hero->getDistance(hero->currentPosition, touch->getLocation());
	hero->getDirection(hero->currentPosition, touch->getLocation());
	hero->heroMoveTo(touch->getLocation());
	Point position = touch->getLocation();
	CCLOG("%f,%f", position.x, position.y);
	Layer* layer1 = (Layer*)getChildByTag(1);
	//MoveBy* moveby = MoveBy::create((float)distance / 200, Point(Position_x, Position_y));
	//layer1->runAction(moveby);
	
	/*auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size mapSize = Size(2362 * 3, 1532 * 3);
	Vec2 hero_position = hero->getPosition();
	Vec2 layerPosition = Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	if (x >= visibleSize.width / 2 && x <= mapSize.width - visibleSize.width / 2)
	{
		layerPosition.x = visibleSize.width / 2 - x;
	}
	if (x >= mapSize.width - visibleSize.width / 2)
	{
		layerPosition.x = visibleSize.width / 2 - mapSize.width;
	}
	if (y >= visibleSize.height && y <= mapSize.height - visibleSize.height / 2)
	{
		layerPosition.y = visibleSize.height / 2 - y;
	}
	if (y >= mapSize.height - visibleSize.height / 2) { layerPosition.y = visibleSize.height / 2 - mapSize.height; }
	layer1->setPosition(layerPosition);*/
	return false;
}
void MapScene::update(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Size mapSize = Size(2362 , 1532 );
	CCLOG("%f,%f", x, y);
	Vec2 layerPosition = Vec2(origin.x + visibleSize.width/2 , origin.y + visibleSize.height/2 );
	if (x >= visibleSize.width / 2 && x <= mapSize.width - visibleSize.width / 2)
	{
		layerPosition.x = visibleSize.width / 2 - x;
	}
	if (x >= mapSize.width - visibleSize.width / 2)
	{
		layerPosition.x = visibleSize.width / 2 - mapSize.width;
	}
	if (y >= visibleSize.height && y <= mapSize.height - visibleSize.height / 2)
	{
		layerPosition.y = visibleSize.height / 2 - y;
	}
	if (y >= mapSize.height - visibleSize.height / 2) { layerPosition.y = visibleSize.height / 2 - mapSize.height; }
	Layer* layer1=(Layer*) getChildByTag(1);
	layer1->setPosition(layerPosition);
}
/*void MapScene::setViewPointCenter(Point position)
{
	//�Ӵ���С
	Size winSize = Director::getInstance()->getWinSize();
	//��ͼ��С
	Size mapSize = Size(2362 * 3, 1532 * 3);

	//��hero��mainLayer�����ұ߽�����λ���ڰ����Ļ�䲻������ͼ������Ӣ����Layer�����λ����[winSize.w/2,mapSize.w-winSize.w/2]�ķ�Χ�ŷ���
	//��þ�ͷ�ƶ��ķ�Χ(����ͼ������ķ�Χ)
	float scrollX;
	if (position.x > winSize.width / 2)
		 scrollX = position.x;
	else
		 scrollX = winSize.width / 2;
	if (scrollX > mapSize.width - winSize.width / 2)
		 scrollX = mapSize.width - winSize.width / 2;
	else
		 scrollX = scrollX;
	float scrollY;
	if (position.y > winSize.height / 2)
		scrollY = position.y;
	else
		 scrollY = winSize.height / 2;
	if (scrollY > mapSize.height - winSize.height / 2)
		scrollY = mapSize.height - winSize.height / 2;
	else
		float scrollY = scrollY;

	//��ͷ�ƶ�����ͼ������ʱ�����귶Χ(��δ������x,y�ǲ�ȷ��ֵ���������Ƿ�Χ��������ʱx,yΪ��ֵ����ʱ���Ǿ�ͷ�����GameLayer�����ƶ��ľ��롾�����ͷ�����ƶ��Ļ���)
	Point cameraNeedMoveSize = ccp(scrollX, scrollY);

	//��ͷ�����Layer������λ��
	Point centerOfView = ccp(CENTER.x, CENTER.y);

	//���ھ�ͷ�Ǿ�ֹ�ģ������ƶ�Layer��ͬ���ƶ���ͷ
	Point viewPoint = ccpSub(centerOfView, cameraNeedMoveSize);

	//����Layer�ƶ���Ŀ������
	 layer1->setPosition(viewPoint);

}*/

void MapScene::EnterHelloWorldScene(Ref *pSenderBack)
{
	Director::getInstance()->replaceScene((HelloWorld::createScene()));
}