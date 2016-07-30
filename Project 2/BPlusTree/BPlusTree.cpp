//
//  BPlusTree.cpp
//  BPlusTree
//
//  Created by chenshen on 4/26/15.
//  Copyright (c) 2015 chenshen. All rights reserved.
//

#include "BPlusTree.h"

BPlusTree::BPlusTree() {
    nodeRoot = new BPlusTreeNodeLeaf;
    allNodes.push_back(nodeRoot);
}

bool BPlusTree::search(keyType key) {
    BPlusTreeNodeLeaf* leaf = getTargetLeaf(key);
    if (!isKeyExist(leaf, key)) {
        std::cout << std::endl;
        std::cout << "SEARCH ERROR: KEY '" << key << "' DOES NOT EXIST!" << std::endl;
        std::cout << std::endl;
        return false;
    }
    int idx = leaf->getKeyPosition(key);
    valueType value = leaf->getValue(idx);
    
    std::cout << std::endl;
    std::cout << "--- Search Results ---" << std::endl;
    std::cout << "Key: " << key << std::endl;
    std::cout << "Information: " << value << std::endl;
    
    return true;
}

bool BPlusTree::insert(keyType key, valueType value) {
    BPlusTreeNodeLeaf* leaf = getTargetLeaf(key);
    if (isKeyExist(leaf, key)) {
        std::cout << std::endl;
        std::cout << "INSERT ERROR: KEY '" << key << "' ALREADY EXISTS!" << std::endl;
        std::cout << std::endl;
        return false;
    }
    leaf->insertKey(key, value);
    
    if (leaf->isNodeFull()) {
        BPlusTreeNode* nodeExit = fullNodeHandling(leaf);
        if (nodeExit != NULL) {
            nodeRoot = nodeExit;
        }
    }
    return true;
}

bool BPlusTree::update(keyType key, valueType value) {
    BPlusTreeNodeLeaf* leaf = getTargetLeaf(key);
    if (!isKeyExist(leaf, key)) {
        std::cout << std::endl;
        std::cout << "UPDATE ERROR: KEY '" << key << "' DOES NOT EXIST!" << std::endl;
        std::cout << std::endl;
        return false;
    }
    int idx = leaf->getKeyPosition(key);
    leaf->setValue(idx, value);
    
    return true;
}

bool BPlusTree::remove(keyType key) {
    BPlusTreeNodeLeaf* leaf = getTargetLeaf(key);
    if (!isKeyExist(leaf, key)) {
        std::cout << std::endl;
        std::cout << "DELETE ERROR: KEY '" << key << "' DOES NOT EXIST!" << std::endl;
        std::cout << std::endl;
        return false;
    }
    leaf->deleteKey(key);
    
    if (leaf->getKeyCount() == 0) {
        std::vector<keyType> keysInLeaves;
        std::vector<valueType> valuesInLeaves;
        getLeaves(keysInLeaves, valuesInLeaves);
        freeTree();
        nodeRoot = new BPlusTreeNodeLeaf;
        allNodes.push_back(nodeRoot);
        for (int i = 0; i < keysInLeaves.size(); i++) {
            insert(keysInLeaves[i], valuesInLeaves[i]);
        }
    }
    
    return true;
}

BPlusTreeNode* BPlusTree::fullNodeHandling(BPlusTreeNode* node) {
    int midIdx = (node->getKeyCount()) / 2;
    keyType midKey = node->getKey(midIdx);
    BPlusTreeNode* newNode = node->getNodeSplitted();
    allNodes.push_back(newNode);
    
    if (node->getNodeParent() == NULL) {
        node->setNodeParent(new BPlusTreeNodeInner);
        allNodes.push_back(node->getNodeParent());
    }
    newNode->setNodeParent(node->getNodeParent());
    newNode->setNodeLeftSibling(node);
    newNode->setNodeRightSibling(node->getNodeRightSibling());
    if (node->getNodeRightSibling() != NULL) {
        node->getNodeRightSibling()->setNodeLeftSibling(newNode);
    }
    node->setNodeRightSibling(newNode);
    
    return elevateMiddleKey(node->getNodeParent(), midKey, node, newNode);
}

BPlusTreeNode* BPlusTree::elevateMiddleKey(BPlusTreeNode* node, keyType key, BPlusTreeNode* nodeChildLeft, BPlusTreeNode* nodeChildRight) {
    int idx = node->getKeyPosition(key);
    ((BPlusTreeNodeInner*)node)->insertIntoPosition(idx, key, nodeChildLeft, nodeChildRight);
    
    if (node->isNodeFull()) {
        return fullNodeHandling(node);
    } else {
        return (node->getNodeParent() == NULL)? node : NULL;
    }
}

