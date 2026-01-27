#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

typedef vector<vector<int>> Matrix;

Matrix multiplyStrassen(Matrix mat1, Matrix mat2);
Matrix add(Matrix a, Matrix b, int size, int sign = 1);
Matrix resizeMatrix(Matrix &mat, int newR, int newC);
Matrix multiply(Matrix &mat1, Matrix &mat2);

int main()
{
    int a, b, c, d;

    cin >> a >> b >> c >> d;

    if (b != c)
    {
        cout << "IMPOSSIBLE" << endl;
        return 0;
    }

    Matrix mat1(a,vector<int>(b));
    Matrix mat2(c,vector<int>(b));

    return 0;
}

Matrix multiply(Matrix &mat1, Matrix &mat2)
{
    // Compute size of the smallest power of 2 >= max(n, m, q)
    int n = mat1.size(), m = mat1[0].size(), q = mat2[0].size();
    int size = pow(2, ceil(log2(max(n, max(m, q)))));

    // Pad both matrices to size×size with zeros
    Matrix aPad = resizeMatrix(mat1, size, size);
    Matrix bPad = resizeMatrix(mat2, size, size);

    // Perform Strassen multiplication on padded matrices
    Matrix cPad = multiplyStrassen(aPad, bPad);

    // Extract the valid n×q result from the padded result
    Matrix C(n, vector<int>(q));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < q; j++)
            C[i][j] = cPad[i][j];

    return C ;
}

Matrix resizeMatrix(Matrix &mat, int newR, int newC)
{
                                            
    Matrix resized(newR, vector<int>(newC, 0));
    for (int i = 0; i < mat.size(); ++i)
        for (int j = 0; j < mat[0].size(); ++j)
            resized[i][j] = mat[i][j];
            
    return resized;
}

Matrix multiplyStrassen(Matrix mat1, Matrix mat2)
{
    int n = mat1.size();
    Matrix ans(n, vector<int>(n,0));

    //base case 1x1 matrix
    if (n == 1)
    {
        ans[0][0] = (mat1[0][0] * mat2[0][0]); 
        return ans;
    }

    //split into 4 matrix
    int newSize = n / 2;
    Matrix a11(newSize, vector<int>(newSize));
    Matrix a12(newSize, vector<int>(newSize));
    Matrix a21(newSize, vector<int>(newSize));
    Matrix a22(newSize, vector<int>(newSize));
    Matrix b11(newSize, vector<int>(newSize));
    Matrix b12(newSize, vector<int>(newSize));
    Matrix b21(newSize, vector<int>(newSize));
    Matrix b22(newSize, vector<int>(newSize));

    //fill matrix
    for (int i = 0; i < newSize; i++)
    {
        for (int j = 0; j < newSize; j++)
        {
            a11[i][j] = mat1[i][j];
            a12[i][j] = mat1[i][j + newSize];
            a21[i][j] = mat1[i + newSize][j];
            a22[i][j] = mat1[i + newSize][j + newSize];
            b11[i][j] = mat2[i][j];
            b12[i][j] = mat2[i][j + newSize];
            b21[i][j] = mat2[i + newSize][j];
            b22[i][j] = mat2[i + newSize][j + newSize];
        }
    }

    // Compute the 7 products using Strassen’s formulas
    Matrix m1 = multiplyStrassen(add(a11, a22, newSize), add(b11, b22, newSize));
    Matrix m2 = multiplyStrassen(add(a21, a22, newSize), b11);
    Matrix m3 = multiplyStrassen(a11, add(b12, b22, newSize, -1));
    Matrix m4 = multiplyStrassen(a22, add(b21, b11, newSize, -1));
    Matrix m5 = multiplyStrassen(add(a11, a12, newSize), b22);
    Matrix m6 = multiplyStrassen(add(a21, a11, newSize, -1), add(b11, b12, newSize));
    Matrix m7 = multiplyStrassen(add(a12, a22, newSize, -1), add(b21, b22, newSize));

    // Calculate result quadrants from m1...m7
    Matrix c11 = add(add(m1, m4, newSize), add(m7, m5, newSize, -1), newSize);
    Matrix c12 = add(m3, m5, newSize);
    Matrix c21 = add(m2, m4, newSize);
    Matrix c22 = add(add(m1, m3, newSize), add(m6, m2, newSize, -1), newSize);

    // Combine result quadrants into final matrix
    for (int i = 0; i < newSize; i++)
        for (int j = 0; j < newSize; j++) {
            ans[i][j] = c11[i][j];
            ans[i][j + newSize] = c12[i][j];
            ans[i + newSize][j] = c21[i][j];
            ans[i + newSize][j + newSize] = c22[i][j];
        }

    return ans;
}

Matrix add(Matrix a, Matrix b, int size, int sign = 1)
{
    Matrix ans(size, vector<int>(size));
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            ans[i][j] = a[i][j] + sign * b[i][j];
    return ans;
}
