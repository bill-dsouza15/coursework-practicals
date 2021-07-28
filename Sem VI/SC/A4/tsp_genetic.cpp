#include <iostream>
#include <vector>
#include <map>

#define V 7
#define POPNS 2 * V
#define SCITY 0

using namespace std;

struct individual
{
    string chromosome; //Size of chromosome is V+1 to include start city at the end
    int fitness;
};

//Generate a random number in the range [s,e]
int randRange(int s, int e)
{
    int r = s + (rand() % (e - s));
    return r;
}

//Generate a random number in the range [s,e] except w
int randRangeExcept(int s, int e, int w)
{
    int r;
    while (true)
    {
        r = s + (rand() % (e - s));
        if (r != w)
        {
            break;
        }
    }
    return r;
}

//Check if a gene repeats in the chromosome
bool checkRepeat(string chromosome, char gene)
{
    for (int i = 0; i < chromosome.length(); i++)
    {
        if (chromosome[i] == gene)
        {
            return 1;
        }
    }
    return 0;
}

//Creates a chromosome at random
string createChromosome()
{
    string chromosome;

    char gene = (char)(SCITY + 48);
    chromosome.push_back(gene);

    while (1)
    {
        if (chromosome.length() == V)
        {
            char gene = (char)(SCITY + 48);
            chromosome.push_back(gene);
            break;
        }
        else
        {
            int city = randRangeExcept(0, V, SCITY);
            char gene = (char)(city + 48);
            if (!checkRepeat(chromosome, gene))
            {
                chromosome.push_back(gene);
            }
        }
    }

    return chromosome;
}

//Calculate fitness of chromosome based on adjacency matrix
int calcFitness(string chromosome, int adj[V][V])
{
    int fitness = 0;
    for (int i = 0; i < V; i++)
    {
        if (adj[chromosome[i] - '0'][chromosome[i + 1] - '0'] == INT_MAX)
        {
            return INT_MAX;
        }
        fitness += adj[chromosome[i] - '0'][chromosome[i + 1] - '0'];
    }
    return fitness;
}

//Selection of parents
struct individual selectParent(vector<struct individual> population)
{
    double sum = 0;
    double prob[POPNS];
    for (int i = 0; i < POPNS; i++)
    {
        sum += ((double)1) / ((double)population[i].fitness);
    }
    for (int i = 0; i < POPNS; i++)
    {
        prob[i] = ((double)1 / population[i].fitness) / ((double)sum);
    }

    //Find one parent based on the probability
    int i = 0;
    double r = (double)rand() / (RAND_MAX);

    for (i = 0; i < POPNS; i++)
    {
        if (r < prob[i])
        {
            break;
        }
        else
        {
            r -= prob[i];
        }
    }
    return population[i];
}

//Crossover two parents using on order crossover (since permutation encoding is used for TSP)
string crossoverChild(string P1, string P2)
{
    int crossLen = V / 2;
    int crossPoint = randRange(1, V - 1 - crossLen);

    string c;

    map<char, int> mp;
    int ind = 0;
    for (int i = 0; i < crossLen; i++)
    {
        mp[P1[crossPoint + i]]++;
    }
    while (ind < P2.length())
    {
        if (mp[P2[ind]] == 0)
        {
            c.push_back(P2[ind]);
        }
        ind++;
        if (c.length() == crossPoint)
        {
            break;
        }
    }
    for (int i = crossPoint; i < crossPoint + crossLen; i++)
    {
        c.push_back(P1[i]);
    }
    while (ind < P2.length())
    {
        if (mp[P2[ind]] == 0)
        {
            c.push_back(P2[ind]);
        }
        ind++;
        if (c.length() == V + 1)
        {
            break;
        }
    }
    return c;
}

vector<string> crossoverPairs(string P1, string P2)
{
    //Ordered crossover
    vector<string> children;

    string c1, c2;
    int i = 0;

    //cout << "P1 : " << P1 << endl;
    //cout << "P2 : " << P2 << endl;

    c1 = crossoverChild(P1, P2);
    children.push_back(c1);

    c2 = crossoverChild(P2, P1);
    children.push_back(c2);
    return children;
}

string createMutation(string chromosome)
{
    while (1)
    {
        int p1 = randRange(1, V - 1);
        int p2 = randRange(1, V - 1);
        if (p1 != p2)
        {
            char temp = chromosome[p1];
            chromosome[p1] = chromosome[p2];
            chromosome[p2] = temp;
            break;
        }
    }
    return chromosome;
}

void printGen(vector<struct individual> population)
{
    cout << "CHROMOSOME  FITNESS\n";
    for (int i = 0; i < POPNS; i++)
    {
        cout << population.at(i).chromosome;
        for (int i = 0; i <= 10 - V; i++)
        {
            cout << " ";
        }
        cout << population.at(i).fitness << endl;
    }
    cout << "\n";
}

void TSPGA(int adj[V][V])
{
    int genStart = 0;
    int genMax = V;

    vector<struct individual> population;

    for (int i = 0; i < POPNS; i++)
    {
        struct individual in;
        in.chromosome = createChromosome();
        in.fitness = calcFitness(in.chromosome, adj);
        population.push_back(in);
    }

    for (int i = genStart; i <= genMax; i++)
    {
        cout << "GEN " << i << endl;
        printGen(population);

        vector<struct individual> nextGen;
        while (nextGen.size() <= POPNS)
        {
            vector<string> children;
            struct individual parent1 = selectParent(population);
            struct individual parent2 = selectParent(population);
            children = crossoverPairs(parent1.chromosome, parent2.chromosome);

            struct individual c1;
            c1.chromosome = children[0];
            c1.chromosome = createMutation(c1.chromosome);
            c1.fitness = calcFitness(c1.chromosome, adj);
            nextGen.push_back(c1);

            struct individual c2;
            c2.chromosome = children[1];
            c2.chromosome = createMutation(c2.chromosome);
            c2.fitness = calcFitness(c2.chromosome, adj);
            nextGen.push_back(c2);
        }
        population = nextGen;
    }
}

int main()
{
    int adj[V][V] = {
        {0, INT_MAX, 83, 9, 30, 6, 50},
        {INT_MAX, 0, 66, 37, 17, 12, 26},
        {29, 1, 0, 19, INT_MAX, 12, 5},
        {32, 83, 66, 0, 49, INT_MAX, 80},
        {3, 21, 56, 7, 0, INT_MAX, 28},
        {INT_MAX, 85, 8, 42, 89, 0, INT_MAX},
        {18, INT_MAX, INT_MAX, INT_MAX, 58, 13, 0}};
    /*
    int adj[V][V] = {{0, 2, INT_MAX, 12, 5},
                     {2, 0, 4, 8, INT_MAX},
                     {INT_MAX, 4, 0, 3, 3},
                     {12, 8, 3, 0, 10},
                     {5, INT_MAX, 3, 10, 0}};
    */
    TSPGA(adj);
    return 0;
}
