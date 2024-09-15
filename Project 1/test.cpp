#include "Creature.hpp" 

int main(){

    Creature dragon;
    dragon.setHitpoints(10);
    dragon.setLevel(5);
    dragon.setTame(true);
    dragon.display();

    Creature worm("wormy",Creature::Category::MYSTICAL, 3,2);
    worm.setTame(true);
    worm.display();
}