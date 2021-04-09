//
// Created by Nick Ray on 4/8/21.
//

#ifndef PARSER_NODE_HPP
#define PARSER_NODE_HPP

struct node {
    std::string base;
    std::vector<std::string> entries;
    node* left;
    node* right;
};

#endif //PARSER_NODE_HPP
