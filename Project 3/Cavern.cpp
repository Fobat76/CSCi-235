/**
 * @file Cavern.cpp
 * @author Devin Chen 
 * @brief Cavern Class
 * @date 3/6/2024
*/
#include "Cavern.hpp"

/**
 * Default constructor.
 * Default-initializes all private members. 
*/
Cavern::Cavern(){
    level_sum_ =0;
    tame_count_=0;
}
/** 
* @param   :   A reference to a Creature entering the Cavern
* @post    :   If the given Creature is not already in the Cavern, add Creature to the Cavern and updates the level sum and the tame Creature count if the creature is tame.
* @return  :   returns true if a Creature was successfully added to the Cavern, false otherwise
           :   Hint: Use the above definition of equality will help determine if a Creature is already in the Cavern
**/
bool Cavern::enterCavern(const Creature &new_creature_added){
if(contains(new_creature_added)){
    return false;
    }
else{
    add(new_creature_added);
    level_sum_ += new_creature_added.getLevel();
    if(new_creature_added.isTame()){
        tame_count_++;
        }
    return true;
    }
}
/** 
* @param   :   A  reference to a Creature leaving the Cavern
* @return  :  returns true if a creature was successfully removed from the Cavern (i.e. items_), false otherwise
* @post    :    removes the creature from the Cavern and updates the level sum.
* If the Creature is tame it also updates the tame count.
**/
bool Cavern::exitCavern(const Creature &new_creature_leaving){
    if(remove(new_creature_leaving)){
        level_sum_ -= new_creature_leaving.getLevel();
        if(new_creature_leaving.isTame()){
            tame_count_--;
        }
        return true;
    }
    return false;
}
/** 
* @return   :  The integer level count of all the creatures currently in the Cavern
**/
int Cavern::getLevelSum()const{
    return level_sum_;
}
/** 
* @return   :  The integer level count of all the creatures currently in the Cavern
**/
int Cavern::calculateAvgLevel()const{
    if(getCurrentSize() == 0){
        return 0;
    }
    return round(static_cast<double>(level_sum_) / getCurrentSize());
}
/**
* @return   :  The integer count of tame Creatures in the Cavern
**/
int Cavern::getTameCount()const{
    return tame_count_;
}
/**
* @return   :  The percentage (double) of all the tame creatures in the Cavern
* @post     :   Computes the percentage of tame creatures in the Cavern rounded up to 2 decimal places.
**/
double Cavern::calculateTamePercentage() const {
    if (getCurrentSize() == 0) {
        return 0; 
    }
    double percentage = static_cast<double>(tame_count_) / static_cast<double>(getCurrentSize()) * 100;
    return std::ceil(percentage * 100) / 100; 
}
/**
* @param  :   A reference to a string representing a creature Category with value in ["UNKNOWN", "UNDEAD", "MYSTICAL", "ALIEN"]
* @return  :  An integer tally of the number of creatures in the Cavern of the given category. 
*If the argument string does not match one of the expected category values, the tally is zero. 
*NOTE: no pre-processing of the input string necessary, only uppercase input will match.
**/
int Cavern::tallyCategory(const std::string &Category)const{
int tally = 0;
for(int i =0; i < getCurrentSize(); i ++){
    if(items_[i].getCategory() == Category){
        tally ++;
    }
}
return tally;
}
/**
* @param  :   An integer representing the level threshold of the creatures to be removed from the Cavern, with default value 0
* @post   :   Removes all creatures from the Cavern whose level is less than the given level. If no level is given, removes all creatures from the Cavern. Ignore negative input.
* @return :   The number of creatures removed from the Cavern
*/
int Cavern::releaseCreaturesBelowLevel(int threshold) {
    int numremoved = 0;
    if(threshold == 0){
        numremoved = getCurrentSize();
        clear();
        level_sum_ =0;
        tame_count_ =0;
    }
    if(threshold > 0){
        for(int i = 0; i < getCurrentSize(); i++){
            if(items_[i].getLevel() < threshold){
                exitCavern(items_[i]);
                numremoved ++;
                i--;
            }
        }

    }
    return numremoved;
}
/**
* @param  : A reference to a string representing a creature Category with a value in ["UNKNOWN", "UNDEAD", "MYSTICAL", "ALIEN"], or default value "ALL" if no category is given
* @post   : Removes all creatures from the Cavern whose category matches the given category. If no category is given, removes all creatures from the Cavern.
* @return : The number of creatures removed from the Cavern
*NOTE: no pre-processing of the input string necessary, only uppercase input will match. If the input string does not match one of the expected category values, do not remove any creatures.
*/
int Cavern::releaseCreaturesOfCategory(const std::string &value){
    int numremoved = 0;
    if(value == "ALL"){
            for(int i = 0; i < getCurrentSize(); i++){
        exitCavern(items_[i]);
        numremoved++;
            }
    }
    else{
        for(int i =0; i < getCurrentSize(); i++){
            if(items_[i].getCategory() == value){
                exitCavern(items_[i]);
                numremoved++;
            }
        }
    }
    return numremoved;
    }
/**
* @post    : Outputs a report of the creatures currently in the Cavern in the form:
    "UNKNOWN: [x]\nUNDEAD: [x]\nMYSTICAL: [x]\nALIEN: [x]\n\nAVERAGE LEVEL: [x]\nTAME:[x]%\n"
    Note that the average level should be rounded to the NEAREST integer, and the percentage of tame creatures in the Cavern should be rounded to 2 decimal places.

Example output: 
UNKNOWN: 1
UNDEAD: 3
MYSTICAL: 2
ALIEN: 1

AVERAGE LEVEL: 5
TAME: 85.72%
*/
void Cavern::cavernReport()const {
std::cout << "UNKNOWN: " << tallyCategory("UNKNOWN") << std::endl;
std::cout << "UNDEAD: " << tallyCategory("UNDEAD") << std::endl;
std::cout << "MYSTICAL: " << tallyCategory("MYSTICAL") << std::endl;
std::cout << "ALIEN: " << tallyCategory("ALIEN") << std::endl << std::endl;
std::cout << "AVERAGE LEVEL: " << calculateAvgLevel() << std::endl;
std::cout << "TAME: " << calculateTamePercentage() << "%" << std::endl;
}

