/*
CSCI235 Spring 2024
Project 2 - Derived Classes
Georgina Woo
Dec 23 2023
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

void Dragon::display()const{
    std::cout 
    << "DRAGON - " << getName() << "\n"
    << "CATEGORY: " << getCategory() << "\n"
    << "HP: " << getHitpoints() << "\n"
    << "LVL: " << getLevel() << "\n"
    << "TAME: " << (isTame()? "TRUE" : "FALSE") << "\n"
    << "ELEMENT: " << getElement() << "\n"
    << "HEADS: " << getNumberOfHeads() << "\n"
    << "IT " << (getFlight() ? "CAN" : "CANNOT") << " FLY\n";
}

bool Dragon::eatMycoMorsel(){
    if(getCategory() == "UNDEAD"){
        setTame(true);
        setHitpoints(getHitpoints() +1);
    }
    if(getCategory() == "ALIEN"){
        setHitpoints(getHitpoints() +1);
    }
    if(getCategory() == "MYSTICAL"){
        if(getElement() == "FIRE"|| "EARTH"){
            setHitpoints(getHitpoints() +1);
        }
        else{
        if(getHitpoints() == 1 ){
            return true;
        }
        else{
            setHitpoints(getHitpoints() - 1);
            setTame(false);
        }
        }
    }
    return false;
}