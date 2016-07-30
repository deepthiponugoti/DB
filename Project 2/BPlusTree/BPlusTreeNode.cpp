//
//  BPlusTreeNode.cpp
//  BPlusTree
//
//  Created by chenshen on 4/22/15.
//  Copyright (c) 2015 chenshen. All rights reserved.
//

#include "BPlusTreeNode.h"

BPlusTreeNode::BPlusTreeNode() {
    keyCount = 0;
    nodeParent = NULL;
    nodeLeftSibling = NULL;
    nodeRightSibling = NULL;
}

int BPlusTreeNode::getKeyCount() {
    return keyCount;
}

keyType BPlusTreeNode::getKey(int idx) {
    return keys[idx];
}

void BPlusTreeNode::setKey(int idx, keyType key) {
    keys[idx] = key;
}

void BPlusTreeNode::setNodeParent(BPlusTreeNode* parent) {
    nodeParent = parent;
}

BPlusTreeNode* BPlusTreeNode::getNodeParent() {
    return nodeParent;
}

BPlusTreeNode* BPlusTreeNode::getNodeLeftSibling() {
    if (nodeLeftSibling != NULL) {
        return nodeLeftSibling;
    } else {
        return NULL;
    }
}

BPlusTreeNode* BPlusTreeNode::getNodeRightSibling() {
    if (nodeRightSibling != NULL) {
        return nodeRightSibling;
    } else {
        return NULL;
    }
}

void BPlusTreeNode::setNodeLeftSibling(BPlusTreeNode* sibling) {
    nodeLeftSibling = sibling;
}

void BPlusTreeNode::setNodeRightSibling(BPlusTreeNode* sibling) {
    nodeRightSibling = sibling;
}

bool BPlusTreeNode::isNodeFull() {
    return (getKeyCount() == keys.size());
}
