#include <algorithm>
#include <bits/stdc++.h>
#include <cstring>
#include <sstream>
using namespace std;

int main() {
    string filename("two.txt");
    vector<string> lines;
    string line;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Can't open file " << filename << endl;
    }

    unsigned long long sum = 0;
    unsigned long long csum = 0;
    int mb = 14, mr = 12, mg = 13;

    while (getline(inputFile, line)) {
        int b = 0, g = 0, r = 0;
        int cb = 1, cr = 1, cg = 1;
        stringstream ss;
        ss << line;
        string temp;
        int found;
        bool first = false;
        int id;
        bool cont = false;
        int before;
        while (!ss.eof()) {
            b = 0;
            g = 0;
            r = 0;
            ss >> temp;
            if (stringstream(temp) >> found) {
                cout << endl << "Found: " << found << endl;
                if (!first) {
                    id = found;
                    first = true;
                    continue;
                }
                before = found;
            } else {
                if (strstr(temp.c_str(), "green")) {
                    if (!cont){
                        g = before;
                    }
                    cg = max(cg, before);
                    cout << "Green " << before << " ";
                }
                if (strstr(temp.c_str(), "red")) {
                    if (!cont){
                        r = before;
                    }
                    cr = max(cr, before);
                    cout << "Red " << before << " ";
                }
                if (strstr(temp.c_str(), "blue")) {
                    if (!cont){
                        b = before;
                    }
                    cb = max(cb, before);
                    cout << "Blue " << before << " ";
                }
                if (b > mb || r > mr || g > mg) {
                    cout << "Break" << endl;
                    cont = true;
                }
            }
            temp = "";
        }
        cout << "R" << cr << " b" << cb << " g" << cg <<endl;
        csum += cr * cb * cg;
        cout << cr * cb * cg << endl;
        if (cont) {
            cont = false;
            continue;
        }
        cout << "ID: " << id << endl;
        sum += id;
    }
    cout << "CSUM: " << csum << endl;
    cout << sum << endl;

    return 0;
}
