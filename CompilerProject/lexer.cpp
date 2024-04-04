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
        case INTEGER: return "int";
        case FINALVARIABLE: return "variable";
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
        case RIGHTBRACE_FINAL: return "RB";
        case LEFTPARENTECES: return "LP";
        case RIGHTPARENTECES: return "RP";
        case SEMIDELI: return "semi";
        case NOT: return "not";
        case NOTEQUAL: return "relop";
        default: return "Uknown";


    }
}

bool isFinalState(States state){ //Dont need it anymore???
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


vector<token> tokenizer(const string& input) {
    vector<token> tokens;
    string currentToken;
    States currentState = START;
    size_t index = 0;

    while (index < input.length()) {
        char c = input[index]; 
        Input nextInput = characterInput(c); //gives next input, calls the characterInput
        States nextState = static_cast<States>(FSA_TABLE[currentState][nextInput]); // Determine the next state, assign to nextState

        switch (nextState) {
            case START:
                currentToken.clear();
                currentState = nextState;
                index++;
                break;
            case ERROR:
                cout<<getTokenClass(nextState)<<endl;
                break;
            case MOP:
                currentToken += c;
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear ();
                currentState = START;
                index++;
                break;
            case DIGIT_STATE:
                currentToken += c;
                currentState = nextState;
                index++;
                break;
            case INTEGER:
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear();
                currentState = START;
                break;
            case VARIABLE:
                currentToken += c;
                currentState = nextState;
                index++;
                break;
            case FINALVARIABLE: 
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear();
                currentState = START;
                break;
            case SLASH_State:
                currentToken += c;
                currentState = nextState;
                index++;
                break;
            case MULTILINE:
                currentToken +=c;
                currentState = nextState;
                index++;
                break;
            case ENDMULTILINE:
                currentToken +=c;
                currentState = nextState;
                index++;
                break;
            case DIVISION:
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear();
                currentState = START;
                break;
            case EQUALS:
                currentToken +=c;
                currentState = nextState;
                index++;
                break;
            case ASSIGMENT:
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear();
                currentState = START;
                break;
            case FINALEQUAL:
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear();
                currentState = START;
                break; 
            case LESSTHAN_STATE:
                currentToken +=c;
                currentState = nextState;
                index++;
                break;
            case LESSTHAN_FINAL:
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear();
                currentState = START;
                break;
            case LESSEQUAL:
                currentToken += c;
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear();
                currentState = START;
                index++;//?????????????????????????????????????????????????????????
                break;
            case GREATHERTHAN_STATE:
                currentToken +=c;
                currentState = nextState;
                index++;
                break;
            case GREATERFINAL:
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear();
                currentState = START;
                break;
            case GREATEREQUAL:
                currentToken += c;
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear();
                currentState = START;
                index++;
                break;
            case ADDFINAL:
                currentToken +=c;
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear();
                currentState = START;
                index++;
                break;
            case MINUSFINAL:
                currentToken +=c;
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear();
                currentState = START;
                index++;
                break;
            case  COMMADEL:
                currentToken +=c;
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear();
                currentState = START;
                index++;
                break;
            case LEFTBRACE_FINAL:
                currentToken +=c;
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear();
                currentState = START;
                index++;
                break;
            case RIGHTBRACE_FINAL:
                currentToken +=c;
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear();
                currentState = START;
                index++;
                break;  
            case LEFTPARENTECES:
                currentToken +=c;
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear();
                currentState = START;
                index++;
                break;  
            case RIGHTPARENTECES:
                currentToken +=c;
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear();
                currentState = START;
                index++;
                break;  
            case SEMIDELI:
                currentToken +=c;
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear();
                currentState = START;
                index++;
                break;  
            case EXCLAMATION:
                currentToken +=c;
                currentState= nextState;
                index++;
                break;
            case NOT:
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear();
                currentState = START;
                break;
            case NOTEQUAL:
                currentToken +=c;
                tokens.push_back({currentToken, getTokenClass(nextState)});
                currentToken.clear();
                currentState = START;
                index++;
                break;
            default:
                cout<<"not found"<<endl;
                break;
            }
        }

    return tokens;
}