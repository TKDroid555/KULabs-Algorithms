#include <iostream>
#include <vector>

using namespace std;

struct myPair
{
    long long first;
    long long second;
};

long long myMax(long long &a, long long &b)
{
    if (a > b) return a;
    else return b;
}

int main() {

    long long round;
    cin >> round;

    vector<long long> enemiesPerRound;
    vector<myPair> scores; // first is dont warp and second is do warp

    enemiesPerRound.resize(round);
    scores.resize(round);

    for (long long i = 0; i < round; i++)
        cin >> enemiesPerRound[i];

    scores[0].first = enemiesPerRound[0]; // not warp kill loey
    scores[0].second = 0; // warp

    for (long long i = 1; i < round; i++)
    {
        long long a = (scores[i-1].first + enemiesPerRound[i]);
        long long b = (scores[i-1].second + (enemiesPerRound[i] * enemiesPerRound[i-1]));

        scores[i].first = myMax(a,b); // fight (if has enemy so fight from last round too)
        scores[i].second = myMax(scores[i-1].first, scores[i-1].second); // just warp and stack with last one no score add
    }

    cout << scores[round-1].first << endl;

    return 0;
}