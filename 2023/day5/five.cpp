#include <bits/fs_fwd.h>
#include <bits/stdc++.h>
#include <utility>
#include <vector>

using namespace std;

#define FOR(i, j, k, in) for (ull i = j; i < k; i += in)
#define RFOR(i, j, k, in) for (ull i = j; i >= k; i -= in)
#define REP(i, j) FOR(i, 0, j, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define INF (ull)1e9
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007

typedef vector<int> VI;
typedef vector<string> VS;
typedef unsigned long long ull;
typedef long long ll;

typedef struct nm {
    ull si;
    ull di;
    ull l;
} nm;

typedef struct convertnm {
    vector<nm> map;
    ull lowest, highest;
} convertnm;

typedef struct seedRange {
    ull lo, hi;
} seedRange;

vector<pair<ull, ull>> f(vector<pair<ull, ull>> v, convertnm cn) {
    vector<pair<ull, ull>> N;
    REP(i, cn.map.size()) {
        nm n = cn.map[i];
        vector<pair<ull, ull>> Nv;
        while (v.size() > 0) {
            pair<ull, ull> p = v[v.size() - 1];
            v.pop_back();
            pair<ull, ull> before = make_pair(p.first, min(p.second, n.si));
            pair<ull, ull> inter =
                make_pair(max(p.first, n.si), min(n.si + n.l, p.second));
            pair<ull, ull> after =
                make_pair(max(n.si + n.l, p.first), p.second);
            if (before.second > before.first) {
                cout << "Before" << endl;
                Nv.push_back(before);
            }
            if (inter.second > inter.first) {
                cout << "INTER" << endl;
                N.push_back(make_pair(inter.first - n.si + n.di,
                                      inter.second - n.si + n.di));
            }
            if (after.second > after.first) {
                cout << "After" << endl;
                Nv.push_back(after);
            }
        }
        v = Nv;
    }
    return v;
}

int main() {
    ull sum = 0;
    ull sum2 = 0;

    // Open the file
    string filename("five.txt");
    VS lines;
    string line;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Can't open file " << filename << endl;
    }

    nm x;
    vector<convertnm> allMaps;
    VI seeds;
    vector<pair<ull, ull>> seedRanges;
    bool firstLinePast = false;
    convertnm convertMaps;

    // Loop through the lines of the file. with `line` containing the line
    // contents. Split by space
    while (getline(inputFile, line)) {
        stringstream ss;
        ss << line;
        string temp;
        ull found;
        bool newMap;

        if (!firstLinePast) {
            bool f = false;
            ull o = 0;
            while (!ss.eof()) {
                ss >> temp;
                if (stringstream(temp) >> found) {
                    if (!f) {
                        o = found;
                        f = true;
                        continue;
                    }
                    seedRanges.push_back(make_pair(o, o + found));
                    // FOR(i, o, o + found, 1) { seeds.push_back(i); }
                    f = false;
                }
                temp = "";
            }
            firstLinePast = true;
            cout << "Got Seeds" << endl;
            REP(i, seedRanges.size()) {
                cout << "SR: " << seedRanges[i].first << " "
                     << seedRanges[i].second << endl;
            }
            continue;
        }

        if (line.size() == 0) {
            continue;
        }

        ull idx = 0;
        bool newSrc = true;
        bool newSrc2 = true;
        while (!ss.eof()) {
            ss >> temp;
            if (stringstream(temp) >> found) {
                if (idx == 0) {
                    x.di = found;
                } else if (idx == 1) {
                    x.si = found;
                } else if (idx == 2) {
                    x.l = found;
                    if (newSrc || x.si < convertMaps.lowest) {
                        newSrc = false;
                        convertMaps.lowest = x.si;
                    }
                    if (newSrc2 || x.si + x.l > convertMaps.highest) {
                        newSrc2 = false;
                        convertMaps.highest = x.si + x.l;
                    }
                }
                idx++;
            }
            temp = "";
        }
        if (line.find(":") != string::npos) {
            if (convertMaps.map.size() > 0) {
                allMaps.push_back(convertMaps);
            }
            convertMaps.map.clear();
        } else {
            convertMaps.map.push_back(x);
            x.l = 0;
            x.di = 0;
            x.si = 0;
        }
    }
    allMaps.push_back(convertMaps);
    convertMaps.map.clear();

    REP(i, allMaps.size()) {
        cout << "NEW MAP----------------------" << endl;
        REP(y, allMaps[i].map.size()) {
            nm d = allMaps[i].map[y];
            cout << " " << d.di << " " << d.si << " " << d.l << endl;
        }
    }

    cout << "Got Maps" << endl;

    cout << "SEEEEEEEEEEDSSSSSSS____________" << endl;
    REP(i, seedRanges.size()) {
        cout << seedRanges[i].first << " " << seedRanges[i].second << endl;
    }

    vector<pair<ull, ull>> y = seedRanges;
    REP(i, allMaps.size()) {
        y = f(y, allMaps[i]);
    }
    sum = INF;
    REP(i, y.size()) {
        cout << y[i].first << " " << y[i].second << endl;
        sum = min(y[i].first, sum);
    }

    cout << "SUM: " << sum << endl;
    cout << "SUM2: " << sum2 << endl;

    return 0;
}
