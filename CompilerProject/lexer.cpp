# include "FSA.h"
# include <iostream>
# include <cctype>
# include <string>
#include <set>
#include <vector>
using namespace std;




string getTokenClass(States state){
    switch(state){
        case ERROR: return "Invalid Input";
        case MOP: return "mop";
        case INTEGER: return " int";
        case FINALVARIABLE: return "var";
        case DIVISION: return "mop";
        case ASSIGMENT: return "assign";
        case FINALEQUAL: return "relop";
        case LESSTHAN_FINAL: return "relop";
        case LESSEQUAL: return "relop";
        case GREATERFINAL: return "relop";
        case GREATEREQUAL: return "relop";
        case ADDFINAL: return "addop";
        case MINUSFINAL: return "addop";
        case COMMADEL: return "comma";
        case LEFTBRACE_FINAL:return "LB";
        case RIGHTBRACE: return "RB";
        case SEMIDELI: return " semi";
        case NOT: return "not";
        case NOTEQUAL: return "relop";
        default: return "Uknown";


    }
}

bool isFinalState(States state){
    static const std:: set <States> finalStates = {
        ERROR,
        MOP,
        INTEGER,
        FINALVARIABLE,
        DIVISION,
        ASSIGMENT,
        FINALEQUAL,
        LESSTHAN_FINAL,
        LESSEQUAL,
        GREATERFINAL,
        GREATEREQUAL,
        ADDFINAL,
        MINUSFINAL,
        COMMADEL,
        LEFTBRACE_FINAL,
        RIGHTBRACE_FINAL,
        LEFTPARENTECES,
        RIGHTPARENTECES,
        SEMIDELI,
        NOT,
        NOTEQUAL,
    };
    return finalStates.find(state) != finalStates.end();
}

vector <token> tokenizer(const string& input){ //Passing by reference 
    vector<token> tokens;
    string currentTokens;
    States currentState = START;


    cout<<input<<endl;
    for(char c: input + " "){
        cout<<characterInput(c);
        Input nextInput = characterInput(c);
        cout<<nextInput<<endl;
        
        
        //Debug
        cout<<c;

        States nextState = static_cast<States>(FSA_TABLE[currentState][nextInput]);
        cout<<nextState<<endl;
        cout<<currentTokens<<" "<<currentState<<endl;
        if(isFinalState(nextState)){
            if(!currentTokens.empty()){
                tokens.push_back(token{currentTokens, getTokenClass (currentState)});
                cout<<currentTokens<<endl;
                currentTokens.clear();
                nextState =START;
            }
            
            if(nextState == ERROR){
                cout<<"Error"<<endl;
                break;
            }
        }
        
        currentState = nextState;

        currentTokens += c;
        
    }
    //cout<<tokens<<endl;
    return tokens;
}
