#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#define pb push_back
#define vstr vector<string>
#define vpis vector<pair<int, string>>
#define vpsii vector<pair<string, pair<int, int>>>
#define psii pair<string, pair<int, int>>
#define psi pair<string, int>
#define fori(s, e) for (int i = (int)s; i < (int)e; i++)

using namespace std;

//Function to create map of codes for the statements
map<string, string> ICcode()
{
    map<string, string> m;
    m["START"] = "(AD,1)";
    m["MOVER"] = "(IS,1)";
    m["MOVEM"] = "(IS,2)";
    m["ADD"] = "(IS,3)";
    m["SUB"] = "(IS,4)";
    m["LTORG"] = "(AD,2)";
    m["DC"] = "(DL,1)";
    m["DS"] = "(DL,2)";
    m["END"] = "(AD,3)";
    return m;
}

// comparison logic for sorting symbol table by location
bool cmp(pair<string, int> &a, pair<string, int> &b)
{
    return a.second < b.second;
}

//Function to generate tokens
vstr tokenizer(string line, char delimiter)
{
    stringstream ss(line);
    string s;
    vstr tokens;
    while (getline(ss, s, delimiter))
    {
        tokens.pb(s);
    }
    return tokens;
}

//Function to check literal
vpsii checkLiteral(vpsii litTable, string cParse, int pool, int *nLit)
{
    //If literal table is empty insert without checking
    if (litTable.size() == 0)
    {
        psii literal = make_pair(cParse, make_pair(0, pool));
        litTable.pb(literal);
        (*nLit)++;
    }
    else
    {
        //Check if same literal exists within the pool. If yes then do not insert literal
        int flag = 0;
        for (auto &x : litTable)
        {
            if (x.first == cParse && x.second.second == pool)
            {
                flag = 1;
                break;
            }
        }
        if (flag == 0)
        {
            psii literal = make_pair(cParse, make_pair(0, pool));
            litTable.pb(literal);
            (*nLit)++;
        }
    }
    return litTable;
}

//Function to check symbol
map<string, int> checkSymbol(map<string, int> symTable, string cParse)
{
    //Insertion of symbol
    psi symbol = make_pair(cParse, 0);
    symTable.insert(symbol);
    return symTable;
}

