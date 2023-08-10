#include <bits/stdc++.h>
using namespace std;
int main()
{
    string s1 = "ami";
    string s2 = "asd";
    cout << s1.append(s2) << endl;
    unordered_map<string, int> gMap;
    map<string, int> map;
    vector<string> ve;

    // gMap.insert({s1.append(s2), 100});
    string s4 = s1.append(s2);
    ve.push_back(s4);
    map.insert({(s1.append(s2)), 100});
    cout << map[ve[0]];
    queue<string> Q;
    Q.push(s2);
    cout << Q.front();
    // cout << gMap[s1.append(s2)];
    // string s3 = s1.append(s2);
    // cout << gMap.at(s3);
    // unordered_map<string, int>::iterator it;
    // for (it = gMap.begin(); it != gMap.end(); it++)
    // {
    //     cout << it->first << " " << it->second;
    // }
}