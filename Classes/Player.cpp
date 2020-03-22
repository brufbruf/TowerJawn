#include "Player.h"
#include "cocos2d.h"
#include <iostream>
#define PI 3.14159265

USING_NS_CC;

bool Player::init() {
  if (!Entity::initWithFile("playerTurret.png")) return false;
  setAnchorPoint(Vec2(0.5, 0.5));

  return true;
}

void Player::rotateTo(float x, float y) {
  float xDiff = this->getPositionX() - x;
  float yDiff = this->getPositionY() - y;
  float distance = sqrt(xDiff*xDiff + yDiff*yDiff);
  float angle = -acos(xDiff/distance)*(180/PI) - 90;

  if(yDiff < 0) {
      angle *= -1;
      angle -= 180;
  } 

  cocos2d::Action *rotateAction = RotateTo::create(0, angle);
  runAction(rotateAction);
}

void Player::destroy() {
  // remove from parent, etc
  // TODO
  // stops all actions and schedulers
  removeFromParentAndCleanup(true);
}

bool Player::takeDamage(int damage) {
  std::cout << "Player taking damage" << std::endl;
  if(!Entity::takeDamage(damage)) {
    // die (but remember that their is a pointer to this) TODO
    destroy();
    return false;
  }

  return true;
}