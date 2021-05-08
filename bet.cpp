#include "bet.h"
#include<iostream>

using namespace std;

////////////////////////////////////
//        PUBLIC FUNCTIONS        //
////////////////////////////////////

// default constructor
BET::BET() {
    root = NULL;
}

// destructor
BET::~BET() {
    makeEmpty();
}

// checks to see if the expression tree is empty
bool BET::isEmpty() const {
    return root==NULL;
}

// empties expression tree
void BET::makeEmpty() {
    
    // pre: empty/non-empty tree
    //
    // post: empty tree

    if(root!=NULL)
        makeEmpty(root);
}

// inserts a prefix operator into the tree
void BET::insertPrefixOperator(char token) {
    
    // pre: empty/non-empty tree with an operator root
    //
    // post: non-empty tree with the root as the new operator: char token

    // assign values to new BETPtr w/ op type and symbol
    BETPtr newPre = new BinaryNode;
    newPre -> info.whichType = OPERATOR;
    newPre -> info.theContent.opsymbol = token;

    // prefix using private var stack<BETPtr> s
    newPre->left = s.top();  s.pop();
    newPre->right = s.top(); s.pop();

    s.push(newPre);
    root = s.top();
}

// inserts a postfix operator into the tree
void BET::insertPostfixOperator(char token) {
    
    // pre: empty/non-empty tree with an operator root
    //
    // post: non-empty tree with the root as the new operator: char token

    // assign values to new BETPtr w/ op type and symbol
    BETPtr newPost = new BinaryNode;
    newPost -> info.whichType = OPERATOR;
    newPost -> info.theContent.opsymbol = token;

    // postfix using private var stack<BETPtr> s
    newPost->right = s.top(); s.pop();
    newPost->left = s.top();  s.pop();

    s.push(newPost);
    root = s.top();
}

// inserts an operand into the tree
void BET::insertOperand(char token) {
    
    // pre: empty/non-empty tree
    //
    // post: non-empty tree with inserted operand: char token

    BETPtr newNum = new BinaryNode;
    newNum -> left = NULL;
    newNum -> right = NULL;
    newNum -> info.whichType = OPERAND;
    newNum -> info.theContent.variable = token;

    s.push(newNum);
}

// public call of preorder to print the expression (prefix)
void BET::preorder() const {
    
    // post: calls private preorder function to print
   
    if(isEmpty())
        cout<<"Empty tree";
    else
        preorder(root);
}

// public call of inorder to print the expression (infix)
void BET::inorder() const {
    
    // post: calls private inorder function to print
    
    if(isEmpty())
        cout<<"Empty tree";
    else
        inorder(root);
}

// public call of postorder to print the expression (postfix)
void BET::postorder() const {
    
    // post: calls private postorder function to print
    
    if(isEmpty())
        cout<<"Empty tree";
    else
        postorder(root);
}

/////////////////////////////////////
//        PRIVATE FUNCTIONS        //
/////////////////////////////////////

// private function makeEmpty; recursively makes tree empty
void BET::makeEmpty(BETPtr& t) const {

    // post: recursively most left and right and remove elements leaf by leaf
    
    if(t!=NULL) {
        makeEmpty(t->left);
        makeEmpty(t->right);
        delete t;
        t = NULL;
    }
}

// private function preorder; recursively prints expression (prefix)
void BET::preorder(BETPtr t) const {
    
    // post: function prints preorder traversal for public preorder
    
    if(t!=NULL) {
        if((t->info.whichType)==OPERAND)
            cout<<t->info.theContent.variable<<" ";
        else
            cout<<t->info.theContent.opsymbol<<" ";
        preorder(t->left);
        preorder(t->right);
    }
    
}

// private function inorder; recursively prints expression (infix)
void BET::inorder(BETPtr t) const {
    
    // post: function prints inorder traversal for public inorder
    
    if(t!=NULL) {
        if(t->left!=NULL)
            cout<<"( ";
        inorder(t->left);
        if((t->info.whichType)==OPERAND)
            cout<<t->info.theContent.variable<<" ";
        else
            cout<<t->info.theContent.opsymbol<<" ";
        inorder(t->right);
        if(t->right!=NULL)
            cout<<") ";
    }
}

// private function postorder; recursively prints expression (postfix)
void BET::postorder(BETPtr t) const {
    
    // post: function prints postorder traversal for public postorder

    if(t!=NULL) {
        postorder(t->left);
        postorder(t->right);
        if((t->info.whichType)==OPERAND)
            cout<<t->info.theContent.variable<<" ";
        else
            cout<<t->info.theContent.opsymbol<<" ";
    }
}