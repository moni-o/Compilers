#ifndef POE_H
#define POE_H
#include "FSA.h"
#include <iostream>
using namespace std;



//Header file for Syntax 
//table is a square matrix 
enum precedenceInput{
    terminator,
    assignment,
    plus_input,
    minus_input,
    leftP,
    rightP,
    asterick,
    slash,
    if_input,
    then_input, 
    while_input,
    do_input,
    odd_input,
    equal_input,
    not_equal,
    greather_than,
    less_than,
    greather_than_equal,
    less_than_equal,
    left_brace,
    right_brace,
    call_input,
    op_else,
    cin_input,
    cout_input, 
    predence_count,
};



//2D array for Predence Operator Table Declaration,
extern int PO_TABLE[predence_count][predence_count];
void ini_PO_TABLE();
void parseTokens(vector<token>& tokens);

void parseBlock(token& tokens, int& current);
precedenceInput mapToInput(token& token);

//Functions for stack
void push(token token);
token pop(int index );
void check(token& token, int& optop);
bool isOperatorToken(precedenceInput type);
string generateTemp();
string generateLabel();
void printQuads();
void handleReduction(int& optop);
void reduceParentheses(token& comingOP,  int& operatorTop);
void ifStatement(token& tokens, int& topToken);
string relopToOp(string relop);
void thenStatement(token& tokens,int& topToken);
void elseStatement(int& topToken,token& tokens);
void whileStatement(int& optop, token& tokens);
void doStatement(int& optop, token& tokens);
void printFixUpStack();
string whileLable();
void popWhileDo();
void popifThen(int& optop);
//Structure for Quads
struct Quad{
    string op;
    string arg1;
    string arg2;
    string result;

};

void  addQuad(string op, string arg1, string arg2, string result);
Quad* getQuadArray();
int getQuadCount();





#endif