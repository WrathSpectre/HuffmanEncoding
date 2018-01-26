#ifndef HUFFMAN_ENCODING_H
#define HUFFMAN_ENCODING_H

#include <map>
#include <queue>
#include <vector>
#include <iostream>

class HuffmanEncoding {
    struct Node {
        char data;
        unsigned frequency;
        Node* left;
        Node* right;

        Node(const char data, const unsigned frequency) : data(data),
            frequency(frequency), left(nullptr), right(nullptr) {}
    };

    struct compare {
        bool operator() (Node* left, Node* right) {
            return (left->frequency > right->frequency);
        }
    };

    std::map<char, unsigned> frequency;
    std::priority_queue<Node*, std::vector<Node*>, compare> heap;

public:
    HuffmanEncoding(const std::string userString) {
        for(const char &Ch: userString)
            frequency[Ch]++;
    }

    void HuffmanCode() {
        Node *left, *right, *top;

        std::map<char, unsigned>::const_iterator itr;

        for(itr=frequency.begin(); itr != frequency.end(); ++itr)
            heap.push(new Node(itr->first, itr->second));

          while(heap.size() != 1) {
              left = heap.top();
              heap.pop();

              right = heap.top();
              heap.pop();

              top = new Node('$', left->frequency + right->frequency);

              top->left = left;
              top->right = right;

              heap.push(top);
          }

          printCodes(heap.top(), "");
    }

    void printCodes(Node* root, std::string str) {
        if(root == nullptr)
            return;

        else
          std::cout<<root->data<< ": "<<str<<std::endl;

        printCodes(root->left, str + "0");
        printCodes(root->right, str + "1");
};

#endif
