#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

int cost(string &x, string &y)
{
    int s = 0;

    for (int i = 0; i < x.size(); i++)
    {
        int a = x[i] - '0';
        int b = y[i] - '0';
        int d = a - b;
        
        if (d < 0)
            d = -d;
        if (10 - d < d)
            d = 10 - d;

        s += d;
    }

    return s;
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    while (cin >> n)
    {
        vector<string> v;

        for (int i = 0; i <= n; i++)
        {
            string s;
            cin >> s;
            v.push_back(s);
        }

        int m = n + 1;

        vector<int> d(m, INT_MAX);
        vector<int> used(m, 0);

        d[0] = 0;
        long long ans = 0;

        for (int i = 0; i < m; i++)
        {
            int x = -1;
            for (int j = 0; j < m; j++)
            {
                if (used[j] == false && ((x == -1) || (d[j] < d[x])))
                    x = j;
            }

            used[x] = 1;
            ans += d[x];

            for (int y = 0; y < m; y++)
            {
                if (used[y] == false)
                {
                    int w = cost(v[x], v[y]);
                    if (w < d[y])
                        d[y] = w;
                }
            }
        }

        ans %= 100000;

        int pad = 5;
        int tmp = ans;

        if (tmp == 0)
            pad -= 1;

        while (tmp > 0)
        {
            pad -= 1;
            tmp /= 10;
        }

        while (pad > 0)
        {
            pad -= 1;
            cout << '0';   
        }
        cout << ans << endl;
    }

    return 0;
}