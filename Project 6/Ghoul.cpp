/*
CSCI235 Spring 2024
Project 4 - MycoMorsels
Georgina Woo
Dec 24 2023
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


/**
    @post     : displays Ghoul data in the form:
    GHOUL - [NAME]\n
    CATEGORY: [CATEGORY]\n
    HP: [HITPOINTS]\n
    LVL: [LEVEL]\n
    TAME: [TAME]\n
    DECAY: [DECAY]\n
    FACTION: [FACTION]\n
    IT [CAN/CANNOT] TRANSFORM\n"
    
    Example:
    
*/
void Ghoul::display() const
{
    std::cout << "GHOUL - " << getName() << std::endl;
    std::cout << "CATEGORY: " << getCategory() << std::endl;
    std::cout << "HP: " << getHitpoints() << std::endl;
    std::cout << "LVL: " << getLevel() << std::endl;
    std::cout << "TAME: " << (isTame() ? "TRUE" : "FALSE") << std::endl;
    std::cout << "DECAY: " << getDecay() << std::endl;
    std::cout << "FACTION: " << getFaction() << std::endl;
    std::cout << "IT " << (getTransformation() ? "CAN" : "CANNOT") << " TRANSFORM" << std::endl;
}


bool Ghoul::eatMycoMorsel()
{
    if(getCategory() == "UNDEAD")
    {
        setTame(true);
        setHitpoints(getHitpoints() + 1);
        return false;
    }
    else if(getFaction() == "FLESHGORGER")
    {
        if(isTame())
        {
            setTame(false);
            return false;
        }
        else
        {
            return true;
        }
    }
    else if(getFaction() == "SHADOWSTALKER")
    {
        if(isTame())
        {
            if(getHitpoints() == 1)
            {
                setTame(false);
            }
            else
            {
                setHitpoints(getHitpoints() - 1);
            }
            return false;
        }
        else
        {
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
* Here are the attacks for the Ghoul:
* 
* 1: Attack name: BITE
*   if ALIEN: 4 PHYSICAL
*   if MYSTICAL: 
*      if FLESHGORGER: 2 PHYSICAL
*      if SHADOWSTALKER: 2 PHYSICAL, 1 VOID
*      if PLAGUEWEAVER: 2 PHYSICAL, 1 POISON
*      if NONE: 2 PHYSICAL
*  if UNDEAD: 2 PHYSICAL, 1 POISON
*  if UNKNOWN: 2 PHYSICAL
* 
* 2: 
*  if FLESHGORGER/NONE: 
*      Attack name: CLAW
*      2 PHYSICAL
*  if SHADOWSTALKER:
*     Attack name: SLASH
*     2 PHYSICAL, 1 VOID
* if PLAGUEWEAVER:
*    Attack name: INFECT
*    2 PHYSICAL, 1 POISON
* 
* 3:
*  if FLESHGORGER/NONE:
*     Attack name: FLY SWARM
*     3 PHYSICAL
* if SHADOWSTALKER:
*     Attack name: SHROUD OF DARKNESS
*     2 PHYSICAL, 1 VOID
* if PLAGUEWEAVER:
*     Attack name: PLAGUE CLOUD
*     2 PHYSICAL, 1 POISON
*  
*/
void Ghoul::addAttack(const int &attack){
    Attack Temp;
    if(attack == 1){
        Temp.name_ = "BITE";
        if(getCategory() == "ALIEN"){// push 4phycail if alein 
            Temp.damage_.push_back(4);
            Temp.type_.push_back("PHYSICAL");
        }
        else if(getCategory() == "MYSTICAL"){
            Temp.damage_.push_back(2);
            Temp.type_.push_back("PHYSICAL");// default 2physcial 
            if(getFaction() == "SHADOWSTALKER"){
                Temp.damage_.push_back(1);
                Temp.type_.push_back("VOID");// check faction and push attack based on the faction 
            }
            else if(getFaction() == "PLAGUEWEAVER"){
                Temp.damage_.push_back(1);
                Temp.type_.push_back("POISON");
            }        
        }
        else if(getCategory() == "UNDEAD"){
            Temp.damage_.push_back(2);
            Temp.type_.push_back("PHYSICAL");// default 
            Temp.damage_.push_back(1);
            Temp.type_.push_back("POISON");
        }
        else if (getCategory() == "UNKNOWN"){
            Temp.damage_.push_back(2);//default
            Temp.type_.push_back("PHYSICAL");
        }
    }
    if(attack == 2){
        Temp.name_ = "CLAW";
        Temp.damage_.push_back(2);//default 
        Temp.type_.push_back("PHYSICAL");
        if(getFaction() == "SHADOWSTALKER"){
            Temp.name_ = "SLASH";
            Temp.damage_.push_back(1);// check faaction and rename temp.name for certain factions also adding additonal attack 
            Temp.type_.push_back("VOID");
        }
        else if(getFaction() == "PLAGUEWEAVER"){
            Temp.name_ = "INFECT";
            Temp.damage_.push_back(1);
            Temp.type_.push_back("POISON");
        }
    }
    if(attack == 3){// no default
        if(getFaction() == "NONE"){
            Temp.name_ = "FLY SWARM";// if NONE FlY swarm 3 physcail
            Temp.damage_.push_back(3);
            Temp.type_.push_back("PHYSICAL");
        }

        if(getFaction() == "FLESHGORGER"){
            Temp.name_ = "FLY SWARM";// FLYSwarm 3 physcail if fleshgorger faction
            Temp.damage_.push_back(3);
            Temp.type_.push_back("PHYSICAL");
        }

        if(getFaction() == "SHADOWSTALKER"){
            Temp.name_ = "SHROUD OF DARKNESS";// SHROUDED OF DARKNESS 2 PHYSCIAL AND 1 VOID if SHADOWSTALKER FACTION
            Temp.damage_.push_back(2);
            Temp.type_.push_back("PHYSICAL");
            Temp.damage_.push_back(1);
            Temp.type_.push_back("VOID");
        }
        else if(getFaction() == "PLAGUEWEAVER"){
            Temp.name_ = "PLAGUE CLOUD";
            Temp.damage_.push_back(2);// PLAUGUE CLOUD 2 PHYSciAL and 1 POSIN if PLAUGUEWEAVER FACTION
            Temp.type_.push_back("PHYSICAL");
            Temp.damage_.push_back(1);
            Temp.type_.push_back("POISON");
        }
    }
    Creature::addAttack(Temp); // push into the creatures attackqueue 
}
/**
  @post     : displays the attacks of the Ghoul in the form:
  [GHOUL] Choose an attack (1-3):\n1: BITE\t\t2: CLAW\t\t3: CLOUD OF DOOM\n
*/
void Ghoul::displayAttacks(){
std::cout << "[GHOUL] Choose an attack (1-3):\n1: BITE\t\t2: CLAW\t\t3: CLOUD OF DOOM\n";   
}