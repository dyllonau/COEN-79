#include <iostream>
#include <string>

using namespace std;

int main()
{
    string input;
    int i = 0, j = 0;
    cout << "Please input something.\n";
    // takes in user's input and takes in whitespace accordingly.
    getline(cin, input);
    // goes through all characters in the input.
    for (int k = 0; k < input.length(); k++) {
        // checks if the character is alphanumeric and increments i.
        if (isalpha(input.at(k)))
            i++;
        // checks if the character is non-alphanumeric and increments j.
        else if (input.at(k) != ' ')
            j++;
    }
    cout << "Number of alphanumeric characters: " << i << endl;
    cout << "Number of non-alphanumeric characters: " << j;
}
