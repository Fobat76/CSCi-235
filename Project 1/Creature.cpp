/**
 * @file Creature.hpp
 * @author Devin Chen 
 * @brief Creature Class 
 * @date 1/20/2024
*/


#include "Creature.hpp"

/**
 * Defaut constructor.
 * Default-initializes all private members. 
 * Default creature name: "NAMELESS". 
 * Booleans are default-initialized to False. 
 * Default enum value: UNKNOWN 
 * Default Hitpoints and Level: 1.
*/
Creature::Creature():name_{"NAMELESS"},category_{UNKNOWN}, hitpoints_{1},level_{1},is_tame_{false}{};

/**
 * Parameterized constructor.
 * @param      : A reference to the name of the creature (a string). Set the creature's name to NAMELESS if the provided string contains non-alphabetic characters.
 * @param      : The category of the creature (a Category enum) with default value UNKNOWN
 * @param      : The creature's hitpoints (an integer) , with default value 1 if not provided, or if the value provided is 0 or negative
 * @param      : The creature's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
 * @param      : A flag indicating whether the creature is tame, with default value False
 * @post       : The private members are set to the values of the corresponding parameters. The name is converted to UPPERCASE if it consists of alphabetical characters only, otherwise it is set to NAMELESS.
*/
Creature::Creature(const std::string &new_name, Category new_category, int new_hitpoint, int new_level, bool new_tame){
    if(!setName(new_name)) {
        name_ = "NAMELESS"; 
    }
    setCategory(new_category);
    if(!setLevel(new_level)){
        level_ = 1;
    }
    if(!setHitpoints(new_hitpoint)){
        hitpoints_ = 1;
    }
    setTame(new_tame);
}


/**
 * @param : the name of the Creature, a reference to string
 * @post  : sets the Creature's name to the value of the parameter in UPPERCASE. 
 * (convert any lowercase character to uppercase)
 * Only alphabetical characters are allowed. 
 * : If the input contains non-alphabetic characters, do nothing.
 * @return : true if the name was set, false otherwise
*/
bool Creature::setName(const std::string &new_name){        
    for(int i = 0; i < new_name.length(); i++){
        if (!isalpha(new_name[i])){
            return false;
        }
    }; 
    std::string tempname;       
    for (int i = 0; i < new_name.length(); i++){
        tempname += toupper(new_name[i]);
    }
    name_ = tempname;
    return true;
};

/**
 * @return : the name of the Creature
*/
std::string Creature::getName() const{
    return name_; 
}

/**
 * @param  : a reference to Category, the category of the Creature (an enum)
 * @post   : sets the Creature's category to the value of the parameter
 * : If the given category was invalid, set category_ to UNKNOWN.
*/
void Creature::setCategory(const Category &new_category){
    if(new_category >= UNKNOWN && new_category <= ALIEN) {
        category_ = new_category;
    }
    else{
        category_ = UNKNOWN;
    }
}
/**
 * @return : the category of the Creature (in string form)
*/
std::string Creature::getCategory() const{
    switch(category_){
        case UNKNOWN:
            return "UNKNOWN";
        case UNDEAD:
            return "UNDEAD";
        case MYSTICAL:
            return "MYSTICAL";
        case ALIEN:
            return "ALIEN";
    }
}

/**
 * @param  : a reference to integer that represents the creature's hitpoints
 * @pre    : hitpoints >= 0 : Characters cannot have negative hitpoints 
 * (do nothing for invalid input)
 * @post   : sets the hitpoints private member to the value of the parameter
 * @return : true if the hitpoints were set, false otherwise
*/
bool Creature::setHitpoints(const int &new_hitpoint){
    if (new_hitpoint <= 0){
        return false;
    }
    hitpoints_ = new_hitpoint;
    return true;
}

/**
 * @return : the value stored in hitpoints_
*/
int Creature::getHitpoints() const{
    return hitpoints_;
}

/**
 * @param  : a reference to integer level
 * @pre    : level >= 0 : Characters cannot have a negative level
 * @post   : sets the level private member to the value of the parameter 
 * (do nothing for invalid input)
 * @return : true if the level was set, false otherwise
*/
bool Creature::setLevel(const int &new_level){
    if (new_level <= 0){
        return false;
    }
    level_ = new_level;
    return true;
}

/**
 * @return : the value stored in level_
*/
int Creature::getLevel() const{
    return level_;
}

/**
 * @param  : a reference to boolean value
 * @post   : sets the tame flag to the value of the parameter
*/
void Creature::setTame(const bool &new_tame){
    is_tame_ = new_tame;
}

/**
 * @return true if the creature is tame, false otherwise
 * Note: this is an accessor function and must follow the same convention as all accessor functions even if it is not called getTame
*/
bool Creature::isTame() const{
    return is_tame_;
}

/**
 * @post     : displays Creature data in the form:
 * "[NAME]\n
 * Category: [CATEGORY]\n
 * Level: [LEVEL]\n
 * Hitpoints: [Hitpoints]\n
 * Tame: [TRUE/FALSE]"   
*/
void Creature::display() const{
    std::cout << name_ << "\n";
    std::cout << "Category: " << getCategory() << "\n";
    std::cout << "Level: " << level_ << "\n";
    std::cout << "Hitpoints: " << hitpoints_ << "\n";
    if(is_tame_){
        std::cout << "Tame: TRUE";
    }
        else {
        std::cout << "Tame: FALSE";
    }
}
