//
// Created by nyxrux62 on 26. 7. 6..
//

#include <queue>

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
    TreeNode* invertTreeRec(TreeNode* root) {
        if (root == nullptr) return root;

        auto temp = root->left;
        root->left = root->right;
        root->right = temp;

        invertTree(root->left);
        invertTree(root->right);

        return root;
    }

    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) return root;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            auto cur = q.front();
            q.pop();

            auto temp = cur->left;
            cur->left = cur->right;
            cur->right = temp;

            if (cur->left != nullptr) q.push(cur->left);
            if (cur->right != nullptr) q.push(cur->right);
        }

        return root;
    }
};

int main()
{
    Solution s;

    // Example 1: [4,2,7,1,3,6,9] -> [4,7,2,9,6,3,1]
    TreeNode *root1 = new TreeNode(4,
        new TreeNode(2, new TreeNode(1), new TreeNode(3)),
        new TreeNode(7, new TreeNode(6), new TreeNode(9)));

    // Example 2: [2,1,3] -> [2,3,1]
    TreeNode *root2 = new TreeNode(2, new TreeNode(1), new TreeNode(3));

    // Example 3: [] -> []
    TreeNode *root3 = nullptr;

    auto res1 = s.invertTree(root1);
    auto res2 = s.invertTree(root2);
    auto res3 = s.invertTree(root3);

    return 0;
}
