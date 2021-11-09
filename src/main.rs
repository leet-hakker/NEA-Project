use std::ops;

#[derive(Copy, Clone)]
pub struct VecTwo {
    x: f32,
    y: f32,
}

impl ops::Mul<f32> for VecTwo {
    type Output = VecTwo;


    fn mul(self, float: f32) -> VecTwo {

        return VecTwo {x: self.x*float, y: self.y*float};
    }
}


impl ops::Add<VecTwo> for VecTwo {
    type Output = VecTwo;

    fn add(self, other: VecTwo) -> VecTwo {
        return VecTwo {x: self.x + other.x, y: self.y + other.y};
    }
}

impl ops::Sub<VecTwo> for VecTwo {
    type Output = VecTwo;

    fn sub(self, other: VecTwo) -> VecTwo {
        return VecTwo {x: self.x - other.x, y: self.y - other.y};
    }
}

impl ops::Div<f32> for VecTwo {
    type Output = VecTwo;

    fn div(self, float: f32) -> VecTwo {
        return VecTwo {x: self.x / float, y: self.y / float};
    }
}

#[derive(Copy, Clone)]
pub struct Particle {
    mass: f32,
    radius: f32,
    velocity: VecTwo,
    acceleration: VecTwo,
    position: VecTwo,
}


//impl Particle {
//
//    fn check_collisions(self, bounding=None) {
//        if bounding {
//
//        } else {
//
//        }
//    }
//
//}

pub struct ParticleSystem {
    size: VecTwo,
    particles: Vec<Particle>
}


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


fn dot(a: VecTwo, b: VecTwo) -> f32 {
    return a.x * b.x + a.y * b.y;
}


fn norm(a: VecTwo) -> f32 {
    return a.x + a.y;
}


fn calculate_resultant_velocities(mut a: Particle, mut b: Particle) -> (Particle, Particle) {

    let a_new_vel: VecTwo = a.velocity - (a.position - b.position) * (dot(a.velocity - b.velocity, a.position - b.position) / norm(a.position-b.position).powf(2.0)) * ((2.0*b.mass)/(a.mass + b.mass));

    let a_new_vel: VecTwo = b.velocity - (b.position - a.position) * (dot(b.velocity - a.velocity, b.position - a.position) / norm(b.position-a.position).powf(2.0)) * ((2.0*a.mass)/(a.mass + b.mass));


    a.velocity = a_new_vel;
    b.velocity = a_new_vel;

    return (a, b);
}

fn main() {
    let a: Particle = Particle {mass: 50.0, radius:1.0, velocity: VecTwo {x:50.0, y:50.0}, acceleration: VecTwo {x:0.0, y:0.0}, position: VecTwo {x:100.0, y:100.0}};
    let b: Particle = Particle {mass: 50.0, radius:1.8, velocity: VecTwo {x:-50.0, y:-50.0}, acceleration: VecTwo {x:0.0, y:0.0}, position: VecTwo {x:170.0, y:170.0}};
    let mut particle_system = ParticleSystem {size: VecTwo {x: 100.0, y: 100.0}, particles: vec![a, b]};

    particle_system = particle_system.update(VecTwo{x:0.0, y:0.0}, 1.0/60.0);
}
