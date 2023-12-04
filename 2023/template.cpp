#include <bits/stdc++.h>

using namespace std;

#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
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
    ull sum = 0;
    ull sum2 = 0;

    // Open the file
    string filename("four.txt");
    VS lines;
    string line;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Can't open file " << filename << endl;
    }

    // Loop through the lines of the file. with `line` containing the line
    // contents. Split by space
    while (getline(inputFile, line)) {
        stringstream ss;
        ss << line;
        string temp;
        int found;
        while (!ss.eof()) {
            ss >> temp;
            if (stringstream(temp) >> found) {

            }
            temp = "";
        }
    }

    cout << "SUM: " << sum << endl;
    cout << "SUM2: " << sum2 << endl;

    return 0;
}
