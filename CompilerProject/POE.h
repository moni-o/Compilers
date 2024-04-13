#ifndef POE_H
#define POE_H
#include "FSA.h"
#include <iostream>
using namespace std;




//Header file for Syntax 
//table is a square matrix 
enum predenceInput{
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
void parseTokens(vector<token>& t);
predenceInput maptToInput(token& token);

#endif