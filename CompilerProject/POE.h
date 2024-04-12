#ifndef POE_H
#define POE_H
#include "FSA.h"
#include <iostream>
using namespace std;




//Header file for Syntax 
enum predenceInput{
    terminator,
    equal_input,
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
    assignment,
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

enum precedenceStates{
    terminator_state,
    assigment_state,
    plus_state,
    minus_state,
    leftP_state,
    rightP_state,
    multiplication_state,
    division_state,
    if_state,
    then_state,
    while_state,
    do_state,
    odd_state,
    equal_state,
    not_equal_state,
    less_than_state,
    greather_than_state,
    greather_equal_state,
    lessEqual_state,
    left_brace_state,
    right_brace_state,
    call_state,
    cin_state,
    cout_state,
    precedenceStates_count,
};

//2D array for Predence Operator Table Declaration,
extern int PO_TABLE[precedenceStates_count][predence_count];
void ini_PO_TABLE();
void parseTokens(vector<token>& t);
precedenceStates mapTokeToState(token& token);
predenceInput maptToInput(token& token);

#endif