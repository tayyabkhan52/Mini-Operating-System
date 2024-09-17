#include <iostream>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <signal.h>

using namespace std;

struct interrupt {
    int minimize = -1, close = -1, in_out_put = -1;
    int process_choice = -1;
};

void close_terminal() {
    std::system("pkill -f gnome-terminal ");
}

int main() {
    int value = -1;
    int process_choice = 5, terminate_signal = 1, yet_to_read = 1;
    char terminate = 'n';
    char op;
    float num1, num2;
    while (terminate == 'n') {
        cout << "enter y to terminate the process n to again" << endl;
        cout << "Enter operator (+, -, *, /): ";
        cin >> op;
        cout << "Enter two numbers: ";
        cin >> num1 >> num2;

        switch (op) {
            case '+':
                cout << num1 << " + " << num2 << " = " << num1 + num2 << endl;
                break;

            case '-':
                cout << num1 << " - " << num2 << " = " << num1 - num2 << endl;
                break;

            case '*':
                cout << num1 << " * " << num2 << " = " << num1 * num2 << endl;
                break;

            case '/':
                if (num2 == 0) {
                    cout << "Error: division by zero." << endl;
                } else {
                    cout << num1 << " / " << num2 << " = " << num1 / num2 << endl;
                }
                break;

            default:
                cout << "Error: invalid operator." << endl;
                break;
        }

        std::ifstream in("shutdown.txt");
        in >> value;
        in.close();
        if (value >= 0) {
            value++;
            std::ofstream o("shutdown.txt");
            o << value << endl;
            o.close();
            close_terminal();
        }

        cout << "want to terminate the program?";
        cin >> terminate;
    }

    std::ofstream outfile("IPC.txt");
    char a = ',';
    outfile << yet_to_read << a << terminate_signal << a << process_choice << endl;
    outfile.close();

    return 0;
}

