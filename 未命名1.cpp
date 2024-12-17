#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <cmath>

using namespace std;

// ������Ķ���
class Complex {
public:
    double real;  // ʵ��
    double imag;  // �鲿
    Complex(double r = 0, double i = 0) : real(r), imag(i) {}

    // ���㸴����ģ
    double modulus() const {
        return sqrt(real * real + imag * imag);
    }

    // ����==����������ڱȽ����������Ƿ���ȣ�ʵ�����鲿����ͬ��
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }
};

// �������������ĺ��������������㷨��
void swapComplex(Complex& a, Complex& b) {
    Complex temp = a;
    a = b;
    b = temp;
}

// ���������Ը�����ģΪ��׼��������ģ��ͬ������£���ʵ��Ϊ��׼��
void bubbleSort(vector<Complex>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            double mod1 = vec[j].modulus();
            double mod2 = vec[j + 1].modulus();
            if (mod1 > mod2 || (mod1 == mod2 && vec[j].real > vec[j + 1].real)) {
                swapComplex(vec[j], vec[j + 1]);
            }
        }
    }
}

// �鲢�����������������
void merge(vector<Complex>& vec, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<Complex> L(n1), R(n2);
    for (int i = 0; i < n1; ++i)
        L[i] = vec[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = vec[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        double mod1 = L[i].modulus();
        double mod2 = R[j].modulus();
        if (mod1 < mod2 || (mod1 == mod2 && L[i].real < R[j].real)) {
            vec[k] = L[i];
            ++i;
        }
        else {
            vec[k] = R[j];
            ++j;
        }
        ++k;
    }

    while (i < n1) {
        vec[k] = L[i];
        ++i;
        ++k;
    }

    while (j < n2) {
        vec[k] = R[j];
        ++j;
        ++k;
    }
}

// �鲢�����Ը�����ģΪ��׼��������ģ��ͬ������£���ʵ��Ϊ��׼��
void mergeSort(vector<Complex>& vec, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vec, left, mid);
        mergeSort(vec, mid + 1, right);
        merge(vec, left, mid, right);
    }
}

// ��������ĸ������������ظ��
vector<Complex> generateRandomComplexVector(int size) {
    vector<Complex> result;
    srand(static_cast<unsigned int>(time(NULL)));
    for (int i = 0; i < size; ++i) {
        double realPart = static_cast<double>(rand()) / RAND_MAX * 10 - 5;  // ���ɷ�Χ��[-5, 5]��ʵ��
        double imagPart = static_cast<double>(rand()) / RAND_MAX * 10 - 5;  // ���ɷ�Χ��[-5, 5]���鲿
        result.push_back(Complex(realPart, imagPart));
    }
    return result;
}

// ����������������ң�
void shuffleVector(vector<Complex>& vec) {
    int n = vec.size();
    for (int i = 0; i < n - 1; ++i) {
        int j = i + rand() % (n - i);
        swapComplex(vec[i], vec[j]);
    }
}

// ���Ҹ�����ʵ�����鲿����ͬ�����ҵ����ص�������û�ҵ�����vec.end()
vector<Complex>::const_iterator findComplex(const vector<Complex>& vec, const Complex& target) {
    return find(vec.begin(), vec.end(), target);
}

// ���븴����������
void insertComplex(vector<Complex>& vec, const Complex& num) {
    vec.push_back(num);
}

// ɾ��������ʵ�����鲿����ͬ���������Ƿ�ɾ���ɹ�
bool deleteComplex(vector<Complex>& vec, const Complex& target) {
    vector<Complex>::const_iterator it = findComplex(vec, target);
    if (it!= vec.end()) {
        // ��const_iteratorת��Ϊiterator���ͣ���Ϊerase����Ҫ���const�ĵ�����
        vector<Complex>::iterator nonConstIt = const_cast<vector<Complex>::iterator>(it);
        vec.erase(nonConstIt);
        return true;
    }
    return false;
}

// Ψһ��������ȥ���ظ�Ԫ�أ�
struct ComplexCompare {
    bool operator()(const Complex& a, const Complex& b) const {
        return a.modulus() < b.modulus() || (a.modulus() == b.modulus() && a.real < b.real);
    }
};
void uniqueVector(vector<Complex>& vec) {
    sort(vec.begin(), vec.end(), ComplexCompare());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
}

