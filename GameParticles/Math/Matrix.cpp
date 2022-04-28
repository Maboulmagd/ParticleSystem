//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <Math.h>
#include <assert.h>

#include "Vect4D.h"
#include "Matrix.h"

Matrix::Matrix() { // constructor for the matrix
	//m0 = 0.0f;
	//m1 = 0.0f;
	//m2 = 0.0f;
	//m3 = 0.0f;
	row_0 = _mm_setzero_ps();

	//m4 = 0.0f;
	//m5 = 0.0f;
	//m6 = 0.0f;
	//m7 = 0.0f;
	row_1 = _mm_setzero_ps();

	//m8 = 0.0f;
	//m9 = 0.0f;
	//m10 = 0.0f;
	//m11 = 0.0f;
	row_2 = _mm_setzero_ps();

	//m12 = 0.0f;
	//m13 = 0.0f;
	//m14 = 0.0f;
	//m15 = 0.0f;
	row_3 = _mm_setzero_ps();
}

void Matrix::setIdentMatrix() { // initialize to the identity matrix
	//m0 = 1.0f;
	//m1 = 0.0f;
	//m2 = 0.0f;
	//m3 = 0.0f;
	row_0 = _mm_set_ps(1.0f, 0.0f, 0.0f, 0.0f);

	//m4 = 0.0f;
	//m5 = 1.0f;
	//m6 = 0.0f;
	//m7 = 0.0f;
	row_1 = _mm_set_ps(0.0f, 1.0f, 0.0f, 0.0f);

	//m8 = 0.0f;
	//m9 = 0.0f;
	//m10 = 1.0f;
	//m11 = 0.0f;
	row_2 = _mm_set_ps(0.0f, 0.0f, 1.0f, 0.0f);

	//m12 = 0.0f;
	//m13 = 0.0f;
	//m14 = 0.0f;
	//m15 = 1.0f;
	row_3 = _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f);
}

void Matrix::get(const MatrixRowEnum row, Vect4D* const t) { // get a row of the matrix
	switch (row)
	{
	case MATRIX_ROW_0:
		t->x = m0;
		t->y = m1;
		t->z = m2;
		t->w = m3;
		break;

	case MATRIX_ROW_1:
		t->x = m4;
		t->y = m5;
		t->z = m6;
		t->w = m7;
		break;

	case MATRIX_ROW_2:
		t->x = m8;
		t->y = m9;
		t->z = m10;
		t->w = m11;
		break;

	case MATRIX_ROW_3:
		t->x = m12;
		t->y = m13;
		t->z = m14;
		t->w = m15;
		break;

	default:
		assert(0);
	}
}

void Matrix::setTransMatrix(const Vect4D* const t) { // set the translation matrix (note: we are row major)
	m0 = 1.0f;
	m1 = 0.0f;
	m2 = 0.0f;
	m3 = 0.0f;

	m4 = 0.0f;
	m5 = 1.0f;
	m6 = 0.0f;
	m7 = 0.0f;

	m8 = 0.0f;
	m9 = 0.0f;
	m10 = 1.0f;
	m11 = 0.0f;

	m12 = t->x;
	m13 = t->y;
	m14 = t->z;
	m15 = 1.0f;
}

void Matrix::SetInverseCameraMatrix() {
	m13 = -10.0f;
	m14 = -15.0f;
}

// End of file