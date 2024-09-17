#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <dirent.h> // for opendir, readdir, closedir
#include <cstring> // for strcmp
#include <string>
#include <thread>
#include <mutex>
#include <semaphore.h>
#include <chrono>
#include <queue>
#include <cstdio>
#include <iomanip>
#include <cstdlib> // for system(), atoi()

using namespace std;

const int max_ram = 32, min_ram = 1, default_ram = 8;
const int max_space = 1000, min_space = 10, default_space = 256;
const int max_core = 32, min_core = 1, default_core = 8;
int ram = default_ram;
int space = default_space;
int core = default_core;

// shared resource protected by a semaphore
sem_t semaphore;
int ram_check = 0;
int space_check = 0;
int core_check = 0;

bool AddZero() {
    ofstream out;
    out.open("Total_Processes.txt", ios::app);
    if (!out.is_open())
        return false;
    out << 0 << endl;
    out.close();
    return true;
}

bool RemoveZero() {
    ifstream in;
    in.open("Total_Processes.txt");
    if (!in.is_open())
        return false;
    string input;
    int count = 0;
    while (!in.eof()) {
        getline(in, input);
        count++;
    }
    in.close();
    ofstream out;
    out.open("Total_Processes.txt");
    for (int i = 1; i < count - 1; i++) {
        out << 0 << endl;
    }
    out.close();
    return true;
}

int TotalZero() {
    ifstream in;
    in.open("Total_Processes.txt");
    if (!in.is_open())
        return -1;
    string input;
    int count = 0;
    while (!in.eof()) {
        getline(in, input);
        count++;
    }
    in.close();
    return count - 1;
}

void ClearFile() {
    ofstream out;
    out.open("Total_Processes.txt");
    cout << "";
    out.close();
}

void *runCommands(void *arg) {
    sem_wait(&semaphore);  // acquire the semaphore before accessing the shared resource
    core_check++;
    ram_check++;
    space_check += 10;
    cout << "\nTotal core being used: " << core_check << "\t Total ram being used: " << ram_check << "\t Total space being used: " << space_check << endl;
    sem_post(&semaphore);        // release the semaphore after accessing the shared resource
    string filename = *static_cast<string*>(arg);
    string compileCmd = "g++ -o " + filename + " " + filename + ".cpp";
    string runCmd = "gnome-terminal -- ./" + filename;

    if (filename == "compress") {
        compileCmd = "g++ -o " + filename + " " + filename + ".cpp -lz";
        runCmd = "gnome-terminal -- ./" + filename;
    } else if (filename == "music") {
        compileCmd = "g++ -o " + filename + " " + filename + ".cpp -lao -lmpg123";

        // Prompt the user to choose the music file
        char choice;
        cout << "Which music file do you want to play? Enter '1' for song.mp3 or '2' for piano.mp3: ";
        cin >> choice;

        // Construct the run command based on user's choice
        if (choice == '1') {
           runCmd = "./" + filename + " song.mp3";

        } else if (choice == '2') {
            runCmd = "./" + filename + " piano.mp3";

        } else {
            cerr << "Invalid choice. Exiting music player." << endl;
            pthread_exit(NULL);
            RemoveZero(); // Remove zeros when the process is terminated
        }
    }
    system(compileCmd.c_str());
    system(runCmd.c_str());

    pthread_exit(NULL);
    RemoveZero(); // Remove zeros when the process is terminated
}

void killTerminals() {
    system("pkill -f gnome-terminal");
}

void startingMenu() {
    cout << "\t**********************************************\n";
    cout << "\t*                                            *\n";
    cout << "\t*          Welcome to Our OS System!         *\n";
    cout << "\t*                                            *\n";
    cout << "\t**********************************************\n\n";
    cout << "Hello, user!\n\n";
}
void displayFeatures() {
    cout << "\n┌─────────────────────────── Features ──────────────────────────┐\n";
    cout << "│   1. Calculator                                                 │\n";
    cout << "│   2. Calendar                                                   │\n";
    cout << "│   3. Copy                                                       │\n";
    cout << "│   4. Compress                                                   │\n";
    cout << "│   5. Delete                                                     │\n";
    cout << "│   6. File                                                       │\n";
    cout << "│   7. Hangman                                                    │\n";
    cout << "│   8. Music                                                      │\n";
    cout << "│   9. Random Number Generator                                    │\n";
    cout << "│  10. Tic Tac Toe                                                │\n";
    cout << "│  11. Timer                                                      │\n";
    cout << "│  12. Watch                                                      │\n";
    cout << "└─────────────────────────────────────────────────────────────────┘\n";
}

