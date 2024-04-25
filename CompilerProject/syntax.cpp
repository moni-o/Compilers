#include "POE.h"
#include "FSA.h"
#include <iostream>
using namespace std;

//Global Variables
const int maxSize = 50;
const int MAXFIXUP = 100;
const int MAXEND = 50;
int top = -1;
int quadCount  = 0;
int tempCount = 0;
int lableCount =0;
int whileCount = 0;
token stack[maxSize];
Quad myquad[maxSize];
string fixupStack[MAXFIXUP];
string endStack[MAXEND];
int endTop = -1;
int fixupTop = -1;

/////////////////////Stack Functions Only///////////////////////
void push(token token) {
    if (top >= maxSize - 1) {
        cerr << "Stack overflow" <<endl;
    }
    cout<<"pushing: "<<token.value<<" "<<token.classification<<endl;;
    stack[++top] = token;

}

token pop(int index = -1) {
    if (index == -1) 
    {    // Pop the top element
        if (top < 0) {
            cerr << "Stack underflow" << endl;
        }
      
        return stack[top--];
    } else {
        // Pop from a specific index
        if (index < 0 || index > top) {
            cerr << "Index out of range" << endl;
        }
        token poppedToken = stack[index];
        // Shift elements to remove the token at the specified index
        for (int i = index; i < top; i++) {
            stack[i] = stack[i + 1];
        }
        top--;
        cout<<"Popping: "<<poppedToken.value<<" "<<poppedToken.classification<<endl;
        return poppedToken;
    }
}


////////////////////////////////////////////////////////////////

bool isOperatorToken(precedenceInput type) {
    switch (type) {
        case terminator:
        case assignment:
        case plus_input:
        case minus_input:
        case leftP:
        case rightP:
        case asterick:
        case slash:
        case if_input:
        case then_input:
        case while_input:
        case do_input:
        case odd_input:
        case equal_input:
        case not_equal:
        case greather_than:
        case less_than:
        case greather_than_equal:
        case less_than_equal:
        case left_brace:
        case right_brace:
        case cin_input:
        case cout_input:

            return true;
        default:
            return false;
    }
}

//Based on the token type, it tells me what input it is in the precedence table, I kept my table in the same order as the enum, so I can use the enum as an index
precedenceInput mapToInput(token& token){
    if(token.value == "=")return assignment;
    if(token.value == "+")return plus_input;
    if(token.value == "-") return minus_input;
    if(token.value == "*") return asterick;
    if(token.value == "/") return slash;
    if(token.value == "(") return leftP;  
    if(token.value == ")") return rightP;  
    if(token.value == "IF") return if_input;
    if(token.value == "THEN") return then_input;
    if(token.value == "ELSE") return op_else;
    if(token.value == "DO") return do_input;
    if(token.value == "WHILE") return while_input;
    if(token.value == "{")return left_brace;
    if (token.value == "}") return right_brace;
    if (token.value == ">") return greather_than;
    if (token.value == "<") return less_than;
    if(token.value == "==") return equal_input;
    if(token.value == "!=") return not_equal;
    if(token.value == ">=") return greather_than_equal;
    if(token.value == "<=") return less_than_equal;
    return terminator;
}

//Function to add Quads to the Quad Array
void addQuad(string op ="?", string arg1="?", string arg2 = "?" , string result = "?" ){
    myquad[quadCount].op = op;
    myquad[quadCount].arg1 = arg1;
    myquad[quadCount].arg2 = arg2;
    myquad[quadCount].result = result;
    quadCount++;
    cout<<"Quad: "<<op<<" "<<arg1<<" "<<arg2<<" "<<result<<endl;
    
}
void addToFixUp(string label ="?"){
    fixupStack[fixupTop] = label;
    fixupTop++;
    cout<<"Fixup: "<<fixupStack[fixupTop]<<endl;
}
string generateTemp() {
        return "Temp" + to_string(++tempCount);  // Increment and return a new temp variable name
    }
