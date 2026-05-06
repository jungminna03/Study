//
// Created by jungk on 26. 3. 22..
//

#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    // O(n)
    int missingNumberPrev(vector<int>& nums) {
        unordered_map <int, int> mp;

        for (int i = 0; i < nums.size(); i++)
            mp[nums[i]] = 1;

        for (int i = 1; i <= nums.size(); i++)
        {
            if (mp.find(i) == mp.end())
                return i;
        }

        return 0;
    }

    // 가우스 공식 n * (n + 1) / 2로 1~n까지의 연속적인 수의 덧샘을 구할 수 있음

    // 응용
    // 1. m * n * (n + 1) / 2  =>  10, 20, 30등 연속적으로 증가하는 값의 덧샘 구하기
    // 2. (x, y)를 1차원 배열에 저장할때 사용
    // 등등 너무 많음,,,
    int missingNumber(vector<int>& nums) {
        int n = nums.size();
        int nSum = n * (n + 1) / 2;

        int allSum = 0;
        for (int i = 0; i < n; i++)
            allSum += nums[i];

        return nSum - allSum;
    }

    // XOR : A xor A = 0, A xor 0 = A
    // 중간에 A xor B가 계산된 값은 무시하고 교환법칙과 결합법칙을 이용하여 결론을 도출해낸다는 접근법 필요
    int missingNumberXOR(vector<int>& nums) {
        int n = nums.size();
        int res = n; // n은 루프에서 인덱스로 안 나오니까 미리 넣어줍니다.

        for (int i = 0; i < n; i++) {
            res ^= i;        // 0부터 n-1까지 XOR
            res ^= nums[i];  // nums[0]부터 nums[n-1]까지 XOR
        }

        // 결과적으로 (0 ^ 1 ^ ... ^ n) ^ (nums[0] ^ nums[1] ^ ... ^ nums[n-1]) 이 됩니다.
        return res;
    }
};

int main()
{
    Solution s;
    auto nums = vector<int>{3, 0, 1};
    auto nums2 = vector<int>{0, 1};
    auto nums3 = vector<int>{9,6,4,2,3,5,7,0,1};

    auto result1 = s.missingNumber(nums);
    auto result2 = s.missingNumber(nums2);
    auto result3 = s.missingNumber(nums3);

    return 0;
}