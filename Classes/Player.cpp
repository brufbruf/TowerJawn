#include "Player.h"
#include "cocos2d.h"
#include "Game.h"
#include "BasicProjectile.h"
#include <iostream>
#define PI 3.14159265

USING_NS_CC;

bool Player::init() {
  if (!Entity::initWithFile("blank.png")) return false;
  setAnchorPoint(Vec2(0.5, 0.5));
  //Instantiate sprites for the graphics of Player
  playerTurret = Sprite::create("playerTurret.png");
  auto turretBase = Sprite::create("turretBase.png");
  //Add graphic sprites as children of PLayer
  addChild(turretBase);
  addChild(playerTurret);
  //Set postition of turret base to the middle of the game screen
  turretBase->setPosition(this->getTextureRect().size.width/2, this->getTextureRect().size.height/2);
  turretBase->setAnchorPoint(Vec2(0.5, 0.5));
  //Set postition of player turret to the middle of the game screen
  playerTurret->setPosition(this->getTextureRect().size.width/2, this->getTextureRect().size.height/2);
  playerTurret->setAnchorPoint(Vec2(0.5, 0.5));

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
  playerTurret->runAction(rotateAction);
}

void Player::destroy() {
  // remove from parent, etc
  // TODO
  // stops all actions and schedulers
  unschedule("playerDeath");
  removeFromParentAndCleanup(true);
}

bool Player::takeDamage(int damage) {
  std::cout << "Player taking damage" << std::endl;
  if(!Entity::takeDamage(damage)) {
    // die (but remember that their is a pointer to this) TODO
    schedule(CC_CALLBACK_0(Player::destroy, this), 1, "playerDeath");
    Game::getInstance().TowerKilled(this);
    return false;
  }

  return true;
}

void Player::attackEnemy(Enemy *enemy) {
  // send a projectile, also make enemy take damage
  launchProjectileAtEnemy(enemy);
}

void Player::launchProjectileAtEnemy(Enemy *enemy) {
  std::cout << "launching projectile" << std::endl;
  auto projectile = BasicProjectile::create();
  projectile->setPosition(convertToWorldSpace(findTipOfGun()));
  projectile->setRotation(playerTurret->getRotation());
  getParent()->addChild(projectile);
  auto schedulerFunc = [&](float f) -> void {
    if(!((Entity *)enemy)->takeDamage(attackDamage)) {
      enemy->destroy();
    }
  };
  projectile->fireTowardsEntity(enemy, schedulerFunc);
}

Vec2 Player::findTipOfGun() {
  float rotation = playerTurret->getRotation();
  float hheight = playerTurret->getBoundingBox().size.height/2;
  float hwidth = playerTurret->getBoundingBox().size.width/2;

  float xFromCenter = hwidth*cos(rotation);
  float yFromCenter = hheight*sin(rotation);

  return Vec2(xFromCenter - hwidth, yFromCenter - hheight);
}