#include <iostream>
#include <string>
#include <vector>

using namespace std;

string recurMultiply(vector<string> numberArr, int start, int end);
string multiplyStrings(string s1, string s2);

int main()
{
    vector<string> numbers;
    string current;
    string temp;

    while (cin >> temp)
        numbers.push_back(temp);

    current = numbers[0];

    string ans = recurMultiply(numbers, 0, numbers.size() - 1);
    cout << ans << endl;

    return 0;
}

string recurMultiply(vector<string> numberArr, int start, int end)
{
    if (start == end)
        return numberArr[start];

    int mid = (start + end) / 2;
    string answer = multiplyStrings(recurMultiply(numberArr, start, mid), recurMultiply(numberArr, mid + 1, end));

    return answer;
}

string multiplyStrings(string s1, string s2)
{
    int n1 = s1.size(), n2 = s2.size();
    if (n1 == 0 || n2 == 0)
        return "0";

    vector<int> result(n1 + n2, 0);

    int i1 = 0; 
    int i2 = 0; 

    for (int i = n1 - 1; i >= 0; i--) {
        int carry = 0;
        int n1 = s1[i] - '0';
        i2 = 0;

        for (int j = n2 - 1; j >= 0; j--) {
            int n2 = s2[j] - '0';
            int sum = n1 * n2 + result[i1 + i2] + carry;

            carry = sum / 10;

            result[i1 + i2] = sum % 10;

            i2++;
        }

        if (carry > 0)
            result[i1 + i2] += carry;

        i1++;
    }

    int i = result.size() - 1;
    while (i >= 0 && result[i] == 0)
        i--;

    if (i == -1)
        return "0";

    string ans = "";

    while (i >= 0)
        ans += to_string(result[i--]);

    return ans;
}