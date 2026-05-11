//
// Created by jungk on 26. 5. 11.
//

#include <set>
#include <stack>
using namespace std;

class MinStack {
public:
    stack<int> stk;

    void push(int val) {
        stk.push(val);

    }

    void pop() {

        stk.pop();
    }

    int top() {
        return stk.top();
    }

    int getMin() {
        return 0;
    }
};

int main()
{
    MinStack minStack;
    minStack.push(-2);
    minStack.push(0);
    minStack.push(-3);
    auto res1 = minStack.getMin(); // return -3
    minStack.pop();
    auto res2 = minStack.top();    // return 0
    auto res3 = minStack.getMin(); // return -2

    return 0;
}