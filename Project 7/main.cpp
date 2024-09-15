#include "SkillTree.hpp"

int main(){
    auto test = SkillTree("debug.csv");
    test.preorderDisplay();
    std::cout << "\n\n\n\n";
    test.balance();
    test.preorderDisplay();
}