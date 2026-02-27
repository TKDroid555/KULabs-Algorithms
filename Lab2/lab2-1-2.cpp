#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector<vector<int>> adj;
vector<bool> blocked;
vector<vector<int>> blockList;
vector<int> path;
vector<int> cycleSizes;

/* unblock helper */
void unblock(int u)
{
    blocked[u] = false;
    for (int v : blockList[u])
        if (blocked[v])
            unblock(v);
    blockList[u].clear();
}

/* DFS to find cycles */
bool dfsCycle(int v, int start)
{
    bool foundCycle = false;
    path.push_back(v);
    blocked[v] = true;

    for (int w : adj[v])
    {
        if (w == start)
        {
            cycleSizes.push_back(path.size());
            foundCycle = true;
        }
        else if (!blocked[w])
        {
            if (dfsCycle(w, start))
                foundCycle = true;
        }
    }

    if (foundCycle)
        unblock(v);
    else
        for (int w : adj[v])
            blockList[w].push_back(v);

    path.pop_back();
    return foundCycle;
}

/* Find all cycles */
void findAllCycles(int V)
{
    blocked.assign(V + 1, false);
    blockList.assign(V + 1, vector<int>());
    path.clear();

    for (int s = 1; s <= V; s++)
    {
        fill(blocked.begin(), blocked.end(), false);
        for (auto &v : blockList) v.clear();
        dfsCycle(s, s);
    }
}

int main()
{
    int V, E;
    cin >> V >> E;

    adj.assign(V + 1, vector<int>());

    for (int i = 0; i < E; i++)
    {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
    }

    findAllCycles(V);

    sort(cycleSizes.begin(), cycleSizes.end());

    for (int sz : cycleSizes)
        cout << sz << "\n";

    return 0;
}
