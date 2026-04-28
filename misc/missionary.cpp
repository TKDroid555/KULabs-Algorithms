#include <iostream>

using namespace std;

struct Land
{
    int lm, lc, rm, rc;
};

int myMax(int a, int b, int c)
{
    int most = a;
    if (most < b)
        most = b;
    if (most < c)
        most = c;
        
    return most;
}

int tryCrossGo(Land land, int m, int c, int dir) // dir 1 = go , dir 2 = back
{
    if (land.rc == 5 && land.rm == 5)
        return 1;

    // --- go ---
    if (dir = 1)
    {
        // mm
        if (land.lm - 2 >= land.lc && land.rm + 2 >= land.rc)
            return tryCrossGo(land, 2, 0, 2);
        // mc
        else if (land.lm - 1 >= land.lc - 1 && land.rm + 1 >= land.rc + 1)
            return tryCrossGo(land, 1, 1, 2);
        // cc
        else if (land.lm >= land.lc - 2 && land.rm >= land.rc + 2)
            return tryCrossGo(land, 0, 2, 2);
        else
            return 0;
    }
    // --- back ----
    if (dir = 2)
    {
        // mm
        if (land.lm - 2 >= land.lc && land.rm + 2 >= land.rc)
            return tryCrossGo(land, 2, 0, 1);
        // mc
        else if (land.lm - 1 >= land.lc - 1 && land.rm + 1 >= land.rc + 1)
            return tryCrossGo(land, 1, 1, 1);
        // cc
        else if (land.lm >= land.lc - 2 && land.rm >= land.rc + 2)
            return tryCrossGo(land, 0, 2, 1);
        else
            return 0;
    }
}

int main()
{
    Land land;
    land.lc = 5;
    land.lm = 5;
    land.rc = 0;
    land.rm = 0;

    cout << myMax(
        tryCrossGo(land, 2, 0, 1),
         tryCrossGo(land, 1, 1, 1),
         tryCrossGo(land, 0, 2, 1)
    );

    return 0;
}