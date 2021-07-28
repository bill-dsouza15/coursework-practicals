#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

#define pb push_back
#define vstr vector<string>
#define vstri vector<pair<string, pair<int,int>>>
#define psii pair<string, pair<int,int>> 
#define fori(s,e) for(int i=(int)s;i<(int)e;i++)

using namespace std;

//Function to generate tokens
vstr tokenizer(string line, char delimiter){
    stringstream ss(line);
    string s;
    vstr tokens;

    while (getline(ss, s, delimiter)){
        tokens.pb(s);
    }
    return tokens;
}

//Function to check literal
vstri checkLiteral(vstri litTable, string cParse, int pool, int *nLit){
    //If literal table is empty insert without checking
    if(litTable.size() == 0){
        psii literal = make_pair(cParse,make_pair(0, pool));
        litTable.pb(literal);
        (*nLit)++;
    }
    else{
        //Check if same literal exists within the pool. If yes then do not insert literal
        int flag = 0;
        for(auto&x : litTable){
            if(x.first == cParse && x.second.second == pool){
                flag=1;
                break;
            }
        }
        if(flag==0){
            psii literal = make_pair(cParse,make_pair(0, pool));
            litTable.pb(literal);
            (*nLit)++;
        }
    }
    return litTable;
}

//Driver function
int main(int argc, char** argv){
    //istream object for opening file for reading
    ifstream file(argv[1]);
    string cmdline;

    //Declaration part
    int location;                                   //keeps track of the location
    vstri litTable;                                 //literal table
    int nLit=0, pool=1;                             //keeps track of no of literals and pool count
    
    
    while(getline(file,cmdline)){
        vstr sParse = tokenizer(cmdline,' ');

        //Logic for checking the tokens and finding the type of statements
        if(sParse[0].compare("START") == 0){
            //Get the start location
            location = stoi(sParse[1]);
        }

        else if(sParse[0] == "MOVEM" ||  sParse[0] == "MOVER" || sParse[0] == "ADD" || sParse[0] == "SUB"){   
            vstr cParse = tokenizer(sParse[1], ',');
            if(cParse[1][0] == '='){
                //Check literal and insert
                litTable = checkLiteral(litTable,cParse[1],pool,&nLit);
            }
            location++;
        }

        else if(sParse[0] == "LTORG"){
            /*Insert literals in the pool before LTORG 
and insert their locations in literal table*/
            fori(litTable.size()-nLit,litTable.size()){
                litTable[i].second.first = location;
                location++;
            }
            pool++;
            nLit = 0;
        }
        else if(sParse[0] == "END"){
            /*Insert no of literals in the pool before END in vector 
and insert their locations in literal table*/
            fori(litTable.size()-nLit,litTable.size()){
                litTable[i].second.first = location;
                location++;
            }
            pool++;
            nLit = 0;
            break;
        }
        else
        {
            if(sParse[1] == "DS"){
                //Increment location by space mentioned after DS 
                location+=stoi(sParse[2]);
            }
            else if(sParse[1] == "DC"){
                /*Assign current location to symbol mentioned along with DC 
   and increment location by one*/
                location++;
            }
            else{
                //Rest of the line
                vstr cParse = tokenizer(sParse[2], ',');
                if(cParse[1][0] == '='){
                    //Check literal and insert
                    litTable = checkLiteral(litTable,cParse[1],pool,&nLit);
                }
                location++;
            }
        }
    }
    file.close();

    //Print literal table
    cout<<"LITERAL TABLE"<<endl;
    for(auto&x : litTable){
        cout<<x.first<<"\t"<<x.second.first<<endl;
    }
    cout<<endl;

    return 0;
}