int main(int argc, char *argv[]) {

    string os_name = "22F-3440 22F-3449 22F-8814 OS";
    string args;
    char choice_flag = 'y';
    char choice_flag_inner = 'n';
    char ans;
    char choice = 'y';
    int ready_queue_flag = 0;
    int task = 0;
    bool kernel_check = false, user_check = false;
    int req_space;
    int req_ram;
    sem_init(&semaphore, 0, 1);
    queue<int> ready_queue;
    cout << "\n\tWelcome to " << os_name << "!\n";
    cout << "----------------------------------------\n";
    cout << "Please select a mode:\n";
    cout << "1. Kernel Mode\n";
    cout << "2. User Mode\n";
    cout << "----------------------------------------\n";
    int input;
    while (ready_queue_flag == 0) {
        cout << "Enter your choice: ";
        cin >> input;
        if (input == 1 || input == 2) {
            ready_queue_flag++;
        } else {
            cout << "Invalid choice. Please enter 1 or 2.\n";
        }
    }
    if (input == 1) {
        kernel_check = true;
            startingMenu();
    } else if (input == 2) {
        user_check = true;
            startingMenu();
    }
    while (choice == 'y') {
        if (kernel_check == true) {
            cout << "Do you want to change the requirements? (y/n): ";
            cin >> ans;
            if (ans == 'y') {
                cout << "Enter your requirements:\n";
                cout << "RAM [" << min_ram << "-" << max_ram << "]: ";
                cin >> req_ram;
                if (req_ram < min_ram) {
                    cout << "RAM too low, using default value.\n";
                } else if (req_ram > max_ram) {
                    cout << "RAM too high, using maximum value.\n";
                    ram = max_ram;
                } else {
                    ram = req_ram;
                }
                cout << "Storage space [" << min_space << "-" << max_space << "]: ";
                cin >> req_space;
                if (req_space < min_space) {
                    cout << "Storage space too low, using default value.\n";
                } else if (req_space > max_space) {
                    cout << "Storage space too high, using maximum value.\n";
                    space = max_space;
                } else {
                    space = req_space;
                }
                cout << "Number of cores [" << min_core << "-" << max_core << "]: ";
                int req_core;
                cin >> req_core;
                if (req_core < min_core) {
                    cout << "Number of cores too low, using default value.\n";
                } else if (req_core > max_core) {
                    cout << "Number of cores too high, using maximum value.\n";
                    core = max_core;
                } else {
                    core = req_core;
                }
                cout << "\nYour system configuration:\n";
                cout << "RAM: " << ram << " GB\n";
                cout << "Storage space: " << space << " GB\n";
                cout << "Number of cores: " << core << "\n";
            }
        }
        core_check = TotalZero();
        ram_check = TotalZero();
        space_check = TotalZero() * 10;
        if (choice_flag == 'y') {
            if (TotalZero() == core) {
                while (true) {
                    displayFeatures();
                    cout << "\nSelect a task (1-13): ";
                    cin >> task;
                    ready_queue.push(task);
                    cout << "\nThe system is currently at maximum capacity and cannot allocate additional resources. Please complete existing tasks to free up resources. Your task has been added to the ready queue and will be allocated resources as they become available.\n";
                    cout << "Do you want to perform another task? (y/n) ";
                    cin >> choice;
                    choice_flag_inner = 'y';
                    if (choice == 'n') {
                        choice_flag = 'n';
                    }
                    if (!ready_queue.empty()) {
                        if (ready_queue.front() > 0 && ready_queue.front() < 14) {
                            task = ready_queue.front();
                            core_check = TotalZero();
                            ram_check = TotalZero();
                            space_check = TotalZero() * 10;
                        }
                        ready_queue.pop();
                        break;
                    }
                    if (TotalZero() != core) {
                        break;
                    }
                }
            } else {
                if (ready_queue.empty()) {
                    displayFeatures();
                    cout << "\nSelect a task (1-13): ";
                    cin >> task;
                }
                if (!ready_queue.empty()) {
                    if (ready_queue.front() > 0 && ready_queue.front() < 14) {
                        task = ready_queue.front();
                        core_check = TotalZero();
                        ram_check = TotalZero();
                        space_check = TotalZero() * 10;
                    }
                    ready_queue.pop();
                }
            }
        } else {
            if (TotalZero() == core) {
                while (true) {
                    if (TotalZero() != core) {
                        break;
                    }
                }
            }
            if (TotalZero() < core) {
                int check_core_loop = TotalZero();
                while (true) {
                    if (TotalZero() < check_core_loop) {
                        break;
                    }
                }
            }
            if (ready_queue.empty()) {
                break;
            }
            if (!ready_queue.empty()) {
                if (ready_queue.front() > 0 && ready_queue.front() < 14) {
                    task = ready_queue.front();
                    core_check = TotalZero();
                    ram_check = TotalZero();
                    space_check = TotalZero() * 10;
                }
                ready_queue.pop();
            }
        }
        switch (task) {
            case 1:
                args = "calculator";
                if (TotalZero() == core) {
                    ready_queue.push(1);
                } else {
                    AddZero();
                    pthread_t thread_1;
                    pthread_create(&thread_1, NULL, runCommands, &args);
                    pthread_join(thread_1, NULL);
                }
                break;
            case 2:
                args = "calendar";
                if (TotalZero() == core) {
                    ready_queue.push(2);
                } else {
                    AddZero();
                    pthread_t thread_2;
                    pthread_create(&thread_2, NULL, runCommands, &args);
                    pthread_join(thread_2, NULL);
                }
                break;
            case 3:
                args = "copy";
                if (TotalZero() == core) {
                    ready_queue.push(3);
                } else {
                    AddZero();
                    pthread_t thread_3;
                    pthread_create(&thread_3, NULL, runCommands, &args);
                    pthread_join(thread_3, NULL);
                }
                break;
            case 4:
                args = "compress";
                if (TotalZero() == core) {
                    ready_queue.push(4);
                } else {
                    AddZero();
                    pthread_t thread_4;
                    pthread_create(&thread_4, NULL, runCommands, &args);
                    pthread_join(thread_4, NULL);
                }
                break;
            case 5:
                args = "delete";
                if (TotalZero() == core) {
                    ready_queue.push(5);
                } else {
                    AddZero();
                    pthread_t thread_5;
                    pthread_create(&thread_5, NULL, runCommands, &args);
                    pthread_join(thread_5, NULL);
                }
                break;
            case 6:
                args = "file";
                if (TotalZero() == core) {
                    ready_queue.push(6);
                } else {
                    AddZero();
                    pthread_t thread_6;
                    pthread_create(&thread_6, NULL, runCommands, &args);
                    pthread_join(thread_6, NULL);
                }
                break;
            case 7:
                args = "hungman";
                if (TotalZero() == core) {
                    ready_queue.push(7);
                } else {
                    AddZero();
                    pthread_t thread_7;
                    pthread_create(&thread_7, NULL, runCommands, &args);
                    pthread_join(thread_7, NULL);
                }
                break;
            case 8:
                args = "music";
                if (TotalZero() == core) {
                    ready_queue.push(8);
                } else {
                    AddZero();
                    pthread_t thread_8;
                    pthread_create(&thread_8, NULL, runCommands, &args);
                    pthread_join(thread_8, NULL);
                }
                break;
            case 9:
                args = "randomnumber";
                if (TotalZero() == core) {
                    ready_queue.push(9);
                } else {
                    AddZero();
                    pthread_t thread_9;
                    pthread_create(&thread_9, NULL, runCommands, &args);
                    pthread_join(thread_9, NULL);
                }
                break;
            case 10:
                args = "tictac";
                if (TotalZero() == core) {
                    ready_queue.push(10);
                } else {
                    AddZero();
                    pthread_t thread_10;
                    pthread_create(&thread_10, NULL, runCommands, &args);
                    pthread_join(thread_10, NULL);
                }
                break;
            case 11:
                args = "timer";
                if (TotalZero() == core) {
                    ready_queue.push(11);
                } else {
                    AddZero();
                    pthread_t thread_11;
                    pthread_create(&thread_11, NULL, runCommands, &args);
                    pthread_join(thread_11, NULL);
                }
                break;
            case 12:
                args = "watch";
                if (TotalZero() == core) {
                    ready_queue.push(13);
                } else {
                    AddZero();
                    pthread_t thread_13;
                    pthread_create(&thread_13, NULL, runCommands, &args);
                    pthread_join(thread_13, NULL);
                }
                break;
            default:
                cerr << "Invalid task number." << endl;
                break;
        }
        if (choice_flag == 'y' && ready_queue.empty() && choice_flag_inner == 'n') { // flag to check if user does not want to perform another task
            cout << "Do you want to perform another task? (y/n) ";
            cin >> choice;
        }
        choice_flag_inner = 'n';
        if (choice == 'n') {  // condition to check user does not want to perform another task
            choice_flag = 'n';
            if (!ready_queue.empty()) { // condition to check if queue is empty or not
                choice = 'y';
                continue;
            }
            if (ready_queue.empty()) { // condition to check if queue is empty or not
                choice = 'n';
            }
        }
    }
    ClearFile();
    cout << "Exiting";
    for (int i = 0; i < 5; i++) {
        cout << ".";
        cout.flush();
        this_thread::sleep_for(chrono::seconds(1));
    }
    cout << endl;

    // Kill all child processes' terminals
    killTerminals();

    return 0;
}

