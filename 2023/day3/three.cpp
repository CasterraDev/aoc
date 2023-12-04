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

    // Tells me when to insert the num into the vector
    bool newNum = true, stored = false;
    int n = 0;      // current number we are parsing
    int start = 0;  // start Idx of the current num
    int len = 0;    // Length of the current num
    int strIdx = 0; // StringIdx. Idx of the line vector `vecs`. or coordinate y

    // Map of numbers with the key being `unique`. I don't
    // know why I didn't just use a vector
    map<int, numst> nums;

    int unique = 0; // Unique index for `nums`
    // Last StringIdx or `strIdx` that had a number. Used for end
    // of line and end of grid
    int lastNumSI;

    // Count for the gears. Used find and count in nvim on the puzzle input and
    // found that my program wasn't finding all gears
    int cc = 0;

    for (int i = 0; i < vecs.size(); i++) {
        // Current String
        string cs = vecs[i];
        strIdx = i;
        for (int j = 0; j < cs.size(); j++) {
            const char c = cs[j];
            // Count the gears for debugging purposes
            if (c == '*') {
                cc++;
            }
            if (c >= '0' && c <= '9') {
                // If this digit is the first one then reset the variables
                if (newNum) {
                    stored = true;
                    n = 0;
                    start = j;
                    len = 0;
                }
                // If it's not the first digit then add on to the variables
                lastNumSI = i;
                newNum = false;
                n = (n * 10) + int(c - '0');
                len++;
            } else {
                // If char isn't a digit then the next digit will be a new
                // Number
                newNum = true;
            }
            // For the last number in the line
            if (newNum && stored) {
                struct numst x = {start, n, lastNumSI, len};
                nums[unique] = x;
                unique++;
                stored = false;
            }
        }
    }
    // For the last number in the grid if the number is also the last char of
    // the grid EX.
    // ...73...
    // 829*....
    // 92...*83
    // This code is for that 83
    if (!newNum && stored) {
        struct numst x = {start, n, lastNumSI, len};
        nums[unique] = x;
        unique++;
        stored = false;
    }
    // Print out all the numbers variables for debugging purposes
    for (int i = 0; i < nums.size(); i++) {
        struct numst x = nums[i];
        cout << "NEW NUM- " << x.num << " " << x.strIdx << " " << x.idx << " "
             << x.len << endl;
    }

    map<int, numst>::iterator it;
    map<unsigned long long, vector<int>>::iterator git;

    map<unsigned long long, vector<int>> gm;
    unsigned long long sum2 = 0;

    for (it = nums.begin(); it != nums.end(); it++) {
        struct numst t = it->second;
        string s = vecs[t.strIdx];

        // ----------Check the neighbors for symbols and gears----------

        // Check the left neighbor with (startIdx - 1)
        if (t.idx > 0) {
            if (s[t.idx - 1] != '.') {
                sum += t.num;
                if (s[t.idx - 1] == '*') {
                    // I flipped x & y by accident
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
        // Check the right neighbor with (startingIdx + numLength + 1)
        if (t.idx + t.len < s.length()) {
            if (s[t.idx + t.len] != '.') {
                sum += t.num;
                if (s[t.idx + t.len] == '*') {
                    // I flipped x & y by accident
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
        // Check the top line above the number from (startingIdx - 1 to
        // startingIdx + Length + 1)
        if (t.strIdx > 0) {
            string o = vecs[t.strIdx - 1];
            cout << "LINE: ";
            for (int y = max(t.idx - 1, 0);
                 y < clamp(t.idx + t.len + 1, 0, (int)o.size()); y++) {
                if (o[y] != '.' && (o[y] < '0' || o[y] > '9')) {
                    sum += t.num;
                    cout << o[y];
                    if (o[y] == '*') {
                        // Use cantor packing to combine the x and y coordinates
                        // into one int
                        // I flipped x & y by accident
                        int x = t.strIdx - 1;
                        int z = (y + x) * (y + x + 1) / 2 + x;
                        // Use that cantor packed int to index the gear map
                        vector<int> g = gm[z];
                        g.push_back(t.num);
                        gm[z] = g;
                    }
                }
            }
            cout << endl;
        }
        // Check the bottom line below the number from (startingIdx - 1 to
        // startingIdx + Length + 1)
        if (t.strIdx < vecs.size() - 1) {
            string o = vecs[t.strIdx + 1];
            for (int y = max(t.idx - 1, 0);
                 y < clamp(t.idx + t.len + 1, 0, (int)o.size()); y++) {
                if (o[y] != '.' && (o[y] < '0' || o[y] > '9')) {
                    sum += t.num;
                    if (o[y] == '*') {
                        // I flipped x & y by accident
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
        }
    }
    // Go through each gear if it has two adjacent numbers
    for (git = gm.begin(); git != gm.end(); git++) {
        vector<int> r = git->second;
        if (r.size() == 2) {
            int p = r[0] * r[1];
            sum2 += p;
        }
    }
    // Count the amount of gears the program detects for debugging purposes
    int cnt = 0;
    // Output the gear combinations for debugging purposes
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

    // Part 1
    cout << "Sum: " << sum << endl;
    // Part 2
    cout << "Sum2: " << sum2 << endl;

    return 0;
}
