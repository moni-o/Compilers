#include <iostream>
#include <fstream>
#include "FSA.h"
using namespace std;

int main(){
    //ofstream myfile("tokens");
    char a;
    initFSA();
    cout<<"please enter a character: "<<endl;
    cin>> a;
    cout<<characterInput(a)<<endl;
    
}