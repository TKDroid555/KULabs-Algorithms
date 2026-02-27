#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

int main()
{
    int Vsize, Esize;

    cin >> Vsize >> Esize;
    vector<vector<int>> adjList;
    adjList.resize(Vsize + 1);

    int tempA, tempB;

    for (int i = 0; i < Esize; i++)
    {
        cin >> tempA >> tempB;

        adjList[tempA].push_back(tempB);
    }

    bool visited[Vsize + 1];
    for (int i = 0; i <= Vsize; i++) {
        visited[i] = 0;}

    stack<int> path;
    path.push(1);
    cout << DFS(1, adjList, visited, path) << endl;

    return 0;
}

int DFS(int target, vector<vector<int>> &adjList, bool visited[], stack<int> path)
{
    int current = target;
    path.push(current);

    for (int i : adjList[current])
    {
        if (target == i) return path.size();
        
        if (visited[i] == false)
        {
            visited[i] = true;
            DFS(i, adjList, visited, path);
        }
    }

    path.pop();
}