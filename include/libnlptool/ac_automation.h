
#ifndef AC_AUTOMATION_H
#define AC_AUTOMATION_H

#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

#include "node.h"

using namespace std;

class Automation {
public:
    /**
     * 根节点
     */
    Node* root;

    /**
     * 用于存储所所有尾节点
     */
    vector<Node*> instances;

public:
    Automation();
    ~Automation();

    /**
     * 将字符串拆分成数组
     *
     * @param current
     * @param wordLength
     * @param characters
     */
    void splitWord(const string& word, int& wordLength, vector<string>& characters);

    /**
     * 获取当前节点的下一节点
     *
     * @param current    当前节点
     * @param character  键值
     * @return
     */
    Node* getNext(Node* current, string& character);

    /**
     * 添加字典
     *
     * @param word
     */
    void add(const string& word);

    /**
     * 创建字典
     */
    void build();

    /**
     * 匹配 词典中任何一个词汇匹配成功都会返回
     *
     * @param buf
     * @return
     */
    bool match(const string& buf);

    /**
     * 返回所有命中的节点信息
     *
     * @param buf
     */
    void search(const string& buf, map<string, Node*>& nodes);

    /**
     * 打印字典
     */
    void print();
};

#endif  // AC_AUTOMATION_H
