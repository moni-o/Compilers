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


vector<token> tokenizer(const string& input) {
    vector<token> tokens;
    string currentToken;
    States currentState = START;
    size_t index = 0;

    while (index <= input.length()) {
        char c = input[index]; 
        Input nextInput = characterInput(c); // Categorize the input character
        States nextState = static_cast<States>(FSA_TABLE[currentState][nextInput]); // Determine the next state

        // If the character is not a space, or if transitioning from a final state, accumulate it
        if (!isspace(c)) {
            currentToken += c;
            cout<<currentToken<< " FSA :"<<currentState<<" "<< nextInput << " Next state "<< nextState<<endl;
        }

        // When encountering a final state or a delimiter (space/newline), finalize the token??? maybe change
        if ((isFinalState(nextState) || isspace(c)) && !currentToken.empty()) {


            //Since FinalVar and Integer are triggered by any input we have to do print the nexState classification
            //instead of the current state; 
            if(isFinalState(nextState) == FINALVARIABLE || isFinalState (nextState) || INTEGER )
            {
                tokens.push_back(token{currentToken, getTokenClass(nextState)}); // Save the token
                currentToken.clear(); // Reset for the next token, clearts the accumulator
                nextState = START;  // after finalizing token, need nexState to start at 0 again, so is passed to the current State
            }
            else{
                tokens.push_back(token{currentToken, getTokenClass(currentState)}); // Save the token
                currentToken.clear(); // Reset for the next token, clearts the accumulator
                nextState = START; 
            }
        }

        // If an error state is encountered, report and stop processing
        if (nextState == ERROR) {
            cout << "Error encountered." << endl;
            break;
        }

        currentState = nextState; // Update the state
        ++index; // Move to the next character
    }



    return tokens;
}