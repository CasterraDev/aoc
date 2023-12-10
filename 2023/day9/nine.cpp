#include <bits/stdc++.h>

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

ll f(vector<ll> x){
    vector<ll> o;
    ll zc = 0;
    for(ll i = 0; i < x.size()-1; i++){
        o.push_back(x[i+1]-x[i]);
        if (x[i+1] - x[i] == 0){
            zc++;
        }
    }
    if (zc == x.size() - 1){
        return x[0];
    }else{
        return x[0] - f(o);
    }
}

int main() {
    // Open the file
    string filename("nine.txt");
    VS lines;
    string line;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Can't open file " << filename << endl;
    }

    ll sum = 0;
    vector<ll> vo;

    // Loop through the lines of the file. with `line` containing the line
    // contents.
    ull lineidx = 0;
    while (getline(inputFile, line)) {
        stringstream ss(line);
        ll found;
        string temp;
        cout << "NUM: " << endl;
        while (!ss.eof()) {
            ss >> temp;
            if (stringstream(temp) >> found) {
                cout << found << endl;
                vo.push_back(found);
            }
            temp = "";
        }
        sum += f(vo);
        vo.clear();
        lineidx++;
    }


    cout << "Sum: " << sum << endl;

    return 0;
}
