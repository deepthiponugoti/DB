//
//  BPlusTree.h
//  BPlusTree
//
//  Created by chenshen on 4/26/15.
//  Copyright (c) 2015 chenshen. All rights reserved.
//

#ifndef BPlusTree_BPlusTree_h
#define BPlusTree_BPlusTree_h

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <cmath>
#include "BPlusTreeNodeInner.h"
#include "BPlusTreeNodeLeaf.h"

using namespace std;

class BPlusTree {
    
public:
    
    BPlusTree();
    
    bool insert(keyType key, valueType value);
    
    bool remove(keyType key);
    
    bool update(keyType key, valueType value);
    
    bool search(keyType key);
    
    bool getLeaves(std::vector<keyType>& keysInLeaves, std::vector<valueType>& valuesInLeaves);
    
    void showLeaves();
    
    void showSnapShot();
    
private:
    
    BPlusTreeNode* nodeRoot;
    
    std::vector<BPlusTreeNode*> allNodes;
    
    void freeTree();
    
    BPlusTreeNodeLeaf* getTargetLeaf(keyType key);
    
    BPlusTreeNode* fullNodeHandling(BPlusTreeNode* node);
    
    BPlusTreeNode* elevateMiddleKey(BPlusTreeNode* node, keyType key, BPlusTreeNode* nodeChildLeft, BPlusTreeNode* nodeChildRight);
    
    bool isKeyExist(BPlusTreeNodeLeaf* node, keyType key);
};

#endif
