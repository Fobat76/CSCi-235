#include "Pantry.hpp"
#pragma once

/*
* Default Constructor
* @post: Creates a new Ingredient object with default values. String defaults to empty string. 
* Default quantity is 0, default price is 1.
*/
Ingredient::Ingredient():name_{},description_{}, quantity_{0}, price_{1}{}

/**
     Parameterized Constructor
    @param: A string representing a ingredient name
    @param: A string representing ingredient description
    @param: An int representing the ingredient's quantity
    @param: An int representing the ingredient's price
    @param: A vector holding Ingredient pointers representing the ingredient's recipe
    @post: Creates a new Ingredient object with the given parameters
*/
Ingredient::Ingredient(const std::string &NewName_, const std::string  &NewDescription_, const int  &NewQuantity_, const int &NewPrice, const std::vector <Ingredient*> &NewRecipes_)
:name_{NewName_},description_{NewDescription_}, quantity_{NewQuantity_}, price_{NewPrice}, recipe_{NewRecipes_}{}

/**
    Default Constructor
*/
Pantry::Pantry(){} // Default Constructor

/**
    @param: the name of an input file
    @pre: Formatting of the csv file is as follows:
        Name: A string
        Description: A string
        Quantity: A non negative integer
        Price: A non negative integer
        Recipe: A list of Ingredient titles of the form [NAME1] [NAME2];
        For example, to make this ingredient, you need (Ingredient 1 AND Ingredient 2)
        The value may be NONE.
    Notes:
        - The first line of the input file is a header and should be ignored.
        - The recipe are separated by a semicolon and may be NONE.
        - The recipe may be in any order.
        - If any of the recipe are not in the list, they should be created as new ingredients with the following information:
            - Title: The name of the ingredient
            - Description: "UNKNOWN"
            - Quantity: 0
            - Price: 0
            - Recipe: An empty vector
        - However, if you eventually encounter a ingredient that matches one of the "UNKNOWN" ingredients while parsing the file, you should update all the ingredient details.
        
        For example, given a row in the file:
        Inferno_Espresso,An energizing elixir brewed with mystical flames providing resistance to caffeine crashes for a limited time.,1,50,Fiery_Bean Ember_Spice

        The order of the ingredients in the list:
        Fiery_Bean, Ember_Spice, Inferno_Espresso
        Hint: update as needed using addIngredient()
        
    @post: Each line of the input file corresponds to a ingredient to be added to the list. No duplicates are allowed.
*/
Pantry::Pantry(const std::string &inputfilename){
        std::ifstream input(inputfilename);
        std::string ignoredline;
        std::getline(input, ignoredline); // Ignore first line 
        std::string line;

        while (std::getline(input, line)){
            std::istringstream stream(line);
            std::string Name, Description, Recipe, Temp;
            int Quantity, Price;

            std::vector<Ingredient*> Pramingredient;
            std::getline(stream, Temp, ',');
            Name = Temp;
            std::getline(stream, Temp, ',');
            Description = Temp;
            std::getline(stream, Temp, ',');
            std::istringstream convertquantity(Temp); 
            convertquantity >> Quantity;
            std::getline(stream, Temp, ',');
            std::istringstream convertprice(Temp); 
            convertprice >> Price;
            std::getline(stream, Temp);
            Recipe = Temp;

            if(Recipe != "NONE"){//If recipe isnt NONE add all elements to the vector 
                std::vector<std::string> stringvector;
                std::istringstream Rec(Recipe);
                while(Rec >> Temp){
                    Temp.erase(std::remove(Temp.begin(), Temp.end(), ';'), Temp.end());
                    stringvector.push_back(Temp);
                }
                for (const auto& named : stringvector){
                    if(contains(named)){
                        Pramingredient.push_back(getEntry(getPosOf(named)));
                    } else {
                        Ingredient *newIngredient = new Ingredient(Name, "UNKNOWN", 0, 1, std::vector<Ingredient*>());
                        addIngredient(newIngredient);
                        Pramingredient.push_back(newIngredient);
                    }
                }
            }
        Ingredient *ptr = new Ingredient(Name, Description, Quantity, Price, Pramingredient);
        Pantry::addIngredient(ptr);
        }
    input.close();
}

