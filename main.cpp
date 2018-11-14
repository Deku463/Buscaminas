#include <iostream>
#include <ctime>

using namespace std;

const int maxSize = 30;

void printBoard(char board[][maxSize], int bSize){
    cout <<"    " ;
    for(int i = 0; i < bSize; i++){
        cout << i << "   ";
    }
    cout << endl << endl;
    for(int i = 0; i < bSize; i++){
        cout << i << "   ";
        for(int j = 0; j < bSize; j++){
            cout << board[i][j] << "   ";
        }
        cout << endl << endl;
    }
}

void setUpBoard(char board[][maxSize], char revealedBoard[][maxSize], int bSize, int nMinas){
    for(int i = 0; i < bSize; i++){
        for(int j = 0; j < bSize; j++){
            board[i][j] = '+';
            revealedBoard[i][j] = '0';
        }
    }
    srand(time(NULL));
    int min = 0;
    int max = bSize;
    int x,y;
    for(int i = 0; i < nMinas; i++){
        do{
            x = rand() % max;
            y = rand() % max;
        }while(revealedBoard[y][x] == 'm');
        revealedBoard[y][x] = 'm';
        if(y != 0){
            if(revealedBoard[y-1][x] != 'm'){
                revealedBoard[y-1][x]++;
            }
            if(x > 0 && revealedBoard[y-1][x-1] != 'm'){
                revealedBoard[y-1][x-1]++;
            }
            if(x < bSize-1 && revealedBoard[y-1][x+1] != 'm'){
                revealedBoard[y-1][x+1]++;
            }
        }
        if(y != bSize-1){
            if(revealedBoard[y+1][x] != 'm'){
                revealedBoard[y+1][x]++;
            }
            if(x > 0 && revealedBoard[y+1][x-1] != 'm'){
                revealedBoard[y+1][x-1]++;
            }
            if(x < bSize-1 && revealedBoard[y+1][x+1] != 'm'){
                revealedBoard[y+1][x+1]++;
            }
        }
        if(x != 0 && revealedBoard[y][x-1] != 'm'){
            revealedBoard[y][x-1]++;
        }
        if(x != bSize-1 && revealedBoard[y][x+1] != 'm'){
            revealedBoard[y][x+1]++;
        }

    }
}

void updateBoard(char board[][maxSize], char revealedBoard[][maxSize], int x, int y, int bSize, int& nDescubiertas){
    if(board[y][x] == '+' && revealedBoard[y][x] != 'm'){
        board[y][x] = revealedBoard[y][x];
        nDescubiertas++;
        if (board[y][x] == '0'){
            if(y > 0){
                updateBoard(board, revealedBoard, x, y-1, bSize, nDescubiertas);
            }
            if(y < bSize-1){
                updateBoard(board, revealedBoard, x, y+1, bSize, nDescubiertas);
            }
            if(x > 0){
                updateBoard(board, revealedBoard, x-1, y, bSize, nDescubiertas);
            }
            if(x < bSize-1){
                updateBoard(board, revealedBoard, x+1, y, bSize, nDescubiertas);
            }
        }
    }
}

void playGame(char board[][maxSize], char revealedBoard[][maxSize], int bSize, int nMinas){
    int x,y;
    int nDescubiertas = 0;
    setUpBoard(board, revealedBoard, bSize, nMinas);
    while(true){
        if(nDescubiertas == (bSize*bSize)-nMinas){
            printBoard(revealedBoard, bSize);
            cout << "\n Victoria!!! \n" << endl;
            break;
        }
        printBoard(board, bSize);
        cout << "Ingrese una jugada o -1 para salir: ";
        cin >> x;
        if(x == -1){
            cout << "Saliendo...\n" << endl;
            break;
        }
        else{
            cin >> y;
        }
        if(x < 0 || y < 0 || x > bSize-1 || y > bSize-1){
            cout << "\nJugada invalida.\n" << endl;
        }
        else if(revealedBoard[y][x] == 'm'){
            revealedBoard[y][x] = 'M';
            printBoard(revealedBoard, bSize);
            cout << "\n Oops!!! \n" << endl;
            break;
        }
        else{
            updateBoard(board, revealedBoard, x, y, bSize, nDescubiertas);
            cout << endl;
        }
    }
}

int main(){
    char board[maxSize][maxSize];
    char revealedBoard[maxSize][maxSize];
    int bSize;
    int nMinas;
    int opcion;
    while(true){
        cout << "--Buscaminas--\n" << endl;
        cout << "1. Nuevo juego\n2. Salir" << endl;
        cout << "Elige una opcion: ";
        cin >> opcion;
        if(opcion == 1){
            cout << "\nIngresa el tamano del tablero: ";
            cin >> bSize;
            cout << "Ingresa el numero de minas: ";
            cin >> nMinas;
            cout << endl;
            playGame(board, revealedBoard, bSize, nMinas);
        }
        else if(opcion == 2){
            break;
        }
        else{
            cout << "\nOpcion invalida.\n" << endl;
        }
    }
}
