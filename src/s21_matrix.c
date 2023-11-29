#include "s21_matrix.h"

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 0;
  if (rows <= 0 || columns <= 0 || result == NULL) {
    res = 1;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = malloc(rows * sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = malloc(columns * sizeof(double));
    }
  }
  return res;
}

void s21_remove_matrix(matrix_t *A) {
  if (A && A->matrix) {
    for (int i = 0; i < A->rows; i++) {
      free(A->matrix[i]);
    }
    free(A->matrix);
  }
}

int s21_matrix(matrix_t *A) {  // доп. функция условия существования матрицы
  int res = 0;
  if (!A || A->rows <= 0 || A->columns <= 0 || !(A->matrix)) {
    res = 1;
  }
  return res;
}

int s21_rows_columns_matrix(
    matrix_t *A,
    matrix_t *B) {  // доп. функция условия равенства строк и столбцов
  int res = 0;
  if (A->rows == B->rows && A->columns == B->columns) {
    res = 1;
  }
  return res;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = SUCCESS;
  if (s21_matrix(A) || s21_matrix(B)) {
    res = FAILURE;
  } else {
    if (s21_rows_columns_matrix(A, B)) {
      for (int i = 0; i < A->rows && res; i++) {
        for (int j = 0; j < A->columns && res; j++) {
          if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS) {
            res = FAILURE;
          }
        }
      }
    } else {
      res = FAILURE;
    }
  }
  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (!result || s21_matrix(A) || s21_matrix(B)) {
    res = 1;
  } else {
    if (s21_rows_columns_matrix(A, B)) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
        }
      }
    } else {
      res = 2;
    }
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (!result || s21_matrix(A) || s21_matrix(B)) {
    res = 1;
  } else {
    if (s21_rows_columns_matrix(A, B)) {
      s21_create_matrix(A->rows, A->columns, result);
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < B->columns; j++) {
          result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
        }
      }
    } else {
      res = 2;
    }
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = 0;
  if (!result || s21_matrix(A)) {
    res = 1;
  } else {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = number * A->matrix[i][j];
      }
    }
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = 0;
  if (!result || s21_matrix(A) || s21_matrix(B)) {
    res = 1;
  } else if (A->columns != B->rows) {
    res = 2;
  } else {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = 0;
        for (int k = 0; k < A->columns; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (!result || s21_matrix(A)) {
    res = 1;
  } else {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        result->matrix[i][j] = A->matrix[j][i];
      }
    }
  }
  return res;
}

matrix_t s21_matrix_for_minor(matrix_t A, int row, int column) {
  matrix_t res;
  int i_res = 0, j_res = 0;
  s21_create_matrix(A.rows - 1, A.columns - 1, &res);
  for (int i = 0; i < A.rows; i++) {
    if (i == row) {
      continue;
    }
    for (int j = 0; j < A.columns; j++) {
      if (j == column) {
        continue;
      } else {
        res.matrix[i_res][j_res] = A.matrix[i][j];
        j_res++;
      }
    }
    j_res = 0;
    i_res++;
  }
  return res;
}

int s21_row_column_matrix(
    matrix_t *A) {  // доп. функция условия равенства строк и столбцов матрицы
  int res = 0;
  if (A->rows != A->columns) {
    res = 1;
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = 0;
  matrix_t tmp_s21_matrix_for_minor;
  double minor = 0, algeb_compl;
  if (!result || s21_matrix(A)) {
    res = 1;
  } else if (s21_row_column_matrix(A)) {
    res = 2;
  } else {
    if (A->rows == 1) {
      *result = **(A->matrix);
    } else if (A->rows == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[0][1] * A->matrix[1][0];
    } else {
      *result = 0;
      for (int j = 0; j < A->columns; j++) {
        tmp_s21_matrix_for_minor = s21_matrix_for_minor(*A, 0, j);
        s21_determinant(&tmp_s21_matrix_for_minor, &minor);
        s21_remove_matrix(&tmp_s21_matrix_for_minor);
        algeb_compl = pow(-1, 0 + j) * minor;
        *result += A->matrix[0][j] * algeb_compl;
      }
    }
  }
  return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (!result || s21_matrix(A)) {
    res = 1;
  } else if (s21_row_column_matrix(A) || A->rows == 1) {
    res = 2;
  } else {
    matrix_t tmp_s21_matrix_for_minor;
    double algeb_compl, minor = 0;
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        tmp_s21_matrix_for_minor = s21_matrix_for_minor(*A, i, j);
        s21_determinant(&tmp_s21_matrix_for_minor, &minor);
        s21_remove_matrix(&tmp_s21_matrix_for_minor);
        algeb_compl = pow(-1, i + j) * minor;
        result->matrix[i][j] = algeb_compl;
      }
    }
  }
  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = 0;
  double determ = 0;
  matrix_t res_compl, res_transp;
  if (!result || s21_matrix(A)) {
    res = 1;
  } else if (A->rows == 1 || s21_row_column_matrix(A)) {
    res = 2;
  } else {
    s21_determinant(A, &determ);
    if (fabs(determ) < 1E-10) {
      res = 2;
    } else {
      s21_calc_complements(A, &res_compl);
      s21_transpose(&res_compl, &res_transp);
      s21_mult_number(&res_transp, 1 / determ, result);
      s21_remove_matrix(&res_compl);
      s21_remove_matrix(&res_transp);
    }
  }
  return res;
}

void s21_fill_matrix(matrix_t *result, double num) {
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] = num;
      num++;
    }
  }
}

void s21_anti_fill_matrix(matrix_t *result, double num) {
  for (int i = 0; i < result->rows; i++) {
    for (int j = 0; j < result->columns; j++) {
      result->matrix[i][j] = num;
      num--;
    }
  }
}