/**
        Destructor
        @post: Explicitly deletes every dynamically allocated Ingredient object
*/
Pantry:: ~Pantry(){clear();}    

/**
    @param: A const string reference to a ingredient name
    @return: The integer position of the given ingredient if it is in the Pantry, -1 if not found.
*/
int Pantry::getPosOf(const std::string&IngredientName){//if empty return -1 else interate through the list compare each node.
    if(isEmpty()){
        return -1;
    }
    for(int i = 0; i < getLength(); i ++){
        if(getEntry(i)->name_ == IngredientName){
            return i;
        }
    }
        return -1;
}

/**
    @param: A const string reference to a ingredient name
    @return: True if the ingredient information is already in the Pantry
*/
bool Pantry::contains(const std::string&IngredientName){// Calls getposOf, if it returns a value greater than -1 then it is in the pantry
    if(isEmpty()){
        return false;
    }
    if(getPosOf(IngredientName)!= -1){
        return true;
    }
    return false;
}


/**
    @param:  A pointer to an Ingredient object
    @post:  Inserts the given ingredient pointer into the Pantry, unless an ingredient of the same name is already in the pantry. 
            Each of its Ingredients in its recipe are also added to the Pantry IF not already in the list.
    @return: True if the ingredient was added successfully, false otherwise.
*/
bool Pantry::addIngredient(Ingredient* const &object){ // Check if subrecipes are in the pantry and add if not 
    if(object->recipe_.size() > 0){
        for(int i = 0; i < object->recipe_.size(); i ++){
            if(!contains(object->recipe_[i]->name_)){
                insert(getLength(), object->recipe_[i]);
            }
        }
    }

    if(!contains(object->name_)){//Check if the main ingredient is not in the pantry. If not in list add it and return true. Else return false
        insert(getLength(), object);
        return true;
    }
    else{
        return false;
    }
}

/**
    @param: A const string reference representing a ingredient name
    @param: A const string reference representing ingredient description
    @param: A const int reference representing the ingredient's quantity
    @param: A const int reference representing the ingredient's price
    @param: A const reference to a vector holding Ingredient pointers representing the ingredient's recipe
    @post:   Creates a new Ingredient object and inserts a pointer to it into the Pantry. 
            Each of its Ingredients in its recipe are also added to the Pantry IF not already in the list.
    @return: True if the ingredient was added successfully
*/
bool Pantry::addIngredient(const std::string& ingredient_name, const std::string& ingredient_description, const int& ingredient_quantity,const int& ingredient_price, const std::vector<Ingredient*> ingredient_recipe){
    Ingredient* ptr = new Ingredient(ingredient_name, ingredient_description, ingredient_quantity, ingredient_price,ingredient_recipe);
    return addIngredient(ptr);
}//Calls AddIngredient to do the same step and return what it returns.

/**
    @param:  A Ingredient pointer
    @return: A boolean indicating if all the given ingredient can be created (all of the ingredients in its recipe can be created, or if you have enough of each ingredient in its recipe to create it)
*/
bool Pantry::canCreate(Ingredient* const &pointer){
    if((pointer->recipe_).size() == 0){//If recipe_ is empty that means nothing can be created / UNCRAFTABLE 
        return false;
    }
    for(int i =0; i <(pointer->recipe_).size(); i ++){ // Check if subrecipe is in the list. If not return false
        if(!contains((pointer->recipe_[i])->name_)){
            return false;
        };
        if(pointer->recipe_[i]->quantity_ == 0){ // If subrecipe is in the list with 0 instance then we use recursion and find if it's sub ingredient is in the pantry
            if(!canCreate(pointer->recipe_[i])){
                return false;
            }
        }
    }
    return true;
}

