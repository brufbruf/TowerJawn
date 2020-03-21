#include "Enemy.h"

Enemy * Enemy::createWithFile(const std::string &filename) {
  Enemy* pRet = new Enemy();
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

bool Enemy::initWithFile(const std::string &filename)
{
    if (!Entity::initWithFile(filename)) return false;

    return true;
}

void Enemy::destroy() {
  // remove from parent, etc
  // TODO
  // stops all actions and schedulers
  this->cleanup();
}