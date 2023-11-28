#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

using namespace std;

int main()
{
    string input, correct;
    int guess, guesses[20], steps = 0;
    cout << "Think of a number between 1 and 20. Press enter when you are ready.\n";
    // Takes in the "Enter" command specifically.
    cin.ignore();
    // Sets seed for the random number generator.
    srand(time(0));
    // Loop runs as long as the user input is not "Y".
    while (correct != "Y") {
        // rolls a random number between 1 and 20.
        guess = rand() % 20 + 1;
        // goes through the array of past guesses that the program has tried before and rerolls if the guess has already been done.
        for (int i = 0; i < steps; i++) {
            if (guess == guesses[i]) {
                guess = rand() % 20 + 1;
                i = -1;
            }
        }
        cout << "Is the number " << guess << "? Y or N:\n";
        // User confirms if guess is correct or not.
        cin >> correct;
        if (correct != "Y")
            guesses[steps] = guess;
        // Number of steps increment after every iteration of the loop.
        steps++;
    }
    cout << "I found the number in " << steps << " step(s).";
}
