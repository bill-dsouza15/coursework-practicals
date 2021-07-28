#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <queue>
#include <stack>

#define N 3
#define MAX 99999

using namespace std;

// CLASS STATE BEGINS
class State
{
public:
    //Member variables
    char **board;
    int gn;
    int hn;
    int fn;
    State *parent;

    //Member functions
    State();
    void print_board();
    State *get_parent();
    void set_parent(State *parent);
    int get_gn();
    void set_gn(int gn);
    int get_hn();
    void set_hn(int hn);
    int get_fn();
    void set_fn(int fn);
    int *find_space();
};

// CONSTRUCTOR
State::State()
{
    board = new char *[N];
    for (int i = 0; i < N; i++)
    {
        board[i] = new char[N];
    }
}

// BOARD
void State::print_board()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

// GETTER AND SETTER
State *State::get_parent()
{
    return this->parent;
}

void State::set_parent(State *parent)
{
    this->parent = parent;
}

int State::get_gn()
{
    return this->gn;
}

void State::set_gn(int gn)
{
    this->gn = gn;
}

int State::get_hn()
{
    return this->hn;
}

void State::set_hn(int hn)
{
    this->hn = hn;
}

int State::get_fn()
{
    return this->fn;
}

void State::set_fn(int fn)
{
    this->fn = fn;
}

// OTHER CLASS UTILITY FUNCTIONS
int *State::find_space()
{
    int *arr = new int[2];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (board[i][j] == '_')
            {
                arr[0] = i;
                arr[1] = j;
                break;
            }
        }
    }
    return arr;
}
// CLASS STATE ENDS

// COPY STATE
State *copy_state(State *obj)
{
    State *temp = new State;
    temp->board = new char *[N];
    for (int i = 0; i < N; i++)
    {
        temp->board[i] = new char[N];
    }
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            temp->board[i][j] = obj->board[i][j];
        }
    }

    temp->gn = obj->gn;
    temp->hn = obj->hn;
    temp->fn = obj->fn;
    return temp;
}

// SORTING COMPARATOR
bool sort_comp(State *left, State *right)
{
    return left->get_fn() < right->get_fn();
}

// STATES COMPARATOR
bool compare_states(State *lhs, State *rhs)
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (lhs->board[i][j] != rhs->board[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

// CALCULATE HN
int calculate_hn(State *child, State *goal)
{
    int misplaced = 0;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (child->board[i][j] != goal->board[i][j] && child->board[i][j] != '_')
            {
                misplaced++;
            }
        }
    }
    return misplaced;
}

// CREATE CHILD
State *create_child(State *parent, State *goal, int spaceOI, int spaceOJ, int spaceNI, int spaceNJ)
{
    State *child;
    child = copy_state(parent);

    char temp;
    temp = child->board[spaceOI][spaceOJ];
    child->board[spaceOI][spaceOJ] = child->board[spaceNI][spaceNJ];
    child->board[spaceNI][spaceNJ] = temp;

    int childHn = calculate_hn(child, goal);

    child->parent = parent;
    child->set_hn(childHn);
    child->set_gn(child->get_gn() + 1);
    child->set_fn(child->get_hn() + child->get_gn());
    return child;
}

// MAIN ASTAR UTIL
State *astar_util(State *goal, vector<State *> closed, vector<State *> open)
{
    State *current;
    while (true)
    {
        current = open.front();

        if (compare_states(current, goal))
        {
            break;
        }

        int *sloc = current->find_space();
        int i = sloc[0], j = sloc[1];
        int pos[][2] = {{i, j + 1}, {i, j - 1}, {i + 1, j}, {i - 1, j}};

        for (int s = 0; s < 4; s++)
        {
            if (pos[s][0] < N && pos[s][0] >= 0 && pos[s][1] < N && pos[s][1] >= 0)
            {
                open.push_back(create_child(current, goal, i, j, pos[s][0], pos[s][1]));
            }
        }
        closed.push_back(current);
        open.erase(open.begin());

        sort(open.begin(), open.end(), &sort_comp);
    }
    return current;
}

int main()
{
    State *initial = new State;
    cout << "Enter initial state :\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> initial->board[i][j];
        }
    }

    State *final = new State;
    cout << "Enter final state :\n";
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> final->board[i][j];
        }
    }

    cout << "\nInitial Board\n";
    initial->print_board();
    cout << "\nFinal Board\n";
    final->print_board();

    initial->set_hn(calculate_hn(initial, final));
    initial->set_gn(0);
    initial->set_fn(initial->get_gn() + initial->get_hn());
    initial->set_parent(nullptr);

    vector<State *> open;
    vector<State *> closed;
    open.push_back(initial);

    State *result = astar_util(final, closed, open);

    cout << "\nThe path of the solution\n";
    stack<State *> path;
    while (result != NULL)
    {
        path.push(result);
        result = result->parent;
    }
    while (!path.empty())
    {
        path.top()->print_board();
        cout << "\n";
        path.pop();
    }
    return 0;
}

/*
Initial :
1 2 3
8 _ 4
7 6 5

Goal :
2 8 1
_ 4 3
7 6 5
*/