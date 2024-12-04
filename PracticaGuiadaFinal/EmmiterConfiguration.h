#pragma once
#include "Solid.h"

class EmmiterConfiguration
{
	private:

		int numParticles;
		int emissionPeriod;
		Solid* particle;

	public:	
	
		EmmiterConfiguration(int numParticles, int emissionPeriod, Solid* particle) :
			numParticles(numParticles), emissionPeriod(emissionPeriod), particle(particle) {}

		EmmiterConfiguration(Solid* particle) :
			numParticles(25), emissionPeriod(10), particle(particle) {}

		EmmiterConfiguration() :
			numParticles(500), emissionPeriod(500), particle(NULL) {}

		inline int getParticleNum() const { return this->numParticles; }
		inline int getEmissionPeriod() const { return this->emissionPeriod; }
		inline Solid* getParticle() const { return this->particle; }

		inline void setParticleNum(int numParticles) { this->numParticles = numParticles; }
		inline void setEmissionPeriod(int emissionPeriod) { this->emissionPeriod = emissionPeriod; }
		inline void setParticle(Solid* particle) { this->particle = particle; }
};

