#include <iostream>
#include <cmath>
#include <vector>

using mat = std::vector<std::vector<double> >;

void printMatrix(mat A);
mat multiplyMatrix(mat A, mat B);
mat initMatrix(int size);
mat transposeMatrix(mat A);
mat roundMatrix(mat A);

const int numRuns = 100;

std::vector<double> singularValues(mat input)
{
	int rows;
	int columns;

	mat input_T = transposeMatrix(input);
	input = multiplyMatrix(input, input_T);

	printMatrix(input);
	std::cout << '\n';

	for (int k = 0; k < input.size() - 2; k++)
	{
		//finding the sign of input[k+1][k]
		double sign;
		if (input[k + 1][k] >= 0)
			sign = 1;
		else
			sign = -1;

		//finding alpha for Householder reduction
		double alpha = 0;
		for (int i = k + 1; i < input.size(); i++)
			alpha += input[i][k] * input[i][k];
		alpha = sqrt(alpha) * sign;

		//finding r for Householder reflection
		double r = sqrt(.5 * (alpha * alpha - input[k + 1][k] * alpha));

		//constructing vector v
		std::vector<double> v(input.size());
		for (int i = 0; i <= k; i++)
			v[i] = 0;
		v[k + 1] = (input[k + 1][k] - alpha) / (2 * r);
		for (int i = k + 2; i < input.size(); i++)
			v[i] = input[i][k] / (2 * r);

		//creating identity matrix
		mat I = initMatrix(input.size());
		for (int i = 0; i < input.size(); i++)
			I[i][i] = 1;

		//creation of Householder matrix P = I - 2vv^t
		mat P = initMatrix(input.size());
		for (int i = 0; i < input.size(); i++)
			for (int j = 0; j < input.size(); j++)
				P[i][j] = I[i][j] - 2 * v[i] * v[j];

		//multiplication A[i+1] = P * A[i] * P
		input = multiplyMatrix(P, input);
		input = multiplyMatrix(input, P);

		input = roundMatrix(input);

		printMatrix(input);

		std::cout << '\n';
	}
	mat H = input;
    
    for (int runs = 0; runs < numRuns; runs++)
    {

        //intializing Q transpose to an identity matrix
        mat Qt = initMatrix(H.size());
        for (int i = 0; i < H.size(); i++)
            Qt[i][i] = 1;

        //creating a temporary holder for H so that H is not altered by the Givens rotations
        mat H_temp = initMatrix(H.size());
        H_temp = H;

        //Beginning of the Givens rotations
        for (int l = 0; l < H.size() - 1; l++) {

            double a = H_temp[l + 1][l];                       //defining a and b for Givens rotation
            double b = H_temp[l][l];
            double r = hypot(a, b);                            //defining r for Givens rotation
            double c = b / r;                                  //defining sin and cos for Givens rotation
            double s = -a / r;

            //creating Givens matrix G
            mat G = initMatrix(H.size());
            for (int i = 0; i < H.size(); i++)
                G[i][i] = 1;
            G[l][l] = c;
            G[l + 1][l] = s;
            G[l][l + 1] = -s;
            G[l + 1][l + 1] = c;

            Qt = multiplyMatrix(G, Qt);

            H_temp = multiplyMatrix(G, H_temp);
        }
        //at this point, H has been upper triangularized through a series of Givens rotations        
        
        mat Q = transposeMatrix(Qt);

        //performing multiplication H(i+1) = Qt * H * Q
        H = multiplyMatrix(Qt, H);
        H = multiplyMatrix(H, Q);

        //rounding down small elements of H
        for (int i = 0; i < H.size(); i++)
            for (int j = 0; j < H.size(); j++)
                if (abs(H[i][j]) < 10E-5)
                    H[i][j] = 0;

        
    }

	std::vector<double> result;
	for (int i = 0; i < H.size(); i++)
		result.push_back(sqrt(H[i][i]));

	return result;
}

