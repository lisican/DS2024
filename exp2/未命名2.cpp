#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// 实现计算矩形最大面积的函数
int largestRectangleArea(const std::vector<int>& heights) {
    int max_area = 0;
    std::stack<int> stack;
    // 在原高度数组前后各添加一个高度为0的元素，方便计算
    std::vector<int> extended_heights = heights;
    extended_heights.insert(extended_heights.begin(), 0);
    extended_heights.push_back(0);

    for (size_t i = 0; i < extended_heights.size(); ++i) {
        while (!stack.empty() && extended_heights[stack.top()] > extended_heights[i]) {
            int popped_index = stack.top();
            stack.pop();
            int width = i - stack.top() - 1;
            int area = extended_heights[popped_index] * width;
            max_area = std::max(max_area, area);
        }
        stack.push(i);
    }

    return max_area;
}

// 随机生成10组数据进行测试
int main() {
    // 设置随机数生成器的种子，基于当前时间
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    for (int i = 0; i < 10; ++i) {
        // 随机生成高度数组的长度，范围在1到100000之间
        int length = std::rand() % (100 - 1 + 1) + 1;
        std::vector<int> heights(length);

        // 随机生成每个柱子的高度，范围在0到10000之间
        for (int j = 0; j < length; j++) {
            heights[j] = std::time(NULL);
        }

        int result = largestRectangleArea(heights);
        std::cout << "测试第" << i + 1 << "组数据：输入 heights = [";
    for (std::vector<int>::size_type j = 0; j < heights.size(); ++j) {
    int value = heights[j];
    std::cout << value << ", ";
    }  
    std::cout << "]，输出面积 = " << result << std::endl;
    }

    return 0;
}
