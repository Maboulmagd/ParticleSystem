//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PARTICLE_H
#define PARTICLE_H

// include
#include "Vect4D.h"

class Particle final {
public:
	friend class ParticleEmitter;

    explicit Particle();
	~Particle();

	bool IsAlive() const;

	const bool Update(const float& time_elapsed);
	void CopyDataOnly(const Particle * const p);

private:
	float life;

	union state {
		struct {
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

			float	rotation;
			float	rotation_velocity;
			
			Vect4D	curr_Row0;
			Vect4D	curr_Row1;
			Vect4D  curr_Row2;
			Vect4D  curr_Row3;
		} live;

		Particle* next;

		state() {}
		~state() {}
	} state;
};

#endif

// End of File
