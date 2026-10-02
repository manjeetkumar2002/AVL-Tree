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

Node * deleteToAVL(Node * root,int key){
    if(!root) return nullptr;

    if(key<root->data){
        root->left = deleteToAVL(root->left,key);
    }
    else if(key>root->data){
        root->right = deleteToAVL(root->right,key);
    }
    else{
        // no children exist
        if(!root->left and !root->right){
            delete root;
            return nullptr;
        }
        // one children exist
        else if(!root->left and root->right){
            Node * temp = root->right;
            delete root;
            return temp;
        }
        else if(root->left and !root->right){
            Node * temp = root->left;
            delete root;
            return temp;
        }
        else{
             // both child exist
            // find the inorder successor
            Node * succ = findInorderSuccessor(root->right);
            root->data = succ->data;
            root->right = deleteToAVL(root->right,succ->data);
        }
       
    }

    root->height = 1+max(getHeight(root->left),getHeight(root->right));

    int balance = getBalance(root);

    if(balance>1){
        // LL Case
        if(getBalance(root->left)>=0){
            return rightRotation(root);
        }
        // LR case
        else{
            root->left = leftRotation(root->left);
            return rightRotation(root);
        }
    }
    else if(balance<-1){
        // RR case
        if(getBalance(root->right)<=0){
            return leftRotation(root);
        }
        // RL case
        else{
            root->right = rightRotation(root->right);
            return leftRotation(root);
        }
    }
    else{
        return root;
    }
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

int getHeight(Node * root){
    if(!root) return 0;

    return root->height;
}

int getBalance(Node* root){
    return getHeight(root->left)-getHeight(root->right);
}

Node * findInorderSuccessor(Node * root){
    Node * curr = root;

    while(curr->left){
        curr=curr->left;
    }

    return curr;
}