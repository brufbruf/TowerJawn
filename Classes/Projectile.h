#ifndef __PROJECTILE_H__
#define __PROJECTILE_H__
#include "cocos2d.h"
#include "Entity.h"
class Projectile : public cocos2d::Sprite
{
  public:
    static Projectile * createWithFile(const std::string &filename) {
      Projectile* pRet = new Projectile();
      if (pRet && pRet->initWithFile(filename))
      {
          pRet->autorelease();
      }
      else
      {
          CC_SAFE_DELETE(pRet);
      }
      return pRet;
    }

    virtual bool initWithFile(const std::string &filename) {
      if (!cocos2d::Sprite::initWithFile(filename)) return false;

      return true;
    }

    virtual void destroy() {
      removeFromParentAndCleanup(true);
    }

    virtual void fireTowardsEntity(Entity *entity, cocos2d::ccSchedulerFunc callback) {};
    Projectile(){}
    ~Projectile(){}
};
#endif