/*
CSCI235 Spring 2024
Project 4 - MycoMorsels
Georgina Woo
Dec 24 2023
Dragon.cpp implements the constructors and private and public functions of the Dragon class
*/

#include "Dragon.hpp"

Dragon::Dragon() : element_{NONE}, number_of_heads_{1}, flight_{false}
{
    setCategory(MYSTICAL); 
    
}


Dragon::Dragon(const std::string& name, Category category, int hitpoints, int level, bool tame, Element element, int number_of_heads, bool flight) : Creature(name, category, hitpoints, level, tame)
{
    element_ = element;
    if(!setNumberOfHeads(number_of_heads))
    {
        number_of_heads_ = 1;
    }
    flight_ = flight;
}

std::string Dragon::getElement() const
{
    switch(element_)
    {
        case FIRE:
            return "FIRE";
        case WATER:
            return "WATER";
        case EARTH:
            return "EARTH";
        case AIR:
            return "AIR";
        default:
            return "NONE";
    }
}

void Dragon::setElement(const Element& element)
{
    element_ = element;
}

int Dragon::getNumberOfHeads() const
{
    return number_of_heads_;
}

bool Dragon::setNumberOfHeads(const int& number_of_heads)
{
    if(number_of_heads > 0)
    {
        number_of_heads_ = number_of_heads;
        return true;
    }
    else
    {
        return false;
    }
}

bool Dragon::getFlight() const
{
    return flight_;
}

void Dragon::setFlight(const bool& flight)
{
    flight_ = flight;
}


void Dragon::display() const
{
    std::cout << "DRAGON - " << getName() << std::endl;
    std::cout << "CATEGORY: " << getCategory() << std::endl;
    std::cout << "HP: " << getHitpoints() << std::endl;
    std::cout << "LVL: " << getLevel() << std::endl;
    std::cout << "TAME: " << (isTame() ? "TRUE" : "FALSE") << std::endl;
    std::cout << "ELEMENT: " << getElement() << std::endl;
    std::cout << "HEADS: " << getNumberOfHeads() << std::endl;
    std::cout << "IT " << (getFlight() ? "CAN" : "CANNOT") << " FLY" << std::endl;
}



bool Dragon::eatMycoMorsel()
{
    if(getCategory() == "UNDEAD")
    {
        setTame(true);
        setHitpoints(getHitpoints() + 1);
        return false;
    }
    else if(getCategory() == "ALIEN")
    {
        setHitpoints(getHitpoints() + 1);
        return false;
    }
    else if(getCategory() == "MYSTICAL")
    {
        if(getElement() == "FIRE" || getElement() == "EARTH")
        {
            setHitpoints(getHitpoints() + 1);
            return false;
        }
        else if(getHitpoints() == 1)
        {
            return true;
        }
        else
        {
            setHitpoints(getHitpoints() - 1);
            setTame(false);
            return false;
        }
    }
    else
    {
        return false;
    }
}

