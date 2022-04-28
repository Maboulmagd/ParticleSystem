//----------------------------------------------------------------------------
// Copyright 2019, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#include "DO_NOT_MODIFY\OpenGLInterface.h"
#include "Framework.h"

#include "ParticleEmitter.h"
#include "Settings.h"

extern Timer GlobalTimer;

static const unsigned char squareColors[] =
{
	200,  200,  0,  255, // Color   
	200,  200,  0,  255, // Color   
	200,  200,  0,  255, // Color   
	200,  200,  0,  255, // Color   
};

static const float squareVertices[] =
{
	-0.015f,  -0.015f, 0.0f, // Size of Triangle  
	 0.015f,  -0.015f, 0.0f, // Size of Triangle  
	-0.015f,   0.015f, 0.0f, // Size of Triangle  
	 0.015f,   0.015f, 0.0f, // Size of Triangle  
};

// Added these here as static variables, so as to avoid declaring them in every Draw() loop
static float cosine_rotation{ 0.0f };
static float sine_rotation{ 0.0f };

ParticleEmitter::ParticleEmitter() {
	GlobalTimer.Toc();

	particles = new Particle[NUM_PARTICLES];
	first_available = &particles[0];// The first one is available
	
	int i = 0;
	for (; i < NUM_PARTICLES - 1; ++i) {
		Particle* const new_particle = &particles[i];
		new_particle->state.next = &particles[i + 1];
	}

	// Take care of last particle
	Particle* const new_particle = &particles[i];
	new_particle->state.next = nullptr;

	//Trace::out("sizeof(Vect4D): %d\n", sizeof(Vect4D));
	//Trace::out("alignof(Vect4D): %d\n", alignof(Vect4D));
	
	//Particle p;

	//Trace::out("sizeof(p.state): %d\n", sizeof(p.state));
	//Trace::out("sizeof(p.state.live): %d\n", sizeof(p.state.live));

	//Trace::out("sizeof(p): %d\n", sizeof(p));

	//Trace::out("default compiler alignment: %d\n", __STDCPP_DEFAULT_NEW_ALIGNMENT__);

	last_spawn = GlobalTimer.TimeInSeconds();
	last_loop = GlobalTimer.TimeInSeconds();
}

ParticleEmitter::~ParticleEmitter()
{
	// do nothing
}

void ParticleEmitter::ReinitializeParticle() {
	assert(first_available != nullptr);

	// Remove it from the available list
	Particle* const new_particle = first_available;
	first_available = new_particle->state.next;

	// re-initialize the particle
	new_particle->life = 0.0f;

	new_particle->rotation = 0.0f;
	new_particle->rotation_velocity = -0.5f;

	new_particle->state.live.position = Vect4D(1.0f, 1.0f, 1.0f);
	new_particle->state.live.velocity = Vect4D(0.0f, 1.0f, 0.0f);
	new_particle->state.live.scale = Vect4D(2.0f, 2.0f, 2.0f, 1.0f);

	//new_particle->state.next = nullptr;

	// apply the variance
	Execute(new_particle->state.live.position, new_particle->state.live.velocity, new_particle->state.live.scale);
}

void ParticleEmitter::update() {
	// get current time
	GlobalTimer.Toc();
	const float current_time = GlobalTimer.TimeInSeconds();

	// spawn particles
	float time_elapsed = current_time - last_spawn;

	// update
	while (first_available != nullptr) {
		// re-initialize a particle
		ReinitializeParticle();

		// adjust time
		time_elapsed -= 0.0000001f;// spawn_frequency
		// last time
		last_spawn = current_time;
	}

	// total elapsed
	time_elapsed = current_time - last_loop;

	Particle* curr_particle = &particles[0];
	for (int i = 0; i < NUM_PARTICLES; ++i) {
		if (curr_particle->Update(time_elapsed)) {// curr_particle is now dead

			// Add this particle to the front of the free list
			curr_particle->state.next = first_available;
			first_available = curr_particle;

			assert(first_available != nullptr);
		}

		curr_particle++;
	}

	last_loop = current_time;
}

