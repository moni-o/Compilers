#include "POE.h"
#include <iostream>
#include <iomanip>
using namespace std;


int PO_TABLE[predence_count][predence_count];

void ini_PO_TABLE(){
    
    
     //Terminator row
     PO_TABLE[terminator][assignment]= 1;


     //Assigment row
     PO_TABLE[assignment][terminator]= 3;
     PO_TABLE[assignment][plus_input]= 1;
     PO_TABLE[assignment][minus_input]= 1;
     PO_TABLE[assignment][leftP]= 1;
     PO_TABLE[assignment][asterick]= 1;
     PO_TABLE[assignment][slash]= 1;
     PO_TABLE[assignment][right_brace]= 3;
     

    // Plus row
    PO_TABLE[plus_input][terminator]= 3;
    PO_TABLE[plus_input][plus_input]= 3; //?
    PO_TABLE[plus_input][minus_input]= 3 ;
    PO_TABLE[plus_input][leftP]= 1;
    PO_TABLE[plus_input][rightP]= 3;
    PO_TABLE[plus_input][asterick]= 1;
    PO_TABLE[plus_input][slash]= 1;
    PO_TABLE[plus_input][then_input]= 3;
    PO_TABLE[plus_input][do_input]= 3;
    PO_TABLE[plus_input][equal_input]= 3; //?
    PO_TABLE[plus_input][not_equal]= 3;
    PO_TABLE[plus_input][greather_than]= 3;
    PO_TABLE[plus_input][less_than]= 3;
    PO_TABLE[plus_input][greather_than_equal]= 3;
    PO_TABLE[plus_input][less_than_equal]= 3;
    PO_TABLE[plus_input][right_brace]= 3;

    //Minus state
    PO_TABLE[minus_input][terminator]= 3;
    PO_TABLE[minus_input][plus_input]= 3;
    PO_TABLE[minus_input][minus_input]= 3;
    PO_TABLE[minus_input][leftP]= 1;
    PO_TABLE[minus_input][rightP]= 3;
    PO_TABLE[minus_input][asterick]= 1 ;
    PO_TABLE[minus_input][slash]= 1;
    PO_TABLE[minus_input][then_input]= 3;
    PO_TABLE[minus_input][do_input]= 3;
    PO_TABLE[minus_input][equal_input]= 3;
    PO_TABLE[minus_input][not_equal]= 3;
    PO_TABLE[minus_input][greather_than]= 3;
    PO_TABLE[minus_input][less_than]= 3;
    PO_TABLE[minus_input][greather_than_equal]= 3;
    PO_TABLE[minus_input][less_than_equal]= 3;
    PO_TABLE[minus_input][right_brace]= 3;


    //Left Parenteces
    PO_TABLE[leftP][plus_input]= 1;
    PO_TABLE[leftP][minus_input]= 1;
    PO_TABLE[leftP][leftP]= 1;
    PO_TABLE[leftP][rightP]= 2;
    PO_TABLE[leftP][asterick]= 1;
    PO_TABLE[leftP][slash]= 1;

    //Right Parenteces
    PO_TABLE[rightP][terminator]= 3;
    PO_TABLE[rightP][plus_input]= 3;
    PO_TABLE[rightP][minus_input]= 3;
    PO_TABLE[rightP][rightP]= 3;
    PO_TABLE[rightP][asterick]= 3;
    PO_TABLE[rightP][slash]= 3;

    //Multiplication row

    PO_TABLE[asterick][terminator]= 3;
    PO_TABLE[asterick][plus_input]= 3;
    PO_TABLE[asterick][minus_input]= 3;
    PO_TABLE[asterick][leftP]= 1;
    PO_TABLE[asterick][rightP]= 3;
    PO_TABLE[asterick][asterick]= 3;
    PO_TABLE[asterick][slash]= 3;
    PO_TABLE[asterick][then_input]= 3;
    PO_TABLE[asterick][do_input]= 3;
    PO_TABLE[asterick][equal_input]= 3;
    PO_TABLE[asterick][not_equal]= 3;
    PO_TABLE[asterick][greather_than]= 3;
    PO_TABLE[asterick][less_than]= 3;
    PO_TABLE[asterick][greather_than_equal]= 3;
    PO_TABLE[asterick][less_than_equal]= 3;
    PO_TABLE[asterick][right_brace]= 3;

    //Division row

    PO_TABLE[slash][terminator]= 3;
    PO_TABLE[slash][plus_input]= 3;
    PO_TABLE[slash][minus_input]= 3;
    PO_TABLE[slash][leftP]= 1;
    PO_TABLE[slash][rightP]= 3;
    PO_TABLE[slash][asterick]= 3;
    PO_TABLE[slash][slash]= 3;
    PO_TABLE[slash][then_input]= 3; 
    PO_TABLE[slash][do_input]= 3;  
     PO_TABLE[slash][equal_input]= 3;
    PO_TABLE[slash][not_equal]= 3;
    PO_TABLE[slash][greather_than]= 3;
    PO_TABLE[slash][less_than]= 3;
    PO_TABLE[slash][greather_than_equal]= 3;
    PO_TABLE[slash][less_than_equal]= 3;
    PO_TABLE[slash][right_brace]= 3;

    //IF row
    PO_TABLE[if_input][plus_input]= 1;
    PO_TABLE[if_input][minus_input]= 1;
    PO_TABLE[if_input][leftP]= 1;
    PO_TABLE[if_input][asterick]= 1;
    PO_TABLE[if_input][slash]= 1;
    PO_TABLE[if_input][then_input]= 2;
    PO_TABLE[if_input][odd_input]= 1;
    PO_TABLE[if_input][equal_input]= 1;
    PO_TABLE[if_input][not_equal]= 1;
    PO_TABLE[if_input][greather_than]= 1;
    PO_TABLE[if_input][less_than]= 1;
    PO_TABLE[if_input][greather_than_equal]= 1;
    PO_TABLE[if_input][less_than_equal]= 1;

    //Then row
    PO_TABLE[then_input][equal_input]= 1;
    PO_TABLE[then_input][if_input]= 1;
    PO_TABLE[then_input][left_brace]= 1;
    PO_TABLE[then_input][call_input]= 1;

    //While row
    PO_TABLE[while_input][plus_input]= 1;
    PO_TABLE[while_input][minus_input]= 1;
    PO_TABLE[while_input][leftP]= 1;
    PO_TABLE[while_input][asterick]= 1;
    PO_TABLE[while_input][slash]= 1;
    PO_TABLE[while_input][do_input]= 2;
    PO_TABLE[while_input][odd_input]= 1;
    PO_TABLE[while_input][equal_input]= 1;
    PO_TABLE[while_input][not_equal]= 1;
    PO_TABLE[while_input][greather_than]= 1;
    PO_TABLE[while_input][less_than]= 1;
    PO_TABLE[while_input][greather_than_equal]= 1;
    PO_TABLE[while_input][less_than_equal]= 1;

    //DO row
    PO_TABLE[do_input][assignment]= 1;
    PO_TABLE[do_input][while_input]= 1;
    PO_TABLE[do_input][left_brace]= 1;
    PO_TABLE[do_input][call_input]= 1;

    //ODD row
    PO_TABLE[odd_input][plus_input]= 1;
    PO_TABLE[odd_input][minus_input]= 1;
    PO_TABLE[odd_input][leftP]= 1;
    PO_TABLE[odd_input][asterick]= 1;
    PO_TABLE[odd_input][slash]= 1;
    PO_TABLE[odd_input][then_input]= 1;
    PO_TABLE[odd_input][do_input]= 1;


    
    // == row
    PO_TABLE[equal_input][plus_input]= 1;
    PO_TABLE[equal_input][minus_input]= 1;
    PO_TABLE[equal_input][leftP]= 1;
    PO_TABLE[equal_input][asterick]= 1;
    PO_TABLE[equal_input][slash]= 1;
    PO_TABLE[equal_input][then_input]= 1;
    PO_TABLE[equal_input][do_input]= 1;

    // NotEqual row
    PO_TABLE[not_equal][plus_input]= 1;
    PO_TABLE[not_equal][minus_input]= 1;
    PO_TABLE[not_equal][leftP]= 1;
    PO_TABLE[not_equal][asterick]= 1;
    PO_TABLE[not_equal][slash]= 1;
    PO_TABLE[not_equal][then_input]= 1;
    PO_TABLE[not_equal][do_input]= 1;

    //Greater Than
    PO_TABLE[greather_than][plus_input]= 1;
    PO_TABLE[greather_than][minus_input]= 1;
    PO_TABLE[greather_than][leftP]= 1;
    PO_TABLE[greather_than][asterick]= 1;
    PO_TABLE[greather_than][slash]= 1;
    PO_TABLE[greather_than][then_input]= 1;
    PO_TABLE[greather_than][do_input]= 1;

    //Less Than
    PO_TABLE[less_than][plus_input]= 1;
    PO_TABLE[less_than][minus_input]= 1;
    PO_TABLE[less_than][leftP]= 1;
    PO_TABLE[less_than][asterick]= 1;
    PO_TABLE[less_than][slash]= 1;
    PO_TABLE[less_than][then_input]= 1;
    PO_TABLE[less_than][do_input]= 1;

    //Greater than equal row

    PO_TABLE[greather_than_equal][plus_input]= 1;
    PO_TABLE[greather_than_equal][minus_input]= 1;
    PO_TABLE[greather_than_equal][leftP]= 1;
    PO_TABLE[greather_than_equal][asterick]= 1;
    PO_TABLE[greather_than_equal][slash]= 1;
    PO_TABLE[greather_than_equal][then_input]= 1;
    PO_TABLE[greather_than_equal][do_input]= 1;

    //Lessthan equal
    PO_TABLE[less_than_equal][plus_input]= 1;
    PO_TABLE[less_than_equal][minus_input]= 1;
    PO_TABLE[less_than_equal][leftP]= 1;
    PO_TABLE[less_than_equal][asterick]= 1;
    PO_TABLE[less_than_equal][slash]= 1;
    PO_TABLE[less_than_equal][then_input]= 1;
    PO_TABLE[less_than_equal][do_input]= 1;

    //left Brace
    PO_TABLE[left_brace][equal_input] = 1;
    PO_TABLE[left_brace][if_input] = 1;
    PO_TABLE[left_brace][while_input] = 1;
    PO_TABLE[left_brace][left_brace] = 1;
    PO_TABLE[left_brace][right_brace] = 2;
    PO_TABLE[left_brace][call_input] = 1;

    //  for(int i= 0; i<predence_count;++i){
    //     for(int j= 0; j<predence_count; ++j){
    //        cout<<setw(4)<<PO_TABLE[i][j];
    //     }
    //      cout<<endl;
    //  }

    

    
}
