//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Particle.h"
#include "Matrix.h"

#include "Settings.h"

Particle::Particle() {
	// constructor
	life = 0.0f;

	state.live.position.set(0.0f, 0.0f, 0.0f);
	state.live.velocity.set(0.0f, 0.0f, 0.0f);
	state.live.scale.set(1.0f, 1.0f, 1.0f);
	state.live.rotation = 0.0f;
	state.live.rotation_velocity = -0.5f;

	state.next = nullptr;
}

void* Particle::operator new(size_t size) {
	void* p = _aligned_malloc(size, 16);
	return p;
}

void* Particle::operator new[](size_t size) {
	void* p = _aligned_malloc(size, 16);
	return p;
}

void Particle::operator delete(void* p) {
	_aligned_free(p);
}

void Particle::operator delete[](void* p) {
	_aligned_free(p);
}

Particle::~Particle() {
	// nothing to do
}

bool Particle::IsAlive() const {
	return life >= 0.0f && life <= MAX_LIFE;
}

const bool Particle::Update(const float& time_elapsed) {
	if (IsAlive()) {
		// serious math below - magic secret sauce
		life += time_elapsed;
		state.live.position += (state.live.velocity * time_elapsed);
		Vect4D z_axis(0.0f, -0.25f, 1.0f);
		Vect4D v(3.0f, 4.0f, 0.0f);
		state.live.position.Cross(z_axis, v);
		v.norm(v);
		state.live.position += v * 0.05f * life;

		state.live.rotation += state.live.rotation_velocity * time_elapsed * 2.01f;
	}

	return life > MAX_LIFE;// if it's life exceeds the max_life, we return true to denote that this particle is now 'dead'
}


// End of file
