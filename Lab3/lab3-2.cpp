#include <iostream>

using namespace std;

int main() {

    int min_peak = 0;
    int energy = 0;

    int p, x, z;

    while (cin >> p >> x >> z)
    {
        energy += p;

        if (energy < min_peak)
            min_peak = energy;
    }

    if (min_peak < 0) cout << -min_peak << endl;
    else cout << 0 << endl;
    
    return 0;
}