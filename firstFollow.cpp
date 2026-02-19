#include <iostream>
#include <cstring>
#include <cctype>
using namespace std;

int n; 
string productions[10];
string firstSet[26];
string followSet[26];
bool visitedFirst[26];
bool visitedFollow[26];

bool isTerminal(char c) {
    return !(c >= 'A' && c <= 'Z');
}

// FIRST Function
void findFirst(char c) {
    if (visitedFirst[c - 'A'])
        return;

    visitedFirst[c - 'A'] = true;

    for (int i = 0; i < n; i++) {
        if (productions[i][0] == c) {
            for (int j = 2; j < productions[i].length(); j++) {

                if (isTerminal(productions[i][j])) {
                    if (firstSet[c - 'A'].find(productions[i][j]) == string::npos)
                        firstSet[c - 'A'] += productions[i][j];
                    break;
                }
                else {
                    findFirst(productions[i][j]);

                    for (char ch : firstSet[productions[i][j] - 'A']) {
                        if (ch != '#')
                            if (firstSet[c - 'A'].find(ch) == string::npos)
                                firstSet[c - 'A'] += ch;
                    }

                    if (firstSet[productions[i][j] - 'A'].find('#') == string::npos)
                        break;
                    else if (j == productions[i].length() - 1)
                        firstSet[c - 'A'] += '#';
                }
            }
        }
    }
}

// FOLLOW Function
void findFollow(char c) {

    if (visitedFollow[c - 'A'])
        return;

    visitedFollow[c - 'A'] = true;

    if (c == productions[0][0])
        followSet[c - 'A'] += '$';

    for (int i = 0; i < n; i++) {
        for (int j = 2; j < productions[i].length(); j++) {

            if (productions[i][j] == c) {

                if (j + 1 < productions[i].length()) {

                    char next = productions[i][j + 1];

                    if (isTerminal(next)) {
                        if (followSet[c - 'A'].find(next) == string::npos)
                            followSet[c - 'A'] += next;
                    }
                    else {
                        findFirst(next);

                        for (char ch : firstSet[next - 'A']) {
                            if (ch != '#')
                                if (followSet[c - 'A'].find(ch) == string::npos)
                                    followSet[c - 'A'] += ch;
                        }

                        if (firstSet[next - 'A'].find('#') != string::npos)
                            findFollow(productions[i][0]);
                    }
                }
                else {
                    if (c != productions[i][0])
                        findFollow(productions[i][0]);

                    for (char ch : followSet[productions[i][0] - 'A']) {
                        if (followSet[c - 'A'].find(ch) == string::npos)
                            followSet[c - 'A'] += ch;
                    }
                }
            }
        }
    }
}

int main() {

    cout << "Enter number of productions: ";
    cin >> n;

    cout << "Enter productions (Example: E=TR):\n";
    for (int i = 0; i < n; i++)
        cin >> productions[i];

    // Compute FIRST
    for (int i = 0; i < n; i++)
        findFirst(productions[i][0]);

    // Compute FOLLOW
    for (int i = 0; i < n; i++)
        findFollow(productions[i][0]);

    cout << "\nFIRST Sets:\n";
    for (int i = 0; i < 26; i++) {
        if (!firstSet[i].empty())
            cout << "FIRST(" << char(i + 'A') << ") = { " << firstSet[i] << " }\n";
    }

    cout << "\nFOLLOW Sets:\n";
    for (int i = 0; i < 26; i++) {
        if (!followSet[i].empty())
            cout << "FOLLOW(" << char(i + 'A') << ") = { " << followSet[i] << " }\n";
    }

    return 0;
}
