% chap5_matrix.m  - Linear Algebra
% COEN 4830 - Computer Graphics
% Fred J. Frigo, Ph.D.
% 15-Sep-2021

A = [ 1, 9, 2; 8, 3, 5; 4, 7, 6]
x = [ 3; 1; 4]

det(A)
A_transpose = transpose(A)
A_inv = A^-1
y = A*x