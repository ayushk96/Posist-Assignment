#include <bits/stdc++.h>
using namespace std;
class Graph                            // for determining the skeleton of the structure
{
    int V;
    list<int> *adj;

public:
    Graph(int V);
    void addEdge(int v, int w);
    void longestPathLength();
    pair<int, int> bfs(int u);

};
Graph::Graph(int V)                               // declaration of the graph
{
    this->V = V;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);
    adj[w].push_back(v);
}
pair<int, int> Graph::bfs(int u)             // bfs traversal of the skeleton of the structure
{
    int dis[V];
    memset(dis, -1, sizeof(dis));

    queue<int> q;
    q.push(u);
    dis[u] = 0;

    while (!q.empty())
    {
        int t = q.front();
        q.pop();
        for (auto it = adj[t].begin(); it != adj[t].end(); it++)
        {
            int v = *it;
            if (dis[v] == -1)
            {
                q.push(v);
                dis[v] = dis[t] + 1;
            }
        }
    }

    int maxDis = 0;
    int nodeIdx;
    for (int i = 0; i < V; i++)
    {
        if (dis[i] > maxDis)
        {
            maxDis = dis[i];
            nodeIdx = i;
        }
    }
    return make_pair(nodeIdx, maxDis);
}

void Graph::longestPathLength()          //for longest chain in the structure
{
    pair<int, int> t1, t2;
    t1 = bfs(0);
    t2 = bfs(t1.first);

    cout << "Longest path is of length\n " << t2.second;
}
Graph g(100);
struct Node                               // Node Structure
{
    int key,valcheck,count;
    string str;
    vector<Node *>child;                   // vector for storing the children ,each node will have this
};
Node *newNode(int key,string str,int valcheck,int count)   // for declaration of new node
{
    Node *temp = new Node;
    temp->key = key;
    temp->str=str;
    temp->valcheck=valcheck;
    temp->count=count;
    return temp;
}
void insert(Node * root,string str,int value,int count)              // inserting a new node
{
    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        int n = q.size();
        while (n > 0)
        {
            Node * p = q.front();
            q.pop();
            if(p->valcheck>value)      // Sum of a set of value of siblings should never be greater than the value
                                       // of the root node
            {
                p->valcheck-=value;
                (p->child).push_back(newNode(value,str,value,count));
                g.addEdge(p->count-1,count-1);        //defining the skeleton of the structure
                return;
            }
            for (int i=0; i<p->child.size(); i++)
                q.push(p->child[i]);
            n--;
        }

        cout << endl;
    }
}
void LevelOrderTraversal(Node * root)             // traversal of the structure
{
    if (root==NULL)
        return;


    queue<Node *> q;
    q.push(root);
    while (!q.empty())
    {
        int n = q.size();

        while (n > 0)
        {

            Node * p = q.front();
            q.pop();
            cout << p->key << " ";


            for (int i=0; i<p->child.size(); i++)
                q.push(p->child[i]);
            n--;
        }

        cout << endl;
    }
}
int main()
{
    int value,ch,temp=1,nodeid=1;
    string str;
    cout<<"enter the value for genesis node and name of the owner\n";
    cin>>value;
    cin>>str;

    Node *Genesis_Node = newNode(value,str,value,nodeid);
    while(temp==1)
    {
         cout<<"enter the option\n";
         cout<<"enter 1 to insert a new node\n";
         cout<<"enter 2 to traverse\n";
         cout<<"enter 3 for longest chain of the genesis node\n";
         cout<<"enter 4 to exit\n";
         cin>>ch;
         switch(ch)
         {
             case 1:cout<<"enter the value of node and name of the owner\n";
                    cin>>value;
                    cin>>str;
                    nodeid++;
                    insert(Genesis_Node,str,value,nodeid);
                    break;

            case 2:LevelOrderTraversal(Genesis_Node);
                   break;
            case 3:g.longestPathLength();
                   break;
            case 4:temp=0;
                   break;
         }
    }
    return 0;
}
