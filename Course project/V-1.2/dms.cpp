#include <iostream>
#include <fstream>
#include <string>
//#include <filesystem>

using namespace std;

int check_command(string command);
int create_table(string command);
void add_schema(string table_details);
void insert_values(string command);
void drop_tables(string command);
void update_data(string command);
void instr();
void desc(string command);
void show_tables();
int check_exist(string table_name);

int main()
{
    string command;
    int command_code;

    while(true)
    {
        cout<<"TY17_dms>";
        getline(cin,command);
        
        command_code = check_command(command);

        if(command_code==1)
        {
            if(create_table(command)==1)
                cout<<"Successfully table created\n"<<endl;
        }
        else if(command_code==2)
        {
            insert_values(command);
            cout<<"values added table successfully\n";
        }
        else if(command_code==3)
        {
            drop_tables(command);
            cout<<"table deleted successfully\n";
        }
        else if(command_code==4)
        {
            update_data(command);
            cout<<"data updated successfully\n";
        }
        else if(command_code==5)
        {
            instr();
            cout<<"\n\n instruction execution successfully\n";
        }
        else if(command_code==6)
        {
            desc(command);
            cout<<"\nhelp table executed\n";
        }
        else if(command_code==7)
        {
            show_tables();
            cout<<"\nall the tables\n";
        }
        else if(command_code==0)
        {
            cout<<"\nquiting"<<endl;
            break;
        }
        else if(command_code==-1)
        {
            cout<<"\ncommand invalid\n"<<endl;
        }

    }

    return 0;
}

int check_command(string command)
{
    if(command.substr(0,12) == "CREATE TABLE")
        return 1;
    else if(command=="HELP CMD")
        return 5;
    else if(command.substr(0,4)=="DESC")
        return 6;
    else if(command=="HELP TABLES")
        return 7;
    else if(command.substr(0,11) == "INSERT INTO")
        return 2;
    else if(command.substr(0,10) == "DROP TABLE")
        return 3;
    else if(command.substr(0,6) == "UPDATE")
        return 4;
    else if(command.substr(0,4) == "QUIT")
        return 0;
    else
        return -1;
}

int check_exist(string table_name)
{
    string data;

    ifstream file("schema//schema.txt");
    while(getline(file,data))
    {
        if(table_name==data.substr(0,data.find("(")))
        {
            return 0;
        }
    }
    return 1;
}

void instr()
{
    string data;
    ifstream file("HelpCmd.txt");
    while(getline(file,data))
    {
        cout<<data<<endl;
    }
}

void show_tables()
{
    string data;

    ifstream file("schema//schema.txt");
    while(getline(file,data))
    {
        cout<<data.substr(0,data.find("("))<<endl;
    }
}

void desc(string command)
{
    string table_name,column_names,data;
    int table_name_len=0,i=0;
    int a=0,b=0;

    // getting table name
    while(command[5+i]!= ';')
    {
        table_name_len=table_name_len+1;
        i = i+1;
    }
    table_name= command.substr(5,table_name_len);
    i=0;

    ifstream file("schema//schema.txt");
    while(getline(file,data))
    {
        if(data.substr(0,data.find("("))==table_name)
        {
            a=data.find("(")+1;
            b=data.find(")");
            cout<<data.substr(a,b);
        }
    }
}

void add_schema(string table_details)
{
    fstream out("schema\\schema.txt",ios::app);
    out<<table_details<<endl;
    out.close();
}

