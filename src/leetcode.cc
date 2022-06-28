
#include "leetcode.h"

namespace leetcode {

int Solution::minDistance(string word1, string word2) {
    int m = word1.size();
    int n = word2.size();
    // int dp[m + 1][n + 1];

    vector<vector<int>> dp;
    for (int i = 0; i <= m; i++) {
        dp[i][0] = i;
    }
    for (int j = 0; j <= n; j++) {
        dp[0][j] = j;
    }
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = std::min(dp[i - 1][j] + 1, std::min(dp[i][j - 1] + 1, dp[i - 1][j - 1] + 1));
            }
        }
    }
    return dp[m][n];
}
bool Solution::isMatch(string s, string p) {
    int m = s.size();
    int n = p.size();
    // bool dp[m][n];
    vector<vector<bool>> dp;
    dp[0][0] = true;
    // 初始化数组
    for (int i = 1; i < m + 1; i++) {
        dp[i][0] = false;
    }
    for (int j = 1; j < n + 1; j++) {
        if (p[j - 1] == '*') {
            dp[0][j] = dp[0][j - 2];
        } else {
            dp[0][j] = false;
        }
    }

    for (int i = 1; i < m + 1; i++) {
        for (int j = 1; j < n + 1; j++) {
            if (s[i - 1] == p[j - 1] || p[j - 1] == '.') {
                dp[i][j] = dp[i - 1][j - 1];
            } else if (p[j - 1] == '*') {
                if (s[i - 1] == p[j - 2] || p[j - 2] == '.') {
                    dp[i][j] = dp[i][j - 2] || dp[i - 1][j - 2] || dp[i - 1][j];
                } else {
                    dp[i][j] = dp[i][j - 2];
                }
            } else {
                dp[i][j] = false;
            }
        }
    }

    return dp[m][n];
}

int maxDepth(TreeNode* root, int* diameter) {
    if (root == nullptr)
        return 0;

    int left_depth = maxDepth(root->left, diameter);
    int right_depth = maxDepth(root->right, diameter);
    *diameter = std::max(right_depth + left_depth, *diameter);
    return std::max(left_depth, right_depth) + 1;
}

int Solution::diameterOfBinaryTree(TreeNode* root) {
    int diameter = 0;
    if (root == nullptr) {
        return 0;
    }
    maxDepth(root, &diameter);
    return diameter;
}

// 快排
inline void swap(int arr[], int x, int y) {
    int temp;
    temp = arr[x];
    arr[x] = arr[y];
    arr[y] = temp;
}

int partition(int arr[], int left, int right) {
    // 随机选择pivot
    int pivot_index = left + rand() % (right - left + 1);
    int pivot = arr[pivot_index];
    swap(arr, pivot_index, right);
    int low = 0, high = right - 1;
    while (low <= high) {
        if (arr[low] <= pivot) {
            low++;
        } else if (arr[high] > pivot) {
            high--;
        } else {
            swap(arr, low++, high--);
        }
        /* code */
    }
    // low指针和high指针重合后,再进行一次比较,此时交换low和right
    swap(arr, low, right);
    return low;
}

void Solution::quickSort(int arr[], int left, int right) {
    if (left >= right) {
        return;
    }
    int pivot_index = partition(arr, left, right);
    Solution::quickSort(arr, left, pivot_index - 1);
    Solution::quickSort(arr, pivot_index + 1, right);
}

void Solution::quickSort(int arr[], int length) {
    if (length <= 1) {
        return;
    };
    Solution::quickSort(arr, 0, length - 1);
}

int64_t Solution::intPartition() {
    // dp[i][j][k] i个数总和为j并且第i位数字为k的方案数目
    int64_t dp[2022 + 1][10 + 1] = {0};
    dp[0][0] = 1;
    for (int i = 1; i <= 2022; i++) {
        for (int j = 2022; j >= i; j--) {
            for (int k = 1; k <= 10; k++) {
                dp[j][k] += dp[j - i][k - 1];
            }
        }
    }
    return dp[2022][10];
}

}  // namespace leetcode