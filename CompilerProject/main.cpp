#include <iostream>
#include <fstream>
#include "FSA.h"
#include <vector>
using namespace std;

int main(){
    //ofstream myfile("tokens");
    string a = "a + b";
    initFSA();
    cout<<"please enter a character: "<<endl;
    
    vector<token> tokens =tokenizer(a);
    for(const auto& token: tokens){
        cout<<"Tokens: "<<token.value<<", type: "<< token.classification<<endl;
    }
    

}