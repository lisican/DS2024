#include <iostream>
#include <ctime>
#include <cstdlib>

// 交换两个元素的值
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// 起泡排序
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// 插入排序
void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// 选择排序
void selectionSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        if (minIndex!= i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

// 归并操作，用于归并排序
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int* L = new int[n1];
    int* R = new int[n2];
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int j = 0; j < n2; j++) {
        R[j] = arr[mid + 1 + j];
    }
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        }
        else {
            arr[k++] = R[j++];
        }
    }
    while (i < n1) {
        arr[k++] = L[i++];
    }
    while (j < n2) {
        arr[k++] = R[j++];
    }
    delete[] L;
    delete[] R;
}

// 归并排序
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// 快速排序划分函数
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// 快速排序
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// 堆调整函数，用于堆排序
void heapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;
    if (l < n && arr[l] > arr[largest]) {
        largest = l;
    }
    if (r < n && arr[r] > arr[largest]) {
        largest = r;
    }
    if (largest!= i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

// 堆排序
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// 打印数组
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// 测试函数，测试每种排序算法在不同序列下的性能
void testSortingAlgorithms() {
    const int size = 10000;  // 可以调整测试数据规模
    int arr[size];

    // 顺序序列测试
    for (int i = 0; i < size; i++) {
        arr[i] = i;
    }
    int arrCopy1[size];
    int arrCopy2[size];
    int arrCopy3[size];
    int arrCopy4[size];
    int arrCopy5[size];
    int arrCopy6[size];
    for (int i = 0; i < size; i++) {
        arrCopy1[i] = arrCopy2[i] = arrCopy3[i] = arrCopy4[i] = arrCopy5[i] = arrCopy6[i] = arr[i];
    }
    clock_t start, end;

    start = clock();
    bubbleSort(arrCopy1, size);
    end = clock();
    std::cout << "顺序序列 起泡排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;

    start = clock();
    insertionSort(arrCopy2, size);
    end = clock();
    std::cout << "顺序序列 插入排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;

    start = clock();
    selectionSort(arrCopy3, size);
    end = clock();
    std::cout << "顺序序列 选择排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;

    start = clock();
    mergeSort(arrCopy4, 0, size - 1);
    end = clock();
    std::cout << "顺序序列 归并排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;

    start = clock();
    quickSort(arrCopy5, 0, size - 1);
    end = clock();
    std::cout << "顺序序列 快速排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;

    start = clock();
    heapSort(arrCopy6, size);
    end = clock();
    std::cout << "顺序序列 堆排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;

    // 逆序序列测试
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
    for (int i = 0; i < size; i++) {
        arrCopy1[i] = arrCopy2[i] = arrCopy3[i] = arrCopy4[i] = arrCopy5[i] = arrCopy6[i] = arr[i];
    }
    start = clock();
    bubbleSort(arrCopy1, size);
    end = clock();
    std::cout << "逆序序列 起泡排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;

    start = clock();
    insertionSort(arrCopy2, size);
    end = clock();
    std::cout << "逆序序列 插入排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;

    start = clock();
    selectionSort(arrCopy3, size);
    end = clock();
    std::cout << "逆序序列 选择排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;

    start = clock();
    mergeSort(arrCopy4, 0, size - 1);
    end = clock();
    std::cout << "逆序序列 归并排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;

    start = clock();
    quickSort(arrCopy5, 0, size - 1);
    end = clock();
    std::cout << "逆序序列 快速排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;

    start = clock();
    heapSort(arrCopy6, size);
    end = clock();
    std::cout << "逆序序列 堆排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;

    // 随机序列测试
    std::srand((unsigned int)time(NULL));  // 使用当前时间作为随机数种子
    for (int i = 0; i < size; i++) {
        arr[i] = std::rand();
    }
    for (int i = 0; i < size; i++) {
        arrCopy1[i] = arrCopy2[i] = arrCopy3[i] = arrCopy4[i] = arrCopy5[i] = arrCopy6[i] = arr[i];
    }
    start = clock();
    bubbleSort(arrCopy1, size);
    end = clock();
    std::cout << "随机序列 起泡排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;

    start = clock();
    insertionSort(arrCopy2, size);
    end = clock();
    std::cout << "随机序列 插入排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;

    start = clock();
    selectionSort(arrCopy3, size);
    end = clock();
    std::cout << "随机序列 选择排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;

    start = clock();
    mergeSort(arrCopy4, 0, size - 1);
    end = clock();
    std::cout << "随机序列 归并排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;

    start = clock();
    quickSort(arrCopy5, 0, size - 1);
    end = clock();
    std::cout << "随机序列 快速排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;

    start = clock();
    heapSort(arrCopy6, size);
    end = clock();
    std::cout << "随机序列 堆排序时间: " << (double)(end - start) / CLOCKS_PER_SEC << " 秒" << std::endl;
}

int main() {
    testSortingAlgorithms();
    return 0;
}
