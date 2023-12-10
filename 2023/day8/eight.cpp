#include <bits/stdc++.h>
#include <numeric>
#include <regex>
#include <unordered_map>
#include <utility>

using namespace std;

#define FOR(i, j, k, in) for (int i = j; i < k; i += in)
#define RFOR(i, j, k, in) for (int i = j; i >= k; i -= in)
#define REP(i, j) FOR(i, 0, j, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define FOREACH(it, l) for (auto it = l.begin(); it != l.end(); it++)
#define INF (int)1e9
#define EPS 1e-9
#define PI 3.1415926535897932384626433832795
#define MOD 1000000007

typedef vector<int> VI;
typedef vector<string> VS;
typedef unsigned long long ull;
typedef long long ll;

int main() {
    // Open the file
    string filename("eight.txt");
    VS lines;
    string line;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Can't open file " << filename << endl;
    }

    string go;
    getline(inputFile, go);

    unordered_map<string, array<string, 2>> m;

    const regex mask(R"(([A-Z0-9]+) = \(([A-Z0-9]+), ([A-Z0-9]+)\))");
    smatch match;
    // Loop through the lines of the file. with `line` containing the line
    // contents.
    while (getline(inputFile, line)) {
        regex_search(line, match, mask);
        m[match[1]] = {{match[2], match[3]}};
        // cout << match[1] << ":" << match[2] << ":" << match[3] << endl;
    }

    // string cur = "AAA";
    unordered_map<string, pair<string, ull>> curPos;
    vector<string> pos;
    for (const auto& [key, val] : m) {
        string s = key;
        if (key.size() == 0)
            continue;
        if (key[key.size() - 1] == 'A') {
            pos.push_back(key);
            curPos[key] = make_pair(key, 0);
        }
    }

    REP(i, pos.size()) {
        cout << pos[i] << endl;
    }

    ull idx = 0;
    ull steps = 0;
    map<ull, ull> ts;
    while (true) {
        string tp;
        REP(i, pos.size()) {
            if (go[idx] == 'L') {
                tp = m[curPos[pos[i]].first][0];
            } else {
                tp = m[curPos[pos[i]].first][1];
            }
            curPos[pos[i]] = make_pair(tp, curPos[pos[i]].second + 1);
            if (tp[tp.size() - 1] == 'Z') {
                cout << "TS: " << ts.size() << " PS: " << pos[i]
                     << " CSS: " << curPos[pos[i]].second << endl;
                ts[i] = curPos[pos[i]].second;
            }
            if (ts.size() == pos.size()) {
                ull ans = 1;
                REP(j, ts.size()) {
                    cout << "TS: " << ts[i] << endl;
                    ans = (ts[j] * ans) / gcd(ts[j], ans);
                }
                cout << "Ans: " << ans << endl;
                return 0;
            }
        }
        idx++;
        if (idx == go.size()) {
            idx = 0;
        }
    }

    return 0;
}
