#ifndef __Player_H__
#define __Player_H__

#include "cocos2d.h"
#include "Entity.h"

class Player : public Entity
{
public: 
    CREATE_FUNC(Player);
    virtual bool init();

    void rotateTo(float x, float y);

    //clean up
    virtual void destroy();

    bool takeDamage(int damage);

private:
    Player(){}
    ~Player(){}
};

#endif