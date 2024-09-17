#include <iostream>
#include <unistd.h>
#include <fstream>

using namespace std;

int main() {
    char filename[256];
    char buffer[256];
    int process_choice = 11, terminate_signal = 1, yet_to_read = 1; 
    char terminate = 'n';
    while (terminate != 'y') {
        cout << "Enter file name: ";
        cin >> filename;

        if (access(filename, F_OK) != -1) {
            getcwd(buffer, sizeof(buffer));
            cout << "File location: " << buffer << "/" << filename << endl;
        } else {
            cerr << "Error: file '" << filename << "' does not exist" << endl;
        }

        cout << "Want to terminate the program? Press y if yes, or any other key to continue." << endl;
        cin >> terminate;
    }

    std::ofstream outfile("IPC.txt");
    char a = ',';
    // Write two integer values to the file
    outfile << yet_to_read << a << terminate_signal << a << process_choice << endl;
    // Close the file
    outfile.close();

    return 0;
}

