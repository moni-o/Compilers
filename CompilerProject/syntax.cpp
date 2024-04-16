#include "POE.h"
#include "FSA.h"
#include <iostream>
using namespace std;

//Global Variables
const int maxSize = 50;
int top = -1;
int quadCount  = 0;
int tempCount = 0;

token stack[maxSize];
Quad myquad[100];

/////////////////////Stack Functions Only///////////////////////
void push(token token) {
    if (top >= maxSize - 1) {
        cerr << "Stack overflow" <<endl;
        exit(EXIT_FAILURE);
    }
    cout<<"pushing: "<<token.value<<" "<<token.classification<<endl;;
    stack[++top] = token;
}

token pop(int index = -1) {
    if (index == -1) 
    {    // Pop the top element
        if (top < 0) {
            cerr << "Stack underflow" << endl;
            exit(EXIT_FAILURE);
        }
        return stack[top--];
    } else {
        // Pop from a specific index
        if (index < 0 || index > top) {
            cerr << "Index out of range" << endl;
            exit(EXIT_FAILURE);
        }
        token poppedToken = stack[index];
        // Shift elements to remove the token at the specified index
        for (int i = index; i < top; i++) {
            stack[i] = stack[i + 1];
        }
        top--;
        return poppedToken;
    }
}


token topOfStack() {
    if (top < 0) {
        throw out_of_range("Stack is empty"); 
    }

    return stack[top];
}

////////////////////////////////////////////////////////////////


bool isNonTerminal(token token) {
     return token.classification == "variable" || token.classification == "int";
}

void addQuad(string op ="?", string arg1="?", string arg2 = "?" , string result = "?" ){
    myquad[quadCount].op = op;
    myquad[quadCount].arg1 = arg1;
    myquad[quadCount].arg2 = arg2;
    myquad[quadCount].result = result;
    quadCount++;
    cout<<"Quad: "<<op<<" "<<arg1<<" "<<arg2<<" "<<result<<endl;
    
}


string generateTemp() {
        return "Temp" + to_string(++tempCount);  // Increment and return a new temp variable name
    }

void handleReduction(int& optop) {
    string ope = pop(optop).value;  // Pop the operator
    string arg2 = pop().value;  // Pop the right operand
    string arg1 = pop().value;  // Pop the left operand
    string result;
    optop = top;  // Update the optop to the new top of the stack

    if (ope == "=") {
        // Assignment does not need a new temp variable.
        addQuad(ope, arg1, arg2);
        tempCount =0;
    } else {
        // Generate a temp for other operations
        result = generateTemp();
        addQuad(ope, arg1, arg2, result);
        push({result, "variable"});  // Push the result for further use.

    }
}

/////////////////////Original Code in Check Function , refratured to individual Function ////////////////////////
//                 ope = pop(optop).value;
//                 arg2 = pop().value;
//                 arg1 = pop().value;
//                 optop= top;
//                 }
//                 if(ope == "="){                   
//                     addQuad(ope, arg1, arg2);
//                 }
//                 else{
//                     result = generateTemp();
//                     addQuad(ope, arg1, arg2, result);
//                     push({result, "variable"});
//                 }
                
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void handleParentheses(int& optop) {
    pop();  // 
    optop = top;   //Now the top opertor is at the top of the stack, which should be some Temp Variable
    optop--;  // /we need to decrement the optop to get the next operato
    pop(optop);  //We pop this operator which should be the Left Parentences,
    optop--;   //Decrement the optop so it correctly points to the previous operator
}

void check(token& tokens, int& optop){
        token topToken = stack[optop];
        precedenceInput input= mapToInput(tokens);
        int op = PO_TABLE[mapToInput(topToken)][input];
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
                    handleParentheses(optop);
                    break;
                }
                else{
                    handleReduction(optop);
                    
                }
                if(stack[optop].classification != "terminator"){
                    check(tokens,optop);
                    
                }
               
                break;
        default:
            cout<<"Skipping: "<<tokens.value<<endl;
            break;
        }
    }




precedenceInput mapToInput(token& token){
    if(token.value == "=")return assignment;
    if(token.value == "+")return plus_input;
    if(token.value == "-") return minus_input;
    if(token.value == "*") return asterick;
    if(token.value == "/") return slash;
    if(token.value == "(") return leftP;  
    if(token.value == ")") return rightP;  
    return terminator;
}





//Start of Grammar
void parseTokens(vector<token>& tokens) {
    bool parsing = false;
    int optop;
    size_t i = 0;
    push(token{"$","terminator"}); //Pushing the EOF token
    optop = top;
    
    for( ;i <tokens.size(); i++){

        //if statement to help bypass until the { LB and the actual beginig of the pogram
        if(tokens[i].value == "{" ){
            parsing = true;
            continue;
        }
      
        if(parsing){
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
                cout<<"Left Parentences"<<endl;
                check(tokens[i], optop);
                continue;
            }

            if(tokens[i].classification == "LB"){
                //parseBlock(tokens, i);
                cout<<"LB"<<endl;
                continue;
            }
            if(tokens[i].classification == "RB"){
                cout<<"RB"<<endl;
                check(tokens[i], optop);
                //parseBlock(tokens, i);
                continue;
            }
            if(tokens[i].classification == "EOF"){
                cout<<"Finished The end of list"<<endl;
                parsing =false;

                cout<<endl;
                printQuads();
                
            }
            else{
                push(tokens[i]);
            }
       }
     } 
 }
    
void printQuads(){
    cout<<"Printing Quads"<<endl;
    for(int i = 0; i<quadCount; i++){
        cout<<myquad[i].op<<" "<<myquad[i].arg1<<" "<<myquad[i].arg2<<" "<<myquad[i].result<<endl;
    }
}

// void parseEx(vector<token>& tokens, size_t& current, int& optop){ 
//     while(current < tokens.size() && tokens[current].value != ";")
//         {
//             if(tokens[current].classification == "variable" || tokens[current].classification == "int"){
//                 push(tokens[current]);
                
//             }
//             if (tokens[current].classification == "="){
//                 check(tokens[current], current,  optop);
                
//             }
//             if(tokens[current].classification == "mop"){
//             check(tokens[current], current,  optop);

//             }
//             if(tokens[current].classification == "addop"){
//                 check(tokens[current], current,  optop);
                
                
//             }
//         }
//         if (tokens[current].classification == "semi"){
//             check(tokens[current], current,  optop);
//             return;
//         } 
        
//     }
