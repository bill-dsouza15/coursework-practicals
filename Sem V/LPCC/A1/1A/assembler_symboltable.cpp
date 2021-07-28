#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>

#define pb push_back
#define vstr vector<string>
#define vi vector<int>
#define psi pair<string, int> 
#define fori(s,e) for(int i=(int)s;i<(int)e;i++)

using namespace std;

// comparison logic for sorting symbol table by location
bool cmp(pair<string, int>& a, pair<string, int>& b) 
{ 
    return a.second < b.second; 
} 
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
vstr checkLiteral(vstr litTable, string cParse){
    //If literal table is empty insert without checking
    if(litTable.size() == 0){
        litTable.pb(cParse);
    }
    else{
        /*Check if same literal exists within the pool. 
        If yes then do not insert literal*/
        int flag = 0;
        for(auto&x : litTable){
            if(x == cParse){
                flag=1;
                break;
            }
        }
        if(flag==0){
            litTable.pb(cParse);
        }
    }
    return litTable;
}

//Function to check symbol
map<string,int> checkSymbol(map<string,int> symTable, string cParse){
    //Insertion of symbol
    psi symbol;
    symbol.first = cParse;
    symbol.second = 0;
    symTable.insert(symbol);
    return symTable;
}
//Driver function
int main(int argc, char** argv){
    //istream object for opening file for reading
    ifstream file(argv[1]);
    string cmdline;

    //Declaration part
    int location;                                   //keeps track of the location
    vstr litTable;                                  //literal table
    map<string,int> symTable;                       //symbol table
    
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
                litTable = checkLiteral(litTable,cParse[1]);
            }
            else{
                //Check symbol and insert
                symTable = checkSymbol(symTable, cParse[1]);    
            }
            location++;
        }
        else if(sParse[0] == "LTORG"){
            location += litTable.size();
            litTable.clear();
        }
        else if(sParse[0] == "END"){
            location += litTable.size();
            litTable.clear();
            break;
        }
        else
        {
            if(sParse[1] == "DS"){
                /*Assign current location to symbol mentioned along with DS 
                and increment location by space mentioned after DS */
                symTable[sParse[0]] = location;
                location+=stoi(sParse[2]);
            }
            else if(sParse[1] == "DC"){
                /*Assign current location to symbol mentioned along with DC 
                and increment location by one */
                symTable[sParse[0]] = location;
                location++;
            }
            else{
                //Add label to symbol table
                symTable[sParse[0]] = location;

                //Rest of the line
                vstr cParse = tokenizer(sParse[2], ',');
                if(cParse[1][0] == '='){
                    //Check literal and insert
                    litTable = checkLiteral(litTable,cParse[1]);
                }
                else{
                    //Insertion of symbol
                    symTable = checkSymbol(symTable,cParse[1]);
                }
                location++;
            }
        }
    }
    file.close();

    //Print symbol table
    vector<psi> v(symTable.size());
    copy(symTable.begin(), symTable.end(),v.begin());
    sort(v.begin(), v.end(), cmp);

    cout<<"SYMBOL TABLE"<<endl;
    for (auto itr = v.begin(); itr != v.end(); ++itr){
        cout<<itr->first;
        if(itr->first.length() < 4){
            fori(0 , (4 - itr->first.length())){
                cout<<" ";
            }
        }
        cout<<"\t"<<itr->second<<endl;
    }
    cout<<endl;
    return 0;
}