// ��������㷨�����ҳ�ģ����[m1, m2) ������Ԫ�أ��������һ������������Ϊ����ֵ
vector<Complex> rangeSearch(const vector<Complex>& vec, double m1, double m2) {
    vector<Complex> result;
    for (vector<Complex>::const_iterator it = vec.begin(); it!= vec.end(); ++it) {
        double mod = it->modulus();
        if (mod >= m1 && mod < m2) {
            result.push_back(*it);
        }
    }
    return result;
}

// ���Ժ������Ƚ���������͹鲢�����Ч��
void testSortEfficiency(vector<Complex>& vec) {
    vector<Complex> copy1 = vec;
    vector<Complex> copy2 = vec;
    clock_t start, end;

    // ������������
    start = clock();
    bubbleSort(copy1);
    end = clock();
    cout << "Bubble Sort Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl;

    // ���Թ鲢����
    start = clock();
    mergeSort(copy2, 0, copy2.size() - 1);
    end = clock();
    cout << "Merge Sort Time: " << double(end - start) / CLOCKS_PER_SEC << " seconds" << endl;
}

int main() {
    // ��������ĸ�������
    vector<Complex> complexVec = generateRandomComplexVector(10);

    // ���Ҳ�������
    vector<Complex> shuffledVec = complexVec;
    shuffleVector(shuffledVec);
    cout << "Shuffled Vector: ";
    for (vector<Complex>::const_iterator it = shuffledVec.begin(); it!= shuffledVec.end(); ++it) {
        cout << "(" << it->real << ", " << it->imag << ") ";
    }
    cout << endl;

    // ���Ҳ�������
    Complex target(complexVec[3].real, complexVec[3].imag);
    vector<Complex>::const_iterator it = findComplex(complexVec, target);
    if (it!= complexVec.end()) {
        cout << "Found: (" << it->real << ", " << it->imag << ")" << endl;
    }
    else {
        cout << "Not found" << endl;
    }

    // �����������
    Complex newComplex(2.5, 3.5);
    insertComplex(complexVec, newComplex);
    cout << "After Insert: ";
    for (vector<Complex>::const_iterator it = complexVec.begin(); it!= complexVec.end(); ++it) {
        cout << "(" << it->real << ", " << it->imag << ") ";
    }
    cout << endl;

    // ɾ����������
    bool deleted = deleteComplex(complexVec, target);
    if (deleted) {
        cout << "Deleted successfully" << endl;
    }
    else {
        cout << "Deletion failed" << endl;
    }
    cout << "After Delete: ";
    for (vector<Complex>::const_iterator it = complexVec.begin(); it!= complexVec.end(); ++it) {
        cout << "(" << it->real << ", " << it->imag << ") ";
    }
    cout << endl;

    // Ψһ����������
    vector<Complex> withDuplicates = generateRandomComplexVector(15);
    uniqueVector(withDuplicates);
    cout << "After Unique: ";
    for (vector<Complex>::const_iterator it = withDuplicates.begin(); it!= withDuplicates.end(); ++it) {
        cout << "(" << it->real << ", " << it->imag << ") ";
    }
    cout << endl;

    // ����Ч�ʲ��ԣ�˳�������
    vector<Complex> sortedVec = generateRandomComplexVector(10);
    sort(sortedVec.begin(), sortedVec.end(), ComplexCompare());
    cout << "Testing Sort Efficiency in Ordered Case:" << endl;
    testSortEfficiency(sortedVec);

    // ����Ч�ʲ��ԣ����������
    vector<Complex> disorderedVec = generateRandomComplexVector(10);
    cout << "Testing Sort Efficiency in Disordered Case:" << endl;
    testSortEfficiency(disorderedVec);

    // ����Ч�ʲ��ԣ����������
    vector<Complex> reversedVec = generateRandomComplexVector(10);
    sort(reversedVec.begin(), reversedVec.end(), ComplexCompare());
    cout << "Testing Sort Efficiency in Reversed Case:" << endl;
    testSortEfficiency(reversedVec);

    // ������Ҳ���
    vector<Complex> rangeTestVec = generateRandomComplexVector(20);
    sort(rangeTestVec.begin(), rangeTestVec.end(), ComplexCompare());
    double m1 = 1.0, m2 = 3.0;
    vector<Complex> resultRange = rangeSearch(rangeTestVec, m1, m2);
    cout << "Range Search Result: ";
    for (vector<Component>::const_iterator it = resultRange.begin(); it!= resultRange.end(); ++it) {
        cout << "(" << it->real << ", " << it->imag << ") ";
    }
    cout << endl;

    return 0;
}
