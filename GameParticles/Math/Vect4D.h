//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

// This is a 4 dimensional Vect4D class
#ifndef Vect4D_H
#define Vect4D_H

// includes
#include "Enum.h"
#include "Align16.h"

// Foward Declarations
class Matrix;

// class
class __declspec(align(16)) Vect4D final : public Align16 {
public:
	friend class ParticleEmitter;
	friend class Matrix;

	explicit Vect4D();
	explicit Vect4D(float tx, float ty, float tz, float tw = 1.0f);
	~Vect4D();

	void norm(Vect4D &out);
	void set(float tx, float ty, float tz, float tw = 1.0f);

	Vect4D operator + (Vect4D t);
	Vect4D operator - (Vect4D t);
	Vect4D operator * (float scale);

	void operator *= (const float scale);
	void operator += (const Vect4D& t);

	void Cross(Vect4D &vin, Vect4D &vout);

	float &operator[](VECT_ENUM e);

private:

	// anonymous union
	union {
		__m128 row;

		// anonymous struct
		struct {
			float x;
			float y;
			float z;
			float w;
		};
	};
};

#endif  

// End of file

