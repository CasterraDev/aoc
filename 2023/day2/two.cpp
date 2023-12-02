// Problem statement should be in this folder's README.md
#include <algorithm>
#include <bits/stdc++.h>
#include <cstring>
#include <sstream>
using namespace std;

int main() {
    // Open the file
    string filename("two.txt");
    vector<string> lines;
    string line;

    ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        cout << "Can't open file " << filename << endl;
    }

    unsigned long long sum = 0;
    unsigned long long csum = 0;
    // The max amount of cubes in a possible game for part 1
    int mb = 14, mr = 12, mg = 13;

    // Loop through the lines of the file. with `line` containing the line contents
    while (getline(inputFile, line)) {
        // Ints for each color blue, green, red
        int b = 0, g = 0, r = 0;
        // Since I already used m for the max amount of cubes. I used c for ceiling.
        // It's a weird name but I didn't want to spend time find and replacing 3 variables
        int cb = 1, cr = 1, cg = 1;
        // Use a stringstream to easily extract numbers if needed
        stringstream ss;
        ss << line;
        string temp;
        int found;
        // Used to store the id. The first num found is stored in `id` and `first` becomes true
        bool first = false;
        int id;
        // If the game's possiblity is impossible `cont` (continue) becomes true
        // For Part 2 we need to sum up the powers of all cubes. Whether the game
        // is possible or not
        bool cont = false;
        // Holds the num that was last found. Since the color comes after the num
        int before;
        // Loop through each word
        while (!ss.eof()) {
            // Reset each cube count
            b = 0;
            g = 0;
            r = 0;
            ss >> temp;
            // See if the "word" is a number
            if (stringstream(temp) >> found) {
                cout << endl << "Found: " << found << endl;
                // If it's the first number of the line then it's the game's ID.
                if (!first) {
                    id = found;
                    first = true;
                    continue;
                }
                // Store the number to be used for the next word loop run.
                before = found;
            } else {
                // If the "word" isn't a number then see what color it is.
                // Then add to the cubes count.
                if (strstr(temp.c_str(), "green")) {
                    // This `cont` if statement allows for you to get the answer to
                    // both part 1 and part 2 for any input
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
                // If any color is more than their max color allowed then the game
                // is impossible.
                // For part 2 you still need to parse the rest of the line to multiply
                // the largest amount of cubes
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
    // This is part 2's answer
    cout << "CSUM: " << csum << endl;
    // This is part 1's answer
    cout << sum << endl;

    return 0;
}
