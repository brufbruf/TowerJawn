#ifndef __BasicEnemy_H__
#define __BasicEnemy_H__

#include "cocos2d.h"
#include "Enemy.h"

class BasicEnemy : public Enemy
{
public: 
    CREATE_FUNC(BasicEnemy);
    virtual bool init() {
      if (!Enemy::initWithFile("basicEnemy.png")) return false;

      setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
      setStats(10, 1, 1, 100);
      return true;
    };

private:
    BasicEnemy(){}
    ~BasicEnemy(){}
};

#endif