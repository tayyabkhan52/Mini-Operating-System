#include <iostream>
#include <chrono>
#include <thread>
#include <fstream>

using namespace std;

class Stopwatch {
private:
    chrono::high_resolution_clock::time_point startTime;
    chrono::high_resolution_clock::time_point endTime;

public:
    void start() {
        startTime = chrono::high_resolution_clock::now();
    }

    void stop() {
        endTime = chrono::high_resolution_clock::now();
    }

    double getDuration() {
        chrono::duration<double> duration = chrono::duration_cast<chrono::duration<double>>(endTime - startTime);
        return duration.count();
    }
};

int main() {

    int process_choice = 13, terminate_signal = 1, yet_to_read = 1; 
    char terminate = 'n';
    while (terminate != 'y') {
        Stopwatch stopwatch;

        cout << "Press ENTER to start the stopwatch." << endl;
        cin.ignore();

        stopwatch.start();

        cout << "Stopwatch started. Press ENTER to stop." << endl;
        cin.ignore();

        stopwatch.stop();

        double duration = stopwatch.getDuration();
        cout << "Elapsed time: " << duration << " seconds." << endl;

        cout << "Want to terminate the program? Press y if yes, or any other key to continue." << endl;
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