/**
    @param: A Ingredient pointer
    @post: Prints the ingredient name, quantity, and description.
    The output should be of the form:
    [Ingredient Name]: [Quantity]\n
    [Ingredient Description]\n
    Price: [Price]\n
    Recipe:\n
    [Ingredient0] [Ingredient1]\n


    If the ingredient has no recipe, print "Recipe:\nNONE\n\n" after the price.
*/
void Pantry::printIngredient(Ingredient* pointer)const{// Print the ingredient and it's information 
    if(pointer != nullptr){
        std::cout
        << pointer->name_ << ": " 
        << pointer->quantity_ << "\n"
        << pointer->description_ << "\n"
        << "Price: " << pointer->price_ << "\n";
        if((pointer->recipe_).size() > 0){
            std::cout <<"Recipe:\n";
            for(int i = 0; i < (pointer->recipe_).size(); i ++){//Print out sub recipes
                std::cout << (pointer->recipe_)[i]->name_ << " ";
            }
            std::cout << "\n";
        }
        if((pointer->recipe_).size() == 0){// No sub recipes
            std::cout
            << "Recipe:\nNONE\n\n";
        }
    }
}

/**
    @param: A const string reference to a ingredient name
    @post:  Prints a list of ingredients that must be created before the given ingredient can be created (missing ingredients for its recipe, where you have 0 of the needed ingredient).
            If the ingredient is already in the pantry, print "In the pantry([quantity])\n"
            If there are no instances of the ingredient, if it cannot be crafted because of insufficient ingredients, print "[Ingredient Name](0)\nMISSING INGREDIENTS"
            If it can be crafted, recursively print the ingredients that need to be used (if there are instances of them) or created (if there are no instances of them) in the order that the ingredients appear in the recipe, joined by "<-".
            If the ingredient has no recipe, print "UNCRAFTABLE\n" at the end of the function.

            Below are some of the expected forms. "Scenario: [scenario] is not part of the output. It is just to help you understand the expected output.":

            Scenario: The Ingredient does not exist in the list
            Query: [Ingredient Name]
            No such ingredient

            Scenario: The Ingredient exists in the list, and there are >0 instances of it
            Query: [Ingredient Name]
            In the pantry ([Quantity])

            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it is craftable by using an ingredient that is already in the pantry
            Query: [Ingredient Name0]
            [Ingredient Name0](C)
            [Ingredient Name1](1)

            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it is craftable by using an ingredient that has to be crafted
            Query: [Ingredient Name0]
            [Ingredient Name0](C)
            [Ingredient Name1](C) <- [Ingredient Name2](3)
            
            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and there are multiple ingredients that have to be crafted (each row represents a different ingredient inå the original recipe)
            Query: [Ingredient Name0]
            [Ingredient Name0](C)
            [Ingredient Name1](C) <- [Ingredient Name2](3)
            [Ingredient Name3](C) <- [Ingredient Name4](C) <- [Ingredient Name5] (3)

            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it is not craftable (it has no recipe)
            Query: [Ingredient Name0]
            UNCRAFTABLE

            Scenario: The Ingredient exists in the list, and there are 0 instances of it, and it has a recipe, but you do not have enough of the ingredients to craft it
            Query: [Ingredient Name0]
            [Ingredient Name0](0)
            MISSING INGREDIENTS
    
*/
void Pantry::ingredientQuery(const std::string &ingredient_name) {
    std::cout << "Query: " << ingredient_name << "\n";
    if (!contains(ingredient_name)) {// Not in pantry
        std::cout << "No such ingredient\n";
    } 
    else {// In pantry with greater than 0 instance
        Ingredient* Main = getEntry(getPosOf(ingredient_name));
        if (Main->quantity_ > 0) {
            std::cout << "In the pantry (" << Main->quantity_ << ")" << "\n";
            if (!canCreate(Main)) {//Cannot be crafted
                std::cout << "UNCRAFTABLE\n";
            }
        } 
        else if (!canCreate(Main)) {
            std::cout << "UNCRAFTABLE\n";
        } 
        else {// 0 instance but craftable
            if (canCreate(Main)) {
                std::cout << Main->name_ << "(C)\n";
                Helperfunction(Main);
                std::cout << "\n";
            } else {//missing subrecipes n pantry
                std::cout << Main->name_ << "(0)" << "\n" << "MISSING INGREDIENTS" << "\n";
            }
        }
    }
}

