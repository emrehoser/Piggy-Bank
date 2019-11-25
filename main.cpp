// A C++ program to find strongly connected components in a given
// directed graph using Tarjan's algorithm (single DFS)
#include<iostream>
#include <list>
#include <stack>
#include <fstream>


using namespace std;


class graph
{
    int V;


    void SCCUtil(int u, int disc[], int low[],
                 stack<int> *st, bool stackMember[]);
public:
    graph(int V);
    void add(int v, int w);
    void SCC();
    list<int> *adj;
    int *scclist;
    int sccnum = 0;
};

graph::graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
    scclist =  new int[V];

}

void graph::add(int v, int w)
{
    adj[w-1].push_back(v);
}


void graph::SCCUtil(int u, int disc[], int low[], stack<int> *st,
                    bool stackMember[])
{

    static int time = 0;

    disc[u] = low[u] = ++time;
    st->push(u);
    stackMember[u] = true;


    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;


        if (disc[v] == -1)
        {
            SCCUtil(v, disc, low, st, stackMember);


            low[u]  = min(low[u], low[v]);
        }

        else if (stackMember[v] == true)
            low[u]  = min(low[u], disc[v]);
    }


    int w = 0;
    if (low[u] == disc[u])
    {
        while (st->top() != u)
        {
            w = (int) st->top();
            stackMember[w] = false;
            scclist[w]=sccnum;
            st->pop();
        }
        w = (int) st->top();
        stackMember[w] = false;
        scclist[w]=sccnum;
        st->pop();
        sccnum++;
    }
}


void graph::SCC()
{
    int *disc = new int[V];
    int *low = new int[V];
    bool *stackMember = new bool[V];
    stack<int> *st = new stack<int>();


    for (int i = 0; i < V; i++)
    {
        disc[i] = -1;
        low[i] = -1;
        stackMember[i] = false;
    }


    for (int i = 0; i < V; i++)
        if (disc[i] == -1)
            SCCUtil(i, disc, low, st, stackMember);
}


int main(int argc,char *argv[])
{
    ofstream write(argv[2]);
    ifstream read(argv[1]);


    int n;
    read >> n;
    graph gra(n);
    for(int i =0;i<n;i++){
        int j;
        read >> j;
        for(int k=0;k<j;k++){
            int key;
            read >> key;
            gra.add(i,key);
        }
    }
   
    gra.SCC();

    bool key[gra.sccnum];
    for(int a = 0 ; a<gra.sccnum;a++){
        key[a] = true;
    }
    for(int i =0 ; i<n;i++){
        if(key[gra.scclist[i]]){

            for(int j:gra.adj[i]){
                if(gra.scclist[i]!=gra.scclist[j]){
                    key[gra.scclist[i]]=false;break;
                }
            }
        }
    }
    list<int> ist;
    int count=0;
    for(int i = 0;i<n;i++){
        if(key[gra.scclist[i]]){
            ist.push_back(i);
            key[gra.scclist[i]]= false;
            count++;
        }
    }
    write<<count<<" ";
    for(int i:ist){
        write<<i+1<<" ";
    }

    return 0;
}