//
//  main.cpp
//  BPlusTree
//
//  Created by chenshen on 4/19/15.
//  Copyright (c) 2015 chenshen. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <map>
#include "BPlusTreeProcessor.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // insert code here...
    BPlusTreeProcessor treeProcessor;
    
    treeProcessor.process("INPUT");
    
    std::cout << std::endl;
    std::cout << "Done." << std::endl;
    
    return 0;
}
