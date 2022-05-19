#ifndef LEET_CODE_H
#define LEET_CODE_H
#include <cstdio>
#include <string>

using namespace std;
namespace leetcode {

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    int minDistance(string word1, string word2);
    // 正则表达式匹配
    bool isMatch(string s, string p);
    //二叉树最大直径
    int diameterOfBinaryTree(TreeNode* root);

    void quickSort(int arr[], int length);

private:
    void quickSort(int arr[], int left, int right);
};

}  // namespace leetcode

#endif  // leetcode_h