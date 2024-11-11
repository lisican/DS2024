#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <fstream>
#include <cctype>
#include <cstring>

typedef unsigned int Rank;

class Bitmap {
private:
    unsigned char* M;
    Rank N, _sz;
protected:
    void init(Rank n) {
        M = new unsigned char[N = (n + 7) / 8];
        memset(M, 0, N);
        _sz = 0;
    }
public:
    Bitmap(Rank n = 8) { init(n); }
    Bitmap(char* file, Rank n = 8) {
        init(n);
        FILE* fp = fopen(file, "r");
        fread(M, sizeof(char), N, fp);
        fclose(fp);
        for (Rank k = 0, _sz = 0; k < n; k++) _sz += test(k);
    }
    ~Bitmap() {
        delete[] M;
        M = NULL;
        _sz = 0;
    }
    Rank size() const {
        return _sz;
    }
    void set(Rank k) {
        expand(k);
        _sz++;
        M[k >> 3] |= (0x80 >> (k & 0x07));
    }
    void clear(Rank k) {
        expand(k);
        _sz--;
        M[k >> 3] &= ~(0x07 >> (k & 0x07));
    }
    bool test(Rank k) {
        expand(k);
        return M[k >> 3] & (0x80 >> (k & 0x07));
    }
    void dump(char* file) {
        FILE* fp = fopen(file, "w");
        fwrite(M, sizeof(char), N, fp);
        fclose(fp);
    }

   char*bits2string(Rank n) const {

    Bitmap temp = *this;

    temp.expand(n - 1);

    char* s = new char[n + 1];
    s[n] = '\0';
    for (Rank i = 0; i < n; i++) s[i] = temp.test(i)? '1' : '0';
    return s;
}

    void expand(Rank k) {
        if (k < 8 * N) return;
        Rank oldN = N;
        unsigned char* oldM = M;
        init(2 * k);
        memcpy(M, oldM, oldN);
        delete[] oldM;
    }
};
template <typename T>
struct BinTreeNode {
    T data;
    BinTreeNode<T>* left;
    BinTreeNode<T>* right;
    BinTreeNode(T d) : data(d), left(NULL), right(NULL) {}
};

template <typename T>
class BinTree {
private:
    BinTreeNode<T>* root;
public:
    BinTree() : root(NULL) {}
    ~BinTree() { clear(root); }

    void insert(T data) {
        if (root == NULL) {
            root = new BinTreeNode<T>(data);
        } else {
            insertHelper(root, data);
        }
    }

    void insertHelper(BinTreeNode<T>* node, T data) {
        if (data < node->data) {
            if (node->left == NULL) {
                node->left = new BinTreeNode<T>(data);
            } else {
                insertHelper(node->left, data);
            }
        } else {
            if (node->left == NULL) {
                node->right = new BinTreeNode<T>(data);
            } else {
                insertHelper(node->right, data);
            }
        }
    }

    void preorderTraversal() {
        preorderTraversalHelper(root);
        std::cout << std::endl;
    }

    void preorderTraversalHelper(BinTreeNode<T>* node) {
        if (node!= NULL) {
            std::cout << node->data << " ";
            preorderTraversalHelper(node->left);
            preorderTraversalHelper(node->right);
        }
    }

    void clear(BinTreeNode<T>* node) {
        if (node!= NULL) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }
};
struct HuffTreeNode {
    char data;
    int weight;
    HuffTreeNode* left;
    HuffTreeNode* right;
    HuffTreeNode(char d, int w) : data(d), weight(w), left(NULL), right(NULL) {}
};

struct HuffTreeNodeCompare {
    bool operator()(const HuffTreeNode* a, const HuffTreeNode* b) const {
        return a->weight > b->weight;
    }
};

class HuffTree {
private:
    HuffTreeNode* root;
public:
    HuffTree() : root(NULL) {}
    ~HuffTree() { clear(root); }

    void buildTree(const std::vector<int>& frequencies) {
        std::priority_queue<HuffTreeNode*, std::vector<HuffTreeNode*>, HuffTreeNodeCompare> pq;

        for (char i = 'a'; i <= 'z'; i++) {
            if (frequencies[i - 'a'] > 0) {
                pq.push(new HuffTreeNode(i, frequencies[i - 'a']));
            }
        }

        while (pq.size() > 1) {
            HuffTreeNode* left = pq.top();
            pq.pop();
            HuffTreeNode* right = pq.top();
            pq.pop();

            HuffTreeNode* newNode = new HuffTreeNode('\0', left->weight + right->weight);
            newNode->left = left;
            newNode->right = right;

            pq.push(newNode);
        }

        root = pq.top();
        pq.pop();
    }

    void clear(HuffTreeNode* node) {
        if (node!= NULL) {
            clear(node->left);
            clear(node->right);
            delete node;
        }
    }

    HuffTreeNode* getRoot() { return root; }
};

class HuffCode {
private:
    Bitmap code;
public:
    HuffCode() {}

    void setBit(Rank k) { code.set(k); }

    void clearBit(Rank k) { code.clear(k); }

    bool testBit(Rank k) { return code.test(k); }

    Rank size() { return code.size(); }

    char* bits2string() const {
        return code.bits2string(code.size());
    }
};

void huffmanEncoding(const std::string& text, HuffTree& huffTree, std::vector<HuffCode>& huffmanCodes) {
    HuffTreeNode* root = huffTree.getRoot();

    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        HuffCode code;
        HuffTreeNode* current = root;
        Rank bitIndex = 0;

        while (current!= NULL) {
            if (c < current->data) {
                current = current->left;
                code.setBit(bitIndex);
            } else {
                current = current->right;
                code.clearBit(bitIndex);
            }
            bitIndex++;
        }

        huffmanCodes.push_back(code);
    }
}

std::vector<int> countFrequencies(const std::string& text) {
    std::vector<int> frequencies(26, 0);

    for (size_t i = 0; i < text.length(); ++i) {
        char c = text[i];
        if (isalpha(c)) {
            frequencies[tolower(c) - 'a']++;
        }
    }

    return frequencies;
}
int main() {
    std::ifstream file("i_have_a_dream.txt");
    std::string text;
    std::string line;

    if (file.is_open()) {
        while (getline(file, line)) {
            text += line;
        }
        file.close();
    } else {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }

    std::vector<int> frequencies = countFrequencies(text);

    HuffTree huffTree;
    huffTree.buildTree(frequencies);

    std::vector<HuffCode> huffmanCodes;
    huffmanEncoding("dream", huffTree, huffmanCodes);

    for (size_t i = 0; i < huffmanCodes.size(); ++i) {
        const HuffCode& code = huffmanCodes[i];
        std::cout << code.bits2string() << " ";
    }
    std::cout << std::endl;

    return 0;
}
