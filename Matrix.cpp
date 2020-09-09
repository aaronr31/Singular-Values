#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

using mat = vector<vector<double> >;

mat multiplyMatrix(mat A, mat B)
{
    mat product(A.size());
    for (int i = 0; i < A[0].size(); i++)
        product[i] = vector<double>(A.size());

    for (int i = 0; i < A.size(); i++)
        for (int j = 0; j < B[0].size(); j++)
            for (int k = 0; k < A.size(); k++)
                product[i][j] += A[i][k] * B[k][j];

    return product;
}

void printMatrix(mat A)
{
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A.size(); j++)
        {
            cout << A[i][j] << '\t';
        }
        cout << '\n';
    }
}

mat initMatrix(int size)
{
    mat A(size);
    for (int i = 0; i < size; i++)
        A[i] = vector<double>(size);

    return A;
}

mat transposeMatrix(mat A)
{
    mat At(A.size());
    for (int i = 0; i < A.size(); i++)
        At[i] = vector<double>(A.size());

    for (int i = 0; i < A.size(); i++)
        for (int j = 0; j < A.size(); j++)
            At[i][j] = A[j][i];

    return At;
}

mat roundMatrix(mat A)
{
    for (int i = 0; i < A.size(); i++)
        for (int j = 0; j < A.size(); j++)
            if (abs(A[i][j]) < 0.0001)
                A[i][j] = 0;
    return A;
}