#include <iostream>
#include <vector>
#include <stack>
#include <cstdlib>
#include <ctime>
#include <algorithm>

// ʵ�ּ�������������ĺ���
int largestRectangleArea(const std::vector<int>& heights) {
    int max_area = 0;
    std::stack<int> stack;
    // ��ԭ�߶�����ǰ������һ���߶�Ϊ0��Ԫ�أ��������
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

// �������10�����ݽ��в���
int main() {
    // ��������������������ӣ����ڵ�ǰʱ��
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    for (int i = 0; i < 10; ++i) {
        // ������ɸ߶�����ĳ��ȣ���Χ��1��100000֮��
        int length = std::rand() % (100 - 1 + 1) + 1;
        std::vector<int> heights(length);

        // �������ÿ�����ӵĸ߶ȣ���Χ��0��10000֮��
        for (int j = 0; j < length; j++) {
            heights[j] = std::time(NULL);
        }

        int result = largestRectangleArea(heights);
        std::cout << "���Ե�" << i + 1 << "�����ݣ����� heights = [";
    for (std::vector<int>::size_type j = 0; j < heights.size(); ++j) {
    int value = heights[j];
    std::cout << value << ", ";
    }  
    std::cout << "]�������� = " << result << std::endl;
    }

    return 0;
}
