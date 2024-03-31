#include "FSA.h"
#include <iostream>
#include <iomanip>
#include <cctype>
using namespace std;



int width = 6;

//Initializes the FSA Table 
void initFSA(){
   


    FSA_TABLE[START][LETTER]=VARIABLE;
    FSA_TABLE[START][DIGIT]=DIGIT_STATE;
    FSA_TABLE[START][ASTERICK]=MOP;
    FSA_TABLE[START][SLASH]=SLASH_State;
    FSA_TABLE[START][EQUAL]=EQUALS;
    FSA_TABLE[START][LESSTHAN]=LESSTHAN_STATE;
    FSA_TABLE[START][GREATHERTHAN]= GREATHERTHAN_STATE;
    FSA_TABLE[START][PLUS]=ADDFINAL;
    FSA_TABLE[START][MINUS]=MINUSFINAL;
    FSA_TABLE[START][COMMA]= COMMADEL;
    FSA_TABLE[START][LEFTBRACE]=LEFTBRACE_FINAL;
    FSA_TABLE[START][RIGHTBRACE]=RIGHTBRACE_FINAL;
    FSA_TABLE[START][LEFTP]=LEFTPARENTECES;
    FSA_TABLE[START][RIGHTP]= RIGHTPARENTECES;
    FSA_TABLE[START][SEMICOLON]=SEMIDELI;
    FSA_TABLE[START][Excl]= EXCLAMATION;
    FSA_TABLE[START][WS] = START;
    FSA_TABLE[START][OTHER]= ERROR;

    

    //Error State
    for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[ERROR][input]= ERROR;
        //cout<<FSA_TABLE[ERROR][input];
    }
    

    // MOP STATE
    for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[MOP][input]=MOP;
        //cout<<FSA_TABLE[MOP][input];
        
    }
   

    //Digits State
     for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[DIGIT_STATE][input]=INTEGER;
        //cout<<FSA_TABLE[DIGIT_STATE][input];
    }
    FSA_TABLE[DIGIT_STATE][DIGIT]=DIGIT_STATE;
    

        
    //Integer State
      for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[INTEGER][input]=INTEGER;
        //cout<<FSA_TABLE[INTEGER][input];
    }

    //Variable
      for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[VARIABLE][input]=FINALVARIABLE;
        //cout<<FSA_TABLE[VARIABLE][input];
    }
    FSA_TABLE[VARIABLE][LETTER]=VARIABLE;
    FSA_TABLE[VARIABLE][DIGIT]=VARIABLE;

    //Final Varible state
      for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[FINALVARIABLE][input]=FINALVARIABLE;
        //cout<<FSA_TABLE[VARIABLE][input];
    }
 
    
    //Slash
     for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[SLASH_State][input]=DIVISION;
        //cout<<FSA_TABLE[SLASH_State][input];
    }
    FSA_TABLE[SLASH_State][ASTERICK]=MULTILINE;
   
    
    //MultiLine State
    for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[MULTILINE][input]=MULTILINE;
        //cout<<FSA_TABLE[MULTILINE][input];
    }
    FSA_TABLE[MULTILINE][ASTERICK]=ENDMULTILINE;
    //cout<<endl;

    //End of MultiLine
      for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[ENDMULTILINE][input]=MULTILINE;
        //cout<<FSA_TABLE[SLASH_State][input];
    }
    FSA_TABLE[ENDMULTILINE][SLASH]=START;
    //cout<<endl;

    //Division
      for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[DIVISION][input]=DIVISION;
        //cout<<FSA_TABLE[DIVISION][input];
    }

    //Equals
     for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[EQUALS][input]=ASSIGMENT;
        //cout<<FSA_TABLE[EQUALS][input];
    }
    FSA_TABLE[EQUALS][EQUAL]=FINALEQUAL;

    //Assigment
     for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[ASSIGMENT][input]=ASSIGMENT;
    }

    //Final Equal
     for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[FINALEQUAL][input]=FINALEQUAL;
    }
    
    //LessThan
     for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[LESSTHAN_STATE][input]=LESSTHAN_FINAL;
    }
    FSA_TABLE[LESSTHAN_STATE][LETTER]=LESSTHAN_STATE;
    FSA_TABLE[LESSTHAN_STATE][EQUAL]=LESSEQUAL;

    //LessThanFinal State
    for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[LESSTHAN_FINAL][input]=LESSTHAN_FINAL;
    }

    //LessEqual State
    for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[LESSEQUAL][input]=LESSEQUAL;
    }

    //Greather Than State
    for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[GREATHERTHAN_STATE][input]=GREATERFINAL;
    }
    FSA_TABLE[GREATHERTHAN_STATE][EQUAL]=GREATEREQUAL;

    //Greater Final State
    for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[GREATERFINAL][input]=GREATERFINAL;
    }

    //GreaterEqual State
    for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[GREATEREQUAL][input]=GREATEREQUAL;
    }

    //ADDFinal State
    for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[ADDFINAL][input]=ADDFINAL;
    }

    //MinusFinal State
    for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[MINUSFINAL][input]= MINUSFINAL;
    }

    //Comma Delimiter State
    for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[COMMADEL][input]= COMMADEL;
    }

    //LeftBrace Final State
    for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[LEFTBRACE_FINAL][input]= LEFTBRACE_FINAL;
        
    }

    //Right Brace Final
    for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[RIGHTBRACE_FINAL][input]= RIGHTBRACE_FINAL;
        
    }

    //Left Parenteces Final State
    for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[LEFTPARENTECES][input]= LEFTPARENTECES;
    }
    
    //Right Parenteces Final State
    for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[RIGHTPARENTECES][input]= RIGHTPARENTECES;
        
    }

    //SemiDeli
    for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[SEMIDELI][input]= SEMIDELI;
        
    }

    //Exclamation State
    for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[EXCLAMATION][input]= NOT;
        
    }
     FSA_TABLE[EXCLAMATION][EQUAL]= NOTEQUAL;
     FSA_TABLE[EXCLAMATION][OTHER] = ERROR;    ///? Do I really need it;Recheck this

     //Not State

     for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[NOT][input]= NOT;
        
    }
  
    //Not equal State
    for(int input =0; input<COUNT; ++input)
    {
        FSA_TABLE[NOTEQUAL][input]= NOTEQUAL;
        
    }
    
    cout<<endl;

    // for(int i= 0; i<count_State;++i){
    //     for(int j= 0; j<COUNT; ++j){
    //         cout<<setw(width)<<FSA_TABLE[i][j];
    //     }
    //     cout<<endl;
    // }

}
    

//Function that will identify what type of input we are reading. Is it a letter , digit, we are getting.
Input characterInput(char c){
    if(isalpha(c))return LETTER;
    if(isdigit(c)) return DIGIT;
    switch (c)
    {
    case '*': return ASTERICK;
    case '/': return SLASH;
    case '=': return EQUAL;
    case '<': return LESSTHAN;
    case '>': return GREATHERTHAN;
    case '-': return MINUS;
    case ',': return COMMA;
    case '{': return LEFTBRACE;
    case '}': return RIGHTBRACE;
    case '(': return LEFTP;
    case ')': return RIGHTP;
    case ';': return SEMICOLON;
    case '!': return Excl;
    case ' ': case '\n': case '\t': return WS;
    default:
        return OTHER;
    }
}