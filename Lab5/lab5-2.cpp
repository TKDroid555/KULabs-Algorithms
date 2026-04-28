#include <iostream>
#include <vector>
#include <string>

using namespace std;

char toLower(char c)
{
    if (c >= 'A' && c <= 'Z') return c + 32;
    return c;
}

struct Table
{
    vector<vector<char>> tableArray;
    int rows = 0, cols = 0;

    void setTableSize(int r, int c)
    {
        rows = r;
        cols = c;
        tableArray.resize(r);
        for (int i = 0; i < r; i++)
            tableArray[i].resize(c);
    }

    bool dfs(int x, int y, string &word, int index, vector<vector<bool>> &visited)
    {
        if (index == word.size())
            return true;

        if (x < 0 || y < 0 || x >= rows || y >= cols)
            return false;

        if (visited[x][y] || tableArray[x][y] != word[index])
            return false;

        visited[x][y] = true;

        if (dfs(x - 1, y, word, index + 1, visited) ||
            dfs(x + 1, y, word, index + 1, visited) ||
            dfs(x, y - 1, word, index + 1, visited) ||
            dfs(x, y + 1, word, index + 1, visited))
        {
            visited[x][y] = false;
            return true;
        }

        visited[x][y] = false;
        return false;
    }

    pair<int, int> findPos(string word)
    {
        vector<vector<bool>> visited(rows, vector<bool>(cols, false));
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (dfs(i, j, word, 0, visited))
                    return {i, j};
            }
        }
        return {-1, -1};
    }
};

struct Result
{
    int r, c;
    string originalWord;
};

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, H;
    if (!(cin >> L >> H)) return 0;

    Table table;
    table.setTableSize(H, L);

    for (int i = 0; i < H; i++)
    {
        string rowStr;
        cin >> rowStr;
        for (int j = 0; j < L; j++)
        {
            table.tableArray[i][j] = toLower(rowStr[j]);
        }
    }

    vector<Result> results;
    string inputWord;
    while (cin >> inputWord)
    {
        string lowerWord = "";
        for (char c : inputWord) lowerWord += toLower(c);
        
        pair<int, int> pos = table.findPos(lowerWord);
        if (pos.first != -1)
        {
            results.push_back({pos.first, pos.second, inputWord});
        }
    }

    for (int i = 0; i < results.size(); i++)
    {
        for (int j = i + 1; j < results.size(); j++)
        {
            bool swapNeeded = false;
            if (results[j].r < results[i].r) swapNeeded = true;
            else if (results[j].r == results[i].r && results[j].c < results[i].c) swapNeeded = true;
            else if (results[j].r == results[i].r && results[j].c == results[i].c && results[j].originalWord < results[i].originalWord) swapNeeded = true;

            if (swapNeeded)
            {
                Result temp = results[i];
                results[i] = results[j];
                results[j] = temp;
            }
        }
    }

    for (int i = 0; i < results.size(); i++)
    {
        cout << results[i].originalWord << endl;
    }

    return 0;
}