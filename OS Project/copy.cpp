#include <iostream>
#include <fstream>
using namespace std;

int main() {
    string srcFile, destFile;
    ifstream srcPtr;
    ofstream destPtr;
    int ch;
    int process_choice = 8, terminate_signal = 1, yet_to_read = 1;
    char terminate = 'n';
    while (terminate != 'y') {
        cout << "Enter the source file name: ";
        cin >> srcFile;

        cout << "Enter the destination file name: ";
        cin >> destFile;

        srcPtr.open(srcFile, ios::binary);
        if (!srcPtr.is_open()) {
            cerr << "Error: cannot open source file " << srcFile << endl;
            continue;
        }

        destPtr.open(destFile, ios::binary);
        if (!destPtr.is_open()) {
            cerr << "Error: cannot create destination file " << destFile << endl;
            continue;
        }

        while ((ch = srcPtr.get()) != EOF) {
            destPtr.put(ch);
        }

        srcPtr.close();
        destPtr.close();

        cout << "File " << srcFile << " copied to " << destFile << " successfully.\n";

        cout << "Want to terminate the program? If not, press 'n': ";
        cin >> terminate;
    }

    terminate = 'n';
    ofstream outfile("IPC.txt");
    char a = ',';
    // Write two integer values to the file
    outfile << yet_to_read << a << terminate_signal << a << process_choice << endl;
    // Close the file
    outfile.close();

    return 0;
}

