# Binary Expression Tree
This program will create a Binary Expression Tree based on any form of expression input 
(prefix, postfix, or infix) and then generate its respective counterparts.

**Clarification** 
- BET = Binary Expression Tree  
- BETPtr = Binary Expression Tree (Pointer)
 

# Infix to Postfix
My first step in infix is to take care of all spaces. Using C++ iterators and the 
string class, spaces are removed easily. The syntax follows:

string.erase(remove(str.begin(), str.end(), ' '), str.end()).

From here I will add an opening and closing parenthesis to the front and back of
the string. This is to prevent the program from glitching if there are no parenthesis
present of if there is an unclosed parenthesis from user error.

Afterwards, I will use a client method that I will create to check the precedence of
two tokens passed in. It will only be called if the input number is an operator.

**checkLvl(char newChar, char topChar)** will return a bool and will ignore parenthesis.
If the char is equal to its own precendece level (\*==/, +==-), it will return false
and will cause the infix method to pop the necessary operators.

If a closed parenthesis is read, it will pop and print everything until an
opening parenthesis is found, where it will then pop but NOT print the opening parenthesis.

Finally, if the input is simply a number, it will print that number.

# insertOperand
Creates a BETPtr object and sets its left and right child to NULL (numbers in a BET are leaves).
It then sets the info.whichType to OPERAND and info.theContent.variable to the token passed into
the function.

The new BETPtr object is then pushed to the stack.

# insertPostfixOperator
insertPostfixOperator takes takes a char token input and creates a new BETPtr. Then, it assigns the
info.whichType to OPERATOR and info.theContent.opsymbol to token. Finally, it must get children! It
assigns the top of the stack to the right child first, then pops that value, then assigns top of the
stack to the left child, and then pops. Then, it pushes that value to the stack. Root is assigned to 
this new node.

# insertPrefixOperator
insertPrefixOperator takes takes a char token input and creates a new BETPtr. Then, it assigns the
info.whichType to OPERATOR and info.theContent.opsymbol to token. Finally, it must get children! It
assigns the top of the stack to the left child first, then pops that value, then assigns top of the
stack to the right child, and then pops. Then, it pushes that value to the stack. Root is assigned to 
this new node.