//Driver function
int main(int argc, char **argv)
{
    //istream object for opening file for reading
    ifstream file(argv[1]);
    string cmdline;

    //ostream object for opening file for writing
    ofstream ic("IntermediateCode.txt", ofstream::app);
    string insLine, constants;
    map<string, string> codeMap = ICcode();

    //Declaration part
    int location;              //keeps track of the location
    map<string, int> symTable; //symbol table
    vpsii litTable;            //literal table
    vpis poolTable;            //pool table
    int nLit = 0, pool = 1;    //keeps track of no of literals and pool count

    while (getline(file, cmdline))
    {
        vstr sParse = tokenizer(cmdline, ' ');
        //Logic for checking the tokens and finding the type of statements
        if (sParse[0].compare("START") == 0)
        {
            //Get the start location
            location = stoi(sParse[1]);
            //Intermediate code part
            insLine = codeMap[sParse[0]];             //Adds START
            insLine.append(" (C," + sParse[1] + ")"); //Adds constant (address)
        }
        else if (sParse[0] == "MOVEM" || sParse[0] == "MOVER" || sParse[0] == "ADD" || sParse[0] == "SUB")
        {
            vstr cParse = tokenizer(sParse[1], ',');
            //Intermediate code part
            insLine = codeMap[sParse[0]];    //Adds MOVEM, MOVER, etc.
            insLine.append(" " + cParse[0]); //Adds AREG, BREG, etc.
            if (cParse[1][0] == '=')
            {
                //Check literal and insert
                litTable = checkLiteral(litTable, cParse[1], pool, &nLit);
                //Intermediate code part
                insLine.append(" (L," + to_string(litTable.size()) + ")"); //Adds literal
            }
            else
            {
                //Check symbol and insert
                symTable = checkSymbol(symTable, cParse[1]);
                //Intermediate code part
                insLine.append(" " + cParse[1]); //Adds symbol
            }
            location++;
        }
        else if (sParse[0] == "LTORG")
        {
            //Insert literals in the pool before LTORG and insert their locations in literal table
            fori(litTable.size() - nLit, litTable.size())
            {
                litTable[i].second.first = location;
                location++;
            }
            //Insert entry in pool table
            poolTable.pb(make_pair(pool, "#" + to_string(litTable.size() - nLit + 1)));
            pool++;
            nLit = 0;
            //Intermediate code part
            insLine = codeMap[sParse[0]]; //Adds LTORG
        }
        else if (sParse[0] == "END")
        {
            //Insert no of literals in the pool before END in vector and insert their locations in literal table
            fori(litTable.size() - nLit, litTable.size())
            {
                litTable[i].second.first = location;
                location++;
            }
            //Insert entry in pool table
            poolTable.pb(make_pair(pool, "#" + to_string(litTable.size() - nLit + 1)));
            pool++;
            nLit = 0;
            //Intermediate code part
            insLine = codeMap[sParse[0]]; //Adds END
            ic << insLine << endl;
            break;
        }
        else
        {
            if (sParse[1] == "DS")
            {
                /*Assign current location to symbol mentioned along with DS 
                and increment location by space mentioned after DS */
                symTable[sParse[0]] = location;
                location += stoi(sParse[2]);
                //Intermediate code part
                insLine = codeMap[sParse[1]];             //Adds DS
                insLine.append(" (C," + sParse[2] + ")"); //Adds constant
            }
            else if (sParse[1] == "DC")
            {
                /*Assign current location to symbol mentioned along with DC 
                and increment location by one */
                symTable[sParse[0]] = location;
                location++;
                //Intermediate code part
                insLine = codeMap[sParse[1]];             //Adds DC
                insLine.append(" (C," + sParse[2] + ")"); //Adds constant
            }
            else
            {
                //Add label to symbol table
                symTable[sParse[0]] = location;
                //Rest of the line
                //Intermediate code part
                vstr cParse = tokenizer(sParse[2], ',');
                insLine = codeMap[sParse[1]];    //Adds MOVER, MOVEM, etc
                insLine.append(" " + cParse[0]); //Adds AREG, BREG, etc
                if (cParse[1][0] == '=')
                {
                    //Check literal and insert
                    litTable = checkLiteral(litTable, cParse[1], pool, &nLit);
                    //Intermediate code part
                    insLine.append(" (L," + to_string(litTable.size()) + ")"); //Adds literal
                }
                else
                {
                    //Insertion of symbol
                    symTable = checkSymbol(symTable, cParse[1]);
                    //Intermediate code part
                    insLine.append(" " + cParse[1]); //Adds symbol
                }
                location++;
            }
        }
        ic << insLine << endl;
    }
    file.close();
    ic.close();

    //Convert map to vector for sorting
    vector<psi> v(symTable.size());
    copy(symTable.begin(), symTable.end(), v.begin());
    sort(v.begin(), v.end(), cmp);

    //Print symbol table
    cout << "SYMBOL TABLE" << endl;
    for (auto itr = v.begin(); itr != v.end(); ++itr)
    {
        cout << itr->first;
        if ((itr->first).length() < 4)
        {
            fori(0, (4 - itr->first.length()))
            {
                cout << " ";
            }
        }
        cout << "\t" << itr->second << endl;
    }
    cout << endl;

    //Print literal table
    cout << "LITERAL TABLE" << endl;
    for (auto &x : litTable)
    {
        cout << x.first << "\t" << x.second.first << endl;
    }
    cout << endl;

    //Print pool table
    cout << "POOL TABLE" << endl;
    for (auto &x : poolTable)
    {
        cout << x.first << "\t" << x.second << endl;
    }
    cout << endl;

    //Print intermediate code
    cout << "INTERMEDIATE CODE" << endl;
    //istream object for opening file for reading
    ifstream file1("IntermediateCode.txt");
    while (getline(file1, cmdline))
    {
        cout << cmdline << endl;
    }
    file1.close();
    return 0;
}