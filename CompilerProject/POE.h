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
    cin_input,
    cout_input, 
    predence_count,
};



//2D array for Predence Operator Table Declaration,
extern int PO_TABLE[predence_count][predence_count];
void ini_PO_TABLE();
void parsePgm(vector<token>& t, size_t c);
void parseTokens(std::vector<token>& tokens);
precedenceInput mapToInput(token& token);
void parseBlock(vector<token>& tokens,size_t& current);
void parseAssignment(vector<token>& tokens, size_t& current);
void parseEx(vector<token>& tokens, size_t& current, int& optop);
void parseConst(vector<token>& tokens, size_t& current);
void parseVar(vector<token>& tokens, size_t& current);
void parseStatement(vector<token>& tokens, size_t& current);
//Functions for stack
void push(token token);
token pop(int index );
void check(token& token, int& optop);
bool isNonTerminal(token token);
string generateTemp();
void printQuads();
void handleReduction(int& optop);
void handleParentheses(int& optop);

//Structure for Quads
struct Quad{
    string op;
    string arg1;
    string arg2;
    string result;

};

void  addQuad(string op, string arg1, string arg2, string result);





#endif