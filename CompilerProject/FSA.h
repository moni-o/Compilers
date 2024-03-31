#ifndef FSA_H
#define FSA
#include <vector>;//remove later 

enum Input{
    LETTER,
    DIGIT,
    ASTERICK,
    SLASH,
    EQUAL,
    LESSTHAN,
    GREATHERTHAN,
    PLUS,
    MINUS,
    COMMA,
    LEFTBRACE,
    RIGHTBRACE,
    LEFTP,
    RIGHTP,
    SEMICOLON,
    Excl,
    WS,
    OTHER,
    COUNT

};

enum States{
    START,
    ERROR,
    MOP,
    DIGIT_STATE,
    INTEGER,
    VARIABLE,
    FINALVARIABLE,
    SLASH_State,
    MULTILINE,
    ENDMULTILINE,
    DIVISION,
    EQUALS,
    ASSIGMENT,
    FINALEQUAL,
    LESSTHAN_STATE,
    LESSTHAN_FINAL,
    LESSEQUAL,
    GREATHERTHAN_STATE,
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
    EXCLAMATION,
    NOT,
    NOTEQUAL,
    count_State

};

int FSA_TABLE[count_State][COUNT] ={}; //2D array

void initFSA();
Input characterInput(char c);


//Lexer.H for later usage change 


struct token{
    string type;
    string value;
    
};

vector<token> tokenize(string& string);

#endif