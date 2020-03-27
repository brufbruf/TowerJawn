#include "cocos2d.h"
#include "Enemy.h"
#include <random>
#include "helper.h"
#include "Game.h"

USING_NS_CC;
using namespace std;

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

    attackSpeed = 1;
    movementSpeed = 1;
    attackDamage = 1;
    attackScheduleKey = Helpers::get_uuid();
    _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseDown = CC_CALLBACK_1(Enemy::onMouseClick, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);

    return true;
}

void Enemy::onMouseClick(Event *event) {
  // Mouse is down, take damage from main player.
  EventMouse* e = (EventMouse*)event;
  if(!this->getBoundingBox().containsPoint(Vec2(e->getCursorX(), e->getCursorY()))) 
    return;

  auto mainPlayer = Game::getInstance().GetMainPlayer();
  if(mainPlayer == nullptr)
    return;

  mainPlayer->attackEnemy(this);
}

void Enemy::destroy() {
  // remove from parent, etc
  // TODO
  // stops all actions and schedulers
  removeFromParentAndCleanup(true);
}

void Enemy::setTarget(Entity *target_in) {
    target = target_in;
}

void Enemy::moveToTarget() {
  if(target == nullptr) {
    // break
    std::cout << "this wasn't supposed to happen, target is unassigned" << std::endl;
    exit(1);
  }

  float timeToTarget = distanceToTarget() / movementSpeed;

  cocos2d::Action *action = MoveTo::create(timeToTarget, target->getPosition());
  std::cout << "moving enemy to target" << std::endl;
  runAction(action);
  std::function<void (float)> scheduleFunc = [&](float f) -> void {
    unschedule(attackScheduleKey);
    schedule(CC_CALLBACK_0(Enemy::attackTarget, this), attackSpeed, attackScheduleKey);
  };
  schedule(scheduleFunc, timeToTarget, attackScheduleKey);
}

void Enemy::attackTarget() {
  if(target == nullptr) {
    std::cout << "this wasn't supposed to happen, target is unassigned" << std::endl;
    exit(1);
  }

  if(!target->takeDamage(attackDamage)) {
    unschedule(attackScheduleKey);
    aquireNewTarget();
  }
}

void Enemy::aquireNewTarget() {
  Entity *newTarget = Game::getInstance().EnemyNewTarget();
  setTarget(newTarget);
  if(newTarget == nullptr)
    return;
  moveToTarget();
}

float Enemy::distanceToTarget() {
  if(target == nullptr) {
    std::cout << "this wasn't supposed to happen, target is unassigned" << std::endl;
    exit(1);
  }

  Vec2 targetPos = target->getPosition();
  return targetPos.distance(getPosition());
}