//
// Created by Nick Ray on 4/8/21.
//

#include <iostream>
#include <fstream>
#include "node.hpp"

node* insertNode(std::string str, node* treeNode) {
    std::string strBase = str.substr(0, 2);

    if(treeNode == NULL) {
        treeNode = new node;
        treeNode->base = strBase;
        treeNode->entries.push_back(str);
        treeNode->left = treeNode->right = NULL;
    } else if (strBase == treeNode->base) {
        // Only push str if it's not in vector already
        if (std::find(treeNode->entries.begin(), treeNode->entries.end(), str) == treeNode->entries.end()) {
            treeNode->entries.push_back(str);
        }
    } else if(strBase < treeNode->base) {
        treeNode->left = insertNode(str, treeNode->left);
    } else if(strBase > treeNode->base) {
        treeNode->right = insertNode(str, treeNode->right);
    }

    return treeNode;
}

node* buildTree(std::string filename) {
    std::string buffer;       // String buffer to hold data read from file
    node* root = NULL;        // Root node of the Binary Search Tree

    // Build nodes
    while (fileToRead >> buffer) {
        hasContent = true;
        root = insertNode(buffer, root); // Use each 'buffer' instance (non-terminal) to build a node
    }

    // Return the root node to the fully build BST
    return root;
}

std::string buildEntriesString(std::vector<std::string> entries) {
    std::string entriesString = "";

    for (std::vector<std::string>::iterator it = entries.begin(); it != entries.end(); ++it) {
        entriesString += *it + ' ';
    }

    return entriesString;
}

void printPreorder(node* node, std::ofstream& outputFile, int level = 0) {
    if (node == NULL) return;

    std::string entriesString = buildEntriesString(node->entries);
    std::string formattedOutput = std::string(level * 2, ' ') + std::to_string(level) + ": " + node->base + "- " + entriesString + '\n';

    std::cout << formattedOutput;
    try {
        outputFile << formattedOutput;
    } catch (std::ofstream::failure e) {
        throw 5;
    }
    printPreorder(node->left, outputFile, level + 1);
    printPreorder(node->right, outputFile, level + 1);
}

void processPreorder(node* node, std::string fileName) {
    std::string outputFileName = fileName + ".preorder";
    std::ofstream file;

    try {
        file.open(outputFileName);
    } catch (std::ofstream::failure e) {
        throw 1;
    }

    printPreorder(node, file);

    try {
        file.close();
    } catch (std::ofstream::failure e) {
        throw 4;
    }
}
