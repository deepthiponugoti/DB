//
//  BPlusTreeProcessor.h
//  BPlusTree
//
//  Created by chenshen on 4/20/15.
//  Copyright (c) 2015 chenshen. All rights reserved.
//

#ifndef BPlusTree_BPlusTreeProcessor_h
#define BPlusTree_BPlusTreeProcessor_h

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include <sstream>
#include <fstream>
#include "BPlusTree.h"

using namespace std;

class BPlusTreeProcessor {

public:
    
    BPlusTreeProcessor();
    
    bool process(std::string fileName);
    
private:
    
    const std::string INSERT = "*INSERT";
    
    const std::string SEARCH = "*SEARCH";
    
    const std::string DELETE = "*DELETE";
    
    const std::string UPDATE = "*UPDATE";
    
    const std::string SNAPSHOT = "*SNAPSHOT";
    
    std::string status;
};

#endif
