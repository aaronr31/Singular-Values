#include <iostream>
#include <vector>

using mat = std::vector<std::vector<double> >;
using namespace std;

std::vector<double> singularValues(mat input);

int main()
{
	int rows;
	int columns;

	std::cout << "How many rows are in your matrix?\n";
	std::cin >> rows;
	std::cout << "How many columns are in the matrix?\n";
	std::cin >> columns;
	std::cout << "Enter the matrix: \n";

	mat input(rows);
	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++) {
			double x;
			std::cin >> x;
			input[i].push_back(x);
		}

	vector<double> Values = singularValues(input);
	

	for (int i = 0; i < Values.size(); i++)
		std::cout << "e" << i + 1 << " = " << Values[i] << '\n';

	return 0;
}