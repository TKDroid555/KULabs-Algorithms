#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Node
{
    int self;
    vector<Node*> adj;
};

void dfs1(Node* u, vector<bool>& visited, vector<int>& order)
{
    visited[u->self] = true;
    for (Node* v : u->adj)
        if (!visited[v->self])
            dfs1(v, visited, order);

    order.push_back(u->self);
}

int dfs2(int u, vector<vector<int>>& radj, vector<bool>& visited)
{
    visited[u] = true;
    int cnt = 1;
    for (int v : radj[u])
        if (!visited[v])
            cnt += dfs2(v, radj, visited);
    return cnt;
}

int main()
{
    int Vsize, Esize;
    cin >> Vsize >> Esize;

    vector<Node*> nodes(Vsize);
    for (int i = 0; i < Vsize; i++)
    {
        nodes[i] = new Node();
        nodes[i]->self = i;
    }

    vector<vector<int>> radj(Vsize);

    int a, b;
    for (int i = 0; i < Esize; i++)
    {
        cin >> a >> b;
        a--; b--;

        nodes[a]->adj.push_back(nodes[b]);
        radj[b].push_back(a);
    }

    vector<bool> visited(Vsize, false);
    vector<int> order;

    for (int i = 0; i < Vsize; i++)
        if (!visited[i])
            dfs1(nodes[i], visited, order);

    fill(visited.begin(), visited.end(), false);
    vector<int> ans;

    for (int i = Vsize - 1; i >= 0; i--)
    {
        int u = order[i];
        if (!visited[u])
            ans.push_back(dfs2(u, radj, visited));
    }

    sort(ans.begin(), ans.end(), greater<int>());

    int count = 0;

    for (int i : ans)
    {
        if (count == 5) break;
            cout << i;
        if (count < 4)
            cout << ",";
        count++;
    }

    while (count < 5)
    {
        cout << 0;
        if (count < 4)
            cout << ",";
        count++;
    }

    cout << "\n";

    return 0;
}

