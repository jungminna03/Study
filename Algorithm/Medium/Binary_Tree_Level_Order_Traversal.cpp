//
// Created by jungk on 26. 7. 9..
//

#include <iostream>
#include <vector>

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
    // 이진 트리를 레벨 순서(위 -> 아래, 각 레벨은 왼쪽 -> 오른쪽)로 순회한 결과를 반환한다.
    // 트리가 비어 있으면 빈 벡터.
    vector<vector<int>> levelOrderPrev(TreeNode* root) {
        if (root == nullptr) return {};

        vector<vector<int>> result;

        queue<TreeNode*> q;
        q.push(root);

        while (!q.empty()) {
            vector<TreeNode*> nodes;
            vector<int> res;
            while (!q.empty()) {
                nodes.push_back(q.front());
                q.pop();
            }

            for (auto node : nodes) {
                res.push_back(node->val);
            }

            for (auto node : nodes) {
                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }

            result.push_back(res);
        }

        return result;
    }

    vector<vector<int>> levelOrder(TreeNode* root) {
        if (root == nullptr) return {};
        vector<vector<int>> result;
        queue<TreeNode*> q {{root}};

        while (!q.empty()) {
            int levelSize = static_cast<int>(q.size());
            result.emplace_back();
            vector<int>& res = result.back();
            res.reserve(levelSize);

            for (int i = 0; i < levelSize; ++i) {
                auto node = q.front();
                res.push_back(node->val);
                q.pop();
                if (node->left != nullptr) q.push(node->left);
                if (node->right != nullptr) q.push(node->right);
            }
        }

        return result;
    }
};

int main()
{
    Solution s;

    // Example 1: root = [3,9,20,null,null,15,7] -> [[3],[9,20],[15,7]]
    TreeNode* root1 = new TreeNode(3,new TreeNode(9),
        new TreeNode(20, new TreeNode(15), new TreeNode(7)));

    // Example 2: root = [1] -> [[1]]
    TreeNode* root2 = new TreeNode(1);

    // Example 3: root = [] -> []
    TreeNode* root3 = nullptr;

    auto res = s.levelOrder(root1);  // expected: [[3],[9,20],[15,7]]
    auto res2 = s.levelOrder(root2); // expected: [[1]]
    auto res3 = s.levelOrder(root3); // expected: []



    return 0;
}
