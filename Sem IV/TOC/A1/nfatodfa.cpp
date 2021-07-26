#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <string>
#include <algorithm>
#include <utility>
#include <list>
#define ip 2
#define statelen 2
#define space 16
#define fori(s, e) for (int i = (int)s; i < (int)e; i++)
#define forj(s, e) for (int j = (int)s; j < (int)e; j++)
#define forl(s, e) for (int l = (int)s; l < (int)e; l++)

using namespace std;

vector<string> input()
{
	string state, trstate;
	vector<string> trans;
	cout << "Enter the state: ";
	cin >> state;
	trans.push_back(state);
	fori(0, ip)
	{
		cout << "Enter transition on " << i << ": ";
		cin >> trstate;
		trans.push_back(trstate);
	}
	cout << endl;
	return trans;
}

void printSpace(string temp)
{
	fori(0, space - temp.length())
	{
		cout << " ";
	}
}

void display(vector<string> *trans, int n)
{
	string temp;
	cout << "State\t\t";
	fori(0, ip)
	{
		cout << i << "\t\t";
	}
	cout << endl;
	fori(0, n)
	{
		temp = trans[i].at(0);
		cout << temp;
		printSpace(temp);
		forj(0, ip)
		{
			temp = trans[i].at(j + 1);
			cout << temp;
			printSpace(temp);
		}
		cout << endl;
	}
	cout << endl;
}

vector<string> breakSt(string stOp)
{
	vector<string> ipState;
	string temp;
	int i = 0;
	if (stOp.compare("-") != 0)
	{
		while (i < stOp.length())
		{
			temp = stOp.substr(i, 2);
			ipState.push_back(temp);
			i = i + 3;
		}
	}
	else
	{
		ipState.push_back(stOp);
	}
	return ipState;
}

string combSt(vector<string> tempVs)
{
	string temp;
	int i = 0;
	fori(0, tempVs.size())
	{
		temp.append(tempVs.at(i));
		temp.append(",");
	}
	return temp;
}

vector<string> mergeV(vector<string> tempVs, vector<string> temp1Vs, vector<string> tempf)
{
	fori(0, tempVs.size())
	{
		tempf.push_back(tempVs.at(i));
	}
	fori(0, temp1Vs.size())
	{
		tempf.push_back(temp1Vs.at(i));
	}
	return tempf;
}

bool pred(string a, string b)
{
	if (a.compare(b) == 0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

vector<string> uni(vector<string> tempf)
{
	vector<string> t;
	std::map<string, int> map;
	fori(0, tempf.size())
	{
		map[tempf.at(i)]++;
	}
	for (auto i = map.begin(); i != map.end(); i++)
	{
		if ((i->first).compare("-") != 0)
		{
			t.push_back(i->first);
		}
	}
	return t;
}

int main()
{
	int n;
	cout << "Enter the number of states: ";
	cin >> n;
	vector<string> *trans;
	trans = new vector<string>[n];
	unordered_map<string, int> loc, LState;
	pair<string, int> psi;
	cout << "\nEnter the NFA table below: \n";
	fori(0, n)
	{
		trans[i] = input();
		loc[trans[i].at(0)] = i;
	}
	cout << "\nThe NFA table is as below: \n";
	display(trans, n);

	///////////////////////// DFA CONVERSION ////////////////////////

	vector<vector<string>> finDFA;
	vector<string> tempState; //Final vector for a state on LHS
	vector<string> ipState;	  //State corresponding to input symbol
	list<string> queue;		  //Queue for states
	vector<string> tempVs, temp1Vs;
	finDFA.push_back(trans[0]);
	LState[(finDFA.at(0)).at(0)]++;
	fori(0, ip)
	{
		queue.push_back(((finDFA.at(0)).at(i + 1)));
	}
	while (!queue.empty())
	{
		string stOp = queue.front();
		queue.pop_front();
		//cout<<stOp<<"l"<<"\n";
		if (!LState[stOp] && stOp != "-")
		{
			LState[stOp]++;
			tempState.push_back(stOp);
			if (stOp.length() > 2)
			{
				ipState = breakSt(stOp);
				/*fori(0,ipState.size())
				{
					cout<<ipState.at(i)<<"ip\t";
				}
				cout<<"\n";*/
				fori(0, ip)
				{
					string temp;
					temp = (trans[loc[ipState.at(0)]].at(i + 1));
					forj(1, ipState.size())
					{
						string temp1 = (trans[loc[ipState.at(j)]].at(i + 1));
						tempVs = breakSt(temp);
						temp1Vs = breakSt(temp1);
						vector<string> tempf;

						tempf = mergeV(tempVs, temp1Vs, tempf);
						/*cout<<"TEMPF1"<<"\n";
					 	fori(0,tempf.size())
					 	{
					 		cout<<tempf.at(i)<<"\t";
					 	}
					 	cout<<"\n";*/
						tempf = uni(tempf);
						/*cout<<"TEMPF"<<"\n";
					 	fori(0,tempf.size())
					 	{
					 		cout<<tempf.at(i)<<"\t";
					 	}
					 	cout<<"\n";*/
						temp = combSt(tempf);
					}
					temp = temp.substr(0, temp.length() - 1);
					//cout<<"TEMP\n"<<temp<<"\n";
					tempState.push_back(temp);
					queue.push_back(temp);
				}
			}
			else
			{
				fori(0, ip)
				{
					string temp;
					temp = trans[loc[stOp]].at(i + 1);
					tempState.push_back(temp);
					queue.push_back(temp);
				}
			}
			finDFA.push_back(tempState);
			tempState.clear();
			/*cout<<"State"<<"\n";
			cout<<finDFA.back().at(0)<<"\t"<<finDFA.back().at(1)<<"\t"<<finDFA.back().at(2)<<"\n";*/
		}
	}
	cout << "\nThe DFA table is as below: \n";
	int n1 = finDFA.size();
	vector<string> *transf;
	transf = new vector<string>[n1];
	fori(0, n1)
	{
		transf[i] = finDFA.at(i);
	}
	display(transf, n1);
	return 0;
}