//This is used to handle the reduction of the stack, when the operator is of lower precedence than the incoming token
void handleReduction(int& optop) {
    string ope = pop(optop).value;  // Pop the operator
    string arg2 = pop().value;  // Pop the right operand
    string arg1 = pop().value;  // Pop the left operand
    string result;
    optop = top;  // Update the optop to the new top of the stack

    if (ope == "=" || ope == ">" || ope == "<" || ope == ">=" || ope == "<=" || ope == "!=" || ope == "==") {
        // Assignment does not need a new temp variable.
        addQuad(ope, arg1, arg2);
        tempCount =0;
        cout<<"Current Temp: "<<tempCount<<endl;
    } else {
        // Generate a temp for other operations
        cout<<"Generating Temp"<<tempCount<<endl;
        result = generateTemp();
        cout<<"Current Temp: "<<tempCount<<endl;
        cout<<"Result: "<<result<<endl;
        addQuad(ope, arg1, arg2, result);
        push({result, "variable"});  // Push the result for further use.

    }
}
//Since ( ) have to be pop together but keep the value of it in the stack, I had to create a special function to handle this.
void reduceParentheses(token& comingOP,  int& operatorTop){
    token topToken = stack[operatorTop];
    cout<<"HERE"<<endl;
    if(stack[operatorTop].value == ")" && stack[operatorTop-2].value == "("){
        string  rightParenteces = pop(operatorTop).value;
        string leftParenteces = pop(operatorTop-2).value;
        cout<<"Popped: "<<leftParenteces<<" "<<rightParenteces<<endl;
        cout<<stack[top-1].value<<endl;
        operatorTop = top-1;
    }
}

void check(token& tokens, int& optop){
        token topToken = stack[optop]; //Get the top Operator of the stack
        precedenceInput input= mapToInput(tokens); //Map the incoming token to the precedence table
        int op = PO_TABLE[mapToInput(topToken)][input]; //gives me if the top token should yield, equal or reduce to the incoming token
        cout<<topToken.value<<" and incoming "<<tokens.value<<endl;
        
        switch (op)
        {
        case 1:
        case 2: cout<<"top token: "<<topToken.value<<" yields to: "<<tokens.value<<endl;
                push(tokens);
                optop = top;
                break;
        
        case 3:cout<<"Need to reduce: "<<endl;
                if(topToken.classification == "RP"){
                    reduceParentheses(tokens, optop); //Special case for Parentheses
                }
                else{
                    handleReduction(optop); //Normal Reduction
                    
                }
                if(stack[optop].classification != "terminator"){
                    check(tokens,optop); //Recursively call, in order to see if more reductions can be made after the pop was done.
                    
                }
               
                break;
        default:
            cout<<"Skipping: "<<tokens.value<<endl;
            break;
        }
    }

// *******Start of Grammar

void parseTokens(vector<token>& tokens) {
    bool parsing = false;
    int optop; //This variable is used to keep track of the index of the top token of the stack, as the top of the stack will change as non-terminals are pushed.
    size_t i = 0;
    push(token{"$","terminator"}); //Pushing the EOF token
    optop = top;//since the terminator was pushed,this is currently the top operator but also the top of the stack, 



    
    for( ;i <tokens.size(); i++){    

        

        //if statement to help bypass CLASS PGM Name, until the { LB  is encoutered, as this indicates the start of the program, and and parsing can begin.
        if(tokens[i].value == "{" ){
            parsing = true; //Parsing can now begin
            check(tokens[i], optop); //Check function, to check the current operator and the incoming token precedence, and make the necessary changes to the stack
            continue;
        }
      
        if(parsing){ //After the { is encoutered, parsing can begin, will stop parsing was the EOF sets flag to False 
            if(tokens[i].value == "CONST"){
               while(tokens[i].value != ";"){
                cout<<"Skipping: "<<tokens[i].value<<endl;
                   i++;
               }
                continue;
            }
            if(tokens[i].value == "VAR"){
                while(tokens[i].value != ";"){
                    cout<<"Skipping: "<<tokens[i].value<<endl;
                    i++;
                }
                continue;

            //The If statmetns below, are just to classifiy the tokens, since IF, Else, Then While, Do, have special hadleling when they are being pushed into the stack
             //but the check functions is the one that does the TABLE Driven approach, alot of the if statements below used the same function, to check top of stack operator and incoming token.
            //This was done for better readability and undestanding for me, regarding the flow on how the code should be handled. I could of group them together and not repeat the code.

            }
            if(tokens[i].classification == "assign")
            {
                cout<<tokens[i].value<<endl;
                check(tokens[i], optop);
                
                continue;
            } 
            if(tokens[i].classification == "mop"){
                cout<<tokens[i].value<<endl;
                check(tokens[i], optop);
                continue;
            }

            if(tokens[i].classification == "addop"){
               cout<<tokens[i].value<<endl;
               check(tokens[i], optop);
               continue;
            }
            if(tokens[i].classification == "semi" || tokens[i].value== ";"){
                cout<<"semi"<<endl;
                check(tokens[i], optop);
                continue;
            }
            if(tokens[i].classification == "LP" || tokens[i].classification == "RP"){
                cout<<"Parentences: "<<tokens[i].classification<<endl;
                check(tokens[i], optop);
                continue;
            }
            if(tokens[i].classification == "RB"){
                cout<<"RB in Right Brace statement"<<endl;
                parseBlock(tokens[i],optop);
                cout<<"tokens at the stop of the stack is:"<<stack[optop].value<<endl;
                //Due to that {}brace are popped, Need to decide if then should be pop or not 
              
                if(stack[top].value == "THEN" && stack[top-1].value == "IF" && tokens[i+1].value != "ELSE"){
                        popifThen(optop);
                }
                continue;
            }
            if(tokens[i].classification == "IF")
            {
                ifStatement(tokens[i], optop);
                continue;
            }
             if(tokens[i].classification == "relop"){
                cout<<"relop"<<endl;
                check(tokens[i], optop);
                continue;
            }

             if(tokens[i].classification == "THEN")
            {   cout<<"Then"<<endl;
               thenStatement(tokens[i], optop);
               cout<<"End of Then"<<endl;
                continue;
            }

            if(tokens[i].value == "ELSE")
            {
                cout<<"Else"<<endl;
                elseStatement(optop, tokens[i]);
                continue;
            }
            if(tokens[i].classification == "WHILE")
            {
                whileStatement(optop,tokens[i]);
                continue;
            }
            if(tokens[i].classification == "DO")
            {
                doStatement(optop, tokens[i]);
                continue;
            }
            if(tokens[i].classification == "CIN" || tokens[i].classification == "COUT"){
                cout<<"CIN/COUT"<<endl;
                token current = tokens[i];
                if( tokens[++i].classification == "variable"){
                    addQuad(current.value, tokens[i].value);
                }
                continue;
            }
            if(tokens[i].classification == "EOF"){
                cout<<"Finished The end of list"<<endl;
                parsing =false;

                cout<<endl;
                printQuads();
                //printFixUpStack();
                
            }
            else{ //Automatically pushes NONTerminals to the Stack.
                cout<<"Nonterminal added : ";
                push(tokens[i]);
        
            }
        }
     } 
 }
    


