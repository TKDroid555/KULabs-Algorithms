#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Table
{
    vector<vector<char>> tableArray;
    int rows = 0, cols = 0;

    void setTableSize(int a, int b)
    {
        rows = a;
        cols = b;
        tableArray.resize(a);
        for (int i = 0; i < a; i++)
            tableArray[i].resize(b);
    }

    bool dfs(int x, int y, string &words, int index, vector<vector<bool>> &visited)
    {
        if (index == words.size())
            return true;

        if (x < 0 || y < 0 || x >= rows || y >= cols)
            return false;

        if (visited[x][y] || tableArray[x][y] != words[index])
            return false;

        visited[x][y] = true;

        bool found =
            dfs(x + 1, y, words, index + 1, visited) ||
            dfs(x - 1, y, words, index + 1, visited) ||
            dfs(x, y + 1, words, index + 1, visited) ||
            dfs(x, y - 1, words, index + 1, visited);

        visited[x][y] = false;

        return found;
    }

    bool exist(string word)
    {
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));

        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (tableArray[i][j] == word[0])
                {
                    if (dfs(i, j, word, 0, visited))
                        return true;
                }
            }
        }
        return false;
    }
};

vector<int> findAnswer(Table &table, vector<string> words)
{
    vector<int> ans;

    for (int i = 0; i < words.size(); i++)
    {
        if (table.exist(words[i]))
            ans.push_back(i);
    }

    return ans;
}

int main()
{
    int a, b;
    char tempChar;
    Table table;
    vector<string> toFind;

    cin >> a >> b;
    table.setTableSize(a,b);

    for (int i = 0; i < a*b; i++)
    {
        cin >> tempChar;
        table.tableArray[i % a][i / a] = tempChar;
    }

    string inputToFind;
    while (cin >> inputToFind)
    {
        toFind.push_back(inputToFind);
    }

    vector<int> result = findAnswer(table, toFind);

    for (int i : result)
        cout << toFind[i] << endl;

    return 0;
}