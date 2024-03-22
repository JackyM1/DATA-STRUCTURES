#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

// Function to create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

// Function to insert a node into BST
struct Node* insert(struct Node* root, int data) {
    if (root == NULL)
        return newNode(data);
    if (data < root->data)
        root->left = insert(root->left, data);
    else if (data > root->data)
        root->right = insert(root->right, data);
    return root;
}

// Function to delete a node from BST
struct Node* deleteNode(struct Node* root, int key) {
    if (root == NULL)
        return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        struct Node* temp = root->right;
        while (temp->left != NULL)
            temp = temp->left;
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to find height of BST
int height(struct Node* root) {
    if (root == NULL)
        return -1;
    else {
        int leftHeight = height(root->left);
        int rightHeight = height(root->right);
        if (leftHeight > rightHeight)
            return leftHeight + 1;
        else
            return rightHeight + 1;
    }
}

// Function to print level and height of any node in BST
void printLevelHeight(struct Node* root, int key, int level) {
    if (root == NULL) {
        printf("Node not found in the BST.\n");
        return;
    }
    if (root->data == key) {
        printf("Level of node %d is: %d\n", key, level);
        printf("Height of node %d is: %d\n", key, height(root));
    }
    else if (key < root->data)
        printLevelHeight(root->left, key, level + 1);
    else
        printLevelHeight(root->right, key, level + 1);
}

// Function to print in-order traversal of BST
void inorder(struct Node* root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%d ", root->data);
        inorder(root->right);
    }
}

int main() {
    int arr[] = {30, 20, 40, 10, 25, 35, 45, 5, 15};
    int n = sizeof(arr) / sizeof(arr[0]);
    struct Node* root = NULL;

    // Create BST
    for (int i = 0; i < n; i++)
        root = insert(root, arr[i]);

    printf("In-order traversal of BST: ");
    inorder(root);
    printf("\n");

    // Delete node with value 20
    int keyToDelete = 20;
    root = deleteNode(root, keyToDelete);
    printf("In-order traversal after deleting node %d: ", keyToDelete);
    inorder(root);
    printf("\n");

    // Print height of BST
    printf("Height of BST: %d\n", height(root));

    // Print level and height of node with value 30
    int keyToSearch = 30;
    printLevelHeight(root, keyToSearch, 0);

    return 0;
}
