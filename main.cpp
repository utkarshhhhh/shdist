#include <bits/stdc++.h>
#define MAX 50
#define INF INT_MAX

using namespace std;

int adj_matrix[MAX][MAX];
int N, E, u, v, w;
char x, y;
stack<int> STACK;
int dp[MAX][MAX];
int Path[MAX][MAX];
int speed[MAX];

char decode(int s)
{
    char val = 0;
    return val = s + 97;
}

int encode(char s)
{
    int val;
    if (65 <= s && s <= 90)
    {
        return val = s - 65;
    }
    if (97 <= s && s <= 122)
    {
        return val = s - 97;
    }
    return -1;
}

void print_the_adj_matrix()
{
    cout << endl;
    cout << "Adjacent Matrix" << endl;
    cout << endl;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            //cout<<adj_matrix[i][j]<<"  ";
            printf("%3d  ", adj_matrix[i][j]);
        }
        cout << endl;
    }
}

int maxx(int car, int bus, int onfoot, int bike)
{
    int maxi = car;
    if (bus > maxi)
        maxi = bus;
    if (onfoot > maxi)
        maxi = onfoot;
    if (bike > maxi)
        maxi = bike;

    return maxi;
}

void speedFile()
{
    ifstream fin("speed.txt");
    int car, bus, onfoot, bike;

    if (!fin)
    {
        cout << "Error, please create speed.txt";
        return;
    }

    for (int i = 0; i < N; i++)
    {
        fin >> car >> bus >> onfoot >> bike;
        speed[i] = maxx(car, bus, onfoot, bike);

        for (int j = 0; j < N; j++)
        {
            if (adj_matrix[i][j] != INF)
                adj_matrix[i][j] /= speed[i];
        }
    }

    fin.close();
}

void graphFile()
{
    ifstream fin("graph.txt");

    if (!fin)
    {
        cout << "Error, please create graph.txt";
        return;
    }

    fin >> N;
    fin >> E;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            adj_matrix[i][j] = INF;
            Path[i][j] = -1;
        }
    }

    for (int i = 0; i < E; i++)
    {
        fin >> x >> y >> w;
        u = encode(x);
        v = encode(y);

        adj_matrix[u][v] = w;

        // if (isDistance == 0)
        // adj_matrix[u][v] /= speed[u];

        Path[u][v] = u;
    }

    fin.close();
}

void graph(int isDistance)
{
    if (isDistance == 0)
        cout << "\nFinding shortest time...\n";
    else
        cout << "\nFinding shortest distance...\n";

    graphFile();

    if (isDistance == 0)
        speedFile();
}

void fwalgo()
{

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            dp[i][j] = adj_matrix[i][j];
            if (i == j)
            {
                dp[i][j] = 0;
            }
        }
    }

    for (int k = 0; k < N; k++)
    {
        for (int i = 0; i < N; i++)
        {
            for (int j = 0; j < N; j++)
            {
                if (dp[i][k] + dp[k][j] < dp[i][j] && dp[i][k] < INF && dp[k][j] < INF)
                {
                    dp[i][j] = dp[i][k] + dp[k][j];
                    Path[i][j] = Path[k][j];
                }
            }
        }
    }
}

void path(int source, int destination)
{
    STACK.push(destination);
    while (Path[source][destination] != source)
    {
        STACK.push(Path[source][destination]);
        destination = Path[source][destination];
    }
    cout << decode(source) << " ";
    while (!STACK.empty())
    {
        cout << decode(STACK.top()) << " ";
        STACK.pop();
    }
}

void Print_Result(int isDistance)
{
    for (int i = 0; i < N; i++)
    {
        if (isDistance != 0)
        {
            cout << "\nMinimum distance With Respect to Location: " << decode(i) << endl;
            cout << "     Edges        :      minimum distance"
                 << "   :   Path" << endl;
        }
        else
        {
            cout << "\nMinimum time With Respect to Location: " << decode(i) << endl;
            cout << "     Edges        :      minimum time"
                 << "   :   Path" << endl;
        }

        for (int j = 0; j < N; j++)
        {
            if (dp[i][j] == 0 || dp[i][j] == INF)
            {
                continue;
            }
            printf("%2c  <-->  %2c      :         %3d         :    ", decode(i), decode(j), dp[i][j]);
            path(i, j);
            cout << endl;
        }
    }
}

int main()
{
    int isDistance;
    cout << "Do you want to find \n\t0- min time?\n\t1- min distance?\n";
    cin >> isDistance;
    graph(isDistance);
    fwalgo();
    Print_Result(isDistance);
    return 0;
}
