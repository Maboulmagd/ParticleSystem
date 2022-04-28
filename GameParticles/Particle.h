//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PARTICLE_H
#define PARTICLE_H

// include
#include "Vect4D.h"

class __declspec(align(16)) Particle final : public Align16 {
public:
	friend class ParticleEmitter;

    explicit Particle();
	~Particle();

	bool IsAlive() const;
	const bool Update(const float& time_elapsed);

private:
	// NOTE: Recall that the size of a union is always equal
	//       to the size of its largest data member
	union __declspec(align(16)) state final {
		struct __declspec(align(16)) final {
			Vect4D	position;
			Vect4D	velocity;
			Vect4D	scale;
		} live;

		Particle* next;

		explicit state() {}
		~state() {}
	} state;

	// NOTE: I took out rotation and rotation_velocity from the union (live struct) so that the Particle's total size is 64 bytes (cache-friendly, since cache lines are 64 bytes each in size?),
	//		 as opposed to 80 bytes, which is what it was previously.
	float rotation;
	float rotation_velocity;

	float life;

	// padding
	// float pad0;
};

#endif

// End of File
