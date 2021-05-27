#include<iostream>
#include<string>
#include<fstream>
using namespace std;

#define size 9

bool checkingZero(int board_[size][size]) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (board_[i][j] == 0) {
				return true;
			}
		}
	}
	return false;
}

void display(int board_[size][size]) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << board_[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

bool checkingRow(int board_[size][size], int row_, int num) {
	for (int i = 0; i < size; i++) {
		if (board_[row_][i] == num) {
			return false;
		}
	}
	return true;
}

bool checkingCol(int board_[size][size], int col_, int num) {
	for (int i = 0; i < size; i++) {
		if (board_[i][col_] == num) {
			return false;
		}
	}
	return true;
}

bool checkingBox(int board_[size][size], int row_, int col_, int num) {
	int boxRow = (row_ / 3) * 3;
	int boxCol = (col_ / 3) * 3;
	for (int i = boxRow; i < boxRow + 3; i++) {
		for (int j = boxCol; j < boxCol + 3; j++) {
			if (board_[i][j] == num) {
				return false;
			}
		}
	}
	return true;
}

bool sudoku(int board_[size][size]) {
	if (checkingZero(board_) == false) {
		display(board_);
		ofstream outputFile;
		outputFile.open("sudokuOutput1.txt");
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				outputFile << board_[i][j];
				outputFile << " ";
			}
			outputFile << "\n";
		}
		outputFile.close();
		return true;
	}
	int currentRow, currentCol;
	bool find = false;
	for (int i = 0; i < size && !find; i++) {
		for (int j = 0; j < size && !find; j++) {
			if (board_[i][j] == 0 && find == false) {
				currentRow = i;
				currentCol = j;
				find = true;
			}
		}
	}
	for (int k = 1; k <= 9; k++) {
		if (checkingRow(board_, currentRow, k) &&
			checkingCol(board_, currentCol, k) &&
			checkingBox(board_, currentRow, currentCol, k)) {
			board_[currentRow][currentCol] = k;
			//backtracking search
			//kalau number yang diambil tidak menyelesaikan ambil nomor lain
			if (sudoku(board_)) {
				return true;
			}
			//set kembali ke 0 kalau number yang diambil salah
			board_[currentRow][currentCol] = 0;
		}
	}
	return false;
}

void main() {
	//declare the size of sudoku
	string fileName;
	cout << "Masukkan nama file : ";
	cin >> fileName;
	ifstream file;
	file.open(fileName);
	if (file.is_open()) {
		cout << "Berhasil" << endl;
		int board[size][size];
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				file >> board[i][j];
			}
		}
		display(board);
		file.close();
		if (sudoku(board)) {
			cout << "Berhasil" << endl;
		}
		else {
			cout << "Gagal" << endl;
		}
	}
	else {
		cout << "File doesn't exist" << endl;
	}
}