void ParticleEmitter::draw()
{
	// get the camera matrix from OpenGL
	// need to get the position
	Matrix cameraMatrix;

	// get the camera matrix from OpenGL
	glGetFloatv(GL_MODELVIEW_MATRIX, reinterpret_cast<float*>(&cameraMatrix));

	// get the position from this matrix
	Vect4D camPosVect;
	cameraMatrix.get(Matrix::MATRIX_ROW_3, &camPosVect);

	// camera position
	Matrix transCamera;
	transCamera.setTransMatrix(&camPosVect);

	// iterate throught the list of particles
	Particle* curr_particle = &particles[0];
	for (int i = 0; i < NUM_PARTICLES; ++i) {
		if (curr_particle->IsAlive()) {// NOTE: I was missing THIS check! I was drawing EVERY single particle, EVEN DEAD PARTICLES!
			//Temporary matrix
			Matrix tmp;

			// OpenGL goo... don't worrry about this
			glVertexPointer(3, GL_FLOAT, 0, squareVertices);
			glEnableClientState(GL_VERTEX_ARRAY);
			glColorPointer(4, GL_UNSIGNED_BYTE, 0, squareColors);
			glEnableClientState(GL_COLOR_ARRAY);

			cosine_rotation = cosf(curr_particle->rotation);
			sine_rotation = sinf(curr_particle->rotation);

			// This is the final transformation matrix, done by hand
			tmp.m0 = curr_particle->state.live.scale.x * cosine_rotation;
			tmp.m1 = curr_particle->state.live.scale.x * (-1.0f * sine_rotation);

			tmp.m4 = curr_particle->state.live.scale.y * sine_rotation;
			tmp.m5 = curr_particle->state.live.scale.y * cosine_rotation;

			tmp.m10 = curr_particle->state.live.scale.z;

			tmp.m12 = ((camPosVect.x + curr_particle->state.live.position.x) * cosine_rotation) + ((camPosVect.y + curr_particle->state.live.position.y) * sine_rotation);
			tmp.m13 = ((camPosVect.y + curr_particle->state.live.position.y) * cosine_rotation) - ((camPosVect.x + curr_particle->state.live.position.x) * sine_rotation);
			tmp.m14 = camPosVect.z + curr_particle->state.live.position.z;
			tmp.m15 = 1.0f;

			// set the transformation matrix
			glLoadMatrixf(reinterpret_cast<float*>(&(tmp)));

			// draw the trangle strip
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		}

		curr_particle++;
	}
}

void ParticleEmitter::Execute(Vect4D& pos, Vect4D& vel, Vect4D& sc)
{
	// Add some randomness...

	// See it's ugly - I didn't write this so don't bitch at me   
	// Sometimes code like this is inside real commerical code   
	// ( so now you know how it feels )   

	// x - variance
	float var = static_cast<float>(rand() % 1000) * 0.001f;// Var 
	float sign = static_cast<float>(rand() % 2);// Sign 
	if (sign == 0.0f) {
		var *= -1.0f;
	}
	else {
		pos.x += var;
	}
	
	// y - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	if (sign == 0.0f) {
		var *= -1.0f;
	}
	else {
		pos.y += var;
	}

	// z - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	if (sign == 0.0f) {
		var *= -1.0f;
	}
	else {
		pos.z += var;
	}


	// x  - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	if (sign == 0.0f) {
		var *= -1.0f;
	}
	vel[x] += var;

	// y - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	if (sign == 0.0f) {
		var *= -1.0f;
	}
	vel[y] += 4.0f * var;

	// z - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	if (sign == 0.0f) {
		var *= -1.0f;
	}
	vel[z] += 0.4f * var;

	// correct the sign
	var = 2.0f * static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);

	if (sign == 0.0f) {
		var *= -1.0f;
	}

	sc *= var;
}

void ParticleEmitter::GoodBye() {
	delete[] particles;
}

// End of file
