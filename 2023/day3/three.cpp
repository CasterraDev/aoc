#include <algorithm>
#include <bits/stdc++.h>
#include <map>

using namespace std;

struct numst {
    int idx;
    int num;
    int strIdx;
    int len;
};

int main() {
    unsigned long long sum = 0;

    string filename("three.txt");
    vector<string> lines;
    string line;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Can't open file " << filename << endl;
    }

    vector<string> vecs;

    // Loop through the lines of the file. with `line` containing the line
    // contents
    while (getline(inputFile, line)) {
        vecs.push_back(line);
    }

    bool newNum = true, stored = false;
    int n = 0;
    int start = 0;
    int len = 0;
    int strIdx = 0;
    map<int, numst> nums;
    int unique = 0;
    int lastNumSI;
    int cc = 0;

    for (int i = 0; i < vecs.size(); i++) {
        string cs = vecs[i];
        strIdx = i;
        for (int j = 0; j < cs.size(); j++) {
            const char c = cs[j];
            if (c == '*') {
                cc++;
            }
            if (c >= '0' && c <= '9') {
                if (newNum) {
                    stored = true;
                    n = 0;
                    start = j;
                    len = 0;
                }
                lastNumSI = i;
                newNum = false;
                n = (n * 10) + int(c - '0');
                len++;
            } else {
                newNum = true;
            }
            if (newNum && stored) {
                struct numst x = {start, n, lastNumSI, len};
                nums[unique] = x;
                unique++;
                stored = false;
            }
        }
    }
    if (!newNum && stored) {
        struct numst x = {start, n, lastNumSI, len};
        nums[unique] = x;
        unique++;
        stored = false;
    }

    for (int i = 0; i < nums.size(); i++) {
        struct numst x = nums[i];
        cout << "NEW NUM- " << x.num << " " << x.strIdx << " " << x.idx << " " << x.len << endl;
    }

    map<int, numst>::iterator it;
    map<unsigned long long, vector<int>>::iterator git;

    map<unsigned long long, vector<int>> gm;
    unsigned long long sum2 = 0;

    for (it = nums.begin(); it != nums.end(); it++) {
        struct numst t = it->second;
        string s = vecs[t.strIdx];
        if (t.idx > 0) {
            if (s[t.idx - 1] != '.') {
                sum += t.num;
                if (s[t.idx - 1] == '*') {
                    int y = t.idx - 1;
                    int x = t.strIdx;
                    int z = (y + x) * (y + x + 1) / 2 + x;
                    cout << t.num << " Y: " << t.idx - 1 << " X: " << t.strIdx
                         << endl;
                    vector<int> g = gm[z];
                    g.push_back(t.num);
                    gm[z] = g;
                }
            }
        }
        if (t.idx + t.len < s.length()) {
            if (s[t.idx + t.len] != '.') {
                sum += t.num;
                if (s[t.idx + t.len] == '*') {
                    int y = t.idx + t.len;
                    int x = t.strIdx;
                    int z = (y + x) * (y + x + 1) / 2 + x;
                    cout << t.num << " Y: " << t.idx + t.len
                         << " X: " << t.strIdx << endl;
                    vector<int> g = gm[z];
                    g.push_back(t.num);
                    gm[z] = g;
                }
            }
        }
        if (t.strIdx > 0) {
            string o = vecs[t.strIdx - 1];
            cout << "LINE: ";
            for (int y = max(t.idx - 1, 0);
                 y < clamp(t.idx + t.len + 1, 0, (int)o.size()); y++) {
                if (o[y] != '.' && (o[y] < '0' || o[y] > '9')) {
                    sum += t.num;
                    cout << o[y];
                    if (o[y] == '*') {
                        int x = t.strIdx - 1;
                        int z = (y + x) * (y + x + 1) / 2 + x;
                        cout << t.num << " Y: " << y << " X: " << t.strIdx - 1
                             << endl;
                        vector<int> g = gm[z];
                        g.push_back(t.num);
                        gm[z] = g;
                    }
                }
            }
            cout << endl;
        }
        if (t.strIdx < vecs.size() - 1) {
            string o = vecs[t.strIdx + 1];
            for (int y = max(t.idx - 1, 0);
                 y < clamp(t.idx + t.len + 1, 0, (int)o.size()); y++) {
                if (o[y] != '.' && (o[y] < '0' || o[y] > '9')) {
                    sum += t.num;
                    if (o[y] == '*') {
                        int x = t.strIdx + 1;
                        int z = (y + x) * (y + x + 1) / 2 + x;
                        cout << t.num << " Y: " << y << " X: " << t.strIdx + 1
                             << endl;
                        vector<int> g = gm[z];
                        g.push_back(t.num);
                        gm[z] = g;
                    }
                }
            }
            //          cout << endl;
        }
    }
    for (git = gm.begin(); git != gm.end(); git++) {
        vector<int> r = git->second;
        if (r.size() == 2) {
            int p = r[0] * r[1];
            sum2 += p;
            //          cout << "ADD: " << sum2 << " " << r[0] << "*" << r[1] <<
            //          endl;
        }
    }
    int cnt = 0;
    cout << "GEARS __________" << endl;
    for (git = gm.begin(); git != gm.end(); git++) {
        cnt++;
        vector<int> r = git->second;
        for (int i = 0; i < r.size(); i++) {
            cout << r[i] << " ";
        }
        cout << "MOD: " << git->first % 121 << " REM: " << git->first / 121
             << endl;
    }
    cout << "Gear Cnt" << cnt << endl;
    cout << "Cnt" << cc << endl;

    cout << "Sum: " << sum << endl;
    cout << "Sum2: " << sum2 << endl;

    return 0;
}
