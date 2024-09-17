#include <iostream>
#include <fstream>
#include <pthread.h>

using namespace std;

char square[10] = {'o','1','2','3','4','5','6','7','8','9'};

int checkwin() {
    if (square[1] == square[2] && square[2] == square[3])
        return 1;
    else if (square[4] == square[5] && square[5] == square[6])
        return 1;
    else if (square[7] == square[8] && square[8] == square[9])
        return 1;
    else if (square[1] == square[4] && square[4] == square[7])
        return 1;
    else if (square[2] == square[5] && square[5] == square[8])
        return 1;
    else if (square[3] == square[6] && square[6] == square[9])
        return 1;
    else if (square[1] == square[5] && square[5] == square[9])
        return 1;
    else if (square[3] == square[5] && square[5] == square[7])
        return 1;
    else if (square[1] != '1' && square[2] != '2' && square[3] != '3' 
             && square[4] != '4' && square[5] != '5' && square[6] != '6' 
             && square[7] != '7' && square[8] != '8' && square[9] != '9')
        return 0;
    else
        return -1;
}

void board() {
    system("clear");
    cout << "===============================================================\n";
    cout << "                     TIC TAC TOE                               \n";
    cout << "===============================================================\n";
    cout << "Player 1 (X)  -  Player 2 (O)" << endl << endl;
    cout << endl;
    cout << "     |     |     " << endl;
    cout << "  " << square[1] << "  |  " << square[2] << "  |  " << square[3] << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << square[4] << "  |  " << square[5] << "  |  " << square[6] << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << square[7] << "  |  " << square[8] << "  |  " << square[9] << endl;
    cout << "     |     |     " << endl << endl;
}

void tic() {
    int player = 1, i, choice;
    char mark;
    
    do {
        board();
        player = (player % 2) ? 1 : 2;

        cout << "Player " << player << ", enter a number:  ";
        cin >> choice;

        mark = (player == 1) ? 'X' : 'O';

        if (choice == 1 && square[1] == '1')
            square[1] = mark;
        else if (choice == 2 && square[2] == '2')
            square[2] = mark;
        else if (choice == 3 && square[3] == '3')
            square[3] = mark;
        else if (choice == 4 && square[4] == '4')
            square[4] = mark;
        else if (choice == 5 && square[5] == '5')
            square[5] = mark;
        else if (choice == 6 && square[6] == '6')
            square[6] = mark;
        else if (choice == 7 && square[7] == '7')
            square[7] = mark;
        else if (choice == 8 && square[8] == '8')
            square[8] = mark;
        else if (choice == 9 && square[9] == '9')
            square[9] = mark;
        else {
            cout << "Invalid move ";
            player--;
            cin.ignore();
            cin.get();
        }

        i = checkwin();
        player++;
    } while (i == -1);

    board();

    if (i == 1)
        cout << "==> Player " << --player << " wins!" << endl;
    else
        cout << "==> Game draw!" << endl;

    cin.ignore();
    cin.get();
}

int main() {
    int process_choice = 14, terminate_signal = 1, yet_to_read = 1;
    char terminate = 'n';

    while (terminate != 'y') {
        tic();
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

