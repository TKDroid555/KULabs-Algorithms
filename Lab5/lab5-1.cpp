#include <iostream>
#include <string>
#include <vector>
#include <queue>

using namespace std;

bool isValid(string s)
{
    int count = 0;
    for (int i = 0; i < s.size(); i++)
    {
        if (s[i] == '(') count++;
        else if (s[i] == ')')
        {
            count--;
            if (count < 0) return false;
        }
    }
    return count == 0;
}

bool has(vector<string>& v, string x)
{
    for (int i = 0; i < v.size(); i++)
    {
        if (v[i] == x) return true;
    }
    return false;
}

int main()
{
    string s;
    if (!getline(cin, s)) return 0;

    queue<string> q;
    vector<string> visited;
    vector<string> results;

    q.push(s);
    visited.push_back(s);

    bool found = false;

    while (!q.empty())
    {
        int levelSize = q.size();
        bool levelFound = false;

        for (int i = 0; i < levelSize; i++)
        {
            string current = q.front();
            q.pop();

            if (isValid(current))
            {
                results.push_back(current);
                levelFound = true;
                found = true;
            }

            if (found) continue;

            for (int j = 0; j < current.size(); j++)
            {
                if (current[j] != '(' && current[j] != ')') continue;
                string nextState = current.substr(0, j) + current.substr(j + 1);
                if (!has(visited, nextState))
                {
                    visited.push_back(nextState);
                    q.push(nextState);
                }
            }
        }
        if (levelFound) break;
    }

    for (int i = 0; i < results.size(); i++)
    {
        for (int j = i + 1; j < results.size(); j++)
        {
            if (results[j] < results[i])
            {
                string temp = results[i];
                results[i] = results[j];
                results[j] = temp;
            }
        }
    }

    for (int i = 0; i < results.size(); i++)
    {
        if (i == 0 || results[i] != results[i - 1])
        {
            cout << results[i] << endl;
        }
    }

    return 0;
}