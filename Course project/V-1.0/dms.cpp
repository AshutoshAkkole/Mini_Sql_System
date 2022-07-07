#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int check_command(string command);
void create_table(string command);

int main()
{
    string command;
    int command_code;

    while(true)
    {
        cout<<"TY17_dms>";
        cin>>command;
        
        command_code = check_command(command);

        if(command_code==1)
        {
            create_table(command);
            cout<<"\nSuccessfully table created\n"<<endl;
        }
        else if(command_code==-1)
        {
            cout<<"\ncommand invalid\n"<<endl;
        }
        else if(command_code==0)
        {
            cout<<"\nquiting"<<endl;
            break;
        }

    }

    return 0;
}

int check_command(string command)
{
    if(command.substr(0,12) == "create#table")
        return 1;
    else if(command.substr(0,4) == "quit")
        return 0;
    else
        return -1;
}

void create_table(string command)
{
    string table_name;
    int table_name_len=0,i=0;

    while(command[13+i]!= '#')
    {
        table_name_len=table_name_len+1;
        i = i+1;
    }

    table_name = command.substr(13,table_name_len) + ".txt";
    cout<<"\ntable name is:"<<table_name<<"\n"<<endl;

    ofstream out("tables\\"+command.substr(13,table_name_len));
    out<<command.substr(13,command.length()-12);
}