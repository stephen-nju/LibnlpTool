
// 字典树
// Created by 18073701 on 2011/3/18.
//

#ifndef AC_AUTOMATION_NODE_H
#define AC_AUTOMATION_NODE_H

#include <iostream>
#include <map>
#include <string>

using namespace std;

class Node {
public:
    /**
     * 字
     */
    string word;

    /**
     * 下一节点
     */
    map<string, Node*> next;

    /**
     * 失配指针
     */
    Node* fail;

    /**
     * 是否匹配，即是否为根节点
     */
    bool matched;

    /**
     * 命中的词频
     */
    int repeats;

    /**
     * 字长
     * 注意: 非字符长
     */
    int wordLength;

    /**
     * 第一次出现位置
     */
    int index;

public:
    Node() : word(""), fail(0), matched(false), repeats(0), wordLength(0), index(-1){};
};

#endif  // AC_AUTOMATION_NODE_H
