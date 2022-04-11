//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MATRIX_H
#define MATRIX_H

// includes
#include "Enum.h"

// forward declare
class Vect4D;

// class
class Matrix
{
public:
	friend class ParticleEmitter;

	// local enumerations
	enum MatrixRowEnum
	{
		MATRIX_ROW_0,
		MATRIX_ROW_1,
		MATRIX_ROW_2,
		MATRIX_ROW_3
	};

	Matrix();
	Matrix(Matrix& t);
	~Matrix();

	void set(MatrixRowEnum row, Vect4D *t);
	void get(MatrixRowEnum row, Vect4D *vOut);

	void setIdentMatrix();
	void setTransMatrix(Vect4D *t);
	void setScaleMatrix(Vect4D *s);
	void setRotZMatrix(float Z_Radians);

	void SetInverseCameraMatrix();// Used just for inversing camera matrix in main.cpp

	float &operator[](INDEX_ENUM e);

	Matrix operator*(Matrix &t);

	float Determinant();

	Matrix& Matrix::operator/=(float t);

private:

	// ROW 0
	float m0;
	float m1;
	float m2;
	float m3;

	// ROW 1
	float m4;
	float m5;
	float m6;
	float m7;

	// ROW 2
	float m8;
	float m9;
	float m10;
	float m11;

	// ROW 3
	float m12;
	float m13;
	float m14;
	float m15;
};

#endif 

// End of File

