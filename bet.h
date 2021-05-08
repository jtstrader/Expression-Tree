#include<stack>

using namespace std;

enum OpType {OPERATOR, OPERAND};
union OperandType
{
        char opsymbol;             // Used to store operator when whichType
                                   // is OPERATOR
        char variable;             // Used to store variable when whichType
                                   // is OPERAND
};

struct InfoNode
{
        OpType  whichType;         // Type field to store type of node content 
        OperandType theContent;    // A "union" field with holds either
                                   // operator or operand
};

struct BinaryNode 
{
        InfoNode        info;
        BinaryNode*     left;
        BinaryNode*     right;
};

struct BinaryNode;
typedef BinaryNode* BETPtr;

class BET 
{
public :
    BET ();		// Constructor
    ~BET ();            // Destructor

    bool isEmpty () const;  
    void makeEmpty();
    void insertPrefixOperator (char token); 
    void insertPostfixOperator (char token); 
    void insertOperand (char token); 
    void preorder() const; 
    void inorder() const; 
    void postorder() const;
private :
    // Private Attributes of a BET Object 
    BETPtr root;
    stack<BETPtr> s;

    // Operations needed solely by Public Functions
    void makeEmpty( BETPtr& t ) const;
    void preorder( BETPtr t ) const;
    void inorder( BETPtr t ) const;
    void postorder( BETPtr t ) const;
};
