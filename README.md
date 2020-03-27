# TowerJawn

Player:
-attack
-array of towers
    -tower pings player to determine target
    -if target is killed, tower pings player to determine next best target (strongest, closest, etc)
-array of enemies
    -enemy pings player to determine target each time target is destroyed until enemy death

Tower:
//
Fewer towers that have several guns/subturrets mounted on them that all share the same tower health but individual targeting based on the weapons stats (range, damage, etc) Tower recieved targeting data from player
//
-attack
-range
-health
-target
    -ping player to detemine

Subtower:
//
Mounted on towers and have no individual health. Individual targeting given from the player
//
-attack
-range
-traget
    -ping player to detemine


Enemy Spawner:
-random coordinates (x,y)
-spawn enemy (return enemy to add to array in player?)

Enemy:
-attack
-health
-speed
-target
    -ping player to determine