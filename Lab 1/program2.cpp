#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
    ifstream infile;
    infile.open(argv[1]);
    string input;
    // reads in each word seperated by a space in the text file and checks through each character of the word for alphanumeric characters.
    while (infile >> input) {
        for (int i = 0; i < input.length(); i++) {
            // erases non-alphanumeric characters and reads the word again to scan for more.
            if (!isalpha(input.at(i))) {
                input.erase(input.begin() + i);
                i--;
            }
            // capitalizes each alphanumeric character.
            else
                input.at(i) = toupper(input.at(i));
        }
        // outputs new, capitalized input.
        if (input.length() >= 10)
            cout << input << endl;
    }
}
