//https://contest.yandex.ru/contest/32613/run-report/61100252/
#include <iostream>
#include <queue>

struct Node_BS {
    int Key;
    Node_BS* Left;
    Node_BS* Right;

    explicit Node_BS(int key) : Key(key), Left(nullptr), Right(nullptr) {}
};

void add_bst(int key, Node_BS* &node) {
    std::queue<Node_BS*> stack_node;
    stack_node.push(node);
    while (!stack_node.empty()) {
        Node_BS* node_ = stack_node.front();
        stack_node.pop();
        if (key < node_->Key) {
            if (node_->Left) {
                stack_node.push(node_->Left);
            } else {
                node_->Left = new Node_BS(key);
            }
        } else {
            if (node_->Right) {
                stack_node.push(node_->Right);
            } else {
                node_->Right = new Node_BS(key);
            }
        }
    }
}

int max_depth(Node_BS* node) {
    if (node == nullptr) return 0;
    return std::max(max_depth(node->Left), max_depth(node->Right)) + 1;
}

void FreeTree(Node_BS* node) {
    std::queue <Node_BS*> queue_node;
    queue_node.push(node);
    while (!queue_node.empty()) {
        Node_BS *aboba = queue_node.front();
        queue_node.pop();
        if (aboba != nullptr) {
            queue_node.push(aboba->Left);
            queue_node.push(aboba->Right);
            delete aboba;
        }
    }
}

struct Node_Treap {
    int Key;
    int Priority;
    Node_Treap* Left;
    Node_Treap* Right;
    
    explicit Node_Treap(int key, int priority) : Key(key), Priority(priority), Left(nullptr), Right(nullptr) {}
};

std::pair<Node_Treap*, Node_Treap*> Split(Node_Treap* node, int key) {
    if (node == nullptr) return {nullptr, nullptr};
    if (key < node->Key) {
        std::pair<Node_Treap*, Node_Treap*> p = Split(node->Left, key);
        node->Left = p.second;
        return {p.first, node};
    } else {
        auto [first, second] = Split(node->Right, key);
        node->Right = first;
        return {node, second};
    }
}

Node_Treap* Merge(Node_Treap* left, Node_Treap* right) {
    if (left == nullptr || right == nullptr) {
        return left == nullptr ? right: left;
    }
    if (left->Priority > right->Priority) {
        left->Right = Merge(left->Right, right);
        return left;
    } else {
        right->Left = Merge(left, right->Left);
        return right;
    }
}

void add_treap(Node_Treap* &treap, int key, int priority) {
    auto* new_node = new Node_Treap(key, priority);
    auto [first, second] = Split(treap, key);
    treap = Merge(Merge(first, new_node), second);
}

int max_depth(Node_Treap* node) {
    if (node == nullptr) return 0;
    return std::max(max_depth(node->Left), max_depth(node->Right)) + 1;
}

void FreeTree(Node_Treap* node) {
    std::queue <Node_Treap*> stack_node;
    stack_node.push(node);
    while (!stack_node.empty()) {
        Node_Treap *aboba = stack_node.front();
        stack_node.pop();
        if (aboba != nullptr) {
            stack_node.push(aboba->Left);
            stack_node.push(aboba->Right);
            delete aboba;
        }
    }
}


int main() {
    int n;
    int x, y;
    std::cin >> n;
    std::cin >> x >> y;
    auto* bst = new Node_BS(x);
    auto* treap = new Node_Treap(x, y);

    for (int i = 0; i < n - 1; i++) {
        std::cin >> x >> y;
        add_bst(x, bst);
        add_treap(treap, x, y);
    }
    std::cout << abs(max_depth(bst) - max_depth(treap)) << std::endl;
    FreeTree(bst);
    FreeTree(treap);
    return 0;
}
