//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Math\Matrix.h"
#include "Math\Vect4D.h"
#include "Particle.h"

#include <list>
#include <Settings.h>

class ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();

	void ReinitializeParticle();

	void update();
	void draw();

	void Execute(Vect4D& pos, Vect4D& vel, Vect4D& sc);
	void GoodBye();

private:
	Vect4D	start_position;
	Vect4D	start_velocity;

	float	max_life;
	int		max_particles;
	float	spawn_frequency;
	float	last_spawn;
	float	last_loop;

	// added for speed efficiency
	Vect4D	vel_variance;
	Vect4D	pos_variance;
	float	scale_variance;

	Particle* first_available;// Free list
	Particle* particles;

	// Added these to avoid declaring them in every Draw() loop
	float cosine_rotation;
	float sine_rotation;
};

#endif

// End of File
