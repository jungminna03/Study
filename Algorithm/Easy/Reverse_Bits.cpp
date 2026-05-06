//
// Created by jungk on 26. 4. 2..
//

class Solution {
public:
    // 가장 "빠르게" 뒤집기 = 새로 배열 만들어서 뒤에서부터 집어넣기
    int reverseBits(int n) {
        int res = 0;
        for (int i = 0; i < 32; ++i)
        {
            res <<= 1;
            res |= n & 1;
            n >>= 1;
        }

        return res;
    }
};

int main()
{
    Solution s;

    auto result = s.reverseBits(43261596);
    auto result2 = s.reverseBits(2147483644);

    return 0;
}