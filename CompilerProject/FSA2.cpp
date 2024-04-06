#include "FSA2.h"
#include <iostream>
#include <iomanip>
using namespace std;

int FSA2[State_Count][Input_Count];

int w = 4;

void initFSA2(){



    //Start State
    FSA2[Start][Class]=Class_State;

    //Class State
    FSA2[Class_State][Variable] = PGM_Final;

    //PGM Name Final State
    FSA2[PGM_Final][LeftB] = PGM_Start;

    //PGM Start
    FSA2[PGM_Start][Variable] = Inter_State;
    FSA2[PGM_Start][Const]= Const_D;
    FSA2[PGM_Start][VAR] = VAR_State;
    FSA2[PGM_Start][Reserved]=Inter_State;

    //Const Declaration

    FSA2[Const_D][Variable]= Const_State;

    //Const State
    FSA2[Const_State][Equal] = Assigment_State;

    //Assigmen_State
    FSA2[Assigment_State][Int]= Const_VAR_De;

    //Constant Variable Declaration
    FSA2[Const_VAR_De][Comma]= Const_D;
    FSA2[Const_VAR_De][SemiColon]= PGM_Start;

    //Variable State
    FSA2[VAR_State][Variable]= VAR_Variable;

    //VAR variable
    FSA2[VAR_Variable][Comma]= VAR_State;
    FSA2[VAR_Variable][SemiColon]= PGM_Start;

    //Intermidiatefor(int input =0; input<COUNT; ++input)
    for(int input =0; input<Input_Count; ++input)
    {
        FSA2[Inter_State][input]= Inter_State;
        
    }
    FSA2[Inter_State][Const] =Const_D;
    FSA2[Inter_State][Int] = Int_Final;
    FSA2[Inter_State][VAR] = VAR_State;
    FSA2[Inter_State][EOF_Input] = EOF_STATE;

    //Integer Final
    for(int input =0; input<Input_Count; ++input)
    {
        FSA2[Int_Final][input]= Inter_State;
        
    }
    FSA2[Int_Final][EOF_Input] = EOF_STATE;


    // for(int i= 0; i<State_Count;++i){
    //     for(int j= 0; j<Input_Count; ++j){
    //        cout<<setw(w)<<FSA2[i][j];
    //     }
    //      cout<<endl;
    //  }

 

}

  SymbolInput mapSymbolInput(string c){
        if(c == "CLASS")
        {
            return Class;
        }
        else if (c == "variable")
        {
            return Variable;
        }
        else if( c == "LB")
        {
            return LeftB;
        }
        else if( c == "CONST")
        {
            return Const;
        }
       else if( c == "assign"){
        return Equal;
       }
       else if( c == "int"){
            return Int;
       }
       else if ( c == "comma"){
        return Comma;
       }
       else if(c == "semi"){
        return SemiColon;
       }
        else if( c == "VAR"){
            return VAR;
        }
        else if(isReserved(c)){
            return Reserved;
        }
        else if (c == "EOF")
        {
            return EOF_Input;
        }
        else{
            return Any;
        }
}