/**
  * @param: A const reference to int corresponding to the attack to be added to the attack queue.
  * @post: Adds an attack to the attack queue based on the int parameter.
  * Here are the attacks for the Dragon:
  
* 1: Attack name: BITE
*      if ALIEN: 4 PHYSICAL
*      if MYSTICAL: 2 PHYSICAL, and additional damage of 1 [FIRE/WATER/EARTH/AIR] if the Dragon has an elemental affinity of FIRE, WATER, EARTH, or AIR)
*      if UNDEAD: 2 PHYSICAL, 1 POISON
*      if UNKNOWN: 2 PHYSICAL

* 2: Attack name: STOMP
*      if ALIEN: 2 PHYSICAL
*      if MYSTICAL: 1 PHYSICAL, and additional damage of 1 [FIRE/WATER/EARTH/AIR] if the Dragon has an elemental affinity of FIRE, WATER, EARTH, or AIR)
*      if UNDEAD: 1 PHYSICAL, 1 POISON
*      if UNKNOWN: 1 PHYSICAL

* 3: Attack name: [ELEMENTAL BREATH/BAD BREATH], where the name is ELEMENTAL BREATH if the Dragon has an elemental affinity, otherwise it is BAD BREATH
*      if ALIEN: 6 [POISON/FIRE/WATER/EARTH/AIR], where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON
*      if MYSTICAL: 3 [POISON/FIRE/WATER/EARTH/AIR], where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON
*      if UNDEAD: 3 [POISON/FIRE/WATER/EARTH/AIR], 1 POISON. The damage types and amount are added to the vector as two separate entries, even if both entries are POISON type.
*      if UNKNOWN: 3 [POISON/FIRE/WATER/EARTH/AIR] where the damage type is the Dragon's elemental affinity if it has one, otherwise it is POISON  
*/
void Dragon::addAttack(const int &attack){
    Attack Temp;
    if(attack == 1){// if attack is 1 
        Temp.name_ = "BITE";// name default bite 
        if(getCategory() == "ALIEN"){//If Category is ALIEN then attack = 4 PHYSICAL
            Temp.damage_.push_back(4);
            Temp.type_.push_back("PHYSICAL");
        }

        if(getCategory() == "MYSTICAL"){// If Category is MYSTICAL base Attack = 2 PHYSICAL
            Temp.damage_.push_back(2);
            Temp.type_.push_back("PHYSICAL");
            if(element_ != NONE){//If Element is Not NONE add 1 and the element name 
                Temp.damage_.push_back(1);
                Temp.type_.push_back(getElement());
            }
        }
        if(getCategory() == "UNDEAD"){ // undead 2Physical and 1 poison
            Temp.damage_.push_back(2);
            Temp.type_.push_back("PHYSICAL");
            Temp.damage_.push_back(1);
            Temp.type_.push_back("POISON");
        }
        if(getCategory() == "UNKNOWN"){// if unknown 2 physcail 
            Temp.damage_.push_back(2);
            Temp.type_.push_back("PHYSICAL");
        }
    }
    if(attack == 2){// runs if attack == 2 
        Temp.name_ = "STOMP";// default name STOMP
        if(getCategory() == "ALIEN"){// If aleiane default 2 PHYSICL
            Temp.damage_.push_back(2);
            Temp.type_.push_back("PHYSICAL");
        }
        if(getCategory() == "MYSTICAL"){//if mystical default 1 physcial 
            Temp.damage_.push_back(1);
            Temp.type_.push_back("PHYSICAL");

            if(element_ != NONE){//If Element is Not NONE add 1 and the element name
                Temp.damage_.push_back(1);
                Temp.type_.push_back(getElement());
            }
        }
        if(getCategory() == "UNDEAD"){ // if undead deafult 1physcail and 1 posion
            Temp.damage_.push_back(1);
            Temp.type_.push_back("PHYSICAL");
            Temp.damage_.push_back(1);
            Temp.type_.push_back("POISON");
        }
        if(getCategory() == "UNKNOWN"){ // if unknown 1 physcial
            Temp.damage_.push_back(1);
            Temp.type_.push_back("PHYSICAL");
        }
    }
    if(attack == 3){// run if attack == 3 
        if(element_ == NONE){ // check the element of the creature. If NONE then the attack is named Bad breath 
            Temp.name_ = "BAD BREATH";
        }
        else{
            Temp.name_ = "ELEMENTAL BREATH";// it not true then we know it has a elmenet so it is now ELEMENTAL breath 
        }
        if(getCategory() == "ALIEN"){// If aleian defualt attack 6 type yet to be decalred
            Temp.damage_.push_back(6);
            if(getElement() == "NONE"){// check if there is a element if true then it is the element name else poison. WOuld be easier just checking the name of Temp.name
                Temp.type_.push_back("POISON");
            }
            else{
                Temp.type_.push_back(getElement());
            }
        }
        if(getCategory() == "MYSTICAL"){// if mystical defualt 3 type undecalred
            Temp.damage_.push_back(3);
            if(getElement() == "NONE"){// check if there is a element if true then it is the element name else poison. 
                Temp.type_.push_back("POISON");
            }
            else{
            Temp.type_.push_back(getElement());
            }
        }
        if(getCategory() == "UNDEAD"){//default 3 type undecalred same as previous 
            Temp.damage_.push_back(3);
            if(getElement() == "NONE"){
                Temp.type_.push_back("POISON");
            }
            else
            {
                Temp.type_.push_back(getElement());
            }
            Temp.damage_.push_back(1); // addiational attack 
            Temp.type_.push_back("POISON");
        }
        if(getCategory() == "UNKNOWN"){
            Temp.damage_.push_back(3);
            if(getElement() == "NONE"){
                Temp.type_.push_back("POISON");
            }    
            else
            {
                Temp.type_.push_back(getElement());
            }
        }
    }
    Creature::addAttack(Temp); // add these attack to the queue 
}

/**
  * @post:  displays the attacks of the Dragon in the form:
  *        [DRAGON] Choose an attack (1-3):\n1: BITE\t\t2: STOMP\t\t3: ELEMENTAL BREATH\n
  */
void Dragon::displayAttacks(){
    std::cout << "[DRAGON] Choose an attack (1-3):\n1: BITE\t\t2: STOMP\t\t3: ELEMENTAL BREATH\n";
}