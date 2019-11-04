#include <iostream>
#include <fstream>
#include <string>
using namespace std;
char choice = 'n';
void printScreen(int grid[9][9]) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			cout << grid[i][j] << " ";
		}
		cout << endl;
	}
}
void printFile(int grid[9][9], ofstream& of) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			of << grid[i][j] << " ";
		}
		of << endl;
	}
}
void readFile(int grid[9][9], ifstream& inf) {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			inf >> grid[i][j];
		}
	}
}
bool checkEmpty(int grid[9][9], int &row, int &col) {
	for (row = 0; row < 9; row++) {
		for (col = 0; col < 9; col++) {
			if (grid[row][col] == 0) {
				return true;
			}
		}
	}
	return false;
}
bool isSafe(int grid[9][9], int row, int col, int num) {
	//Kiem tra hang
	for (int c = 0; c < 9; c++) {
		if (c == col) {
			continue;
		}
		else {
			if (num == grid[row][c]) {
				return false;
			}
		}
	}
	//Kiem tra cot
	for (int r = 0; r < 9; r++) {
		if (r == row) {
			continue;
		}
		else
		{
			if (num == grid[r][col]) {
				return false;
			}
		}
	}
	//Kiem tra o 3x3
	for (int r = 0; r < 3; r++) {
		for (int c = 0; c < 3; c++) {
			if (r == row % 3 && c == col % 3) {
				continue;
			}
			else
			{
				if (num == grid[r + row - row % 3][c + col - col % 3]) {
					return false;
				}
			}
		}
	}
	return true;
}
bool checkPuzzle(int grid[9][9]) {
	int num;
	for (int row = 0; row < 9; row++) {
		for (int col = 0; col < 9; col++) {
			if (grid[row][col] != 0) {
				num = grid[row][col];
				if (isSafe(grid, row, col, num) == false) {
					return false;
				}
			}
		}
	}
	return true;
}
bool solveSudoku(int grid[9][9]) {
	int num, row, col;
	if (!checkEmpty(grid, row, col)) {
		printScreen(grid);
		cout << "do you want another answer? y/n" << endl;
		cin >> choice;
		return true;
	}
	else {
		for (num = 1; num <= 9; num++) {
			if (isSafe(grid, row, col, num)) {
				grid[row][col] = num;
				if (solveSudoku(grid)) {
					if (choice == 'y') {
						choice = 'n';
						grid[row][col] = 0;
						continue;
					}
					return true;
				}
				grid[row][col] = 0;
			}
		}
	}
	return false;
}
void showPuzzle()
{
	cout << "1_de1" << endl;
	cout << "2_de2" << endl;
	cout << "3_de3" << endl;
	cout << "4_de4" << endl;
	cout << "5_de5" << endl;
}
int main()
{
	int grid[9][9];
	ifstream inFile;
	ofstream outFile;
	string fileName;
	showPuzzle();
	cout << "Choose 1 puzzle(input name) : ";
	while (1) {
		cin >> fileName;
		if (fileName == "de1" || fileName == "de2" || fileName == "de3" || fileName == "de4" || fileName == "de5") {
			break;
		}
		cout << "Invalid input. Try again" << endl;
	}
	fileName.append(".txt");
	inFile.open(fileName.c_str());
	outFile.open("result.txt");
	readFile(grid, inFile);
	printScreen(grid);
	cout << "--------------------" << endl;
	if (checkPuzzle(grid) == true) {
		if (solveSudoku(grid) == true) {
			printFile(grid, outFile);
		}
		cout << "Done" << endl;
	}
	else {
		cout << "No solution exists" << endl;
	}
	inFile.close();
	outFile.close();
	system("pause");
	return 0;
}