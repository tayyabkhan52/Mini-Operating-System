#include <iostream>
#include <ctime>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    while (true) {
        // Get the current time
        auto now = chrono::system_clock::now();
        time_t time = chrono::system_clock::to_time_t(now);

        // Convert the time to a string
        char* timeStr = ctime(&time);

        // Clear the console and move the cursor to the top left corner
        cout << "\033[2J\033[1;1H";

        // Print the current time
        cout << "Current time: " << timeStr;

        // Wait for one second before updating the time again
        this_thread::sleep_for(chrono::seconds(1));
    }

    return 0;
}

