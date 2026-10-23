#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <complex>
#include <ctime>
using namespace std;

using Complex=complex<double>;
class Matrix {
public:
    int rows;
    int cols;
    vector<vector<Complex>> data;

    Matrix(int rows_, int cols_) {
        rows = rows_;
        cols = cols_;
        data.resize(rows, vector<Complex>(cols, Complex(0.0,0.0)));
    }

    void display() const {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    void setValue(int row, int col, Complex value) {
        data[row - 1][col - 1] = value;
    }

    void randomise() {
        srand(static_cast<unsigned int>(time(nullptr)));

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                data[i][j] = (rand() % 19) - 9;
            }
        }
    }

    Matrix transpose() const {
        Matrix result(cols, rows);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[j][i] = data[i][j];
            }
        }

        return result;
    }
    
    Matrix mult(Complex n) const {
        Matrix result(rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] * n;
            }
        }

        return result;
    }

    Matrix addToEach(double n) const {
        Matrix result(rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + n;
            }
        }

        return result;
    }

    Matrix operator*(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            cout << "Not conformable!" << endl;
            return Matrix(0, 0);
        }

        Matrix result(rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] * other.data[i][j];
            }
        }

        return result;
    }

    Matrix dotProd(const Matrix& m2) const {
        if (cols != m2.rows) {
            cout << "Not conformable!" << endl;
            return Matrix(0, 0);
        }

        Matrix result(rows, m2.cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < m2.cols; j++) {
                Complex sum = 0.0;

                for (int k = 0; k < cols; k++) {
                    sum += data[i][k] * m2.data[k][j];
                }

                result.data[i][j] = sum;
            }
        }

        return result;
    }

    Matrix operator+(const Matrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            cout << "Not conformable!" << endl;
            return Matrix(0, 0);
        }

        Matrix result(rows, cols);

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }

        return result;
    }

    Matrix tensor(const Matrix& other) const {
        Matrix result(rows * other.rows, cols * other.cols);
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                for (int k = 0; k < other.rows; k++) {
                    for (int l = 0; l < other.cols; l++) {
                        result.data[i * other.rows + k][j * other.cols + l] = data[i][j] * other.data[k][l];
                    }
                }
            }
        }
        return result;
    }

    static Matrix createDiagonalMatrix(int n, double val) {
        Matrix result(n, n);

        for (int i = 0; i < n; i++) {
            result.data[i][i] = val;
        }

        return result;
    }
};