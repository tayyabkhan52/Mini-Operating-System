#include <iostream>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <cstring>
#include <fstream>

using namespace std;

void close_terminal() {
    system("pkill -f gnome-terminal ");
}

int main() {
    int value = -1;
    int process_choice = 6, terminate_signal = 1, yet_to_read = 1;
    char terminate = 'n';
    srand(time(NULL));

    cout << "Welcome to the Mini Game!\n";
    cout << "=========================\n";

    int target = rand() % 100 + 1;
    int guess;
    int attempts = 0;
    cout << "Enter 'y' to terminate the process" << endl;
    while (terminate != 'y') {
        cout << "Guess the number between 1 and 100: ";
        cin >> guess;

        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        attempts++;

        if (guess < target) {
            cout << "Too low. Try again.\n";
        } else if (guess > target) {
            cout << "Too high. Try again.\n";
        } else {
            cout << "Congratulations! You guessed the number in " << attempts << " attempts.\n";
            break;
        }
        cout << "Enter 'y' to terminate the process" << endl;
        cin >> terminate;
    }

    ofstream outfile("IPC.txt");
    char a = ',';
    // Write two integer values to the file
    outfile << yet_to_read << a << terminate_signal << a << process_choice << endl;
    // Close the file
    outfile.close();

    return 0;
}

