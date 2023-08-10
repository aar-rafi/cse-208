#include <bits/stdc++.h>

using namespace std;

int main()
{
    freopen("in.txt", "w", stdout);
    srand(time(0));
    int n = 3;
    int instruction = 100000;
    int range = 50;
    map<int, bool> mp;
    while (instruction--)
    {
        int op = rand() % n;
        int key = rand() % range;
        // op += (key == 400);
        switch (op)
        {
        case 0:
            if (mp[key] == true)
            {
                instruction++;
                continue;
            }
            cout << "I " << key << endl;
            mp[key] = true;
            break;
        case 1:
            cout << "D " << key << endl;
            mp[key] = false;
            break;
        case 2:
            cout << "F " << key << endl;
            break;
        case 3:
            cout << "T ";
        }
    }
    cout << "T" << endl;
}