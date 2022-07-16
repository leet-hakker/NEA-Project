# NEA-Project


## Problem

To create a program capable of simulating the laws of newtonian physics.

## Steps to problem solution

The first steps taken should be to correctly calculate the result of a collision given the velocities and masses of two circular objects.

Once this step has been completed, the next logical step is to run through the simulation in timesteps and to update the velocities and positions of the objects along these timesteps.
We can now check for collisions each timestep and use the already written collision resolution function to resolve these collisions.

## 24/11/21

As of 24/11/21 the following things have been completed:

Correctly calculate the result of collisions

```
fn calculate_resultant_velocities(mut a: Particle, mut b: Particle) -> (Particle, Particle) {

    let a_new_vel: VecTwo = a.velocity - (a.position - b.position) * (dot(a.velocity - b.velocity, a.position - b.position) / norm(a.position-b.position).powf(2.0)) * ((2.0*b.mass)/(a.mass + b.mass));

    let a_new_vel: VecTwo = b.velocity - (b.position - a.position) * (dot(b.velocity - a.velocity, b.position - a.position) / norm(b.position-a.position).powf(2.0)) * ((2.0*a.mass)/(a.mass + b.mass));


    a.velocity = a_new_vel;
    b.velocity = a_new_vel;

    return (a, b);
}
```
Update the positions and velocities of particles in a particle system

```
impl ParticleSystem {

    fn update(self, acceleration: VecTwo, dt: f32) -> ParticleSystem {

        let mut new_particles = Vec::<Particle>::new();
        for particle in self.particles {
            let mut new_particle = particle;

            new_particle.velocity = particle.velocity + particle.acceleration * dt;
            new_particle.position = particle.position + particle.velocity * dt;

//            particle.check_collisions(bounding=self.size);
            new_particles.push(new_particle)
        }

        return ParticleSystem {size: self.size, particles: new_particles}
    }

}
```
