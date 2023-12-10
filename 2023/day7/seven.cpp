#include <algorithm>
#include <bits/stdc++.h>
#include <cstring>
#include <sstream>

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

enum TypeEnum {
    HIGHCARD = 1,
    ONEPAIR = 2,
    TWOPAIR = 3,
    THREEKIND = 4,
    FULLHOUSE = 5,
    FOURKIND = 6,
    FIVEKIND = 7,
};

typedef struct hst {
    string hand;
    ull relRank;
    ull rank;
    ull bid;
} hst;

bool compareRelRanks(hst one, hst sec) { return (one.relRank < sec.relRank); }

bool compareRanks(hst one, hst sec) { return (one.rank < sec.rank); }

int main(int argc, char* argv[]) {
    bool part2 = false;
    if (argc == 1) {
        part2 = true;
    }
    ull sum = 0;
    ull sum2 = 0;

    // Open the file
    string filename("seven.txt");
    VS lines;
    string line;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Can't open file " << filename << endl;
    }

    map<char, int> cards;
    cards['2'] = 1;
    cards['3'] = 2;
    cards['4'] = 3;
    cards['5'] = 4;
    cards['6'] = 5;
    cards['7'] = 6;
    cards['8'] = 7;
    cards['9'] = 8;
    cards['T'] = 9;
    cards['J'] = part2 ? 0 : 10;
    cards['Q'] = 11;
    cards['K'] = 12;
    cards['A'] = 13;

    vector<hst> hands;

    // Loop through the lines of the file. with `line` containing the line
    // contents.
    ull lineIdx = 0;
    while (getline(inputFile, line)) {
        char* p;
        p = strtok(line.data(), " ");
        int c = 0;
        while (p != NULL) {
            if (c == 0) {
                cout << p << endl;
                hst ht;
                ht.hand = p;
                ht.relRank = 0;
                ht.bid = 0;
                hands.push_back(ht);
            } else {
                cout << p << endl;
                stringstream ss(p);
                ull found;
                string temp;
                ss >> temp;
                if (stringstream(temp) >> found) {
                    hands[lineIdx].bid = found;
                }
                temp = "";
            }
            c++;
            p = strtok(NULL, " ");
        }
        lineIdx++;
    }

    REP(i, hands.size()) {
        map<char, int> hc;
        REP(j, hands[i].hand.size()) {
            char h = hands[i].hand[j];
            hc[h] = hc[h] + 1;
        }
        cout << "HC: " << hc.size() << endl;
        ull hs = hc.size();
        ull joffset = part2 ? 1 : 0;
        ull jc = hc['J'];
        ull hjc = hs;
        if (hjc == 1) {
            hands[i].relRank = FIVEKIND;
        }
        if (hjc == 2) {
            hands[i].relRank = FULLHOUSE;
            for (const auto y : hc) {
                if (y.second == 4) {
                    hands[i].relRank = FOURKIND;
                    break;
                }
            }
            if (jc != 0) {
                hands[i].relRank = FIVEKIND;
            }
        }
        if (hjc == 3) {
            hands[i].relRank = THREEKIND;
            bool firstPair = false;
            for (const auto y : hc) {
                if (y.second == 2) {
                    if (firstPair) {
                        hands[i].relRank = TWOPAIR;
                    } else {
                        firstPair = true;
                    }
                }
            }
            if (jc != 0) {
                hands[i].relRank = FOURKIND;
                bool firsttwo = false;
                for (const auto y : hc) {
                    if (y.first == 'J') continue;
                    if (y.second == 2){
                        if (firsttwo){
                            hands[i].relRank = FULLHOUSE;
                        }else{
                            firsttwo = true;
                        }
                    }
                }
            }
        }
        if (hjc == 4) {
            hands[i].relRank = ONEPAIR;
            if (jc != 0) {
                hands[i].relRank = THREEKIND;
            }
        }
        if (hjc == 5) {
            hands[i].relRank = HIGHCARD;
            if (jc != 0) {
                hands[i].relRank = ONEPAIR;
            }
        }
    }

    sort(hands.begin(), hands.end(), compareRelRanks);

    REP(i, hands.size()) {
        cout << "HAND: " << hands[i].hand << " BID: " << hands[i].bid
             << " RR: " << hands[i].relRank << " R: " << hands[i].rank << endl;
    }

    ull rank = 1;
    ull oldRelRank = 1;
    ull cnt = 1;
    for (ull x = 0; x < hands.size(); x++) {
        if (hands[x].relRank != oldRelRank) {
            oldRelRank = hands[x].relRank;
            rank = cnt;
        }
        cnt++;
        hands[x].rank = rank;
        for (ull y = 0; y < hands.size(); y++) {
            if (x == y)
                continue;
            cout << "X: " << x << " Y: " << y << endl;
            if (hands[x].relRank == hands[y].relRank) {
                REP(i, hands[x].hand.size()) {
                    if (cards[hands[x].hand[i]] > cards[hands[y].hand[i]]) {
                        cout << "GR" << endl;
                        hands[x].rank++;
                        break;
                    } else if (cards[hands[x].hand[i]] <
                               cards[hands[y].hand[i]]) {
                        cout << "LS" << endl;
                        break;
                    }
                }
            }
        }
    }

    sort(hands.begin(), hands.end(), compareRanks);

    REP(i, hands.size()) {
        cout << "HAND: " << hands[i].hand << " BID: " << hands[i].bid
             << " RR: " << hands[i].relRank << " R: " << hands[i].rank << endl;
        sum += hands[i].rank * hands[i].bid;
    }

    cout << "SUM: " << sum << endl;
    cout << "SUM2: " << sum2 << endl;

    return 0;
}
