#include <bits/stdc++.h>
using namespace std;

void print(vector<vector < int>> &sudoku)
{
	cout << "Below is the solved Sudoku\n";
	int N = sudoku.size();
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
			cout << sudoku[i][j] << " ";
		cout << '\n';
	}
}

bool isSafe(vector<vector < int>> &sudoku, int x, int y, int val)
{
	int N = sudoku.size();
	for (int i = 0; i < N; i++)
	{
		if (sudoku[x][i] == val || sudoku[i][y] == val)
			return false;
	}

	N = sqrt(N);
	int a = x - x % N, b = y - y % N, cnt = 0;
	for (int i = a; i < a + N; i++)
	{
		for (int j = b; j < b + N; j++)
		{
			if (i == x && j == y)
				continue;
			else if (sudoku[i][j] == val)
				return false;
		}
	}

	return true;
}

bool solve2(vector<vector < int>> &sudoku, int x, int y)
{
	int N = sudoku.size();
	for (int i = x; i < N; i++)
	{
		int j;
		if (i == x)
			j = y + 1;
		for (j = 0; j < N; j++)
		{
			if (sudoku[i][j] == 0)
			{
				int cnt = 0;
				for (int k = 1; k <= N; k++)
				{
					if (isSafe(sudoku, i, j, k))
					{
						sudoku[i][j] = k;
						if (!solve2(sudoku, i, j))
							sudoku[i][j] = 0;
						else
						{
							cnt = 1;
							break;
						}
					}
				}

				if (cnt == 0)
					return false;
			}
		}
	}

	return true;
}

bool solve(vector<vector < int>> &sudoku)
{
	int N = sudoku.size();
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			if (sudoku[i][j] == 0)
			{
				int cnt = 0;
				for (int k = 1; k <= N; k++)
				{
					if (isSafe(sudoku, i, j, k))
					{
						sudoku[i][j] = k;
						if (!solve2(sudoku, i, j))
							sudoku[i][j] = 0;
						else
						{
							cnt = 1;
							break;
						}
					}
				}

				if (cnt == 0)
					return false;
			}
		}
	}

	return true;
}

bool isPerfectSquare(int n)
{
	int d = sqrt(n);
	return ((d *d) == n);
}

int main()
{
	cout << "Enter the size of Sudoku\n";
	int N;
	cin >> N;
	vector<vector < int>> sudoku;
	if (!isPerfectSquare(N))
		cout << "Invalid Size - It has to be a perfect square\n";
	else
	{
		cout << "Enter the Sudoku with each entry separated by a space\nMake sure each entry is in[0," << N << "] range where the empty entries are 0\n";
		int k = 0;
		for (int i = 0; i < N; i++)
		{
			vector<int> temp;
			for (int j = 0; j < N; j++)
			{
				int val;
				cin >> val;
				temp.push_back(val);
				if (val < 0 || val > N *N)
				{
					k = 1;
					break;
				}
			}

			if (k == 1)
				break;
			sudoku.push_back(temp);
		}

		if (k == 1)
			cout << "Invalid Entry\n";
		else
		{
			if (solve(sudoku))
				print(sudoku);
			else
				cout << "No Solution Exists\n";
		}
	}
}