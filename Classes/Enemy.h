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
    Enemy(){}
    ~Enemy(){}
};

#endif