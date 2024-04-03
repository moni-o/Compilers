#include <iostream>
#include <fstream>
#include <sstream>
#include "FSA.h"
#include <vector>
using namespace std;

int main(){
    //ofstream myfile("tokens");

    initFSA();
   
    string a = "Class PRGM1{ CONST M = 7, n N = 85; VAR X, Y, Z; X = M + Y * Z; X = M + Y * Z + 12;} ";

    string filePath = "trial.txt"; // Path to the file to read
    ifstream file(filePath);
    stringstream buffer;

    if (!file.is_open()) {
        
        return EXIT_FAILURE;
    }
    buffer << file.rdbuf();
    
    string input = buffer.str();

    file.close(); // Close the file




   vector<token> tokens =tokenizer(input);
    for(const auto& token: tokens){
        cout<<"Token "<<token.value<<" type: "<< token.classification<<endl;
    }
    

}