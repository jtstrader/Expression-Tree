#include<iostream>
#include<string>
#include<algorithm>
#include<stack>

#include "bet.h"

using namespace std;

// functions
char menu(); // main menu
BET preTree(string s); // creates a tree from a prefix expression
BET inTree(string s); // creates a postfix expression from infix, then calls postTree()
BET postTree(string s); // creates a tree from a postfix expression
bool checkLvl(char newChar, char topChar); // checks precedence level of chars
void print(const BET t); // prints preorder, inorder, and postorder expressions
bool closeCheck(); // checks if the user wishes to close the program
string lower(string s); // lowers string for closeCheck()
string expression(); // gets input from user for their expression. Called by preTree(), inTree(), postTree() 

// main
int main() {
    bool ex = false; string error;

    do {
        system("clear");
        // calls menu. return 'e' for default case if error occurs
        switch(menu()) {
            case '1': print(preTree(expression())); ex = closeCheck(); break;
            case '2': print(inTree(expression())); ex = closeCheck(); break;
            case '3': print(postTree(expression())); ex = closeCheck(); break;
            default:
                cout<<"Please enter a valid option. Press enter to continue"<<endl<<endl;
                getline(cin, error);
                break;

        }
    }while(!ex);

    cout<<endl<<"Porgram Now Deconstructing Tree & Exiting..."<<endl<<endl<<endl;
    
    return 0;
}

// menu
char menu() {

    // post: returns char value of an input string (to avoid InputMismatch errors)

    string input;

    cout<<"========EXPRESSION CALCULATOR========"<<endl;
    cout<<"= 1. Prefix                         ="<<endl;
    cout<<"= 2. Infix                          ="<<endl;
    cout<<"= 3. Postfix                        ="<<endl;
    cout<<"====================================="<<endl;
    cout<<endl;
    cout<<"Enter expression type: ";
    getline(cin, input);

    if(input.length()>1)
        return 'e'; // incorrect input
    else
        return input[0]; // char form of input returned
}

BET preTree(string input) {

    // pre: PREFIX expression input by user and inserted into tree

    BET pre;

    // removes spaces
    input.erase(remove(input.begin(), input.end(), ' '), input.end());

    // inputs tokens into BET
    for(int i=input.length()-1; i>=0; i--) {
        char token = input[i];
        if(token=='+'||token=='-'||token=='*'||token=='/')
            pre.insertPrefixOperator(token);
        else
            pre.insertOperand(token);
    }
    return pre;
}

BET inTree(string input) {

    // post: INFIX expression input by user and inserted into tree (through a postfix string)

    // removes spaces
    input.erase(remove(input.begin(), input.end(), ' '), input.end());

    // add parenthesis if not present on the input string
    input = '('+input;
    input+=')';

    // convert infix to postfix
    stack<char> in;
    string postString; // postfix string
    for(int i=0; i<input.length(); i++) {
        char token = input[i];

        // if a symbol
        if(token=='+'||token=='-'||token=='*'||token=='/') {
            // precedence requires change
            while(!checkLvl(token, in.top())) {
                postString+=in.top();
                in.pop();
            }
            in.push(token);
        }

        // opening parenthesis -- no change
        else if(token=='(')
            in.push(token);
        
        // closing parenthesis -- push until open is found, then pop open to remove
        else if(token==')') {
            while(in.top()!='(') {
                postString+=in.top();
                in.pop();
            }
            in.pop(); // remove opening parenthesis
        }

        // number
        else
            postString+=token;
    }

    // inputs tokens into BET
    return postTree(postString);
}

BET postTree(string input) {

    // post: POSTFIX expression input by user and inserted into tree

    BET post;

    // removes spaces
    input.erase(remove(input.begin(), input.end(), ' '), input.end());

    // inputs tokens into BET
    for(int i=0; i<input.length(); i++) {
        char token = input[i];
        if(token=='+'||token=='-'||token=='*'||token=='/')
            post.insertPostfixOperator(token);
        else
            post.insertOperand(token);
    }
    return post;
}

void print(BET t) {
    
    // post: prints all 3 expressions after input
    cout<<endl;
    
    // prefix
    cout<<"Prefix Expression:"<<endl;
    t.preorder(); cout<<endl<<endl;

    // infix
    cout<<"Infix Expression:"<<endl;
    t.inorder(); cout<<endl<<endl;

    // postfix
    cout<<"Postfix Expression:"<<endl;
    t.postorder(); cout<<endl<<endl;
}

bool checkLvl(char newChar, char topChar) {
        
    // pre: take in two chars (can be any non numerical character)
    //
    // post: return TRUE if values do NOT need to be popped
    //       return FALSE if values DO need to be popped

    // avoids parenthesis
    if(topChar=='(')
        return true;
    
    // check if topChar has higher precedence than newChar
    if( ((newChar=='*')||(newChar=='/')) && ((topChar=='*')||(topChar=='/')) ) 
        return false;
    else if( ((newChar=='+')||(newChar=='-')) && ((topChar=='+')||(topChar=='-')) )
        return false;
    else if( ((newChar=='+')||(newChar=='-')) && ((topChar=='*')||(topChar=='/')) )
        return false;
    else if( ((newChar=='*')||(newChar=='/')) && ((topChar=='+')||(topChar=='-')) )
        return true;
    else
        return true;
}

bool closeCheck() {
    // post: program is closed or continued based on user input
    string input;

    cout<<endl;
    cout<<"Build Another Tree? [Y/N]: ";
    getline(cin, input);
    input = lower(input);

    if(input.length()>1) {
        if(input=="yes")
            return false;
        else if(input=="no")
            return true;
        else
            return false;
    }
    else {
        if(input=="y")
            return false;
        else if(input=="n")
            return true;
        else
            return false;
    }
}

string lower(string s) {

    // post: lowers inputed string
    
    string z;
    for(int i=0; i<s.length(); i++)
        z+=tolower(s[i]);
    return z;
}

string expression() {
    
    //post: gets expression input from user

    string input;
    cout<<"Enter your expression: ";
    getline(cin, input);
    return input;
}
