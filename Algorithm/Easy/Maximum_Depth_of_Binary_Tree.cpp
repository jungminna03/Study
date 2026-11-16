//
// Created by jungk on 26. 7. 8..
//

#include <iostream>

using namespace std;

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Solution {
public:
    // 이진 트리의 최대 깊이(루트에서 가장 먼 리프까지의 노드 수)를 반환한다.
    // 트리가 비어 있으면 0.
    int maxDepthPrev(TreeNode* root) {
        if (root == nullptr) return 0;

        int left = maxDepth(root->left);
        int right = maxDepth(root->right);

        return left > right ? ++left : ++right; //return max(left, right) + 1;
    }

    int maxDepth(TreeNode* root) {
        if (root == nullptr) return 0;
        return max(maxDepthPrev(root->left), maxDepthPrev(root->right)) + 1;
    }
};

int main()
{
    Solution s;

    // Example 1: root = [3,9,20,null,null,15,7] -> 3
    TreeNode* root1 = new TreeNode(3,
        new TreeNode(9),
        new TreeNode(20, new TreeNode(15), new TreeNode(7)));

    // Example 2: root = [1,null,2] -> 2
    TreeNode* root2 = new TreeNode(1, nullptr, new TreeNode(2));

    auto res = s.maxDepth(root1); // expected: 3
    auto res2 = s.maxDepth(root2); // expected: 2

    return 0;
}
