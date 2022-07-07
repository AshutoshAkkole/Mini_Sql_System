#include <iostream>
#include <string>

using namespace std;

int main()
{
    string s = "hello";
    string *b = NULL;
    int n;
    cout<<s.substr(0,3)<<endl;
    cout<<s.length()<<endl;
    cout<<s.substr(0,s.length());
    //cin>>n;
    //b = new string[n];
    //free(b);
    return 0;

}