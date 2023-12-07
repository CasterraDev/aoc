#include <bits/stdc++.h>
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
    ull sum = 1;

    vector<pair<ull, ull>> timeDists;

    // Open the file
    string filename("six.txt");
    VS lines;
    string line;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Can't open file " << filename << endl;
    }

    // Loop through the lines of the file. with `line` containing the line
    // contents. Split by space
    int lineIdx = 0;
    while (getline(inputFile, line)) {
        stringstream ss;
        ss << line;
        string temp;
        ull found;
        int nidx = 0;
        ull num = 0;
        while (!ss.eof()) {
            ss >> temp;
            if (stringstream(temp) >> found) {
                if (num == 0) {
                    num = found;
                    cout << "FF: " << found << endl;
                } else {
                    ull t = found;
                    do {
                        num *= 10;
                        t /= 10;
                    }while(t != 0);
                    num += found;
                    cout << "FN: " << found << ":" << num << endl;
                }
            }
            temp = "";
            nidx++;
        }
        if (lineIdx == 0) {
            timeDists.push_back(make_pair(num, 0));
        } else {
            timeDists[0].second = num;
        }
        lineIdx++;
    }

    REP(i, timeDists.size()) {
        vector<pair<ull, ull>> mnmx;
        cout << timeDists[i].first << ":" << timeDists[i].second << endl;
        bool firstDone = false;
        REP(j, timeDists[i].first) {
            ull dist = timeDists[i].second;
            ull firstIdx = 0;
            if ((timeDists[i].first - j) * j > dist) {
                if (!firstDone) {
                    mnmx.push_back(make_pair(j, 0));
                    firstDone = true;
                    firstIdx = mnmx.size() - 1;
                } else {
                    mnmx[firstIdx].second = j;
                }
            }
        }
        REP(i, mnmx.size()) {
            cout << mnmx[i].first << ":" << mnmx[i].second << endl;
            sum *= mnmx[i].second - mnmx[i].first + 1;
        }
    }

    cout << "SUM: " << sum << endl;

    return 0;
}
