//https://contest.yandex.ru/contest/32613/run-report/62443706/

#include <iostream>
#include <queue>

struct Node_BS {
    int Key;
    Node_BS* Left;
    Node_BS* Right;

    explicit Node_BS(int key) : Key(key), Left(nullptr), Right(nullptr) {}
};

void add_bst(int key, Node_BS* &node) {
    Node_BS* stack_node = node;
    while (stack_node) {
        Node_BS* node_ = stack_node;
        if (key < node_->Key) {
            if (node_->Left) {
                stack_node = node_->Left;
            } else {
                node_->Left = new Node_BS(key);
                stack_node = nullptr;
            }
        } else {
            if (node_->Right) {
                stack_node = node_->Right;
            } else {
                node_->Right = new Node_BS(key);
                stack_node = nullptr;
            }
        }
    }
}

int max_depth(Node_BS* node) {
    if (node == nullptr) return 0;
    return std::max(max_depth(node->Left), max_depth(node->Right)) + 1;
}

void FreeTree(Node_BS* node) {
    std::queue <Node_BS*> queue;
    queue.push(node);
    while (!queue.empty()) {
        Node_BS *aboba = queue.front();
        queue.pop();
        if (aboba != nullptr) {
            queue.push(aboba->Left);
            queue.push(aboba->Right);
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

std::pair<Node_Treap*, Node_Treap*> Split(Node_Treap* node, int key) {
    if (node == nullptr) return {nullptr, nullptr};
    if (node->Key < key) {
        Node_Treap *help = node;
        auto [first, second] = Split(node->Right, key);
        help->Right = first;
        return {help, second};
    } else {
        Node_Treap *help = node;
        auto [first, second] = Split(node->Left, key);
        help->Left = second;
        return {first, help};
    }
}

void add_treap(Node_Treap* &treap, int key, int priority) {
    if (!treap) {
        treap = new Node_Treap(key, priority);
        return;
    }
    if (treap->Priority < priority) {
        auto [first, second] = Split(treap, key);
        auto* new_node = new Node_Treap(key, priority);
        new_node->Left = first;
        new_node->Right = second;
        treap = new_node;
        return;
    }
    if (treap->Key <= key) add_treap(treap->Right, key, priority);
    else if (treap->Key > key) add_treap(treap->Left, key, priority);
}

int max_depth(Node_Treap* node) {
    if (node == nullptr) return 0;
    return std::max(max_depth(node->Left), max_depth(node->Right)) + 1;
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
