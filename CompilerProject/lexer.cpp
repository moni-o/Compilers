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

    while (index <= input.length()) {
        char c = input[index]; 
        Input nextInput = characterInput(c); //gives next input, calls the characterInput
        States nextState = static_cast<States>(FSA_TABLE[currentState][nextInput]); // Determine the next state, assign to nextState

     switch (nextInput) {
            case WS:  
                if (!currentToken.empty()) {
                    tokens.push_back({currentToken, getTokenClass(nextState)});
                    currentToken.clear();
                }
                currentState = START;
                break;

            case COMMA:
            case LEFTBRACE:
            case RIGHTBRACE:
            case SEMICOLON:
                if (!currentToken.empty()) {
                    tokens.push_back({currentToken, getTokenClass(nextState)});
                    currentToken.clear();
                    currentState = START;
                }
                // Treat the delimiter itself as a token
                nextState = static_cast<States>(FSA_TABLE[currentState][nextInput]); // Determine the next state
                tokens.push_back({string(1, c), getTokenClass(nextState)});
                currentState = START;  // Reset state after handling a delimiter
                break;
            case ASTERICK:
            case PLUS:
            case MINUS:
                if (!currentToken.empty()) {
                    tokens.push_back({currentToken, getTokenClass(nextState)});
                    currentToken.clear();
                    currentState = START;
                }
                // Treat the delimiter itself as a token
                nextState = static_cast<States>(FSA_TABLE[currentState][nextInput]); // Determine the next state
                tokens.push_back({string(1, c), getTokenClass(nextState)});
                currentState = START;  // Reset state after handling a delimiter
                break;
            default:
                // For other characters, accumulate if not transitioning to a final state
                if (!isFinalState(nextState) || currentState == nextState) {
                    currentToken += c;
                }
                if (isFinalState(nextState)) {
                    // finalize token if transitioning to a final state
                    if (!currentToken.empty()) {
                        tokens.push_back({currentToken, getTokenClass(currentState)});
                        currentToken.clear();
                    }
                    currentState = START;
                } else {
                    currentState = nextState;  // Proceed with next state transition
                }
                break;
        }

        index++;  // Move to the next character
    }

    return tokens;
}