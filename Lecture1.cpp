// insertion in avl tree
#include<iostream>
using namespace std;
class Node{
    public:
    int data;
    Node *left,*right;
    int height;
    Node(int value){
        data = value;
        left = right = nullptr;
        height = 1;
    }
};
int getHeight(Node * root){
    if(!root) return 0;

    return root->height;
}

int getBalance(Node* root){
    return getHeight(root->left)-getHeight(root->right);
}

Node * leftRotation(Node * root){
    Node * child = root->right;
    Node * childLeft = child->left;

    // update the pointer 
    child->left = root;
    root->right = childLeft;

    // update the heights
    root->height = 1 + max(getHeight(root->left),getHeight(root->right));
    child->height = 1 + max(getHeight(child->left),getHeight(child->right));

    return child;
}

Node * rightRotation(Node * root){
    Node * child = root->left;
    Node * childRight = child->right;

    // update pointers
    child->right = root;
    root->left = childRight;

    // update the root and child height
    root->height = 1 + max(getHeight(root->left),getHeight(root->right));
    child->height = 1 + max(getHeight(child->left),getHeight(child->right));

    return child;
}

Node * insertToAVL(Node * root,int& key){
    if(!root){
        return new Node(key);
    }

    if(key<root->data){
        root->left = insertToAVL(root->left,key);
    }
    else if(key>root->data){
        root->right= insertToAVL(root->right,key);
    }
    else{
        // duplicate node not allowed
        return root;
    }

    // update the height
    root->height = 1 + max(getHeight(root->left),getHeight(root->right));

    // check the balance factor
    int balance = getBalance(root);

    // LL case
    if(balance>1 && key < root->left->data){
        // right rotation of the root
        return rightRotation(root);
    }
    // RR case
    else if(balance<-1 && key > root->right->data){
        return leftRotation(root);
    }
    // LR case
    else if(balance>1 && key > root->left->data){
        // right rotation of root child
        root->left = leftRotation(root->left);
        return rightRotation(root);
    }
    // RL case
    else if(balance<-1 && key<root->right->data){
        root->right = rightRotation(root->right);
        return leftRotation(root);
    }
    else{
        return root;
    }
}