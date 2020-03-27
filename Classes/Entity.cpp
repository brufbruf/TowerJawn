#include "Entity.h"

Entity * Entity::createWithFile(const std::string &filename) {
  Entity* pRet = new Entity();
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

bool Entity::initWithFile(const std::string &filename)
{
    if (!Sprite::initWithFile(filename)) return false;

    health = 0;

    return true;
}

// returns true if alive
bool Entity::takeDamage(int damage) {
  health -= damage;
  if(health <= 0) {
    health = 0;
    return false;
  }

  return true;
}

void Entity::destroy() {
  // remove from parent, etc
  // TODO

  removeFromParentAndCleanup(true);
}