/**
 * @file SkillTree.cpp
 * @author Devin Chen 
 * @brief SkillTree Class
 * @date 5/6/2024
*/

#include "SkillTree.hpp"
#pragma once
/**
  * Default Constructor
  */
SkillTree::SkillTree(){}
/**
 * @param: A const reference to string: the name of a csv file
 * @post: The SkillTree is populated with Skills from the csv file
 * The file format is as follows:
 * id,name,description,leveled
 * Ignore the first line. Each subsequent line represents a Skill to be added to the SkillTree.
*/
SkillTree::SkillTree(const std::string &csv_file){
 std::ifstream input(csv_file);
        std::string ignoredline;
        std::getline(input, ignoredline); // Ignore first line 
        std::string line;

        while (std::getline(input, line)){
            std::istringstream stream(line);
            std::string ID, NAME, DESCRIPTION, LEVEL, Temp;

            std::getline(stream, Temp, ',');
            ID = Temp;
            std::getline(stream, Temp, ',');
            NAME = Temp;
            std::getline(stream, Temp, ',');
            DESCRIPTION = Temp;
            std::getline(stream, Temp, ',');
            LEVEL = Temp;

            int id; 
            bool leveled;

            if(std::stoi(LEVEL) == 0){
                leveled = false;
            }
            else{
                leveled = true;
            }

            id = std::stoi(ID);

            add(Skill(id, NAME, DESCRIPTION, leveled));
        }
}
/**
 * @param: A const reference to int representing the id of the Skill to be found
 * @return: A pointer to the node containing the Skill with the given id, or nullptr if the Skill is not found
*/
BinaryNode<Skill>* SkillTree::findSkill(const int &id){
    if(isEmpty()){
        return nullptr;
    }
    if(id == 0){
        return nullptr;
    }
    std::shared_ptr<BinaryNode<Skill>> Temp = getRoot();
    while(Temp!= nullptr){
        if((Temp.get()->getItem()).id_ == id){
            return Temp.get();
        }
        else if(id < (Temp.get()->getItem()).id_){
            Temp = Temp.get()->getLeftChildPtr();
        }
        else{
            Temp = Temp.get()->getRightChildPtr();
        }
    }
    return nullptr;
}
/**
  * @param: A const reference to Skill 
  * @post: The Skill is added to the tree (in BST order as implemented in the base class) only if it was not already in the tree. Note that all comparisons are id-based as implemented by the Skill comparison operators.
  * @return: True if the Skill is successfully added to the SkillTree, false otherwise
  */
bool SkillTree::addSkill(const Skill &skill){
    if(findSkill(skill.id_) != nullptr){
        return false;
    }
    else{
        add(skill);
        return true;
    }
}
/**
  * @param: A const reference to string: the name of a Skill
  * @return: True if the Skill is successfully removed from the SkillTree, false otherwise
  */
bool SkillTree::removeSkill(const std::string &skill_name){
    std::shared_ptr<BinaryNode<Skill>> Main = removeskillhelper(getRoot(), skill_name);
    if(Main != nullptr){
        remove(Main.get()->getItem());
        return true;
    }
    if(Main == nullptr){
        return false;
    }

}
/**
  * @param: A shared_ptr a node on the Binary tree and a string
  * @post: Traverse the tree searching if the item's name in the node matches the string
  * @return: Return the node when the item's name matches with the string.
  */
std::shared_ptr<BinaryNode<Skill>> SkillTree::removeskillhelper(std::shared_ptr<BinaryNode<Skill>> node, std::string name){
    if(node == nullptr){ // Base if the root is Null <- end of the tree and we didn't find it 
        return nullptr;
    }
    if(node.get()->getItem().name_ == name){// Node is found now returning it 
        return node;
    }
    else{// Node is not found search through left and right node 
        std::shared_ptr<BinaryNode<Skill>> left = removeskillhelper(node.get()->getLeftChildPtr(), name);
        std::shared_ptr<BinaryNode<Skill>> right = removeskillhelper(node.get()->getRightChildPtr(), name);

        if(right != nullptr){
            return right;
        }
        if(left != nullptr){
            return left;
        }
    }
    return nullptr;
}
/**
  * @post: Clears the tree
  */
void SkillTree::clear(){
    setRoot(nullptr);
}
/**
  * @param: A const reference to int representing the id of a Skill
    * Note: For a Skill to be leveled up, its parent Skill must also be leveled up, thus the Skill points are the number of Skills that must be leveled up before and including the Skill with the given id.
  * @return: an integer: the number of skill points needed to level up the Skill with the given id, starting from the root (i.e. the number of nodes from root to the given Skill).
  * Include the Skill with the given id in the count. For example, if the tree contains the following Skills (represented by their ids):
  *   5
  *  / \
  * 1   8
  * and the function parameter queries for id 8, the function should return 2.
  * Disregard the leveled_ field of the existing Skills in the tree.
  * If the Skill with the given id is not found, return -1.
  */
