//
//  BPlusTreeNodeLeaf.h
//  BPlusTree
//
//  Created by chenshen on 4/20/15.
//  Copyright (c) 2015 chenshen. All rights reserved.
//

#ifndef BPlusTree_BPlusTreeNodeLeaf_h
#define BPlusTree_BPlusTreeNodeLeaf_h

#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include "BPlusTreeNode.h"

using namespace std;

class BPlusTreeNodeLeaf: public BPlusTreeNode {
    
public:
    
    BPlusTreeNodeLeaf();
    
    keyType getKeyLeaf(int idx);
    
    void setKeyLeaf(int idx, keyType key);
    
    valueType getValue(int idx);
    
    void setValue(int idx, valueType value);
    
    void insertIntoPosition(int idx, keyType key, valueType value);
    
    void insertKey(keyType key, valueType value);
    
    void deleteKey(keyType key);
    
    virtual int getNodeType();
    
    virtual int getKeyPosition(keyType key);
    
    virtual BPlusTreeNode* getNodeSplitted();
    
private:
    
    std::vector<valueType> values;
    
};

#endif
