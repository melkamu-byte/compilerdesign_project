#include <iostream>
using namespace std;

bool isValidBinary(string str) {
    for (char ch : str) {
        if (ch != '0' && ch != '1') {
            return false;
        }
    }
    return true;
}

int main() {
    string input;
    cout << "Enter a string: ";
    cin >> input;

    if (isValidBinary(input))
        cout << "Valid binary string" << endl;
    else
        cout << "Invalid binary string" << endl;

    return 0;
}

