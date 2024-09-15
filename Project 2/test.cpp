#include "Creature.hpp"
#include "Dragon.hpp"
#include "Ghoul.hpp"
#include "Mindflayer.hpp"
void newDisplay(const Creature &crea){
    std::cout << "NAME: "<< crea.getName() << "\n";
    std::cout << "CATEGORY: " << crea.getCategory() << "\n";   
    std::cout << "HP: " << crea.getHitpoints() << "\n";
    std::cout << "LVL: " << crea.getLevel()<< "\n";
    std::cout << "TAME: " << (crea.isTame()? "TRUE" : "FALSE") << "\n";
    std::cout << std::endl;
    }
    

void dragonDisplay(const Dragon &Drag){
    newDisplay(Drag);
    std::cout<< "ELEMENT: " << Drag.getElement() << "\n";
    std::cout<< "HEADS: " << Drag.getNumberOfHeads() << "\n";
    std::cout<< "FLIGHT: " << (Drag.getFlight() ? "TRUE" : "FALSE") << "\n";
    std::cout << std::endl;
}

void ghoulDisplay(const Ghoul &g1){
    newDisplay(g1);    
    std::cout<< "DECAY: " << g1.getDecay()<< "\n";
    std::cout<< "FACTION: " << g1.getFaction() << "\n";
    std::cout<< "TRANSFORM: " << (g1.getTransformation() ? "TRUE" : "FALSE") << "\n";
    std::cout << std::endl;
}
void MindflayerDisplay(Mindflayer &m2){
    newDisplay(m2);
        for(int i =0; i < m2.getProjectiles().size(); i++){
       auto temp = m2.getProjectiles()[i];
        std::cout << m2.variantToString(temp.type_)<< " : " << temp.quantity_ << "\n";
    }
        std::cout << "SUMMONING: " << (m2.getSummoning() ? "TRUE" : "FALSE")<<"\n";
    if(m2.getAffinities().size()){
        std::cout << "AFFINITIES: \n";
       
    } 
    for (int i = 0; i < m2.getAffinities().size(); i ++){
        auto temp = m2.getAffinities();
        std::cout << m2.variantToString(temp[i])<< "\n";
    }
std::cout << std::endl;
}

int main(){
    Dragon Drag;
    dragonDisplay(Drag);


    Dragon d2("Smog");
    dragonDisplay(d2);

    Dragon d3("Burny", Creature::Category::UNDEAD, 100, 10, true, Dragon::Element::FIRE, 1, true);
    dragonDisplay(d3);

    d3.setElement(Dragon::Element::WATER);
    d3.setNumberOfHeads(2);
    d3.setNumberOfHeads(0);
    d3.setFlight(false);
    dragonDisplay(d3);

    Ghoul g1;
    ghoulDisplay(g1);


    Ghoul g2("Homph");
    ghoulDisplay(g2);

    Ghoul g3("CHOMPER", Creature::Category::ALIEN, 100, 10, true, 3, Ghoul::Faction::FLESHGORGER, true);
    ghoulDisplay(g3);

    g3.setDecay(2);
    g3.setDecay(-20);
    g3.setFaction(Ghoul::Faction::SHADOWSTALKER);
    g3.setTransformation(false);
    ghoulDisplay(g3);


    Mindflayer m1;
    MindflayerDisplay(m1);

std::vector<Mindflayer::Projectile> proj = {{Mindflayer::Variant::PSIONIC, 2}, {Mindflayer::Variant::TELEPATHIC, 1}, {Mindflayer::Variant::PSIONIC, 1}, {Mindflayer::Variant::ILLUSIONARY, 3}}; 
    std::vector<Mindflayer::Variant> att = {Mindflayer::Variant::PSIONIC, Mindflayer::Variant::TELEPATHIC, Mindflayer::Variant::PSIONIC, Mindflayer::Variant::ILLUSIONARY}; 
    Mindflayer m2 ("BIGBRAIN", Creature::MYSTICAL, 100, 10, true, proj,
    true,att);
    MindflayerDisplay(m2);

}
