#ifndef SRC_S21_MATRIX_H_
#define SRC_S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define SUCCESS 1
#define FAILURE 0
#define EPS 1E-7

typedef struct matrix_struct {
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns, matrix_t *result);
void s21_remove_matrix(matrix_t *A);
int s21_matrix(matrix_t *A);  // доп. функция условия существования матрицы
int s21_rows_columns_matrix(
    matrix_t *A,
    matrix_t *B);  // доп. функция условия равенства строк и столбцов матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B);
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_mult_number(matrix_t *A, double number, matrix_t *result);
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result);
int s21_transpose(matrix_t *A, matrix_t *result);
matrix_t s21_matrix_for_minor(matrix_t A, int row,
                              int column);  // матрица минора
int s21_row_column_matrix(matrix_t *A);  // доп. функция условия равенства
                                         // строк и столбцов матрицы
int s21_determinant(matrix_t *A, double *result);
int s21_calc_complements(matrix_t *A, matrix_t *result);
int s21_inverse_matrix(matrix_t *A, matrix_t *result);
void s21_fill_matrix(matrix_t *result, double num);
void s21_anti_fill_matrix(matrix_t *result, double num);

#endif  // SRC_S21_MATRIX_H_