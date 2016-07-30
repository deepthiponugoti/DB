//
//  BPlusTreeNodeInner.cpp
//  BPlusTree
//
//  Created by chenshen on 4/22/15.
//  Copyright (c) 2015 chenshen. All rights reserved.
//

#include "BPlusTreeNodeInner.h"

BPlusTreeNodeInner::BPlusTreeNodeInner() {
    keys = std::vector<keyType> (NODE_ORDER_INNER + 1, EMPTY_SYMBOL);
    children = std::vector<BPlusTreeNode*> (NODE_ORDER_INNER + 2, NULL);
}

int BPlusTreeNodeInner::getNodeType() {
    return NODE_INNER;
}

int BPlusTreeNodeInner::getKeyPosition(keyType key) {
    int i;
    for (i = 0; i < getKeyCount(); i++) {
        if (key == getKey(i)) {
            return i + 1;
        } else if (key < getKey(i)) {
            return i;
        }
    }
    
    return i;
}

BPlusTreeNode* BPlusTreeNodeInner::getChild(int idx) {
    return (BPlusTreeNode*)children[idx];
}

void BPlusTreeNodeInner::setChild(int idx, BPlusTreeNode* child) {
    children[idx] = child;
    if (child != NULL) {
        child->setNodeParent(this);
    }
}

void BPlusTreeNodeInner::insertIntoPosition(int idx, keyType key, BPlusTreeNode* leftChild, BPlusTreeNode* rightChild) {
    for (int i = getKeyCount() + 1; i > idx; i--) {
        setChild(i, getChild(i - 1));
    }
    for (int i = getKeyCount(); i > idx; i--) {
        setKey(i, getKey(i - 1));
    }
    
    setKey(idx, key);
    setChild(idx,leftChild);
    setChild(idx + 1, rightChild);
    keyCount++;
}

BPlusTreeNode* BPlusTreeNodeInner::getNodeSplitted() {
    int midIdx = getKeyCount() / 2;
    BPlusTreeNodeInner* newNode = new BPlusTreeNodeInner;
    for (int i = midIdx + 1; i < getKeyCount(); i++) {
        newNode->setKey(i - midIdx - 1, getKey(i));
        setKey(i, EMPTY_SYMBOL);
    }
    for (int i = midIdx + 1; i <= getKeyCount(); i++) {
        newNode->setChild(i - midIdx - 1, getChild(i));
        newNode->getChild(i - midIdx - 1)->setNodeParent(newNode);
        setChild(i, NULL);
    }
    
    setKey(midIdx, EMPTY_SYMBOL);
    newNode->keyCount = getKeyCount() - midIdx - 1;
    keyCount = midIdx;
    
    return (BPlusTreeNode*)newNode;
}