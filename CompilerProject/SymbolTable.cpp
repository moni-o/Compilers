#include <iostream>
#include <vector>
#include "FSA2.h"
#include "FSA.h"
using namespace std;


vector<SymbolTable_Entries>SymbolTable(vector<token>& tokens){
    vector<SymbolTable_Entries> tableEntry;
    string currentToken;
    SymbolStates currentState = Start;
    int addr = 0;
    

    for(int i =0; i < tokens.size(); i++) {
        string c = tokens[i].classification; 
        
        SymbolInput nextInput = mapSymbolInput(c);
        cout<<tokens[i].value<<" "<<tokens[i].classification<<endl;
        SymbolStates nextState = static_cast<SymbolStates>(FSA2[currentState][nextInput]); // Determine the next state, assign to nextState
        cout<<"FSA2["<<currentState<<"]"<<"["<<nextInput<<"]"<<endl; 
        cout<<nextState<<endl;

        switch (nextState) {
            case START:
                currentState = nextState;
                break;
            case Class_State:
                currentState = nextState;
                break;
            case PGM_Final:
                currentToken = tokens[i].value;
                tableEntry.push_back({currentToken, "Pogram name", " " ,addr, "CS"});
                cout<<currentToken<<" Pogram name"<<endl;
                currentState = nextState;
                break;
            case PGM_Start:
                currentState = nextState;
                break;
            case Const_D:
                currentState = nextState;
                break;
            case Const_State:
                currentState = nextState;
                currentToken = tokens[i].value;
                break;
            case Assigment_State:
                currentState = nextState;
                break;
            case Const_VAR_De:
                tableEntry.push_back({currentToken,"ConstVar", tokens[i].value, addr, "DS"});
                addr +=2;
                cout<<currentToken<<"ConstVar"<<tokens[i].value<<endl;
                currentState = nextState;
                break;
            case VAR_State:
                currentState = nextState;
                break;
            case VAR_Variable:
                currentToken = tokens[i].value;
                tableEntry.push_back({currentToken, "VAR", "?", addr, "DS"});
                addr +=2;
                currentState = nextState;
                break;
            case Inter_State:
                currentState = nextState;
                break;
            case Int_Final:
                currentToken = tokens[i].value;
                cout<<"HERE"<<endl;
                cout<<currentToken<<endl;
                tableEntry.push_back({currentToken, "Numeric Literal", currentToken, addr ,"DS"});
                addr +=2;
                currentState = nextState;
                cout<<currentToken<< " Numeric Literal "<< " "<<endl;
                break;
            case EOF_STATE:
                currentState = nextState;
                tableEntry.push_back({"Temp1", "Var (int)", "?", addr, "DS"});
                addr+2;
                tableEntry.push_back({"Temp2", "Var (int)", "?",addr, "DS"});
                addr+2;
                tableEntry.push_back({"Temp3", "Var (int)", "?", addr, "DS"});
                break;
            default:
                break;                              
         }

    }
   
    return tableEntry;
}
