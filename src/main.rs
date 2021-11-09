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

    fn update(self, acceleration: VecTwo, dt: f32) {
        for particle in &mut self.particles {

            particle.velocity = particle.velocity + particle.acceleration * dt;
            particle.position = particle.position + particle.velocity * dt;

//            particle.check_collisions(bounding=self.size);
        }
    }

}


fn dot(a: VecTwo, b: VecTwo) -> f32 {
    return a.x * b.x + a.y * b.y;
}


fn norm(a: VecTwo) -> f32 {
    return a.x + a.y;
}


fn calculate_resultant_velocities(mut A: Particle, mut B: Particle) -> (Particle, Particle) {

    let A_new_vel: VecTwo = A.velocity - (A.position - B.position) * (dot(A.velocity - B.velocity, A.position - B.position) / norm(A.position-B.position).powf(2.0)) * ((2.0*B.mass)/(A.mass + B.mass));

    let B_new_vel: VecTwo = B.velocity - (B.position - A.position) * (dot(B.velocity - A.velocity, B.position - A.position) / norm(B.position-A.position).powf(2.0)) * ((2.0*A.mass)/(A.mass + B.mass));


    A.velocity = A_new_vel;
    B.velocity = B_new_vel;

    return (A, B);
}

fn main() {
    let mut A: Particle = Particle {mass: 50.0, radius:1.0, velocity: VecTwo {x:50.0, y:50.0}, acceleration: VecTwo {x:0.0, y:0.0}, position: VecTwo {x:100.0, y:100.0}};
    let mut B: Particle = Particle {mass: 50.0, radius:1.8, velocity: VecTwo {x:-50.0, y:-50.0}, acceleration: VecTwo {x:0.0, y:0.0}, position: VecTwo {x:170.0, y:170.0}};
    let mut particle_system = ParticleSystem {size: VecTwo {x: 100.0, y: 100.0}, particles: vec![A, B]};

    println!("{}, {}", &particle_system.particles[0].position.x, &particle_system.particles[0].position.y);
    println!("{}, {}", &particle_system.particles[1].position.x, &particle_system.particles[0].position.y);
    particle_system.update(VecTwo{x:0.0, y:0.0}, 1.0/60.0);
    println!("{}, {}", &particle_system.particles[0].position.x, &particle_system.particles[0].position.y);
    println!("{}, {}", &particle_system.particles[1].position.x, &particle_system.particles[0].position.y);
}
