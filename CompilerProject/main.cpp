#include <iostream>
#include <fstream>
#include <sstream>
#include "FSA.h"
#include "FSA2.h"
#include <vector>
#include <iomanip>
using namespace std;

int main(){
    //ofstream myfile("tokens");

    initFSA();
    initFSA2();
   
    string a = "hello this is me";
    string filePath = "Pgm1.txt"; // Path to the file to read
    ifstream file(filePath);
    stringstream buffer;
    int x = 45;

    if (!file.is_open()) {
        
        return EXIT_FAILURE;
     }
    buffer << file.rdbuf();
    
     string input = buffer.str();

     file.close(); // Close the file


   

   vector<token> tokens =tokenizer(input);
    // for(const auto& token: tokens){
    //     cout<<token.value<<" type: "<< token.classification<<endl;
    // }
    
    
    vector<SymbolTable_Entries> finalTable=SymbolTable(tokens);
    cout<<"Symbol"<<setw(x-2)<<" Classification"<<setw(x)<<" Value"<<setw(x)<<" Address"<<setw(x)<<" Segment"<<endl;
     for(const auto& token: finalTable){
       cout<<token.symbol<<std::right<<setw(x)<<token.classi<<setw(x)<<token.val<<setw(x)<<token.addr<<setw(x)<<token.seg<<endl;
    }

    return 0;
}