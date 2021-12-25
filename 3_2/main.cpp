//https://contest.yandex.ru/contest/32613/run-report/62778957/

#include <iostream>

struct AVLNode {
    int Key;
    int Height;
    int Count;
    AVLNode* Left;
    AVLNode* Right;

    explicit AVLNode(int key) : Key(key), Height(1), Count(1), Left(nullptr), Right(nullptr) {}
};

int Height(AVLNode* node) {
    return node ? node->Height : 0;
}

int Count(AVLNode* node) {
    return node != nullptr ? node->Count : 0;
}

void FixHeight(AVLNode* node) {
    node->Height = std::max(Height(node->Left), Height(node->Right)) + 1;
}

void FixCount(AVLNode* node) {
    node->Count = Count(node->Left) + Count(node->Right) + 1;
}

int Balance(AVLNode* node) {
    if (!node) return 0;
    return Height(node->Right) - Height(node->Left);
}

AVLNode* RotateRight(AVLNode* root) {
    AVLNode* left = root->Left;
    root->Left = left->Right;
    left->Right = root;
    FixHeight(root);
    FixHeight(left);
    FixCount(root);
    FixCount(left);
    return left;
}

AVLNode* RotateLeft(AVLNode* root) {
    AVLNode* right = root->Right;
    root->Right = right->Left;
    right->Left = root;
    FixHeight(root);
    FixHeight(right);
    FixCount(root);
    FixCount(right);
    return right;
}

AVLNode* FixTree(AVLNode* node) {
    FixHeight(node);
    FixCount(node);
    if (Balance(node) == 2) {
        if (Balance(node->Right) < 0)
            node->Right = RotateRight(node->Right);
        return RotateLeft(node);
    } else if (Balance(node) == -2) {
        if (Balance(node->Left) > 0)
            node->Left = RotateLeft(node->Left);
        return RotateRight(node);
    }
    return node;
}

void Add(int key, AVLNode*& node) {
    if (!node) {
        node = new AVLNode(key);
        return;
    }
    if (node->Key < key) Add(key, node->Right);
    else Add(key, node->Left);
    node = FixTree(node);
}

AVLNode* FindMin(AVLNode* node) {
    return node->Left ? FindMin(node->Left) : node;
}

AVLNode* RemoveMin(AVLNode* node, AVLNode*& node1) {
    if (node->Left == nullptr) {
        node1 = node;
        return node->Right;
    }
    node->Left = RemoveMin(node->Left, node1);
    return FixTree(node);
}

AVLNode* Del(int key, AVLNode* node) {
    if (!node) return nullptr;
    if (node->Key < key)
        node->Right = Del(key, node->Right);
    else if (node->Key > key)
        node->Left = Del(key, node->Left);
    else {
        AVLNode* left = node->Left;
        AVLNode* right = node->Right;
        delete node;
        if (!right) return left;
        auto* min = new AVLNode(0);
        min->Right = RemoveMin(right, min);
        min->Left = left;
        return FixTree(min);
    }
    return FixTree(node);
}

int Statistics(AVLNode* node, int k) {
    int index = Count(node->Left);
    if (index == k) return node->Key;
    if (index > k) return Statistics(node->Left, k);
    return Statistics(node->Right, k - index - 1);
}

int main() {
    int n;
    int num, k;
    std::cin >> n;
    std::cin >> num >> k;
    std::cout << num << std::endl;
    auto* node = new AVLNode(num);

    for (int i = 0; i < n - 1; i++) {
        std::cin >> num >> k;
        if (num > 0) {
            Add(num, node);
        } else {
            node = Del(-num, node);
        }
        std::cout << Statistics(node, k) << std::endl;
    }
    return 0;
}
