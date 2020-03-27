#ifndef __GAME_H__
#define __GAME_H__
#include "cocos2d.h"
#include "Entity.h"
#include "Enemy.h"
#include "Player.h"
#include "GameOverScene.h"
#include <iostream>
#include <queue>
#include <vector>


// implements a priority queue to give enemies and turrets targets
class Game
{
    public:
        static Game& getInstance()
        {
            static Game instance; // Guaranteed to be destroyed.
                                  // Instantiated on first use.
            return instance;
        }
    private:
        Game() {}                    // Constructor? (the {} brackets) are needed here.
        std::vector<Entity*> towers; 
        Player *mainPlayer;
        // C++ 03
        // ========
        // Don't forget to declare these two. You want to make sure they
        // are unacceptable otherwise you may accidentally get copies of
        // your singleton appearing.
        // Game(Game const&);              // Don't Implement
        // void operator=(Game const&); // Don't implement

        // C++ 11
        // =======
        // We can use the better technique of deleting the methods
        // we don't want.
    public:
        Game(Game const&) = delete;
        void operator=(Game const&) = delete;
        Entity * EnemyNewTarget() {
          if(towers.empty()) {
            // Game over
            GameOver();
            return nullptr;
          }
          return towers[0];
        }
        // Enemy * TowerNewTarget() {

        // }
        void EnemySpawned(Enemy *enemy) {}
        void TowerSpawned(Entity *tower) {
          towers.push_back(tower);
        }

        void TowerKilled(Entity *tower) {
          auto it = std::find(towers.begin(), towers.end(), tower);
          towers.erase(it);
          if(towers.empty()) {
            // Game over
            GameOver();
          }
        }

        void SetMainPlayer(Player *mainPlayer_in) {
          mainPlayer = mainPlayer_in;
        }

        Player *GetMainPlayer() {
          return mainPlayer;
        }

        void GameOver() {
          std::cout << "Game Over" << std::endl;
          auto gameOverScene = GameOverScene::create();
          cocos2d::Director::getInstance()->replaceScene(gameOverScene);
        }

        // Note: Scott Meyers mentions in his Effective Modern
        //       C++ book, that deleted functions should generally
        //       be public as it results in better error messages
        //       due to the compilers behavior to check accessibility
        //       before deleted status
};

#endif