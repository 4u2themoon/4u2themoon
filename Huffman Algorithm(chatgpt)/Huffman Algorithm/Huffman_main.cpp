#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>

using namespace std;

// 定义哈夫曼树结点
struct Node {
    char data;           // 存储字符
    int frequency;       // 字符频率(权值)
    Node* left;          // 左子树
    Node* right;         // 右子树

    Node(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

// 用于比较结点的频率，构建优先级队列
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

// 构建哈夫曼树
Node* buildHuffmanTree(const unordered_map<char, int>& frequencies) {
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (const auto& entry : frequencies) {
        pq.push(new Node(entry.first, entry.second));
    }

    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* internalNode = new Node('\0', left->frequency + right->frequency);
        internalNode->left = left;
        internalNode->right = right;

        pq.push(internalNode);
    }

    return pq.top();
}

// 递归生成哈夫曼编码
void generateHuffmanCodes(Node* root, const string& currentCode, unordered_map<char, string>& codes) {
    if (root) {
        if (root->data != '\0') {
            codes[root->data] = currentCode;
        }
        generateHuffmanCodes(root->left, currentCode + "0", codes);
        generateHuffmanCodes(root->right, currentCode + "1", codes);
    }
}

// 使用哈夫曼编码压缩文本
string compress(const string& text, const unordered_map<char, string>& codes) {
    string compressedText;
    for (char c : text) {
        compressedText += codes.at(c);
    }
    return compressedText;
}

// 使用哈夫曼编码解压缩文本
string decompress(const string& compressedText, Node* root) {
    string decompressedText;
    Node* current = root;

    for (char bit : compressedText) {
        if (bit == '0') {
            current = current->left;
        }
        else {
            current = current->right;
        }

        if (current->data != '\0') {
            decompressedText += current->data;
            current = root;
        }
    }

    return decompressedText;
}

int main() {
    string text;
    cout << "请输入文档内容: ";
    cin >> text;
    // 统计字符频率
    unordered_map<char, int> frequencies;
    for (char c : text) {
        frequencies[c]++;
    }

    // 构建哈夫曼树
    Node* huffmanTree = buildHuffmanTree(frequencies);

    // 生成哈夫曼编码
    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(huffmanTree, "", huffmanCodes);

    // 压缩文本
    string compressedText = compress(text, huffmanCodes);
    cout << "Compressed Text: " << compressedText << endl;

    // 解压缩文本
    string decompressedText = decompress(compressedText, huffmanTree);
    cout << "Decompressed Text: " << decompressedText << endl;

    return 0;
}
