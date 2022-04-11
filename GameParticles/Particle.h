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

	bool IsAlive() const;

	const bool Update(const float& time_elapsed);

private:
	union state final {
		struct {
			// NOTE/TODO: Not sure why when I take out the 12 useless Vect4D's (192 bytes reduction) the animation is wrong for a split second right at the very start!
			Vect4D	prev_Row0;
			Vect4D	prev_Row1;
			Vect4D  prev_Row2;
			Vect4D  prev_Row3;

			Vect4D	position;
			Vect4D	velocity;
			Vect4D	scale;

			Vect4D  diff_Row0;
			Vect4D  diff_Row1;
			Vect4D  diff_Row2;
			Vect4D  diff_Row3;
			
			Vect4D	curr_Row0;
			Vect4D	curr_Row1;
			Vect4D  curr_Row2;
			Vect4D  curr_Row3;

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
