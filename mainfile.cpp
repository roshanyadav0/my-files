#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

class MaxHeap {
public:
    MaxHeap() : heap() {}

    void insert(int value);
    void printHeap();
    void buildMaxHeap();

private:
    std::vector<int> heap;

    void heapify(int index);
};

void MaxHeap::insert(int value) {
    heap.push_back(value);
    int currentIndex = heap.size() - 1;

    while (currentIndex > 0) {
        int parentIndex = (currentIndex - 1) / 2;
        if (heap[currentIndex] <= heap[parentIndex]) {
            break;
        }
        std::swap(heap[currentIndex], heap[parentIndex]);
        currentIndex = parentIndex;
    }
}

void MaxHeap::heapify(int index) {
    int largest = index;
    int leftChild = 2 * index + 1;
    int rightChild = 2 * index + 2;

    if (leftChild < heap.size() && heap[leftChild] > heap[largest]) {
        largest = leftChild;
    }
    if (rightChild < heap.size() && heap[rightChild] > heap[largest]) {
        largest = rightChild;
    }

    if (largest != index) {
        std::swap(heap[index], heap[largest]);
        heapify(largest);
    }
}

void MaxHeap::printHeap() {
    for (std::vector<int>::const_iterator it = heap.begin(); it != heap.end(); ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';
}

void MaxHeap::buildMaxHeap() {
    for (int i = heap.size() / 2 - 1; i >= 0; --i) {
        heapify(i);
        std::cout << "Step " << heap.size() / 2 - i << ":\n";
        printHeap();
        std::cout << "\n";
    }
}

// ... (rest of the code)

// Binary Tree Node
struct TreeNode {
    int value;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int val) : value(val), left(NULL), right(NULL) {}
};

// Function to insert a value into a binary tree
void insertIntoBinaryTree(TreeNode *&root, int value) {
    if (!root) {
        root = new TreeNode(value);
        return;
    }
    if (value < root->value) {
        insertIntoBinaryTree(root->left, value);
    } else {
        insertIntoBinaryTree(root->right, value);
    }
}

// Function to print binary tree in-order
void printBinaryTreeInOrder(TreeNode *root) {
    if (!root) {
        return;
    }
    printBinaryTreeInOrder(root->left);
    std::cout << root->value << ' ';
    printBinaryTreeInOrder(root->right);
}

int main() {
    std::srand(std::time(NULL)); // Seed the random number generator

    int n;
    std::cout << "Enter the number of elements: ";
    std::cin >> n;

    MaxHeap maxHeap;
    TreeNode *binaryTreeRoot = NULL;

    std::cout << "Randomly generated " << n << " elements:\n";
    for (int i = 0; i < n; ++i) {
        int value = std::rand() % 100; // Generate random value between 0 and 99
        maxHeap.insert(value);
        insertIntoBinaryTree(binaryTreeRoot, value);
        std::cout << value << ' ';
    }
    std::cout << '\n';

    int choice;
    std::cout << "Choose what to view:\n";
    std::cout << "1. Max Heap\n";
    std::cout << "2. Binary Tree\n";
    std::cout << "3. Both\n";
    std::cin >> choice;

    if (choice == 1) {
        std::cout << "Building Max Heap...\n";
        maxHeap.buildMaxHeap();
        std::cout << "Max Heap: ";
        maxHeap.printHeap();
    } else if (choice == 2) {
        std::cout << "Binary Tree In-order: ";
        printBinaryTreeInOrder(binaryTreeRoot);
        std::cout << '\n';
    } else if (choice == 3) {
        std::cout << "Building Max Heap...\n";
        maxHeap.buildMaxHeap();
        std::cout << "Max Heap: ";
        maxHeap.printHeap();

        std::cout << "Binary Tree In-order: ";
        printBinaryTreeInOrder(binaryTreeRoot);
        std::cout << '\n';
    } else {
        std::cout << "Invalid choice\n";
    }

    // Cleanup binary tree
    // You can add a cleanup function to deallocate memory

    return 0;
}