int SkillTree::calculateSkillPoints(const int &id){
    if(findSkill(id) == nullptr){
        return -1;
    }
    if(isEmpty()){
        return -1;
    }
    int returnnum = 1;
    std::shared_ptr<BinaryNode<Skill>> Temp = getRoot();
    while(Temp!= nullptr){
        if(Temp.get()->getItem().id_ == id){
            break;
        }
        else if(Temp.get()->getItem().id_ < id){
            Temp = Temp.get()->getLeftChildPtr();
            returnnum++;
        }
        else{
            Temp = Temp.get()->getRightChildPtr();
            returnnum++;
        }
    }
    return returnnum;
}
/**
  * @post: prints the tree in preorder, in the format:
  [id_] [name_]\n
  [description_]\n 
  [leveled_]
  */
void SkillTree::preorderDisplay(){
    std::shared_ptr<BinaryNode<Skill>> node = getRoot();
    preorderDisplayHelper(node);
}
/**
  * @param: A shared_ptr a node on the Binary tree 
  * @post: Traverse the tree in preorder and displaing the item in format 
  [id_] [name_]\n
  [description_]\n 
  [leveled_]
  */
void SkillTree::preorderDisplayHelper(std::shared_ptr<BinaryNode<Skill>> node){
            std::cout << "  " << node.get()->getItem().id_  << " " << node.get()->getItem().name_ << "\n";
            std::cout << "  " << node.get()->getItem().description_  << "\n";
            std::cout << "  " << node.get()->getItem().leveled_;
    if(node != nullptr){//check if it is a nullptr so there won't be segfault
        if(node.get()->getLeftChildPtr() != nullptr){//check if it has left ptr
            preorderDisplayHelper(node.get()->getLeftChildPtr());
        }
        if(node.get()->getRightChildPtr() != nullptr){//check if it has right ptr
            preorderDisplayHelper(node.get()->getRightChildPtr());
        }
        
        //print current skill 
    }
}
/**
  * @post: Balances the tree. Recall the definition of a balanced tree:
  * A tree is balanced if for any node, its left and right subtrees differ in height by no more than 1. * All paths from root of subtrees to leaf differ in length by at most 1
  * Hint: You may sort the elements and build the tree recursively using a divide and conquer approach      
  */
void SkillTree::balance(){
    std::vector<std::shared_ptr<BinaryNode<Skill>>> vec = Inorder(root_ptr_);
    setRoot(sortedArrayToBST(vec, 0 , vec.size()-1));
}
/**
  * @param: A shared_ptr a node on the Binary tree, a pointer to a vecotor
  * @post: Traverse Breath First search and push nodes into the vecotor
  */
 // adapted from :https://stackoverflow.com/questions/63720121/c-how-to-store-the-nodes-of-an-in-order-traversal-into-an-array
void SkillTree::InorderRecursive(std::shared_ptr<BinaryNode<Skill>> root, std::vector<std::shared_ptr<BinaryNode<Skill>>>& nodes)
{
    if (root == NULL)
        return;

    InorderRecursive(root->getLeftChildPtr(), nodes); //visit left sub-tree

    nodes.push_back(root); // Corrected this line to dereference root

    InorderRecursive(root->getRightChildPtr(), nodes); //visit right sub-tree
}
/**
  * @param: A shared_ptr a node on the Binary tree 
  * @post: Calls InorderRecrusive
  * @return: A vector containing Binary Nodes
  */
 // adapted from :https://stackoverflow.com/questions/63720121/c-how-to-store-the-nodes-of-an-in-order-traversal-into-an-array
std::vector<std::shared_ptr<BinaryNode<Skill>>> SkillTree::Inorder(std::shared_ptr<BinaryNode<Skill>> root)
{
    std::vector<std::shared_ptr<BinaryNode<Skill>>> nodes;    
    InorderRecursive(root, nodes);
    return nodes;
}
/**
  * @param: Address to a vecotor containing nodes, int representing the start and end of the vector
  * @post: Taking the middle of the vector and assigning it as the root. This way the BST is now able to be balanced.
  * as each left and right will have the maximum distance of 1. 
  * @return A shared_ptr that is the new root. 
  */
 // adapted from :  https://github.com/mandliya/algorithms_and_data_structures/blob/master/tree_problems/sortedArrayToBST.cpp
std::shared_ptr<BinaryNode<Skill>> SkillTree::sortedArrayToBST(std::vector<std::shared_ptr<BinaryNode<Skill>>>& arr, int start, int end) {
    if (start > end) {
        return nullptr;
    }
    int mid = (start + end) / 2;
    std::shared_ptr<BinaryNode<Skill>> node = std::make_shared<BinaryNode<Skill>>(*arr[mid]);
    node->setLeftChildPtr(sortedArrayToBST(arr, start, mid - 1));
    node->setRightChildPtr(sortedArrayToBST(arr, mid + 1, end));
    return node;
}
