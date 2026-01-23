#include <iostream>
#include <vector>

using namespace std;

int countNegativeRecur(vector<int> &numbers, int begin, int end);

int main()
{
    vector<int> numbers;

    int temp = -1;
    while (temp != 0)
    {
        cin >> temp;
        if (temp == 0) break;
        numbers.push_back(temp);
    }

    int total = countNegativeRecur(numbers, 0, numbers.size() - 1);
    cout << total << endl;

    return 0;
}

int countNegativeRecur(vector<int> &numbers, int begin, int end)
{
    int sum = 0;

    if (begin == end)
    {
        if (numbers[begin] < 0) return 1;
        else return 0;
    }

    int mid = (begin + end) / 2;

    sum += countNegativeRecur(numbers, begin, mid);
    sum += countNegativeRecur(numbers, mid+1, end);

    return sum;
}