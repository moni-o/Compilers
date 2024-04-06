#ifndef FSA_H
#define FSA_H
#include <string>
#include <vector>
using namespace std;


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

extern int FSA_TABLE[count_State][COUNT]; //2D array

void initFSA();

struct token{
    string value;
    string classification;
    
};


//Lexer.H for later usage change 
Input characterInput(char c);
vector<token> tokenizer(const string& input);
bool isReserved(string& c);

#endif