/**
    @return: An integer sum of the price of all the ingredients currently in the list.
    Note: This should only include price values from ingredients that you have 1 or more of. Do not consider ingredients that you have 0 of, even if you have the ingredients to make them.
*/
int Pantry::calculatePantryValue() const {
    int num = 0; 
    for(int i = 0; i < getLength(); i++) {//Iterate through the pantry and adding it to sum with price * quanity 
        num = num + (getEntry(i)->price_ * getEntry(i)->quantity_);
    }
    return num;
}

/**
    @param: A const string reference to a filter with a default value of "NONE".
    @post: With default filter "NONE": Print out every ingredient in the list.
        With filter "CONTAINS":   Only print out the ingredients with >0 instances in the list.
        With filter "MISSING": Only print out the ingredients with 0 instances in the list.
        With filter "CRAFTABLE":  Only print out the ingredients where you have all the ingredients to craft them.
        If an invalid filter is passed, print "INVALID FILTER\n"
        Printing ingredients should be of the form:

        [Ingredient name]: [Quantity]
        [Ingredient description]\n
        Price: [price]\n
        Recipe:\n
        [Ingredient0] [Ingredient1]\n\n

        If the ingredient has no recipe, print "Recipe:\nNONE\n\n" after the price.
*/
void Pantry::pantryList(const std::string &list){// Calls Print Ingredient if ingredeient matches the requirement 
    if(list == "NONE"){//Filters for NONE 
        for(int i = 0; i < item_count_; i++){
            Ingredient* temp = getEntry(i);
            printIngredient(temp);
        }
    }
    else if(list == "CONTAINS"){//Filters for CONTAIN
        for(int i = 0; i <item_count_; i++){
            Ingredient* temp = getEntry(i);
            if(temp->quantity_ > 0){
                printIngredient(temp);
            }
        }
    }
    else if(list == "MISSING"){//Filter for MISSING
        for(int i = 0; i <item_count_; i++){
            Ingredient* temp = getEntry(i);
            if(temp->quantity_ == 0){
                printIngredient(temp);
            }
        }
    }
    else if(list == "CRAFTABLE"){//Filter for Craftable
        for(int i = 0; i <item_count_; i++){
            Ingredient* temp = getEntry(i);
            if(canCreate(temp)){
                printIngredient(temp);
            }
        }
    }
    else{//Invaild Filter 
        std::cout << "INVALID FILTER\n";
    }
}

/** 
 * @param: A Ingredient pointer
 * @post: Helper function for ingredientQuery()
 * Prints the name of sub ingredient for Ingredient pointer.
 * If the quanity of sub ingredient is 0 then print all neccesary subingredient require to craft it. Using recursion.
*/
void Pantry::Helperfunction(Ingredient* Main){
    for (int i = 0; i < Main->recipe_.size(); i ++) {
        Ingredient* Side = Main->recipe_[i];
        std::cout << Side->name_;
        if (canCreate(Side) && Side->quantity_ == 0) {//Check if Sub Ingredient Quanity is 0. If zero declare it as craftable and print out all sub subingredient required for the sub ingredeint
            std::cout << "(C) <- ";
            Helperfunction(Side);
        } 
        else if (Side->quantity_ > 0) {
            std::cout << "(" << Side->quantity_ << ")" << "\n";
        }
    }
}