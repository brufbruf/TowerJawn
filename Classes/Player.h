#ifndef __Player_H__
#define __Player_H__

#include "cocos2d.h"
#include "Entity.h"
#include "Enemy.h"

class Player : public Entity
{
public: 
    CREATE_FUNC(Player);
    virtual bool init();

    void rotateTo(float x, float y);

    //clean up
    virtual void destroy();

    bool takeDamage(int damage);

    void attackEnemy(Enemy *enemy);

private:
    Player(){}
    ~Player(){}
    void launchProjectileAtEnemy(Enemy *enemy);
    cocos2d::Vec2 Player::findTipOfGun();
    cocos2d::Sprite *playerTurret;
    int attackDamage = 10;
};

#endif