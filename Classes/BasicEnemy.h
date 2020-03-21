#ifndef __BasicEnemy_H__
#define __BasicEnemy_H__

#include "cocos2d.h"
#include "Enemy.h"

class BasicEnemy : public Enemy
{
public: 
    CREATE_FUNC(BasicEnemy);
    virtual bool init() {
      if (!Enemy::initWithFile("enemy.png")) return false;

      this->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
      return true;
    };

private:
    BasicEnemy(){}
    ~BasicEnemy(){}
};

#endif