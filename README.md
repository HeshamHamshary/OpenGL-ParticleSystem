# OpenGL Particle System

This is a particle system built with openGL.

![Sample Particle System Scene](ParticleSystem.gif)

The architecture of this system is as follows:

* Effect: Holds emitters for a specific effect
* Emitter: Is responsible to spawning particles and giving them initial properties. Built with linked list structure and recycles particles instead of deleting them.
* Affector: Affects particles after their initial spawning.
	* VelocityAffector
	* ScaleAffector
	* FadeAffector
	* GravityAffector

## XML Files

All particle data is read from XML files for effects and emitters. Some example files are provided in the effects folder in data.

## Emitters

### Emission Types

* Point Emitter
* Box Emitter
* Sphere Emitter

### Emission Modes

* Continuous
* Burst

### Controls

N : Switch Effects
P : Pause Effect