#include <bits/stdc++.h>
#include <cstring>

using namespace std;

int main() {
    // Open the file
    string filename("four.txt");
    vector<string> lines;
    string line;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Can't open file " << filename << endl;
    }

    unsigned long long sum = 0;

    typedef struct twoint {
        vector<int> wn;
        vector<int> n;
    } twoint;
    typedef struct twostr {
        vector<int> wn;
        vector<int> n;
    } twostr;
    typedef struct sc {
        int wnc;
        int copies;
    } sc;

    vector<sc> vsc;

    // Loop through the lines of the file. with `line` containing the line
    // contents
    while (getline(inputFile, line)) {
        vector<string> t;
        twoint ti;
        char* y = (char*)line.c_str();
        char* x = strtok(y, ":|");
        while (x != NULL) {
            cout << x << endl;
            t.push_back(x);
            x = strtok(NULL, ":|");
        }
        for (int i = 0; i < t.size(); i++) {
            if (i == 0) {
                ti.n.clear();
                ti.wn.clear();
                continue;
            }
            stringstream ss;
            ss << t[i];
            string temp;
            int found;
            while (!ss.eof()) {
                ss >> temp;
                if (stringstream(temp) >> found) {
                    if (i == 1) {
                        ti.wn.push_back(found);
                    } else if (i == 2) {
                        ti.n.push_back(found);
                    }
                }
                temp = "";
            }
        }

        int gc = 0;
        for (int i = 0; i < ti.wn.size(); i++) {
            for (int j = 0; j < ti.n.size(); j++) {
                if (ti.wn[i] == ti.n[j]) {
                    gc++;
                }
            }
        }
        sc o;
        o.wnc = gc;
        o.copies = 0;
        vsc.push_back(o);
        int rs = 0;
        for (int i = 1; i <= gc; i++) {
            if (i == 1) {
                rs = 1;
                continue;
            }
            rs *= 2;
        }
        sum += rs;
        cout << "GC: " << gc << " RS: " << rs << " SUM: " << sum << endl;
    }
    int sum2 = 0;
    for (int i = 0; i < vsc.size(); i++){
       sum2 += 1 + vsc[i].copies; 
       if (vsc[i].wnc > 0){
            for (int j = 1; j <= vsc[i].wnc; j++){
                vsc[i + j].copies += 1 + vsc[i].copies;
            }
       }
    }
    cout << "SUM: " << sum << endl;
    cout << "SUM2: " << sum2 << endl;

    return 0;
}
