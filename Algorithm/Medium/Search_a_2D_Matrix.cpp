//
// Created by jungk on 26. 5. 12.
//

#include <vector>
using namespace std;

class Solution {
public:
    bool searchMatrix(vector<vector<int>>& matrix, int target) {
        int arrLeft = 0;
        int arrRight = matrix.size() - 1;

        while (arrLeft <= arrRight)
        {
            int arrMid = arrLeft + (arrRight - arrLeft) / 2;

            if (matrix[arrMid][0] <= target && matrix[arrMid][matrix[arrMid].size() - 1] >= target)
            {
                int left = 0;
                int right = matrix[arrMid].size() - 1;

                while (left <= right)
                {
                    int mid = left + (right - left) / 2;

                    if (matrix[arrMid][mid] == target)
                    {
                        return true;
                    }

                    if (matrix[arrMid][mid] < target)
                    {
                        left = mid + 1;
                    }
                    else if (matrix[arrMid][mid] > target)
                    {
                        right = mid - 1;
                    }
                }

                return false;
            }

            if (matrix[arrMid][0] <= target)
            {
                arrLeft = arrMid + 1;
            }
            else if (matrix[arrMid][matrix[arrMid].size() - 1] >= target)
            {
                arrRight = arrMid - 1;
            }
        }

        return false;
    }
};

int main()
{
    Solution s;

    vector<vector<int>> matrix = {{1,3,5,7},{10,11,16,20},{23,30,34,60}};
    vector<vector<int>> matrix1 = {{1}};

    auto result1 = s.searchMatrix(matrix,3);
    auto result2 = s.searchMatrix(matrix1,1);

    return 0;
}
