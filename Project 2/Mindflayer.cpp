/**
 * @file Mindflayer.cpp
 * @author Devin Chen 
 * @brief Mindflayer Class 
 * @date 2/19/2024
*/
#include "Mindflayer.hpp"

/**
  Default constructor.
  Default-initializes all private members. 
  Default Category: ALIEN
  Default summoning: False
*/
Mindflayer::Mindflayer():Creature(){
    setCategory(ALIEN);
    setSummoning(false);
};

/**
  Parameterized constructor.
  @param      : A reference to the name of the Mindflayer (a string)
  @param      : The category of the Mindflayer (a Category enum) with default value ALIEN
  @param      : The Mindflayer's hitpoints (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : The Mindflayer's level (an integer), with default value 1 if not provided, or if the value provided is 0 or negative
  @param      : A flag indicating whether the Mindflayer is tame, with default value False
  @param      : The projectiles (a vector of Projectile structs), with default value an empty vector if not provided
  @param      : A flag indicating whether the Mindflayer can summon, with default value False
  @param      : The affinities (a vector of Variant enums), with default value an empty vector if not provided
  @post       : The private members are set to the values of the corresponding parameters.
  Hint: Notice the default arguments in the parameterized constructor.
*/
Mindflayer::Mindflayer(const std::string &new_name, Category new_type, int new_hitpoint,int new_level, bool new_tame, 
std::vector<Projectile> new_projectile, bool new_summon, std::vector<Variant> new_variant)
:Creature(new_name,new_type, new_hitpoint, new_level, new_tame) {
    setProjectiles(new_projectile);
    setSummoning(new_summon);
    setAffinities(new_variant);
};

/**
  Getter for the projectiles.
  @return     : The projectiles (a vector of Projectile structs)
*/
std::vector<Mindflayer::Projectile> Mindflayer::getProjectiles()const{
    return projectiles_;
}

/**
  Setter for the projectiles.
  @param      : A reference to the projectiles (a vector of Projectile structs)
  @post       : The projectiles are set to the value of the parameter. There should not be any duplicate projectiles in Mindflayer's projectiles vector.
        : For example, if the vector in the given parameter contains the following Projectiles: {{PSIONIC, 2}, {TELEPATHIC, 1}, {PSIONIC, 1}, {ILLUSIONARY, 3}}, 
        : the projectiles vector should be set to contain the following Projectiles: {{PSIONIC, 3}, {TELEPATHIC, 1}, {ILLUSIONARY, 3}}.
        : If the quantity of a projectile is 0 or negative, it should not be added to the projectiles vector. 
        : Note the order of the projectiles in the vector.
*/
    void Mindflayer::setProjectiles(const std::vector<Projectile> &new_projectile){  
projectiles_.clear(); // Clear the vector to prevent duplicates
    for (int i = 0; i < new_projectile.size(); i++) {
        const auto& projectile = new_projectile[i];
        if (projectile.quantity_ > 0) {
            bool found = false;
            for (int j = 0; j < projectiles_.size(); j++) {
                auto& p = projectiles_[j];
                if (p.type_ == projectile.type_) {
                    p.quantity_ += projectile.quantity_;
                    found = true;
                    break;
                }
            }
            if (!found) {
                projectiles_.push_back(projectile);
            }
        }
    }
}

/**
  Getter for the summoning.
  @return     : The summoning (a boolean)
*/
    bool Mindflayer::getSummoning() const{
        return summoning_;
    }

/**
  Setter for the summoning.
  @param      : A reference to the summoning (a boolean)
  @post       : The summoning is set to the value of the parameter.
*/
    void Mindflayer::setSummoning(const bool &new_summon){
        summoning_ = new_summon;
    }

/**
  Getter for the affinities.
  @return     : The affinities (a vector of Variant enums)
*/
    std::vector<Mindflayer::Variant> Mindflayer::getAffinities()const{
        return affinities_;
    }

/**
  Setter for the affinities.
  @param      : A reference to the affinities (a vector of Variant enums)
  @post       : The affinities are set to the value of the parameter.
        : There should not be any duplicate affinities in Mindflayer's affinities vector. 
        : For example, if the vector in the given parameter contains the following affinities: {PSIONIC, TELEPATHIC, PSIONIC, ILLUSIONARY}, 
        : the affinities vector should be set to contain the following affinities: {PSIONIC, TELEPATHIC, ILLUSIONARY}.
        : Note the order of the affinities in the vector.
*/
void Mindflayer::setAffinities(const std::vector<Variant>& new_variant) {
    for (int i = 0; i < new_variant.size(); i++) {
        Variant temp = new_variant[i];
        bool found = false;
        for (int j = 0; j < affinities_.size(); j++) {
            if (temp == affinities_[j]) {
                found = true;
                break;
            }
        }
        if (!found) {
            affinities_.push_back(temp);
        }
    }
}
/**
  @param       : A reference to the Variant 
  @return      : The string representation of the variant
*/
    std::string Mindflayer::variantToString(const Variant &new_variant){
        switch(new_variant) {
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
    