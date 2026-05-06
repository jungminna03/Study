//
// Created by jungk on 26. 4. 21..
//

class Solution {
public:
    int badVersion;

    void setBadVersion(int version)
    {
        badVersion = version;
    }

    bool isBadVersion(int version)
    {
        return badVersion >= version;
    }

    int firstBadVersion(int n) {
        if (n <= 1) return n;

        int left = 1, right = n;
        int mid;

        while (left < right)
        {
            mid = (left + right) / 2;

            if (left == mid)
                return mid;

                if (isBadVersion(mid)) left = mid;
            else right = mid;
        }

        return left;
    }
};

int main()
{
    Solution s;

    s.setBadVersion(4);
    auto res = s.firstBadVersion(5);

    s.setBadVersion(1);
    auto res2 = s.firstBadVersion(1);

    return 0;
}