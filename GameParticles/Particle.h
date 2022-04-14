//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PARTICLE_H
#define PARTICLE_H

// include
#include "Vect4D.h"

class __declspec(align(16)) Particle final {
public:
	friend class ParticleEmitter;

    explicit Particle();
	~Particle();

	void* operator new(size_t size);
	void* operator new[](size_t size);

	void operator delete(void* p);
	void operator delete[](void* p);

	bool IsAlive() const;
	const bool Update(const float& time_elapsed);

private:
	union __declspec(align(16)) state final {
		struct __declspec(align(16)) final {
			Vect4D	position;
			Vect4D	velocity;
			Vect4D	scale;

			float	rotation;
			float	rotation_velocity;

			// padding
		    // float pad0;
		    // float pad1;
		} live;

		Particle* next;

		explicit state() {}
		~state() {}
	} state;
	// NOTE: Recall that the size of a union is always equal
	//       to the size of its largest data member

	float life;

	// padding
	// float pad2;
	// float pad3;
	// float pad4;
};

#endif

// End of File
