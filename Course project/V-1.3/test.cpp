#include <iostream>
#include <string>
#include <typeinfo>

using namespace std;

int main()
{
    string s = "hello";
    string *b = NULL;
    char k;
    int n;
    cout<<s.substr(3,1)<<endl;
    cout<<s.length()<<endl;
    cout<<s.substr(0,s.length())<<endl;
    cout<<s.find("h")<<endl;
    cout<<typeid(k).name()<<endl;
    //cin>>n;
    //b = new string[n];
    //free(b);
    return 0;

}