int create_table(string command)
{
    string table_name,column_names;
    int table_name_len=0,i=0;
    int space_watch=0;

    // getting table name
    while(command[13+i]!= '(')
    {
        table_name_len=table_name_len+1;
        i = i+1;
    }

    // get table name
    table_name = command.substr(13,table_name_len);
    if(check_exist(table_name)==0)
    {
        cout<<"table already exist"<<endl;
        return 0;
    }
    else
    {
    cout<<"\ntable name is:"<<table_name<<"\n"<<endl;

    // create table and add table colums

        //get column names
    for(int i=13+table_name_len;i<command.length();i++)
    {
        if(command[i]=='(' || command[i]==')' || command[i]==';' )
        {
            continue;
        }
        else if(command[i]==' ')
        {
            space_watch = 1;
        }
        else if(command[i]==',')
        {
            column_names = column_names + ' ';
            space_watch = 0;
        }
        else if(space_watch == 0)
        {
            column_names = column_names + command[i];
        }
    }

        //create table and column names
    fstream out("tables\\"+command.substr(13,table_name_len),ios::app);
    out<<column_names<<endl;
    out.close();

    // add into schema
    add_schema(command.substr(13,command.length()-12));
    return 1;
    }
}

void insert_values(string command)
{
    string values,table_name;
    int table_name_len=0,i=0;

    // table name length
    while(command[12+i]!= ' ')
    {
        table_name_len=table_name_len+1;
        i = i+1;
    }

    // get table name
    table_name = command.substr(12,table_name_len);
    
    // insert values
    values = command.substr(12+table_name_len+7,command.length()-1);

    fstream out("tables\\"+table_name,ios::app);
    out<<values<<endl;
    out.close();

}

void drop_tables(string command)
{
    string table_name;
    int table_name_len=0,i=0;

    // table name length
    while(command[11+i]!= ';')
    {
        table_name_len=table_name_len+1;
        i = i+1;
    }

    // get table name + location
    table_name = "tables\\"+command.substr(11,table_name_len);
    //cout<<table_name;

    //delete table
    remove(table_name.c_str());
}

