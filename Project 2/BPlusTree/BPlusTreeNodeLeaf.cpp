//
//  BPlusTreeNodeLeaf.cpp
//  BPlusTree
//
//  Created by chenshen on 4/22/15.
//  Copyright (c) 2015 chenshen. All rights reserved.
//

#include "BPlusTreeNodeLeaf.h"

BPlusTreeNodeLeaf::BPlusTreeNodeLeaf() {
    keys = std::vector<keyType> (NODE_ORDER_LEAF + 1, EMPTY_SYMBOL);
    values = std::vector<valueType> (NODE_ORDER_LEAF + 1, "");
}

keyType BPlusTreeNodeLeaf::getKeyLeaf(int idx) {
    return keys[idx];
}

void BPlusTreeNodeLeaf::setKeyLeaf(int idx, keyType key) {
    keys[idx] = key;
}

valueType BPlusTreeNodeLeaf::getValue(int idx) {
    return values[idx];
}

void BPlusTreeNodeLeaf::setValue(int idx, valueType value) {
    values[idx] = value;
}

void BPlusTreeNodeLeaf::insertKey(keyType key, valueType value) {
    int i = 0;
    while (i < getKeyCount() && key > getKey(i)) {
        i++;
    }
    insertIntoPosition(i, key, value);
}

void BPlusTreeNodeLeaf::deleteKey(keyType key) {
    int i = 0;
    while (i < getKeyCount() && key != getKey(i)) {
        i++;
    }
    if (i == getKeyCount() - 1) {
        setKeyLeaf(i, EMPTY_SYMBOL);
        setValue(i, "");
    } else {
        int j = i;
        while (j < getKeyCount()) {
            setKeyLeaf(j, getKeyLeaf(j + 1));
            setValue(j, getValue(j + 1));
            j++;
        }
        if (i == 0 && getNodeParent() != NULL) {
            if (getNodeParent()->getKeyPosition(key) != 0) {
                int idx = (getNodeParent()->getKeyPosition(key)) - 1;
                getNodeParent()->setKey(idx, getKeyLeaf(0));
            }
        }
    }
    keyCount--;
}

void BPlusTreeNodeLeaf::insertIntoPosition(int idx, keyType key, valueType value) {
    for (int i = getKeyCount() - 1; i >= idx; i--) {
        setKeyLeaf(i + 1, getKeyLeaf(i));
    }
    setKeyLeaf(idx, key);
    setValue(idx, value);
    keyCount++;
}

int BPlusTreeNodeLeaf::getNodeType() {
    return NODE_LEAF;
}

int BPlusTreeNodeLeaf::getKeyPosition(keyType key) {
    int i;
    for (i = 0; i < getKeyCount(); i++) {
        if (key == getKey(i)) {
            return i;
        } else if (key < getKey(i)) {
            return -1;
        }
    }
    
    return -1;
}

BPlusTreeNode* BPlusTreeNodeLeaf::getNodeSplitted() {
    int midIdx = getKeyCount() / 2;
    BPlusTreeNodeLeaf* newNode = new BPlusTreeNodeLeaf;
    for (int i = midIdx; i < getKeyCount(); i++) {
        newNode->setKeyLeaf(i - midIdx, getKeyLeaf(i));
        setKeyLeaf(i, EMPTY_SYMBOL);
    }
    newNode->keyCount = getKeyCount() - midIdx;
    keyCount = midIdx;
    
    return (BPlusTreeNode*)newNode;
}