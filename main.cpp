#include<iostream>
#include<string>
using namespace std;
struct Book {
    int id;
	string title;
	string author;
	string genre;
	int year;
	int copies_availible;
    Book(int id, string title, string author, string genre, int copies) {
        this->id = id;
        this->title = title;
        this->author = author;
        this->genre = genre;
        this->copies_availible = copies;
    }
};
class AVLNode {
public:
    Book data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(Book b) : data(b), left(nullptr), right(nullptr), height(1) {}
};

// ====================== AVL TREE CLASS ======================
class AVLTree {
private:
    AVLNode* root;

    // Get height
    int getHeight(AVLNode* node) {
        if (!node) return 0;
        else
            return node->height;
    }

    // Balance Factor
    int getBalance(AVLNode* node) {
        if (!node) return 0;
        return getHeight(node->left) - getHeight(node->right);
    }

    // Right Rotate
    AVLNode* rightRotate(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;

        return x;
    }

    // Left Rotate
    AVLNode* leftRotate(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
        y->height = max(getHeight(y->left), getHeight(y->right)) + 1;

        return y;
    }

    // Insert Helper
    AVLNode* insertNode(AVLNode* node, Book book) {
        if (!node) return new AVLNode(book);

        if (book.id < node->data.id)
            node->left = insertNode(node->left, book);
        else if (book.id > node->data.id)
            node->right = insertNode(node->right, book);
        else
            return node; // Duplicate IDs not allowed

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balance = getBalance(node);

        // Left Left
        if (balance > 1 && book.id < node->left->data.id)
            return rightRotate(node);

        // Right Right
        if (balance < -1 && book.id > node->right->data.id)
            return leftRotate(node);

        // Left Right
        if (balance > 1 && book.id > node->left->data.id) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Right Left
        if (balance < -1 && book.id < node->right->data.id) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }

    // In-order Traversal
    void inorder(AVLNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data.id << " | " << node->data.title << " | "
            << node->data.author << " | " << node->data.genre << endl;
        inorder(node->right);
    }

public:
    AVLTree() : root(nullptr) {}

    void insert(Book book) {
        root = insertNode(root, book);
    }

    void display() {
        inorder(root);
    }
};

// ====================== MAIN ======================
int main() {
    AVLTree library;

    library.insert(Book(3, "The Alchemist", "Paulo Coelho", "Fiction",20));
    library.insert(Book(1, "Clean Code", "Robert Martin", "Programming",10));
    library.insert(Book(5, "Atomic Habits", "James Clear", "Self-help",50));
    library.insert(Book(4, "1984", "George Orwell", "Dystopia",7));

    cout << "Books in library (In-order traversal):\n";
    library.display();

    return 0;
}
