//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef MATRIX_H
#define MATRIX_H

// includes
#include "Enum.h"
#include "Align16.h"

// forward declare
class Vect4D;

// class
class __declspec(align(16)) Matrix final : public Align16 {
public:
	friend class ParticleEmitter;

	// local enumerations
	enum MatrixRowEnum {
		MATRIX_ROW_0,
		MATRIX_ROW_1,
		MATRIX_ROW_2,
		MATRIX_ROW_3
	};

	explicit Matrix();
	~Matrix() = default;

	void get(const MatrixRowEnum row, Vect4D* const vOut);

	void setIdentMatrix();
	void setTransMatrix(const Vect4D* const t);

	void SetInverseCameraMatrix();// Used just for inversing camera matrix in main.cpp

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