BPlusTreeNodeLeaf* BPlusTree::getTargetLeaf(keyType key) {
    BPlusTreeNode* node = nodeRoot;
    while (node->getNodeType() == NODE_INNER) {
        node = ((BPlusTreeNodeInner*)node)->getChild(node->getKeyPosition(key));
    }
    
    return (BPlusTreeNodeLeaf*)node;
}

bool BPlusTree::getLeaves(std::vector<keyType>& keysInLeaves, std::vector<valueType>& valuesInLeaves) {
    keysInLeaves.clear();
    valuesInLeaves.clear();
    BPlusTreeNode* node = nodeRoot;
    while (node->getNodeType() == NODE_INNER) {
        node = ((BPlusTreeNodeInner*)node)->getChild(0);
    }
    do {
        if (node->getKeyCount() > 0) {
            for (int i = 0; i < node->getKeyCount(); i++) {
                keysInLeaves.push_back(((BPlusTreeNodeLeaf*)node)->getKeyLeaf(i));
                valuesInLeaves.push_back(((BPlusTreeNodeLeaf*)node)->getValue(i));
                //std::cout << ((BPlusTreeNodeLeaf*)node)->getKeyLeaf(i) << " ";
            }
        }
        node = node->getNodeRightSibling();
    } while (node != NULL && node->getNodeType() == NODE_LEAF);
    
    return true;
}

void BPlusTree::showSnapShot() {
    BPlusTreeNode* node = nodeRoot;
    BPlusTreeNode* nodeFirst;
    std::vector<keyType> keysInLeaves;
    std::vector<valueType> valuesInLeaves;
    int depth = 0;
    
    std::cout << std::endl;
    std::cout << "---------- Snapshot (first and last key only) ----------" << std::endl;
    while (node != NULL) {
        nodeFirst = node;
        depth++;
        
        if (depth == 1) {
            std::cout << "--- Root ---" << std::endl;
        } else if (node->getNodeType() == NODE_LEAF) {
            std::cout << "--- Leaf Nodes ---" << std::endl;
        } else {
            std::cout << "--- Inner Nodes (current depth " << depth << ") ---" << std::endl;
        }
        
        do {
            if (node->getKeyCount() > 0) {
                std::cout << " ( * ";
                for (int i = 0; i < node->getKeyCount(); i++) {
                    if (node->getNodeType() == NODE_LEAF) {
                        keysInLeaves.push_back(((BPlusTreeNodeLeaf*)node)->getKeyLeaf(i));
                        valuesInLeaves.push_back(((BPlusTreeNodeLeaf*)node)->getValue(i));
                    }
                    if (i == 0 || i == (node->getKeyCount()) - 1) {
                        std::cout << node->getKey(i) << " * ";
                    }
                }
                std::cout << ") ";
            }
            node = node->getNodeRightSibling();
        } while (node != NULL);
        
        std::cout << std::endl;
        node = nodeFirst;
        if (node->getNodeType() == NODE_LEAF) {
            break;
        } else {
            node = ((BPlusTreeNodeInner*)node)->getChild(0);
        }
    }
    
    std::cout << std::endl;
    std::cout << "---------- All Data (name->information pairs) ----------" << std::endl;
    for (int i = 0; i < keysInLeaves.size(); i++) {
        std::cout << "(" << keysInLeaves[i] << " -> " << valuesInLeaves[i] << ")  ";
    }
    std::cout << std::endl;
    
    std::cout << std::endl;
    std::cout << "Records Count: " << keysInLeaves.size() << std::endl;
    std::cout << "Blocks Occupied: " << std::ceil(keysInLeaves.size() / 4) << std::endl;
    std::cout << "Tree Depth: " << depth << std::endl;
    
}

void BPlusTree::showLeaves() {
    std::vector<keyType> keysInLeaves;
    std::vector<valueType> valuesInLeaves;
    getLeaves(keysInLeaves, valuesInLeaves);
    
    std::cout << std::endl;
    for (int i = 0; i < keysInLeaves.size(); i++) {
        std::cout << keysInLeaves[i] << " ";
    }
    std::cout << std::endl;
    
}

bool BPlusTree::isKeyExist(BPlusTreeNodeLeaf* node, keyType key) {
    for (int i = 0; i < node->getKeyCount(); i++) {
        if (key == node->getKey(i)) {
            return true;
        }
    }
    return false;
}

void BPlusTree::freeTree() {
    for (int i = 0; i < allNodes.size(); i++) {
        if (allNodes[i]->getNodeType() == NODE_INNER) {
            delete (BPlusTreeNodeInner*)allNodes[i];
        } else if (allNodes[i]->getNodeType() == NODE_LEAF) {
            delete (BPlusTreeNodeLeaf*)allNodes[i];
        }
    }
    allNodes.clear();
}