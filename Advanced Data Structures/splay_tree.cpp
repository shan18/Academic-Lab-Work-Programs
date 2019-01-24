#include <bits/stdc++.h>
using namespace std;


struct Node {
    int key;
    struct Node *left, *right;
};

/* Create a new node */
struct Node *new_node(int key) {
    struct Node *temp = new Node;
    temp->key = key;
    temp->left = temp->right = NULL;
    return temp;
}

struct Node *right_rotate(struct Node *x) {
    struct Node *y = x->left;
    x->left = y->right;
    y->right = x;
    return y;
}

struct Node *left_rotate(struct Node *x) {
    struct Node *y = x->right;
    x->right = y->left;
    y->left = x;
    return y;
}
 
struct Node *splay(struct Node *root, int key) {
    if (root == NULL || root->key == key)
        return root;

    if (root->key > key) {
        if (root->left == NULL) return root;

        if (root->left->key > key) {
            root->left->left = splay(root->left->left, key);
            root = right_rotate(root); 
        }
        else if (root->left->key < key) {
            root->left->right = splay(root->left->right, key);
            if (root->left->right != NULL) 
                root->left = left_rotate(root->left); 
        }
        return (root->left == NULL)? root: right_rotate(root); 
    } else {
        if (root->right == NULL) return root; 

        if (root->right->key > key) {
            root->right->left = splay(root->right->left, key);
            if (root->right->left != NULL)
                root->right = right_rotate(root->right);
        }
        else if (root->right->key < key) {
            root->right->right = splay(root->right->right, key);
            root = left_rotate(root);
        }

        return (root->right == NULL) ? root: left_rotate(root);
    }
}

struct Node *search(struct Node *root, int key) { 
    return splay(root, key);
}

struct Node *insert(struct Node *root, int k) {
    if (root == NULL) return new_node(k); 

    root = splay(root, k);

    if (root->key == k) return root; 
  
    struct Node *node  = new_node(k); 
  
    if (root->key > k) { 
        node->right = root; 
        node->left = root->left; 
        root->left = NULL; 
    } else { 
        node->left = root; 
        node->right = root->right; 
        root->right = NULL; 
    } 
  
    return node;
}

struct Node* delete_key(struct Node *root, int key) {
    if (!root)
        return NULL;

    struct Node *temp;
    root = splay(root, key);

    if (key != root->key)
        return root;

    if (!root->left) { 
        temp = root; 
        root = root->right; 
    } else { 
        temp = root;
        root = splay(root->left, key);
        root->right = temp->right; 
    }

    free(temp);
    return root; 
      
}

void in_order(struct Node *root) {
    if (root != NULL) {
        in_order(root->left);
        cout << root->key << " ";
        in_order(root->right);
    }
}

int main() {
    struct Node *root = new_node(100);
    root->left = new_node(50);
    root->right = new_node(200);
    root->left->left = new_node(40);
    root->left->left->left = new_node(30);
    root->left->left->left->left = new_node(20);

    root = search(root, 50);
    cout << "In order traversal of the searched Splay tree is \n";
    in_order(root);
    cout << endl;

    root = insert(root, 25);
    cout << "In order traversal of the inserted Splay tree is \n";
    in_order(root);
    cout << endl;

    root = delete_key(root, 40);
    cout << "In order traversal of the deleted Splay tree is \n";
    in_order(root);
    cout << endl;

    return 0;
}
