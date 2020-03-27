#ifndef __Enemy_H__
#define __Enemy_H__

#include "cocos2d.h"
#include "Entity.h"

class Enemy : public Entity
{
public: 
    static Enemy * createWithFile(const std::string &filename);
    virtual bool initWithFile(const std::string &filename);

    // returns true if alive
    // virtual bool takeDamage(int damage);

    //clean up
    virtual void destroy();
    virtual void setTarget(Entity *target_in);
    virtual void moveToTarget();
    virtual void attackTarget();
    virtual void setStats(int health_in,
                            int attackSpeed_in, 
                            int attackDamage_in, 
                            float movementSpeed_in) {
        setHealth(health_in);
        attackSpeed = attackSpeed_in;
        attackDamage = attackDamage_in;
        movementSpeed = movementSpeed_in;
    }
    Enemy(){}
    ~Enemy(){}

    private:
    Entity *target;
    int attackSpeed;
    int attackDamage;
    float movementSpeed;
    std::string attackScheduleKey = "";
    cocos2d::EventListenerMouse *_mouseListener;

    virtual void aquireNewTarget();
    virtual float distanceToTarget();
    virtual void onMouseClick(cocos2d::Event *event);
};

#endif