/**
 * @file SkillTree.hpp
 * @author Devin Chen 
 * @brief SkillTree Class
 * @date 5/6/2024
*/



#include "BinarySearchTree.hpp"
#include <string>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#pragma once

struct Skill
{
public:
    /**
     * @param: A const reference to Skill 
     * @return: True if the id_ of the Skill is equal to that of the argument, false otherwise
     */
    bool operator==(const Skill &SKILL)const{
        return SKILL.id_ == id_;
    }
    /**
     * @param: A const reference to Skill 
     * @return: True if the id_ of the Skill is less than that of the argument, false otherwise
     */
    bool operator<(const Skill &SKILL)const{
        return SKILL.id_ > id_;
    }
    /**
     * @param: A const reference to Skill 
     * @return: True if the id_ of the Skill is greater than that of the argument, false otherwise
     */
    bool operator>(const Skill &SKILL)const{
        return SKILL.id_ < id_;
    }
    // Default constructor
    Skill():id_{0},name_{""},description_{""},leveled_{false}{}
    // Parameterized constructor
    /**
     * @param id: The unique identifier for the Skill
     * @param name: The name of the Skill
     * @param description: The description of the Skill
     * @param leveled: Whether or not the Skill is leveled up
     */
    Skill(int ID, std::string SKILLNAME, std::string DESCRIPTION, bool LEVEL){
        id_ = ID;
        name_ = SKILLNAME;
        description_ = DESCRIPTION;
        leveled_ = LEVEL;
    }
    
    int id_; // A unique identifier for the Skill
    std::string name_; // The name of the Skill
    std::string description_; // The description of the Skill
    bool leveled_; // Whether or not the Skill is leveled up
};


class SkillTree : public BinarySearchTree<Skill>{

public: 
/**
  * Default Constructor
  */
    SkillTree();
/**
 * @param: A const reference to string: the name of a csv file
 * @post: The SkillTree is populated with Skills from the csv file
 * The file format is as follows:
 * id,name,description,leveled
 * Ignore the first line. Each subsequent line represents a Skill to be added to the SkillTree.
*/
    SkillTree(const std::string &csv_file);
/**
 * @param: A const reference to int representing the id of the Skill to be found
 * @return: A pointer to the node containing the Skill with the given id, or nullptr if the Skill is not found
*/
    BinaryNode<Skill>* findSkill(const int &id);
/**
  * @param: A const reference to Skill 
  * @post: The Skill is added to the tree (in BST order as implemented in the base class) only if it was not already in the tree. Note that all comparisons are id-based as implemented by the Skill comparison operators.
  * @return: True if the Skill is successfully added to the SkillTree, false otherwise
  */
    bool addSkill(const Skill &skill);
/**
  * @param: A const reference to string: the name of a Skill
  * @return: True if the Skill is successfully removed from the SkillTree, false otherwise
  */
    bool removeSkill(const std::string &skill_name);
/**
  * @post: Clears the tree
  */
    void clear();
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
    int calculateSkillPoints(const int &id);
/**
  * @post: Balances the tree. Recall the definition of a balanced tree:
  * A tree is balanced if for any node, its left and right subtrees differ in height by no more than 1. * All paths from root of subtrees to leaf differ in length by at most 1
  * Hint: You may sort the elements and build the tree recursively using a divide and conquer approach      
  */
    void balance();
/**
  * @post: prints the tree in preorder, in the format:
  [id_] [name_]\n
  [description_]\n 
  [leveled_]
  */
    void preorderDisplay();
/**
  * @param: A shared_ptr a node on the Binary tree and a string
  * @post: Traverse the tree searching if the item's name in the node matches the string
  * @return: Return the node when the item's name matches with the string.
  */
    std::shared_ptr<BinaryNode<Skill>> removeskillhelper(std::shared_ptr<BinaryNode<Skill>> node, std::string);
/**
  * @param: A shared_ptr a node on the Binary tree 
  * @post: Traverse the tree in preorder and displaing the item in format 
  [id_] [name_]\n
  [description_]\n 
  [leveled_]
  */
    void preorderDisplayHelper(std::shared_ptr<BinaryNode<Skill>> node);
/**
  * @param: A shared_ptr a node on the Binary tree 
  * @post: Calls InorderRecrusive
  * @return: A vector containing Binary Nodes
  */
 // adapted from :https://stackoverflow.com/questions/63720121/c-how-to-store-the-nodes-of-an-in-order-traversal-into-an-array
    std::vector<std::shared_ptr<BinaryNode<Skill>>>Inorder(std::shared_ptr<BinaryNode<Skill>> root);
/**
  * @param: A shared_ptr a node on the Binary tree, a pointer to a vecotor
  * @post: Traverse Breath First search and push nodes into the vecotor
  */
 // adapted from :https://stackoverflow.com/questions/63720121/c-how-to-store-the-nodes-of-an-in-order-traversal-into-an-array
    void InorderRecursive(std::shared_ptr<BinaryNode<Skill>> root, std::vector<std::shared_ptr<BinaryNode<Skill>>>& nodes);
/**
  * @param: Address to a vecotor containing nodes, int representing the start and end of the vector
  * @post: Taking the middle of the vector and assigning it as the root. This way the BST is now able to be balanced.
  * as each left and right will have the maximum distance of 1. 
  * @return A shared_ptr that is the new root. 
  */
 // adapted from :  https://github.com/mandliya/algorithms_and_data_structures/blob/master/tree_problems/sortedArrayToBST.cpp
    std::shared_ptr<BinaryNode<Skill>> sortedArrayToBST( std::vector<std::shared_ptr<BinaryNode<Skill>>> & arr, int start, int end);
};
    