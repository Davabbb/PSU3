//https://contest.yandex.ru/contest/32613/run-report/60822104/

#include <iostream>
#include <queue>
#include <deque>

struct Node {
    int Key;
    Node* Left;
    Node* Right;

    explicit Node(int key) : Key(key), Left(nullptr), Right(nullptr) {}
};

void add(int key, Node* node) {
    std::queue<Node*> stack_node;
    stack_node.push(node);
    while (!stack_node.empty()) {
        Node* node_ = stack_node.front();
        if (key < node_->Key) {
            if (node_->Left) {
                stack_node.pop();
                stack_node.push(node_->Left);
            } else {
                node_->Left = new Node(key);
                stack_node.pop();
            }
        } else {
            stack_node.pop();
            if (node_->Right) {
                stack_node.push(node_->Right);
            } else {
                node_->Right = new Node(key);
            }
        }
    }
}

void print(Node* node) {
    std::deque<Node*> stack_node;
    do {
        while (node != nullptr) {
            stack_node.push_back(node);
            node = node->Left;
        }
        if (!stack_node.empty()) {
            node = stack_node.back();
            stack_node.pop_back();
            std::cout << node->Key << std::endl;
            node = node->Right;
        }
    } while (!stack_node.empty() || node != nullptr);
}

void FreeTree(Node* node) {
    std::queue <Node*> stack_node;
    stack_node.push(node);
    while (!stack_node.empty()) {
        Node *aboba = stack_node.front();
        stack_node.pop();
        if (aboba != nullptr) {
            stack_node.push(aboba->Left);
            stack_node.push(aboba->Right);
            delete aboba;
        }
    }
}

int main() {
    int n = 0, num;
    std::cin >> n >> num;
    Node* root = new Node(num);
    for (int i = 0; i < n - 1; i++) {
        std::cin >> num;
        add(num, root);
    }
    print(root);
    FreeTree(root);
    return 0;
}
