#ifndef __GAMEOVERSCENE_H__
#define __GAMEOVERSCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene() {
      return GameOverScene::create();
    }

    virtual bool init() {
        //////////////////////////////
      // 1. super init first
      if ( !cocos2d::Scene::init() )
      {
          return false;
      }

      auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
      cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

      auto backgroundLayer = cocos2d::LayerColor::create(cocos2d::Color4B(0, 0, 0, 255), visibleSize.width, visibleSize.height);
      addChild(backgroundLayer);

      auto label = cocos2d::Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 24);
      if (label == nullptr)
      {
          printf("Error while loading: %s\n", "'fonts/Marker Felt.ttf'");
      }
      else
      {
          // position the label on the center of the screen
          label->setPosition(cocos2d::Vec2(origin.x + visibleSize.width/2,
                                  origin.y + visibleSize.height - label->getContentSize().height));

          // add the label as a child to this layer
          this->addChild(label, 1);
      }
      return true;
    }
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);
};

#endif