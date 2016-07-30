//
//  BPlusTreeNode.h
//  BPlusTree
//
//  Created by chenshen on 4/20/15.
//  Copyright (c) 2015 chenshen. All rights reserved.
//

#ifndef BPlusTree_BPlusTreeNode_h
#define BPlusTree_BPlusTreeNode_h



#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <map>

#define NODE_INNER 1
#define NODE_LEAF 2
#define NODE_ORDER_INNER 10
#define NODE_ORDER_LEAF 10

#define keyType std::string // int/std::string
#define EMPTY_SYMBOL "" // -1/""
#define valueType std::string

using namespace std;

//typedef int keyType;

class BPlusTreeNode {
    
public:
    
    BPlusTreeNode();

    int getKeyCount();
    
    keyType getKey(int idx);
    
    void setKey(int idx, keyType key);
    
    void setNodeParent(BPlusTreeNode* parent);
    
    virtual int getNodeType() = 0;
    
    virtual int getKeyPosition(keyType key) = 0;
    
    virtual BPlusTreeNode* getNodeSplitted() = 0;
    
    BPlusTreeNode* getNodeParent();
    
    BPlusTreeNode* getNodeLeftSibling();
    
    BPlusTreeNode* getNodeRightSibling();
    
    void setNodeLeftSibling(BPlusTreeNode* sibling);
    
    void setNodeRightSibling(BPlusTreeNode* sibling);
    
    bool isNodeFull();
    
protected:
    
    std::vector<keyType> keys;
    
    int keyCount;
    
    BPlusTreeNode* nodeParent;
    
    BPlusTreeNode* nodeLeftSibling;
    
    BPlusTreeNode* nodeRightSibling;
    
};

#endif
