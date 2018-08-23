#include <bits/stdc++.h>
using namespace std;


struct Node {
    int data;
    struct Node *left;
    struct Node *right;
};

/* Create a new node */
struct Node *new_node(int key) {
    struct Node *temp = new Node;
    temp->data = key;
    temp->left = temp->right = NULL;
    return temp;
}


/* Inorder Traversal */
void inorder_traversal(struct Node *node) {
    if(!node)
        return;
        
    inorder_traversal(node->left);
    cout << node->data << " ";
    inorder_traversal(node->right);
}

/* Search a node in BST */
struct Node *search(struct Node *root, int key) {
    if(root == NULL || root->left->data == key || root->right->data == key)
        return root;
    
    if(key < root->data)
        return search(root->left, key);
    
    return search(root->right, key);
}

/* Insert a new node in BST */
struct Node* insert(struct Node *node, int key) {
    if(node == NULL)
        return new_node(key);
    
    if(key < node->data)
        node->left = insert(node->left, key);
    else if(key > node->data)
        node->right = insert(node->right, key);
    
    return node;
}

struct Node *min_val_node(struct Node *node) {
    struct Node *temp = node;
    while(node->left != NULL)
        node = node->left;
    return node;
}

/* Delete a node from BST */
struct Node *delete_node(struct Node *root, int key) {
    if(root == NULL)
        return root;
    
    if(key < root->data)
        root->left = delete_node(root->left, key);
    else if(key > root->data)
        root->right = delete_node(root->right, key);
    else {
        if(root->left == NULL) {
            struct Node *temp = root->right;
            free(root);
            return temp;
        } else if(root -> right == NULL) {
            struct Node *temp = root->left;
            free(root);
            return temp;
        }
        
        struct Node *temp = min_val_node(root->right);
        root->data = temp->data;
        return delete_node(root->right, temp->data);
    }
}

int main() {
    
    struct Node *root = NULL;

    int ch = 1;

    while(ch > 0 && ch < 4) {
        cout << "1.Insert\n2.Search\n3.Delete\n4.Exit" << endl;
        cin >> ch;

        if(ch == 1) {
            int i_key;
            cout << "\nNumber to be inserted: ";
            cin >> i_key;
            if(!root)
                root = insert(root, i_key);
            else
                insert(root, i_key);
            cout << "\nInorder Traversal after inserting " << i_key << ": ";
            inorder_traversal(root);
            cout << endl << endl;
        } else if(ch == 2) {
            int s_key;
            cout << "\nNumber to be searched: ";
            cin >> s_key;
            struct Node *found = search(root, s_key);
            if(!found)
                cout << "Not Found\n" << endl;
            else
                cout << "Parent of the number: " << found->data << endl;
        } else if(ch == 3) {
            int d_key;
            cout << "\nNumber to be deleted ";
            cin >> d_key;
            delete_node(root, d_key);
            cout << "\nInorder Traversal after deleting " << d_key << ": ";
            inorder_traversal(root);
            cout << endl << endl;
        } else
            break;
    }
}

