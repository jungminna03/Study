//
// Created by jungk on 26. 3. 23..
//

#include <algorithm>
#include <unordered_map>
#include <vector>
using namespace std;

class Solution {
public:
    bool containsDuplicate(vector<int>& nums) {
        unordered_map<int ,int> mp;

        for (int i = 0; i < nums.size(); i++)
        {
            if (mp.find(nums[i]) != mp.end())
                return true;
            else
                mp[nums[i]] = i;
        }

        return false;
    }

    // 메모리를 적게 먹음
    // unordered_map은 데이터가 파편화 되어있어서 캐시 히트가 잘 안 맞음
    // 그래서 for문을 돌아서 하나하나 순회해야할거면 vector가 성능상 유리함
    bool containsDuplicateBest(vector<int>& nums) {
        sort(nums.begin(),nums.end()); // 인트로 소트, 처음에는 퀵소트로 정렬하다가 최악의 경우의 수가 되면 힙소트로 변경, 데이터가 (보통) 16개 이하가 되면 삽입 정렬로 마무리.
        for(int i = 1; i<nums.size();i++){
            if(nums[i] == nums[i-1]){
                return true;
            }
        }
        return false;
    }
};

int main()
{
    Solution s;
    auto nums = vector<int>{1,2,3,1};
    auto nums2 = vector<int>{1,2,3,4};
    auto nums3 = vector<int>{1,1,1,3,3,4,3,2,4,2};

    auto res = s.containsDuplicate(nums);
    auto res2 = s.containsDuplicate(nums2);
    auto res3 = s.containsDuplicate(nums3);

    return 0;
}