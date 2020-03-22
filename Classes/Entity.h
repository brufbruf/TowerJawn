#ifndef __Entity_H__
#define __Entity_H__

#include "cocos2d.h"

class Entity : public cocos2d::Sprite
{
public: 
    static Entity * createWithFile(const std::string &filename);
    virtual bool initWithFile(const std::string &filename);

    // returns true if alive
    virtual bool takeDamage(int damage);
    virtual void setHealth(int health_in) {
        health = health_in;
    }

    //clean up
    virtual void destroy();
    Entity(){}
    ~Entity(){}

private:
    int health;
};

#endif