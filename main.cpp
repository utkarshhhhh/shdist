#include<bits/stdc++.h>
#define MAX 50
#define INF INT_MAX

using namespace std;

int adj_matrix[MAX][MAX];
int N,E,u,v,w;
char x,y;
stack<int> STACK;
int dp[MAX][MAX];
int Path[MAX][MAX];
int speed[MAX];

char decode(int s)
{
    char val = 0;
    return val = s+97;
}
int encode(char s)
{
    int val;
    if(65<= s && s<=90)
    {
        return val = s-65;
    }
    if(97<= s && s<=122)
    {
        return val = s-97;
    }
}

void print_the_adj_matrix()
{
    cout<<endl;
    cout<<"Adjacent Matrix"<<endl;
    cout<<endl;
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            //cout<<adj_matrix[i][j]<<"  ";
            printf("%3d  ",adj_matrix[i][j]);

        }
        cout<<endl;
    }
}

int maxx(int car,int bus,int onfoot,int bike)
{

    int maxi=car;
    if(bus>maxi)
        maxi=bus;
    if(onfoot>maxi)
        maxi=onfoot;
    if(bike>maxi)
        maxi=bike;
    return maxi;

}

void enterSpeed()
{
    int car,bus,onfoot,bike;

    cout<<"Enter the speed available at present Location(0 if not available)\n";
    cout<<"\t---   Car   Bus   Bike  Onfoot\n";
    for(int i=0; i<N; i++)
    {
        cout<<"Location "<<char(97+i);
        cin>>car>>bus>>onfoot>> bike;
        speed[i]=maxx(car,bus,onfoot,bike);
    }
}

void graph(int isDistance)
{
    if(isDistance==0)
        cout<<"For Finding shortest time\n"<<endl;
    else
        cout<<"For Finding shortest distance\n"<<endl;

    cout<<"Enter No of Locations:";
    cin>>N;
    if(isDistance==0)
        enterSpeed();
    cout<<"Enter No of Edges Between Locations:";
    cin>>E;
    cout<<"From\tTo\tDistance";
    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            adj_matrix[i][j] = INF;
            Path[i][j] = -1;
        }
    }
    for(int i=0; i<E; i++)
    {
        cin>>x>>y>>w;
        u = encode(x);
        v = encode(y);
        /*    if(isDistance==0)
            {
                cout<<"\nEnter Speed of car if available else 0:";
                cin>>c;
                cout<<"\nEnter Speed of bus if available else 0:";
                cin>>b;
                cout<<"\nEnter Speed onfoot if available else 0:";
                cin>>f;

                adj_matrix[u][v] = w/maxx(c,b,f);
            }
            else*/
        adj_matrix[u][v] = w;

        if(isDistance==0)
            adj_matrix[u][v]/=speed[u];
        Path[u][v] = u;
    }
}

void fwalgo()
{

    for(int i=0; i<N; i++)
    {
        for(int j=0; j<N; j++)
        {
            dp[i][j] = adj_matrix[i][j];
            if(i==j)
            {
                dp[i][j] = 0;
            }
        }
    }

    for(int k=0; k<N; k++)
    {
        for(int i=0; i<N; i++)
        {
            for(int j=0; j<N; j++)
            {
                if(dp[i][k] + dp[k][j] < dp[i][j] && dp[i][k] < INF && dp[k][j] < INF)
                {
                    dp[i][j] = dp[i][k] + dp[k][j];
                    Path[i][j] = Path[k][j];
                }
            }
        }
    }
}
void path(int source,int destination)
{
    STACK.push(destination);
    while(Path[source][destination] != source)
    {
        STACK.push(Path[source][destination]);
        destination = Path[source][destination];
    }
    cout<<decode(source)<<" ";
    while(!STACK.empty())
    {
        cout<<decode(STACK.top())<<" ";
        STACK.pop();
    }
}
void Print_Result(int isDistance)
{
    for(int i=0; i<N; i++)
    {
        if(isDistance!=0)
        {
            cout<<"Minimum distance With Respect to Location: "<<decode(i)<<endl;
            cout<<"     Edges        :      minimum distance"<<"   :   Path"<<endl;
        }
        else
        {
            cout<<"Minimum time With Respect to Location: "<<decode(i)<<endl;
            cout<<"     Edges        :      minimum time"<<"   :   Path"<<endl;
        }
        for(int j=0; j<N; j++)
        {
            if(dp[i][j] == 0 || dp[i][j] == INF)
            {
                continue;
            }
            printf("%2c  <-->  %2c      :         %3d         :    ",decode(i),decode(j),dp[i][j]);
            path(i,j);
            cout<<endl;
        }
    }
}
int main()
{
    int isDistance;
    cout<<"Do you want to find min time?(0 for true)";
    cin>>isDistance;
    graph(isDistance);
    fwalgo();
    Print_Result(isDistance);
    return 0;
}
