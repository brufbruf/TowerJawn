#ifndef __BASICPROJECTILE_H__
#define __BASICPROJECTILE_H__
#include "cocos2d.h"
#include "Projectile.h"
#include "Entity.h"
#include "helper.h"
#include <iostream>

class BasicProjectile : public Projectile {
  public:
    virtual bool init() {
      if(!Projectile::initWithFile("basicProjectile.png")) {
        std::cout << "could not init projectile with file" << std::endl;
        exit(1); 
      }
      speed = 2;
      callbackKey = Helpers::get_uuid();
      callbackFunc = [](float f) -> void {};
    }

    void fireTowardsEntity(Entity *entity, cocos2d::ccSchedulerFunc callback) {
      _target = entity;
      callbackFunc = callback;
      runMoveTowardsTarget();
    }

    CREATE_FUNC(BasicProjectile);

    private:
      Entity *_target;
      float speed;
      std::string callbackKey;
      cocos2d::ccSchedulerFunc callbackFunc;
      void updatePosition() {
        // TODO handle logic when enemy dies, so that projectiles don't crash game
        if(_target == nullptr) {
          destroy();
          return;
        }

        stopAllActions();
        runMoveTowardsTarget();
        
      }

      void runMoveTowardsTarget() {
        if(_target == nullptr) {
          destroy();
          return;
        }

        float distanceFromTarget = getPosition().distance(_target->getPosition());
        float timeToTarget = distanceFromTarget / speed;
        auto action = cocos2d::MoveTo::create(timeToTarget, _target->getPosition());
        runAction(action);

        // TODO: we also need to angle it towards the enemy

        unschedule(callbackKey);
        schedule([&](float f) -> void {
          unschedule(callbackKey);
          callbackFunc(f);
        }, timeToTarget, callbackKey);
      }
};

#endif