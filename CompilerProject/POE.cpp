#include "POE.h"
#include <iostream>
#include <iomanip>
using namespace std;


int PO_TABLE[precedenceStates_count][predence_count];

void ini_PO_TABLE(){
     //Terminator row
     PO_TABLE[terminator_state][equal_input]= 1;


     //Assigment row
     PO_TABLE[assigment_state][terminator]= 3;
     PO_TABLE[assigment_state][plus_input]= 1;
     PO_TABLE[assigment_state][minus_input]= 1;
     PO_TABLE[assigment_state][leftP]= 1;
     PO_TABLE[assigment_state][asterick]= 1;
     PO_TABLE[assigment_state][slash]= 1;
     PO_TABLE[assigment_state][right_brace]= 3;
     

    // Plus row
    PO_TABLE[plus_state][terminator]= 3;
    PO_TABLE[plus_state][plus_input]= 3; //?
    PO_TABLE[plus_state][minus_input]= 3 ;
    PO_TABLE[plus_state][leftP]= 1;
    PO_TABLE[plus_state][rightP]= 3;
    PO_TABLE[plus_state][asterick]= 1;
    PO_TABLE[plus_state][slash]= 1;
    PO_TABLE[plus_state][then_input]= 3;
    PO_TABLE[plus_state][do_input]= 3;
    PO_TABLE[plus_state][assignment]= 3; //?
    PO_TABLE[plus_state][not_equal]= 3;
    PO_TABLE[plus_state][greather_than]= 3;
    PO_TABLE[plus_state][less_than]= 3;
    PO_TABLE[plus_state][greather_than_equal]= 3;
    PO_TABLE[plus_state][less_than_equal]= 3;
    PO_TABLE[plus_state][right_brace]= 3;

    //Minus state
    PO_TABLE[minus_state][terminator]= 3;
    PO_TABLE[minus_state][plus_input]= 3;
    PO_TABLE[minus_state][minus_input]= 3;
    PO_TABLE[minus_state][leftP]= 1;
    PO_TABLE[minus_state][rightP]= 3;
    PO_TABLE[minus_state][asterick]= 1 ;
    PO_TABLE[minus_state][slash]= 1;
    PO_TABLE[minus_state][then_input]= 3;
    PO_TABLE[minus_state][do_input]= 3;
    PO_TABLE[minus_state][assignment]= 3;
    PO_TABLE[minus_state][not_equal]= 3;
    PO_TABLE[minus_state][greather_than]= 3;
    PO_TABLE[minus_state][less_than]= 3;
    PO_TABLE[minus_state][greather_than_equal]= 3;
    PO_TABLE[minus_state][less_than_equal]= 3;
    PO_TABLE[minus_state][right_brace]= 3;


    //Left Parenteces
    PO_TABLE[leftP_state][plus_input]= 1;
    PO_TABLE[leftP_state][minus_input]= 1;
    PO_TABLE[leftP_state][leftP]= 1;
    PO_TABLE[leftP_state][rightP]= 2;
    PO_TABLE[leftP_state][asterick]= 1;
    PO_TABLE[leftP_state][slash]= 1;

    //Right Parenteces
    PO_TABLE[rightP_state][terminator]= 3;
    PO_TABLE[rightP_state][plus_input]= 3;
    PO_TABLE[rightP_state][minus_input]= 3;
    PO_TABLE[rightP_state][rightP]= 3;
    PO_TABLE[rightP_state][asterick]= 3;
    PO_TABLE[rightP_state][slash]= 3;

    //Multiplication row

    PO_TABLE[multiplication_state][terminator]= 3;
    PO_TABLE[multiplication_state][plus_input]= 3;
    PO_TABLE[multiplication_state][minus_input]= 3;
    PO_TABLE[multiplication_state][leftP]= 1;
    PO_TABLE[multiplication_state][rightP]= 3;
    PO_TABLE[multiplication_state][asterick]= 3;
    PO_TABLE[multiplication_state][slash]= 3;
    PO_TABLE[multiplication_state][then_input]= 3;
    PO_TABLE[multiplication_state][do_input]= 3;
    PO_TABLE[multiplication_state][assignment]= 3;
    PO_TABLE[multiplication_state][not_equal]= 3;
    PO_TABLE[multiplication_state][greather_than]= 3;
    PO_TABLE[multiplication_state][less_than]= 3;
    PO_TABLE[multiplication_state][greather_than_equal]= 3;
    PO_TABLE[multiplication_state][less_than_equal]= 3;
    PO_TABLE[multiplication_state][right_brace]= 3;

    //Division row

    PO_TABLE[division_state][terminator]= 3;
    PO_TABLE[division_state][plus_input]= 3;
    PO_TABLE[division_state][minus_input]= 3;
    PO_TABLE[division_state][leftP]= 1;
    PO_TABLE[division_state][rightP]= 3;
    PO_TABLE[division_state][asterick]= 3;
    PO_TABLE[division_state][slash]= 3;
    PO_TABLE[division_state][then_input]= 3; 
    PO_TABLE[division_state][do_input]= 3;  
     PO_TABLE[division_state][assignment]= 3;
    PO_TABLE[division_state][not_equal]= 3;
    PO_TABLE[division_state][greather_than]= 3;
    PO_TABLE[division_state][less_than]= 3;
    PO_TABLE[division_state][greather_than_equal]= 3;
    PO_TABLE[division_state][less_than_equal]= 3;
    PO_TABLE[division_state][right_brace]= 3;

    //IF row
    PO_TABLE[if_state][plus_input]= 1;
    PO_TABLE[if_state][minus_input]= 1;
    PO_TABLE[if_state][leftP]= 1;
    PO_TABLE[if_state][asterick]= 1;
    PO_TABLE[if_state][slash]= 1;
    PO_TABLE[if_state][then_input]= 2;
    PO_TABLE[if_state][odd_input]= 1;
    PO_TABLE[if_state][assignment]= 1;
    PO_TABLE[if_state][not_equal]= 1;
    PO_TABLE[if_state][greather_than]= 1;
    PO_TABLE[if_state][less_than]= 1;
    PO_TABLE[if_state][greather_than_equal]= 1;
    PO_TABLE[if_state][less_than_equal]= 1;

    //Then row
    PO_TABLE[then_state][equal_input]= 1;
    PO_TABLE[then_state][if_input]= 1;
    PO_TABLE[then_state][left_brace]= 1;
    PO_TABLE[then_state][call_input]= 1;

    //While row
    PO_TABLE[while_state][plus_input]= 1;
    PO_TABLE[while_state][minus_input]= 1;
    PO_TABLE[while_state][leftP]= 1;
    PO_TABLE[while_state][asterick]= 1;
    PO_TABLE[while_state][slash]= 1;
    PO_TABLE[while_state][do_input]= 2;
    PO_TABLE[while_state][odd_input]= 1;
    PO_TABLE[while_state][assignment]= 1;
    PO_TABLE[while_state][not_equal]= 1;
    PO_TABLE[while_state][greather_than]= 1;
    PO_TABLE[while_state][less_than]= 1;
    PO_TABLE[while_state][greather_than_equal]= 1;
    PO_TABLE[while_state][less_than_equal]= 1;

    //DO row
    PO_TABLE[do_state][equal_input]= 1;
    PO_TABLE[do_state][while_input]= 1;
    PO_TABLE[do_state][left_brace]= 1;
    PO_TABLE[do_state][call_input]= 1;

    //ODD row
    PO_TABLE[odd_state][plus_input]= 1;
    PO_TABLE[odd_state][minus_input]= 1;
    PO_TABLE[odd_state][leftP]= 1;
    PO_TABLE[odd_state][asterick]= 1;
    PO_TABLE[odd_state][slash]= 1;
    PO_TABLE[odd_state][then_input]= 1;
    PO_TABLE[odd_state][do_input]= 1;


    
    // == row
    PO_TABLE[equal_state][plus_input]= 1;
    PO_TABLE[equal_state][minus_input]= 1;
    PO_TABLE[equal_state][leftP]= 1;
    PO_TABLE[equal_state][asterick]= 1;
    PO_TABLE[equal_state][slash]= 1;
    PO_TABLE[equal_state][then_input]= 1;
    PO_TABLE[equal_state][do_input]= 1;

    // NotEqual row
    PO_TABLE[not_equal_state][plus_input]= 1;
    PO_TABLE[not_equal_state][minus_input]= 1;
    PO_TABLE[not_equal_state][leftP]= 1;
    PO_TABLE[not_equal_state][asterick]= 1;
    PO_TABLE[not_equal_state][slash]= 1;
    PO_TABLE[not_equal_state][then_input]= 1;
    PO_TABLE[not_equal_state][do_input]= 1;

    //Greater Than
    PO_TABLE[greather_than][plus_input]= 1;
    PO_TABLE[greather_than][minus_input]= 1;
    PO_TABLE[greather_than][leftP]= 1;
    PO_TABLE[greather_than][asterick]= 1;
    PO_TABLE[greather_than][slash]= 1;
    PO_TABLE[greather_than][then_input]= 1;
    PO_TABLE[greather_than][do_input]= 1;

    //Less Than
    PO_TABLE[less_than_state][plus_input]= 1;
    PO_TABLE[less_than_state][minus_input]= 1;
    PO_TABLE[less_than_state][leftP]= 1;
    PO_TABLE[less_than_state][asterick]= 1;
    PO_TABLE[less_than_state][slash]= 1;
    PO_TABLE[less_than_state][then_input]= 1;
    PO_TABLE[less_than_state][do_input]= 1;

    //Greater than equal row

    PO_TABLE[greather_equal_state][plus_input]= 1;
    PO_TABLE[greather_equal_state][minus_input]= 1;
    PO_TABLE[greather_equal_state][leftP]= 1;
    PO_TABLE[greather_equal_state][asterick]= 1;
    PO_TABLE[greather_equal_state][slash]= 1;
    PO_TABLE[greather_equal_state][then_input]= 1;
    PO_TABLE[greather_equal_state][do_input]= 1;

    //Lessthan equal
    PO_TABLE[lessEqual_state][plus_input]= 1;
    PO_TABLE[lessEqual_state][minus_input]= 1;
    PO_TABLE[lessEqual_state][leftP]= 1;
    PO_TABLE[lessEqual_state][asterick]= 1;
    PO_TABLE[lessEqual_state][slash]= 1;
    PO_TABLE[lessEqual_state][then_input]= 1;
    PO_TABLE[lessEqual_state][do_input]= 1;

    //Right Brace
    PO_TABLE[left_brace_state][equal_input] = 1;
    PO_TABLE[left_brace_state][if_input] = 1;
    PO_TABLE[left_brace_state][while_input] = 1;
    PO_TABLE[left_brace_state][left_brace] = 1;
    PO_TABLE[left_brace_state][right_brace] = 2;
    PO_TABLE[left_brace_state][call_input] = 1;

    //  for(int i= 0; i<precedenceStates_count;++i){
    //     for(int j= 0; j<predence_count; ++j){
    //        cout<<setw(4)<<PO_TABLE[i][j];
    //     }
    //      cout<<endl;
    //  }

    

    
}
