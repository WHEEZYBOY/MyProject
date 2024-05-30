#include <iostream>
#include <cstdlib>
#include <ctime>




const int SIZE = 4;

int mesov = 0;

using namespace std;



void initializeBoard(int board[SIZE][SIZE], int size) {
	int num = 1;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			board[i][j] = num++;
		}
	}
	board[size - 1][size - 1] = 0; // пустое пространство 0
}

void shuffleBoard(int board[SIZE][SIZE], int size) {
	srand(time(0));
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			int randRow = rand() % size; //рандомит ряд
			int randCol = rand() % size; // рандомит столбик
			swap(board[i][j], board[randRow][randCol]);
		}
	}
}

void PrintBoard(int board[][SIZE], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << board[i][j] << "\t";
		}
		cout << endl;
	}
	
}

bool isSolved(int board[SIZE][SIZE], int size) {
	int num = 1;
	for (int i = 0; i < size; ++i) {
		for (int j = 0; j < size; ++j) {
			if (board[i][j] != num && !(i == size - 1 && j == size - 1)) {
				return false;
			}
			num++;
		}
	}
	return true;
}

int main() {

	

	setlocale(LC_ALL, "russian");
	
	int size;
	cout << "Выбирите размер поля 3(3x3) или 4(4x4): ";
	cin >> size;

	if (size != 3 && size != 4) {
		cout << "неправильный размер. Пожалуйста выбирите верный 3(3x3) или 4(4x4) ." << endl;
		return 1;
	}

	int board[SIZE][SIZE];
	initializeBoard(board, size);
	shuffleBoard(board, size);

	cout << "Добро пожаловать в мою игру! Выбирите число возле \"0\"" << endl;
	PrintBoard(board, size);

	clock_t startTime = clock();

	while (!isSolved(board, size)) {
		int move;
		cout << "Введите число которое хотите переместить (0 выход): ";
		cin >> move;

		if (move == 0) {
			cout << "байбай!" << endl;
			return 0;
		}

		// положение числа для перемещения
		int row, col;
		bool found = false;
		for (int i = 0; i < size; ++i) {
			for (int j = 0; j < size; ++j) {
				if (board[i][j] == move) {
					row = i;
					col = j;
					found = true;
					break;
				}
			}
			if (found) {
				break;
			}
		}

		// действителен ли ход
		if (row > 0 && board[row - 1][col] == 0) { // вверх
			swap(board[row][col], board[row - 1][col]);
			mesov++;
		}
		else if (row < size - 1 && board[row + 1][col] == 0) { // вниз
			swap(board[row][col], board[row + 1][col]);
			mesov++;
		}
		else if (col > 0 && board[row][col - 1] == 0) { // лево
			swap(board[row][col], board[row][col - 1]);
			mesov++;
		}
		else if (col < size - 1 && board[row][col + 1] == 0) { // право						
			swap(board[row][col], board[row][col + 1]);
			mesov++;
		}
		else {
			cout << "Ошибка выбирите другое число." << endl;
		}

		
		PrintBoard(board, size);
		
	}

	clock_t endTime = clock();
	double timeSpent = (double)(endTime - startTime) / CLOCKS_PER_SEC;
	cout << "Время, потраченное на сбор пятнашек: " << timeSpent << " секунд" << endl;
	cout << "Количество перестановок:" << mesov << endl;

	cout << "Поздравляю! Ты прошел игру. Пока!" << endl;

	return 0;
}
