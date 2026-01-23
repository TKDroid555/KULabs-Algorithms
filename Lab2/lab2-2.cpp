#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main()
{
    int start, target;
    cin >> start >> target;

    vector<int> U, V, W;
    int u, v, w;
    int maxNode = max(start, target);

    while (cin >> u >> v >> w)
    {
        U.push_back(u);
        V.push_back(v);
        W.push_back(w);

        if (u > maxNode) maxNode = u;
        if (v > maxNode) maxNode = v;
    }

    int n = maxNode + 1;
    vector<vector<pair<int, int> > > graph(n);

    for (int i = 0; i < (int)U.size(); i++)
    {
        graph[U[i]].push_back(make_pair(V[i], W[i]));
        graph[V[i]].push_back(make_pair(U[i], W[i]));
    }

    vector<long long> dist(n, -1);
    vector<int> hops(n, -1);
    vector<int> parent(n, -1);

    priority_queue<pair<long long, int> > pq;

    dist[start] = 0;
    hops[start] = 1;
    pq.push(make_pair(0, start));

    while (!pq.empty())
    {
        long long curDist = -pq.top().first;
        int curNode = pq.top().second;
        pq.pop();

        if (curDist != dist[curNode])
            continue;

        for (vector<pair<int, int> >::iterator it = graph[curNode].begin();
             it != graph[curNode].end();
             ++it)
        {
            int nextNode = it->first;
            int weight = it->second;

            long long newDist = dist[curNode] + weight;
            int newHops = hops[curNode] + 1;

            if (dist[nextNode] == -1 ||
                newDist < dist[nextNode] ||
                (newDist == dist[nextNode] && newHops > hops[nextNode]))
            {
                dist[nextNode] = newDist;
                hops[nextNode] = newHops;
                parent[nextNode] = curNode;
                pq.push(make_pair(-newDist, nextNode));
            }
        }
    }

    if (dist[target] == -1)
    {
        cout << "IMPOSSIBLE";
        return 0;
    }

    vector<int> path;
    int cur = target;

    while (cur != -1)
    {
        path.push_back(cur);
        cur = parent[cur];
    }

    for (int i = path.size() - 1; i >= 0; i--)
    {
        cout << path[i];
        if (i) cout << " ";
    }

    return 0;
}
