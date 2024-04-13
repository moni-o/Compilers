#include "POE.h"
#include <iostream>
#include<stack>
using namespace std;








predenceInput maptToInput(token& token){
    if(token.value == "=")return equal_input;
    if(token.value == "+")return plus_input;
    if(token.value == "}") return right_brace;
    return terminator;
}





void parseTokens(vector<token>& tokens){
    stack<token> tokenStack;
    bool startParsing = false;
    size_t index = 0;  // Index to track the current token



    for(int i = 0; i <tokens.size(); i++){

        //if statement to help bypass until the { LB and the actual beginig of the pogram
        if(tokens[i].value == "{" ){
            startParsing = true;
            continue;
        }
      
       if(startParsing){

        if(tokens[i].value == "+" ){
           
            cout<<"The plus is in here"<<endl;
            cout<<tokens[i].value<<endl;
            
        }
        else if(tokens[i].value == "="){
            cout<<"The = is in here"<<endl;
        }
        else{
            tokenStack.push(tokens[i]);
            cout<<"Pushed: " << tokens[i].value<<" "<<tokens[i].classification<<endl;
            
        }
            
            // if(tokens[i].classification == "variable" || tokens[i].classification == "int"){
            // tokenStack.push(tokens[i]);
            // cout<<"Pushed: " << tokens[i].value<<" "<<tokens[i].classification<<endl;
            // }
            // else{
            //     while(!tokenStack.empty()){
            //         token topOp = tokenStack.top();
            //         int precedenceNum = PO_TABLE[mapTokeTop(topOp)][mapTokeTop(token[i])]


            //         //if the prededenceNum is 1 "<", 2 "=", 3 ">"
            //         //if 1 then we yield to it and we push the token[i] into the stack
            //         //if 2 we push it into the stack
            //         //if 3 if we do not push into the stack the token[i], we stead pop, the handle of the stack
            //     }
            // }


        }

       


    }

    
}

