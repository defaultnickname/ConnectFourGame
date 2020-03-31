#include <iostream>
#include <vector>
#include<stdio.h>
#include<conio.h>
#include <algorithm>

/* Created as term project 2020
Created by : 
https://github.com/defaultnickname
https://github.com/MacBono
Command line game
*/

using namespace std;

class plansza {
public:
	vector<vector<int>> mat;
	bool prevMove;  //0 for player A   ......  1 for player B;
	int A_wins, B_wins;
	char A_sign, B_sign;
	int width, height;

	plansza(int width = 7, int height = 6 ,int A_wins=0,int B_wins=0, bool prevMove = 0, char A_sign = 'A', char B_sign = 'B')
		:width(width), height(height),A_wins(A_wins),B_wins(B_wins), prevMove(prevMove), A_sign(A_sign), B_sign(B_sign)
	{
		mat.resize(width, vector<int>(height, 0));
	}

	~plansza() {}

	void A_add() {
		int col;
		do {
			cout << "[Team A]Please select column from 1 to 7 : ";
			cin >> col;
		} while (col < 1 || col>7);
		int p = 0;
		col--;
		for (size_t i = 0; i < mat[col].size(); i++) {
			if (mat[col][i] != 0) {
				p++;
				continue;
			};
		}
	
		if (p != mat[col].size()) {
			mat[col][p] = 1;
			prevMove = 0;
		}
		else {
			A_add();
		}
		
		
	}
	//mat[j][i]  => mat[col][row] => mat[w][h]

	void B_add() {
		int col;
		do {
			cout << "[Team B]Please select column from 1 to 7 : ";
			cin >> col;
		 } while (col < 1 || col>7);
		int p = 0;
		col--;
		for (size_t i = 0; i < mat[col].size(); i++) {
			if (mat[col][i] != 0) {
				p++;
				continue;
			};
		}

		if (p != mat[col].size()) {
			mat[col][p] = 2;
			prevMove = 1;
		}
		else {
			B_add();
		}
		

	}

	void symbolChoosing() {
		cout << "Team A: Choose your symbol" << endl;
		cin >> A_sign;
		cout << "Team B: Choose your symbol" << endl;
		cin >> B_sign;
	}


	void printPlansza() {
		cout<<"AWINS:"<<A_wins<<"     "<<"BWINS:"<<B_wins<<endl;
		cout << "--------------------------" << endl;
		for (int i = height-1; i >= 0; i--) {
			for (int j = 0; j < width; j++) {
				if (mat[j][i] != 0) {
					if (mat[j][i] == 1) {
						cout << A_sign << "   ";
					}
					else if (mat[j][i] == 2) {
						cout << B_sign << "   ";
					}
				}
				else cout << " " << "   ";
			}
			cout << endl;
		}
		cout << "--------------------------" << endl;
	}
	//REMAINDER: EVERY COLUMN IS SEPARATE VECTOR
	

	bool checkPattern(bool prevMove, vector<int> mat) {
		vector<int> D;
		if (prevMove) {
			D = { 2,2,2,2 };
		}
		else {
			D = { 1,1,1,1 };
		}

		auto res_ = search(begin(mat), end(mat), begin(D), end(D)); //Check vertical
		if (res_ == end(mat))
		{
			return 0;
		}
		else
		{
			if (prevMove) {
				B_wins++;
				return 1;
			}
			else {
				A_wins++;
				return 1;
			}

			std::cout << "Found it\n"; //znalaz³em
		}

	}

	bool checkWin() {
		vector<int> a, b, c;
		int k_, r_;
		int k_copy, r_copy;


		for (int j = 0; j < height; j++) {

			for (int i = 0; i < width; i++) {//KA¯DA KOLUMNA TO WEKTOR W KTÓRYM SZUKAMY PATTERNU

				if (checkPattern(prevMove, mat[i])) {

					return 1;
				}

				b.push_back(mat[i][j]);

			}
			if (checkPattern(prevMove, b)) {

				return 1;
			}
			b.clear();

		}


		for (int r = 0; r < height - 1; r++) {
			k_ = 0;
			r_copy = r;
			while (r_copy >= 0 && k_ < width) {
				a.push_back(mat[k_][r_copy]);
				k_++;
				r_copy--;
			}
			if (a.size() >= 4) {
				if (checkPattern(prevMove, a)) {

					return 1;
				}
			}
			a.clear();
		}
		for (int k = 1; k <= width - 1; k++) {
			r_ = height - 1;
			k_copy = k;
			while (k_copy < width - 1 && r_ >= 0) {
				a.push_back(mat[r_][k_copy]);
				r_--;
				k_copy++;
			}
			if (a.size() >= 4) {
				if (checkPattern(prevMove, a)) {

					return 1;
				}
			}
			a.clear();
		}

		for (int r = 0; r < height - 1; r++) {
			k_ = width - 1;
			r_copy = r;
			while (r_copy >= 0 && k_ >= 0) {
				a.push_back(mat[k_][r_copy]);
				k_--;
				r_copy--;
			}
			if (a.size() >= 4) {
				if (checkPattern(prevMove, a)) {

					return 1;
				}
			}
			a.clear();
		}
		for (int k = width - 2; k >= 0; k--) {
			r_ = height - 1;
			k_copy = k;
			while (k_copy >= 0 && r_ >= 0) {
				a.push_back(mat[r_][k_copy]);
				r_--;
				k_copy--;
			}
			if (a.size() >= 4) {
				if (checkPattern(prevMove, a)) {

					return 1;
				}
			}
			b.clear();
		}
		return 0;
	};// checkiwn()
};


//REMAINDER
	//mat[j][i]  => mat[col][row] => mat[w][h]


	
	void clear() {

		std::cout << "\x1B[2J\x1B[H";
	}

	int main() {
		plansza mat;
		mat.symbolChoosing();
		clear();
		while (1) {
			
			mat.printPlansza();
			mat.A_add();
			clear();
			
			if (mat.checkWin()) {
				mat = plansza(mat.width, mat.height, mat.A_wins, mat.B_wins, 0,mat.A_sign,mat.B_sign);
			}
			cout << endl;
			mat.printPlansza();
			mat.B_add();
			clear();
			
			if (mat.checkWin()) {

				mat = plansza(mat.width,mat.height,mat.A_wins,mat.B_wins,0, mat.A_sign, mat.B_sign);
			}
			cout << endl;
			
			
			
		};
	}