void update_data(string command)
{
    string table_name,upt_column,upt_values,schema_column,data,value_check;
    int table_name_len=0,i=0,assign_watcher=0,temp=0,temp1=0,number_of_para_acutal=1,single_comma_counter=0;
    int number_of_para=1,where_para_num=0;
    int *cloumn_count = NULL;
    string *parameters = NULL;
    string *actual_para = NULL;
    string *upt_values_value =NULL;
    string where_para[2]={"",""};

    // table name length
    while(command[7+i]!= ' ')
    {
        table_name_len=table_name_len+1;
        i = i+1;
    }

    // get table name
    table_name =command.substr(7,table_name_len);

    //get coulmns names to be updated
    for(int i= 7 + table_name_len + 5 ; i<command.length();i++)
    {
        
        if(command[i]==',')
        {
            upt_column = upt_column + ' ';
            assign_watcher=0;
        }
        else if(command[i]=='=')
        {
            assign_watcher = 1;
        }
        else if(assign_watcher==0)
        {
            upt_column = upt_column + command[i];
        }
        else
        {
            continue;
        }
    }
    //cout<<upt_column;

    assign_watcher = 0;

    // get the values to be updated
    for(int i= 7 + table_name_len + 5 ; i<command.find("WHERE")-1;i++)
    {
        
        if(command[i]=='=')
        {
            assign_watcher = 1;
        }
        else if(command[i]==',')
        {
            upt_values = upt_values + ' ';
            assign_watcher=0;
        }
        else if(assign_watcher==1)
        {
            upt_values = upt_values + command[i];
        }
        else
        {
            continue;
        }
    }
    //cout<<upt_values<<endl;

    // getting the schema
    ifstream out("schema\\schema.txt");
    while(getline(out,schema_column))
    {
        //cout<<schema_column<<endl;
        //cout<<schema_column.find("(")<<endl;
        if(schema_column.substr(0,schema_column.find("("))==table_name)
        {
            //cout<<"found"<<endl;
            break;
        }
    }
    out.close();

    // looking for # column
    for(int i=0;i<upt_column.length();i++)
    {
        if(upt_column[i]==' ')
        {   
            number_of_para = number_of_para + 1;
        }
    }
    cloumn_count = new int[number_of_para];
    parameters = new string[number_of_para];
    upt_values_value = new string[number_of_para];


    // set dynamic int array to zero
    for(int i=0;i<number_of_para;i++)
    {
        cloumn_count[i]=0;
    }
    
    // assign number for para to set values
        // splitting column names
    for(int i=0;i<number_of_para;i++)
    {
        for(int j=temp;j<upt_column.length();j++)
        {
            if(upt_column[j]==' ')
            {
                temp = j+1;
                break;
            }
            else
            {
                parameters[i]=parameters[i]+upt_column[j];
            }
        }
        //cout<<parameters[i];

    }
    temp=0;
    cout<<"\n";
    for(int i=0;i<number_of_para;i++)
    {
        for(int j=temp;j<upt_values.length();j++)
        {
            if(upt_values[j]==' ' && single_comma_counter%2==0)
            {
                temp = j+1;
                break;
            }
            else if(upt_values[j]=='"')
            {
                single_comma_counter+=1;
                upt_values_value[i]+='"';
            }
            else
            {
                upt_values_value[i]+=upt_values[j];
            }
        }
        cout<<upt_values_value[i]<<endl;

    }

    //assigning numbers
    for(int i=0;i<number_of_para;i++)
    {
        
        for(int j=0;j<schema_column.find(parameters[i]);j++)
        {
            if(schema_column[j]==',')
            {
                cloumn_count[i]+=1;
            }
        }
       // cout<<cloumn_count[i]<<endl;
    }

    //where clause
    temp=0;
    for(int i=command.find("WHERE")+6;i<command.length()-1;i++)
    {
        if(command[i]!='=' && temp==0)
        {
            where_para[0]+=command[i];
        }
        else if(command[i]=='=')
        {
            temp=1;
            continue;
        }
        else
        {
            where_para[1]+=command[i];
        }
    }

    for(int i=0;i<schema_column.find(where_para[0]);i++)
    {

        if(schema_column[i]==',')
        {
            where_para_num= where_para_num + 1;
        }

    }

    //cout<<where_para_num<<endl;
    
   ifstream file("tables\\"+table_name);
   ofstream file2("tables\\"+table_name+'1');

   getline(file,data);

   for(int i=0;i<data.length();i++)
   {
       if(data[i]==' ')
       {
           number_of_para_acutal+=1;
       }
   }

    actual_para = new string[number_of_para_acutal];

   file2<<data<<endl;

   while(getline(file,data))
   {
       temp = where_para_num;
       for(int i=1;i<data.length()-2;i++)
       {
           if(temp==0)
           {
               temp1=i;
               break;
           }
           if(data[i]==',')
           {
               temp-=1;
           }
       }
       //cout<<"temp1 is"<<temp1<<endl;
       for(int j=temp1;j<data.length()-2;j++)
       {
           if(data[j]!=',')
           {
               value_check+=data[j];
           }
           else
           {
               break;
           }
       }
       //cout<<"check value is"<<value_check<<endl;
       //cout<<"where para 2 is"<<where_para[1]<<endl;

       if(value_check==where_para[1])
       {
           temp=0;
           for(int i=0;i<number_of_para_acutal;i++)
           {
               actual_para[i]="";
           }
           for(int i=1;i<data.length()-2;i++)
           {
               if(data[i]==',')
               {
                   temp+=1;
                   continue;
               }
               else
               {
                   actual_para[temp]+=data[i];
               }
           }

           //cout<<"1"<<endl;
           for(int i=0;i<number_of_para;i++)
           {
               temp1 = cloumn_count[i];
               actual_para[temp1]=upt_values_value[i];
               //cout<<actual_para[temp1]<<endl;
           }

           //cout<<"2"<<endl;

            data = "(";
           for(int i=0;i<number_of_para_acutal-1;i++)
           {
               data+=actual_para[i]+",";
           }
           data+=actual_para[number_of_para_acutal-1]+");";

           cout<<"data is"<<data<<endl;

           file2<<data<<endl;
           
           value_check="";
       }

       else
       {
           file2<<data<<endl;
       }

       value_check="";

   }

    file2.close();
    file.close();
   remove(("tables\\"+table_name).c_str());

   rename(("tables\\"+table_name+"1").c_str(),("tables\\"+table_name).c_str());

    


}