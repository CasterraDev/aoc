#include <bits/stdc++.h>
#include <cctype>
#include <string>
#include <vector>

using namespace std;

int main() {
    string filename("one2.txt");
    vector<string> lines;
    string line;

    vector<string> numLet = {
        "zero", "one", "two",   "three", "four",
        "five", "six", "seven", "eight", "nine",
    };
    vector<char> num = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    ifstream input_file(filename);
    if (!input_file.is_open()) {
    }

    unsigned long long sum = 0;

    while (getline(input_file, line)) {
        cout << line << endl;
        bool fb = false, sb = false;
        int fi = -1, si = -1;
        string str;
        str = line;
        for (int i = 0; i < str.length(); i++) {
            bool b = false;
            if (isdigit(str[i])) {
                fi = i;
                cout << "First Idx: " << str[i] << endl;
                break;
            }
            for (int y = 0; y < numLet.size(); y++){
                cout << "1: " << str.substr(i, numLet[y].length()) << endl;
                cout << "1: " << numLet[y] << endl;
                if (str.substr(i, numLet[y].length()) == numLet[y]){
                    fb = true;
                    fi = y;
                    b = true;
                    break;
                }
            }
            if (b){
                break;
            }
        }
        for (int i = str.length() - 1; i >= 0; i--) {
            bool b = false;
            if (isdigit(str[i])) {
                si = i;
                cout << "Second Idx: " << str[i] << endl;
                break;
            }
            for (int y = 0; y < numLet.size(); y++){
                int k = i - numLet[y].length() + 1;
                int mi = max(0, k);
                if (str.substr(mi, numLet[y].length()) == numLet[y]){
                    sb = true;
                    si = y;
                    b = true;
                    break;
                }
            }
            if (b) {
                break;
            }
        }
        string r;
        if (fb) {
            r = string(1, num[fi]);
        } else {
            r = string(1, str[fi]);
        }
        string r2;
        if (sb) {
            r2 = string(1, num[si]);
        } else {
            r2 = string(1, str[si]);
        }
        string re = r + r2;
        int x = stoi(re);
        cout << "RET: " <<  x << endl;
        sum += x;
    }
    input_file.close();
    cout << sum << endl;
    return 0;
}
