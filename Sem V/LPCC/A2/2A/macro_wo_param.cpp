#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#define pb push_back
#define vstr vector<string>
#define vpsi vector<pair<string, int>>
#define vpss vector<pair<string, string>>
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

//Driver function
int main(int argc, char** argv){
    //istream object for opening file for reading
    ifstream file(argv[1]);
    string cmdline;

    //ostream object to open file to write Intermediate code
    ofstream ic ("IntermediateCode.txt", ofstream::app);
    string insLine;

    //Declaration part
    int location = 0;                                   //keeps track of the location
    vpsi mnt;                                           //Macro Name Table
    vpss mdt;                                           //Macro Definition Table
    int d=0,e=1;                                        //Definition and Expansion flags
    
    while(getline(file,cmdline)){
        vstr sParse = tokenizer(cmdline,' ');

        //Logic for checking the tokens and creating MDT and MNT
        if(sParse[0].compare("MACRO") == 0){
            d=1;
            mnt.pb(make_pair(sParse[1],location));
            mdt.pb(make_pair(sParse[1],""));
            location++;
        }
        else if(sParse[0].compare("MEND") == 0){
            d=0;
            mdt.pb(make_pair(sParse[0],""));
            location++;
        }
        else
        {
            if(d==1){
                mdt.pb(make_pair(sParse[0],sParse[1]));
                location++;
            }
            else if(d==0){
                ic<<cmdline<<endl;
            }
        }
    }
    file.close();
    ic.close();

    //Print MNT
    cout<<"MACRO NAME TABLE"<<endl;
    for (auto itr : mnt){
        cout<<itr.first;
        if(itr.first.length() < 8){
            fori(0 , (8 - itr.first.length())){
                cout<<" ";
            }
        }
        cout<<"  "<<itr.second<<endl;
    }
    cout<<endl;

    //Print MDT
    cout<<"MACRO DEFINITION TABLE"<<endl;
    for (auto itr : mdt){
        cout<<itr.first;
        if(itr.first.length() < 8){
            fori(0 , (8 - itr.first.length())){
                cout<<" ";
            }
        }
        cout<<"  "<<itr.second<<endl;
    }
    cout<<endl;
    return 0;
}