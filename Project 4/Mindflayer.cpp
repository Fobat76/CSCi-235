/*
CSCI235 Spring 2024
Project 2 - Derived Classes
Georgina Woo
Dec 23 2023
Mindflayer.cpp implements the constructors and private and public functions of the Mindflayer class
*/

#include "Mindflayer.hpp"

Mindflayer::Mindflayer() : affinities_{}, summoning_{false}, projectiles_{}
{
    setCategory(ALIEN);
}

Mindflayer::Mindflayer(const std::string& name, Category category, int hitpoints, int level, bool tame, std::vector<Projectile> projectiles, bool summoning, std::vector<Variant> affinities) : Creature(name, category, hitpoints, level, tame)
{
    setProjectiles(projectiles);
    summoning_ = summoning;
    setAffinities(affinities);
}

std::vector<Mindflayer::Projectile> Mindflayer::getProjectiles() const
{
    return projectiles_;
}

void Mindflayer::setProjectiles(const std::vector<Projectile>& projectiles)
{
    std::vector<Projectile> temp;
    for(int i = 0; i < projectiles.size(); i++)
    {
        bool found = false;
        for(int j = 0; j < temp.size(); j++)
        {
            if(projectiles[i].type_ == temp[j].type_)
            {
                if(projectiles[i].quantity_ > 0)
                {
                    temp[j].quantity_ += projectiles[i].quantity_;
                    found = true;
                }
            }
        }
        if(!found)
        {
            if(projectiles[i].quantity_ > 0)
            {
                temp.push_back(projectiles[i]);
            }
        }
    }
    projectiles_ = temp;
}

void Mindflayer::setSummoning(const bool& summoning)
{
    summoning_ = summoning;
}

bool Mindflayer::getSummoning() const
{
    return summoning_;
}

std::vector<Mindflayer::Variant> Mindflayer::getAffinities() const
{
    return affinities_;
}

void Mindflayer::setAffinities(const std::vector<Variant>& affinities)
{
    std::vector<Variant> temp;
    for(int i = 0; i < affinities.size(); i++)
    {
        bool found = false;
        for(int j = 0; j < temp.size(); j++)
        {
            if(affinities[i] == temp[j])
            {
                found = true;
            }
        }
        if(!found)
        {
            temp.push_back(affinities[i]);
        }
    }
    affinities_ = temp;
}

std::string Mindflayer::variantToString(const Variant& variant) const
{
    switch(variant)
    {
        case PSIONIC:
            return "PSIONIC";
        case TELEPATHIC:
            return "TELEPATHIC";
        case ILLUSIONARY:
            return "ILLUSIONARY";
        default:
            return "NONE";
    }
}

void Mindflayer::display() const{
    std::cout 
    << "MINDFLAYER - " << getName() << "\n"
    << "CATEGORY: " << getCategory() << "\n"
    << "HP: " << getHitpoints() << "\n"
    << "LVL: " << getLevel() << "\n"
    << "TAME: " << (isTame()? "TRUE" : "FALSE") << "\n"
    << "SUMMONING: " << (getSummoning()? "TRUE" : "FALSE") << "\n";
    for(int i =0; i < getProjectiles().size(); i++){
        auto temp = getProjectiles()[i];
        std::cout << variantToString(temp.type_)<< " : " << temp.quantity_ << "\n";
    }

    if(getAffinities().size()){
        std::cout << "AFFINITIES:\n";
        for(int i =0; i < getProjectiles().size(); i++){
            std::cout << variantToString(getAffinities()[i]) << "\n";
        }
    } 
}

bool Mindflayer::eatMycoMorsel(){
    if(getCategory() == "UNDEAD"){
        setTame(true);
        setHitpoints(getHitpoints() +1);
        return false;
    }

    if(getCategory() == "MYSTICAL"){
        if(!getSummoning()){
            if(isTame()){
                if(getHitpoints() == 1){
                    setTame(false);
                    return false;
                }
                if(getHitpoints() > 1){
                    setHitpoints(getHitpoints() -1);
                    return false;
                }
            }
        if(!isTame()&& getHitpoints() == 1){
            return true;
            }
        }
    }

    if(getCategory() == "ALIEN"){
        for(int i =0; i < getAffinities().size(); i++){
            if(variantToString(getAffinities()[i]) == "TELEPATHIC"){
                setHitpoints(getHitpoints() +1);
                return false;
            }
        }
        for(int i =0; i < getProjectiles().size(); i++){
            if((getProjectiles()[i]).type_ == TELEPATHIC){
                if((getProjectiles())[i].quantity_ > 1 ){
                    (getProjectiles()[i]).quantity_ -= 1;
                    return false;
                }
                if((getProjectiles()[i]).quantity_ == 1){
                    projectiles_.erase(projectiles_.begin() + i);
                    return false;
                }
            }
        }
    setHitpoints(getHitpoints() + 2);
    setTame(true);
    return false;
    }
}