//
//  BPlusTreeProcessor.cpp
//  BPlusTree
//
//  Created by chenshen on 5/6/15.
//  Copyright (c) 2015 chenshen. All rights reserved.
//

#include "BPlusTreeProcessor.h"

BPlusTreeProcessor::BPlusTreeProcessor() {
    
}

bool BPlusTreeProcessor::process(std::string fileName) {
    std::ifstream infile(fileName);
    std::string line;
    std::string line_tmp;
    BPlusTree tree;
    
    while (std::getline(infile, line)) {
        if (line == INSERT) {
            status = INSERT;
        } else if (line == SEARCH) {
            status = SEARCH;
        } else if (line == DELETE) {
            status = DELETE;
        } else if (line == UPDATE) {
            status = UPDATE;
        } else if (line == SNAPSHOT) {
            tree.showSnapShot();
        } else {
            transform(line.begin(), line.end(), line.begin(), ::tolower);
            if (status == INSERT) {
                tree.insert(line, "");
                continue;
            }
            if (status == SEARCH) {
                tree.search(line);
                continue;
            }
            if (status == DELETE) {
                tree.remove(line);
                continue;
            }
            if (status == UPDATE) {
                line_tmp = line;
                getline(infile, line);
                tree.update(line_tmp, line);
                continue;
            }
        }
    }
    
    return true;
}