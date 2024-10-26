#include <iostream>
#include <stack>
#include <cctype>

// 定义运算符优先级
int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

// 执行算术运算
int applyOp(int a, int b, char op) {
    switch (op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/': return a / b;
    }
    return 0;
}

// 实现栈数据结构（整数栈示例）
class IntStack {
private:
    int* data;
    int topIndex;
    int capacity;

public:
    IntStack(int initialCapacity = 10) {
        data = new int[initialCapacity];
        topIndex = -1;
        capacity = initialCapacity;
    }

    ~IntStack() {
        delete[] data;
    }

    void push(int value) {
        if (topIndex == capacity - 1) {
            int* newData = new int[capacity * 2];
            for (int i = 0; i <= topIndex; i++) {
                newData[i] = data[i];
            }
            delete[] data;
            data = newData;
            capacity *= 2;
        }
        data[++topIndex] = value;
    }

    int pop() {
        if (isEmpty()) {
            std::cerr << "Stack is empty." << std::endl;
            return -1;
        }
        return data[topIndex--];
    }

    int top() const {
        if (isEmpty()) {
            std::cerr << "Please enter a valid expression." << std::endl;
            return -1;
        }
        return data[topIndex];
    }

    bool isEmpty() const {
        return topIndex == -1;
    }
};

// 评估字符串表达式
int evaluateStringExpression(std::string expression) {
    IntStack values;
    IntStack ops;

    for (int i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ')
            continue;
        else if (isdigit(expression[i])) {
            int val = 0;
            while (i < expression.length() && isdigit(expression[i])) {
                val = (val * 10) + (expression[i] - '0');
                i++;
            }
            values.push(val);
            i--;
        } else if (expression[i] == '(') {
            ops.push(expression[i]);
        } else if (expression[i] == ')') {
            while (!ops.isEmpty() && ops.top()!= '(') {
                int val2 = values.pop();
                int val1 = values.pop();
                char op = ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            if (!ops.isEmpty())
                ops.pop();
        } else {
            while (!ops.isEmpty() && precedence(ops.top()) >= precedence(expression[i])) {
                int val2 = values.pop();
                int val1 = values.pop();
                char op = ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(expression[i]);
        }
    }

    while (!ops.isEmpty()) {
    int val2 = values.pop();
    int val1 = values.pop();
    char op = ops.pop();
    values.push(applyOp(val1, val2, op));
    }

    return values.top();
}

int main() {

    std::string expression1 = "2 + 3";
    int result1 = evaluateStringExpression(expression1);
    std::cout << "Expression: " << expression1 << ", Result: " << result1 << std::endl;


    std::string expression2 = "(2 + 3) * 4";
    int result2 = evaluateStringExpression(expression2);
    std::cout << "Expression: " << expression2 << ", Result: " << result2 << std::endl;


    std::string expression3 = "2 * 3 + 4 / 2";
    int result3 = evaluateStringExpression(expression3);
    std::cout << "Expression: " << expression3 << ", Result: " << result3 << std::endl;

 

    std::string expression4 = "((2 + 3) * 4 - 5) / 3";
    int result4 = evaluateStringExpression(expression4);
    std::cout << "Expression: " << expression4 << ", Result: " << result4 << std::endl;

    return 0;
}
