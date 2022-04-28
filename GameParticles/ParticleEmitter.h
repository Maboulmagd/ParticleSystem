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

class __declspec(align(16)) ParticleEmitter final : public Align16 {
public:
	explicit ParticleEmitter();
	~ParticleEmitter();

	void ReinitializeParticle();

	void update();
	void draw();

	void Execute(Vect4D& pos, Vect4D& vel, Vect4D& sc);
	void GoodBye();

private:
	Particle* first_available;// Free list
	Particle* particles;

	float	last_spawn;
	float	last_loop;
};

#endif

// End of File
