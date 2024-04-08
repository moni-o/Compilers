#ifndef FSA2_H
#define FSA2_H
#include "FSA.h"
#include <vector>
#include <iostream>

enum SymbolInput{
    Class,
    Variable,
    LeftB,
    Const,
    Equal,
    Int,
    Comma,
    SemiColon,
    VAR,
    Reserved,
    Any,
    EOF_Input,
    Input_Count,

};

enum SymbolStates{
    Start,
    Class_State,
    PGM_Final,
    PGM_Start,
    Const_D,
    Const_State,
    Assigment_State,
    Const_VAR_De,
    VAR_State,
    VAR_Variable,
    Inter_State,
    Int_Final,
    EOF_STATE,
    State_Count,
};

extern int FSA2[State_Count][Input_Count]; //2D array

void initFSA2();

 struct SymbolTable_Entries{
        string symbol;
        string classi;
        string val;
        int addr;
        string seg;
    };

vector<SymbolTable_Entries>SymbolTable(vector<token>& e);
SymbolInput mapSymbolInput(string c);



#endif