void parseBlock(token& tokens,int& topToken){
    int operation = PO_TABLE[mapToInput(stack[topToken])][mapToInput(tokens)];
    switch(operation){
        case 1: //yield in precedence the topTokens vs the token coming in
        case 2: ///EqualPrecedence
            push(tokens);  //If statement is pushed to stack, quad is created, and the top of the stack is updated
            topToken = top;
            break;
        case 3: handleReduction(topToken);
             if(tokens.value == "}"){
                parseBlock(tokens, topToken);
                }


            break;
    }   //Since the the Right brace, can mean end of a block, or end of the program, I needed to furhter check. The 
        if (stack[top-1].value == "{" && stack[top].value == "}") {
            token x = pop();
            token y = pop();
            cout << "Popped: " << x.value << " " << y.value << endl;
            cout << "Current: " << stack[top].value << endl;
            topToken = top;
            }
     
        if(stack[top].value == "ELSE" && stack[top-1].value == "THEN"){
            token x = pop();
            token y = pop();
            token z = pop();
            cout<<"Popped: "<<x.value<<" "<<y.value<<z.value<<endl;
            cout<<"current: "<<stack[top].value<<endl;
            addQuad(endStack[endTop]);
            endTop--;
            topToken = top;
            }
        if(stack[top].value == "DO" && stack[top-1].value == "WHILE"){
            cout <<"stack[top]"<<stack[top].value<<endl;
                    //popWhileDo();
            cout<<"Popping While Do"<<endl;
            token x = pop();
            token y = pop();
            cout<<"Popped: "<<x.value<<" "<<y.value<<endl;
            string W1 = fixupStack[fixupTop];
            fixupTop--;
            string l2 = endStack[endTop];
            endTop--;
            addQuad(W1);
            addQuad(l2);
            topToken = top;
                }
            
             //break;
}  

string generateLabel(){
    return "L" + to_string(++lableCount);
}
string whileLable(){
    return "W" + to_string(++whileCount);
}

