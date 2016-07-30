//
//  BPlusTreeNodeInner.h
//  BPlusTree
//
//  Created by chenshen on 4/20/15.
//  Copyright (c) 2015 chenshen. All rights reserved.
//

#ifndef BPlusTree_BPlusTreeNodeInner_h
#define BPlusTree_BPlusTreeNodeInner_h

#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include "BPlusTreeNode.h"

using namespace std;

class BPlusTreeNodeInner: public BPlusTreeNode {
    
public:
    
    BPlusTreeNodeInner();
    
    BPlusTreeNode* getChild(int idx);
    
    void setChild(int idx, BPlusTreeNode* child);
    
    void insertIntoPosition(int idx, keyType key, BPlusTreeNode* leftChild, BPlusTreeNode* rightChild);
    
    virtual int getNodeType();
    
    virtual int getKeyPosition(keyType key);
    
    virtual BPlusTreeNode* getNodeSplitted();
    
protected:
    
    std::vector<BPlusTreeNode*> children;
    
};

#endif
