#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <fstream>

using namespace std;

int main() {
    char fileName[50];
    int process_choice = 9, terminate_signal = 1, yet_to_read = 1; 
    char terminate = 'n';
    while(terminate != 'y'){
        cout << "Enter the name of the file you want to delete: ";
        cin >> fileName;

        if (remove(fileName) == 0) {
            cout << "File '" << fileName << "' deleted successfully" << endl;
        } else {
            cerr << "Error deleting file '" << fileName << "'" << endl;
        }
        cout << "want to terminate the program press y ?" << endl;
        cin >> terminate;
    }
    terminate = 'n';
    ofstream outfile("IPC.txt");
    char a = ',';
    outfile << yet_to_read << a << terminate_signal << a << process_choice << endl;
    outfile.close();
    return 0;
}

