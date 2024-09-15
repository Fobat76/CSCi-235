/*
CSCI235 Spring 2024
Project 2 - Derived Classes
Georgina Woo
Dec 23 2023
Ghoul.cpp implements the constructors and private and public functions of the Ghoul class
*/

#include "Ghoul.hpp"

Ghoul::Ghoul() :  decay_{0}, faction_{NONE}, transformation_{false}
{
    setCategory(UNDEAD); 
}

Ghoul::Ghoul(const std::string& name, Category category, int hitpoints, int level, bool tame, int decay, Faction faction, bool transformation) : Creature(name, category, hitpoints, level, tame)
{
    if(!setDecay(decay))
    {
        decay_ = 0;
    }
    faction_ = faction;
    transformation_ = transformation;
}

int Ghoul::getDecay() const
{
    return decay_;
}

bool Ghoul::setDecay(const int& decay)
{
    if(decay >= 0)
    {
        decay_ = decay;
        return true;
    }
    else
    {
        return false;
    }
}

std::string Ghoul::getFaction() const
{
    switch(faction_)
    {
        case FLESHGORGER:
            return "FLESHGORGER";
        case SHADOWSTALKER:
            return "SHADOWSTALKER";
        case PLAGUEWEAVER:
            return "PLAGUEWEAVER";
        default:
            return "NONE";
    }
}

void Ghoul::setFaction(const Faction& faction)
{
    faction_ = faction;
}

bool Ghoul::getTransformation() const
{
    return transformation_;
}

void Ghoul::setTransformation(const bool& transformation)
{
    transformation_ = transformation;
}

void Ghoul::display() const{
    std::cout 
    << "GHOUL - " << getName() << "\n"
    << "CATEGORY: " << getCategory() << "\n"
    << "HP: " << getHitpoints() << "\n"
    << "LVL: " << getLevel() << "\n"
    << "TAME: " << (isTame()? "TRUE" : "FALSE") << "\n"
    << "DECAY: " << getDecay() << "\n"
    << "FACTION: " << getFaction() << "\n"
    << "IT " << (getTransformation() ? "CAN" : "CANNOT") << " TRANSFORM\n";
}

bool Ghoul::eatMycoMorsel(){
    if(getFaction() == "FLESHGORGER"){
        if(isTame()){
            setTame(false);
        }
        if(isTame() == false){
            return true;
        }
    }
    if(getFaction() == "SHADOWSTALKER"){
        if(isTame() == true){
            if(getHitpoints() > 1){
                setHitpoints(getHitpoints() -1);
            }
            if(getHitpoints() == 1){
                setTame(false);
            }
        }

    }
    if(getCategory() == "UNDEAD" && !(getFaction() == "FLESHGORGER") && !(getFaction() == "SHADOWSTALKER")){
        setTame(true);
        setHitpoints(getHitpoints() + 1);
    }
    return false;
}
    
    
