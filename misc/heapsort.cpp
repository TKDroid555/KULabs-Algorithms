#include <iostream>
#include <vector>

using namespace std;

void heapSort(vector<int> &arr);
void heapify(vector<int> &arr, int start, int end);

int main()
{
    vector<int> arr;

    int temp = -1;
    while (temp != 0)
    {
        cin >> temp;
        arr.push_back(temp);
    }

    heapSort(arr);

    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}

void heapSort(vector<int> &arr)
{
    heapify(arr, 0, arr.size());
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        heapify(arr, 0, i - 1);
        arr[i] = arr[0];
    }
}

void heapify(vector<int> &arr, int end)
{
    
}