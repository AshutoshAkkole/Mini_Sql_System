#include <iostream>
#include <fstream>

using namespace std;

// the useful classes for working with files c++ are:
// 1. fstreambase base
// 2. ifstream derived
// 3. ofstream derived

int main()
{
    string str0,str = "hello world";
    // 2 way to open a file
    // using constructor
    // ofstream out("sample_file.txt");    // write operation
    // out<<str;

    ifstream in("sample_file.txt");     // read operation

    // in>>str0;
    getline(in,str0);
    cout<<str0<<endl;
    return 0;
}