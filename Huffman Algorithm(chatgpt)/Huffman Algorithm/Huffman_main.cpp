#include <iostream>
#include <unordered_map>
#include <queue>
#include <string>

using namespace std;

// ��������������
struct Node {
    char data;           // �洢�ַ�
    int frequency;       // �ַ�Ƶ��
    Node* left;          // ������
    Node* right;         // ������

    Node(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

// ���ڱȽϽ���Ƶ�ʣ��������ȼ�����
struct Compare {
    bool operator()(Node* left, Node* right) {
        return left->frequency > right->frequency;
    }
};

// ������������
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

// �ݹ����ɹ���������
void generateHuffmanCodes(Node* root, const string& currentCode, unordered_map<char, string>& codes) {
    if (root) {
        if (root->data != '\0') {
            codes[root->data] = currentCode;
        }
        generateHuffmanCodes(root->left, currentCode + "0", codes);
        generateHuffmanCodes(root->right, currentCode + "1", codes);
    }
}

// ʹ�ù���������ѹ���ı�
string compress(const string& text, const unordered_map<char, string>& codes) {
    string compressedText;
    for (char c : text) {
        compressedText += codes.at(c);
    }
    return compressedText;
}

// ʹ�ù����������ѹ���ı�
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
    cout << "�������ĵ�����: ";
    cin >> text;
    // ͳ���ַ�Ƶ��
    unordered_map<char, int> frequencies;
    for (char c : text) {
        frequencies[c]++;
    }

    // ������������
    Node* huffmanTree = buildHuffmanTree(frequencies);

    // ���ɹ���������
    unordered_map<char, string> huffmanCodes;
    generateHuffmanCodes(huffmanTree, "", huffmanCodes);

    // ѹ���ı�
    string compressedText = compress(text, huffmanCodes);
    cout << "Compressed Text: " << compressedText << endl;

    // ��ѹ���ı�
    string decompressedText = decompress(compressedText, huffmanTree);
    cout << "Decompressed Text: " << decompressedText << endl;

    return 0;
}
