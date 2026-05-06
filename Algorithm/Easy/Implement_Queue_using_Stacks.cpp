//
// Created by jungk on 26. 4. 14..
//

#include <stack>

using namespace std;

class MyQueue_mine {
    stack<int> left;
    stack<int> right;
public:
    MyQueue_mine() {

    }

    void push(int x) {
        left.push(x);
    }

    int pop() {
        while(left.size() > 1)
        {
            right.push(left.top());
            left.pop();
        }

        int value =  left.top();
        left.pop();

        while(right.size() > 0)
        {
            left.push(right.top());
            right.pop();
        }

        return value;
    }

    int peek() {
        while(left.size() > 1)
        {
            right.push(left.top());
            left.pop();
        }

        int value =  left.top();

        while(right.size() > 0)
        {
            left.push(right.top());
            right.pop();
        }

        return value;
    }

    bool empty() {
        return left.empty();
    }
};

// left에서 항상 right로 옮겼다가 다시 left로 되돌리는 동작 생략
// in_stack에서 쌓고 out_stack에서 뒤집고, out_stack이 없을때만 뒤집는 것이 포인트
class MyQueue {
    stack<int> in_stack;
    stack<int> out_stack;

    // left에서 right로 데이터를 옮기는 내부 헬퍼 함수
    void move() {
        if (out_stack.empty()) {
            while (!in_stack.empty()) {
                out_stack.push(in_stack.top());
                in_stack.pop();
            }
        }
    }

public:
    MyQueue() {}

    void push(int x) {
        in_stack.push(x);
    }

    int pop() {
        move(); // out_stack이 비어있을 때만 데이터를 옮김
        int val = out_stack.top();
        out_stack.pop();
        return val;
    }

    int peek() {
        move();
        return out_stack.top();
    }

    bool empty() {
        return in_stack.empty() && out_stack.empty();
    }
};

int main()
{
    MyQueue* obj1 = new MyQueue();
    obj1->push(1);
    obj1->push(2);
    int param_3 = obj1->peek();
    int param_2 = obj1->pop();
    bool param_4 = obj1->empty();

    return 0;
}