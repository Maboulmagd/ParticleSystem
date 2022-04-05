//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "Particle.h"
#include "Matrix.h"

#include "Settings.h"

Particle::Particle()
{
	// constructor
	life = 0.0f;

	state.live.position.set(0.0f, 0.0f, 0.0f);
	state.live.velocity.set(0.0f, 0.0f, 0.0f);
	state.live.scale.set(1.0f, 1.0f, 1.0f);
	state.live.rotation = 0.0f;
	state.live.rotation_velocity = -0.5f;

	state.next = nullptr;
}

Particle::~Particle()
{
	// nothing to do
}

bool Particle::IsAlive() const {
	return life >= 0.0f && life <= MAX_LIFE;
}

void Particle::CopyDataOnly(const Particle * const p)
{
	// copy the data only
	// this way of copying data is more efficient than element by element
	state.live.position = p->state.live.position;
	state.live.velocity = p->state.live.velocity;
	state.live.scale = p->state.live.scale;
	state.live.rotation = p->state.live.rotation;
	state.live.rotation_velocity = p->state.live.rotation_velocity;
	life = p->life;
}

const bool Particle::Update(const float& time_elapsed) {
	if (!IsAlive()) {
		return false;
	}

	// Rotate the matrices
	Vect4D tmp_Row0;
	tmp_Row0 = state.live.curr_Row0;
	state.live.prev_Row0 = tmp_Row0;

	Vect4D tmp_Row1;
	tmp_Row1 = state.live.curr_Row1;
	state.live.prev_Row1 = tmp_Row1;

	Vect4D tmp_Row2;
	tmp_Row2 = state.live.curr_Row2;
	state.live.prev_Row2 = tmp_Row2;

	Vect4D tmp_Row3;
	tmp_Row3 = state.live.curr_Row3;
	state.live.prev_Row3 = tmp_Row3;

	Matrix tmp;

	tmp.set(Matrix::MATRIX_ROW_0, &state.live.diff_Row0);
	tmp.set(Matrix::MATRIX_ROW_1, &state.live.diff_Row1);
	tmp.set(Matrix::MATRIX_ROW_2, &state.live.diff_Row2);
	tmp.set(Matrix::MATRIX_ROW_3, &state.live.diff_Row3);

	float MatrixScale = tmp.Determinant();

	// serious math below - magic secret sauce
	life += time_elapsed;
	state.live.position = state.live.position + (state.live.velocity * time_elapsed);
	Vect4D z_axis(0.0f, -0.25f, 1.0f);
	Vect4D v(3.0f, 4.0f, 0.0f);
	state.live.position.Cross(z_axis, v);
	v.norm(v);
	state.live.position = state.live.position + v * 0.05f * life;

	if (MatrixScale > 1.0f)
	{
		MatrixScale = 1.0f / MatrixScale;
	};

	state.live.rotation = state.live.rotation + MatrixScale + state.live.rotation_velocity * time_elapsed * 2.01f;

	return life > MAX_LIFE;// if it's life exceeds the max_life, we return true to denote that this particle is now 'dead'
}


// End of file
