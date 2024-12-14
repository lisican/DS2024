#include <iostream>
#include <ctime>
#include <cstdlib>

// ��������Ԫ�ص�ֵ
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// ��������
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// ��������
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

// ѡ������
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

// �鲢���������ڹ鲢����
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

// �鲢����
void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// �������򻮷ֺ���
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

// ��������
void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// �ѵ������������ڶ�����
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

// ������
void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// ��ӡ����
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

// ���Ժ���������ÿ�������㷨�ڲ�ͬ�����µ�����
void testSortingAlgorithms() {
    const int size = 10000;  // ���Ե����������ݹ�ģ
    int arr[size];

    // ˳�����в���
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
    std::cout << "˳������ ��������ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << std::endl;

    start = clock();
    insertionSort(arrCopy2, size);
    end = clock();
    std::cout << "˳������ ��������ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << std::endl;

    start = clock();
    selectionSort(arrCopy3, size);
    end = clock();
    std::cout << "˳������ ѡ������ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << std::endl;

    start = clock();
    mergeSort(arrCopy4, 0, size - 1);
    end = clock();
    std::cout << "˳������ �鲢����ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << std::endl;

    start = clock();
    quickSort(arrCopy5, 0, size - 1);
    end = clock();
    std::cout << "˳������ ��������ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << std::endl;

    start = clock();
    heapSort(arrCopy6, size);
    end = clock();
    std::cout << "˳������ ������ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << std::endl;

    // �������в���
    for (int i = 0; i < size; i++) {
        arr[i] = size - i;
    }
    for (int i = 0; i < size; i++) {
        arrCopy1[i] = arrCopy2[i] = arrCopy3[i] = arrCopy4[i] = arrCopy5[i] = arrCopy6[i] = arr[i];
    }
    start = clock();
    bubbleSort(arrCopy1, size);
    end = clock();
    std::cout << "�������� ��������ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << std::endl;

    start = clock();
    insertionSort(arrCopy2, size);
    end = clock();
    std::cout << "�������� ��������ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << std::endl;

    start = clock();
    selectionSort(arrCopy3, size);
    end = clock();
    std::cout << "�������� ѡ������ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << std::endl;

    start = clock();
    mergeSort(arrCopy4, 0, size - 1);
    end = clock();
    std::cout << "�������� �鲢����ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << std::endl;

    start = clock();
    quickSort(arrCopy5, 0, size - 1);
    end = clock();
    std::cout << "�������� ��������ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << std::endl;

    start = clock();
    heapSort(arrCopy6, size);
    end = clock();
    std::cout << "�������� ������ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << std::endl;

    // ������в���
    std::srand((unsigned int)time(NULL));  // ʹ�õ�ǰʱ����Ϊ���������
    for (int i = 0; i < size; i++) {
        arr[i] = std::rand();
    }
    for (int i = 0; i < size; i++) {
        arrCopy1[i] = arrCopy2[i] = arrCopy3[i] = arrCopy4[i] = arrCopy5[i] = arrCopy6[i] = arr[i];
    }
    start = clock();
    bubbleSort(arrCopy1, size);
    end = clock();
    std::cout << "������� ��������ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << std::endl;

    start = clock();
    insertionSort(arrCopy2, size);
    end = clock();
    std::cout << "������� ��������ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << std::endl;

    start = clock();
    selectionSort(arrCopy3, size);
    end = clock();
    std::cout << "������� ѡ������ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << std::endl;

    start = clock();
    mergeSort(arrCopy4, 0, size - 1);
    end = clock();
    std::cout << "������� �鲢����ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << std::endl;

    start = clock();
    quickSort(arrCopy5, 0, size - 1);
    end = clock();
    std::cout << "������� ��������ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << std::endl;

    start = clock();
    heapSort(arrCopy6, size);
    end = clock();
    std::cout << "������� ������ʱ��: " << (double)(end - start) / CLOCKS_PER_SEC << " ��" << std::endl;
}

int main() {
    testSortingAlgorithms();
    return 0;
}