void popifThen(int& optop){
token x = pop();
    token y = pop();
    cout<<"Popped: "<<x.value<<" "<<y.value<<endl;
    cout<<"current: "<<stack[top].value<<endl;
    addQuad(fixupStack[fixupTop]);
    fixupTop--;
    optop = top;
}
void ifStatement(token& tokens, int& topToken){
    int operation = PO_TABLE[mapToInput(stack[topToken])][mapToInput(tokens)];
    switch(operation){
        case 1:
        case 2:
            push(tokens);  //If statement is pushed to stack, quad is created, and the top of the stack is updated
            topToken = top;
            addQuad(tokens.value);
            break;
        case 3:
        break;

    }
}
void thenStatement(token& tokens,int& topToken){
    token topOperator = stack[topToken];
    precedenceInput input= mapToInput(tokens);
    int operation = PO_TABLE[mapToInput(topOperator)][mapToInput(tokens)];
    switch(operation){
        case 1: //yields --> Push to stack
        case 2://Equal --> Push to stack
            push(tokens);  //When the Then Statemtn is pushed into the stack a quad should be created
            topToken = top; //Set this as the current top Operator on the stack;
            addQuad(tokens.value, generateLabel(), relopToOp(myquad[quadCount-1].op));
            fixupStack[++fixupTop] = myquad[quadCount-1].arg1;
            cout<<"Fixup: "<<fixupStack[fixupTop]<<" "<<fixupTop<<endl;
            break;
        case 3:
            handleReduction(topToken);
            if(stack[topToken].classification != "terminator"){
                thenStatement(tokens, topToken); //Recursively call, in order to see if more reductions can be made after the pop was done.       
            }    
        break;
    }

}
void elseStatement(int& stackOperator, token& tokenRead){
    cout<<stack[stackOperator].value<<" and incoming "<<tokenRead.value<<endl;
    int relation = PO_TABLE[mapToInput(stack[stackOperator])][mapToInput(tokenRead)];
    switch(relation){
        case 1: //<
        case 2: // ==
            cout<<"top token: "<<stack[stackOperator].value<<" yields to: "<<tokenRead.value<<endl;
            push(tokenRead);  //If statement is pushed to stack, quad is created, and the top of the stack is updated
            stackOperator = top;
            addQuad(tokenRead.value, generateLabel());
            endStack[++endTop] = myquad[quadCount-1].arg1;
            cout<<"EndStack: "<<endStack[endTop]<<endl;
            addQuad(fixupStack[fixupTop]);
            fixupTop--;
            break;
        case 3:
        break;

    }
}
void whileStatement(int& optop, token& tokens){
cout<<stack[optop].value<<" and incoming "<<tokens.value<<endl;
int operation = PO_TABLE[mapToInput(stack[optop])][mapToInput(tokens)];
    switch(operation){
        case 1: //yields --> Push to stack
        case 2://Equal --> Push to stack
            push(tokens);  //When the Then Statemtn is pushed into the stack a quad should be created
            optop = top; //Set this as the current top Operator on the stack;
            addQuad(tokens.value, whileLable());
            fixupStack[++fixupTop] = myquad[quadCount-1].arg1; //While lable to fixUpStack
            cout<<"Fixup: "<<fixupStack[fixupTop]<<" "<<fixupTop<<endl;
        break;
        case 3:   
        break;
    }
}
void doStatement(int& stackOperator, token& tokenRead){
    cout<<stack[stackOperator].value<<" and incoming "<<tokenRead.value<<endl;
    int relation = PO_TABLE[mapToInput(stack[stackOperator])][mapToInput(tokenRead)];
    switch(relation){
        case 1: //<
        case 2: // ==
            cout<<"top token: "<<stack[stackOperator].value<<" yields to: "<<tokenRead.value<<endl;
            push(tokenRead);  //If statement is pushed to stack, quad is created, and the top of the stack is updated
            stackOperator = top;
            addQuad(tokenRead.value, generateLabel(),relopToOp(myquad[quadCount-1].op));
            endStack[++endTop] = myquad[quadCount-1].arg1;
            cout<<"EndStack: "<<endStack[endTop]<<endl;
            break;
        case 3:
            handleReduction(stackOperator);
            if(stack[stackOperator].classification != "terminator"){
                doStatement(stackOperator, tokenRead); //Recursively call, in order to see if more reductions can be made after the pop was done.       
            }
        break;

    }
}
string relopToOp(string relop){
    if(relop == ">") return "JLE";
    if(relop == ">=") return "JL";
    if(relop == "==") return "JNE";
    if(relop == "<") return "JGE";
    if(relop == "<=") return "JG"; 
    if(relop == "!=") return "JE"; 
    return "Unknown";

}
void printQuads(){
    cout<<"Printing Quads"<<endl;
    for(int i = 0; i<quadCount; i++){
        cout<<myquad[i].op<<" "<<myquad[i].arg1<<" "<<myquad[i].arg2<<" "<<myquad[i].result<<endl;
    }
}
void popWhileDo(){
    cout<<"Popping While Do"<<endl;
    token x = pop();
    token y = pop();
    cout<<"Popped: "<<x.value<<" "<<y.value<<endl;
    string W1 = fixupStack[fixupTop];
    fixupTop--;
    string l2 = endStack[endTop];
    endTop--;
    addQuad(W1);
    addQuad(l2);

}
void printFixUpStack(){
    cout<<"Fixup Stack"<<endl;
    for(int i = 0; i<fixupTop; i++){
        cout<<fixupStack[fixupTop]<<endl;
    }
}
//Resturns An Array of Quads.
Quad* getQuadArray() {
    return myquad;
}
//Resturns the Quad Count
int getQuadCount() {
    return quadCount;
}