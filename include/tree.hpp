//
// Created by Nick Ray on 4/8/21.
//

#ifndef PARSER_TREE_HPP
#define PARSER_TREE_HPP

#include "node.hpp"

node* buildTree(std::string filename);
void processPreorder(node* node, std::string fileName);

#endif //PARSER_TREE_HPP
