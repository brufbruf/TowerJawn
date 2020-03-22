#ifndef __EnemySpawner_H__
#define __EnemySpawner_H__

#include "cocos2d.h"
#include "Enemy.h"
#include "BasicEnemy.h"
#include <vector>
#include <random>
#include "Game.h"
#define PI 3.14159265

class EnemySpawner {
  public:
    ~EnemySpawner() {}
    void spawnOne() {
      auto spawnPoint = pickSpawnPoint();
      auto enemy = pickAndConfigureEnemy();


      if(parentNode == nullptr) {
        std::cout << "no parent node" << std::endl;
        exit(1);
      }

      std::cout << "spawning enemy" << std::endl;
      enemy->setTarget(Game::getInstance().EnemyNewTarget());
      parentNode->addChild((cocos2d::Sprite *)enemy);
      enemy->moveToTarget();
    }

    EnemySpawner() {}
    EnemySpawner(cocos2d::Node *parentNode_in) : parentNode(parentNode_in) {}
    void setParentNode(cocos2d::Node *parentNode_in) {
      parentNode = parentNode_in;
    }

  private:
    cocos2d::Node * parentNode;
    cocos2d::Vec2 pickSpawnPoint() {
      float radius = 500;
      float randomPosition = ((float) rand() / (RAND_MAX)) + 1;
      cocos2d::Vec2 pos(radius*cos(randomPosition*2*PI), radius*sin(randomPosition*2*PI));

      return pos;
    }

    Enemy * pickAndConfigureEnemy() {
      auto Enemy = BasicEnemy::create();
      return Enemy;
    }
};

#endif