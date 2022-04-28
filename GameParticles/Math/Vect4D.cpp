//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include <math.h>
#include <assert.h>

#include "Vect4D.h"

Vect4D::Vect4D() : /*x(0.0f), y(0.0f), z(0.0f), w(1.0f) */ row{ _mm_set_ps(0.0f, 0.0f, 0.0f, 1.0f) } {
}

Vect4D::Vect4D(float tx, float ty, float tz, float tw) : /* x(tx), y(ty), z(tz), w(tw)*/ row{ _mm_set_ps(tx, ty, tz, tw) } {
}

Vect4D::~Vect4D() {
	// nothing to delete
}

void Vect4D::norm(Vect4D& out) {
	//const float mag = sqrtf(x * x + y * y + z * z);
	const __m128 squaring = _mm_mul_ps(row, row);
	const __m128 root = _mm_sqrt_ps(squaring);

	//if (0.0f < mag) {
	//	out.x = x / mag;
	//	out.y = y / mag;
	//	out.z = z / mag;
	//	out.w = 1.0f;
	//}
	const __m128 comparison = _mm_cmplt_ps(_mm_setzero_ps(), root);


}

Vect4D Vect4D::operator + (Vect4D t) {
	Vect4D out;

	out.x = x + t.x;
	out.y = y + t.y;
	out.z = z + t.z;

	return out;
}

Vect4D Vect4D::operator - (Vect4D t) {
	Vect4D out;

	out.x = x - t.x;
	out.y = y - t.y;
	out.z = z - t.z;

	return out;
}

Vect4D Vect4D::operator *(float scale) {
	Vect4D tmp;

	tmp.x = x * scale;
	tmp.y = y * scale;
	tmp.z = z * scale;

	return tmp;
}

void Vect4D::operator*=(const float scale) {
	x *= scale;
	y *= scale;
	z *= scale;
}

void Vect4D::operator+=(const Vect4D& t) {
	x += t.x;
	y += t.y;
	z += t.z;
}

float& Vect4D::operator[](VECT_ENUM e) {
	switch (e)
	{
	case 0:
		return x;
		break;
	case 1:
		return y;
		break;
	case 2:
		return z;
		break;
	case 3:
		return w;
		break;
	default:
		assert(0);
		return x;
	}
}

void Vect4D::Cross(Vect4D& vin, Vect4D& vout) {
	vout.x = (y * vin.z - z * vin.y);
	vout.y = (z * vin.x - x * vin.z);
	vout.z = (x * vin.y - y * vin.x);
	vout.w = 1.0f;
}

void Vect4D::set(float tx, float ty, float tz, float tw) {
	x = tx;
	y = ty;
	z = tz;
	w = tw;
}

// End of file
