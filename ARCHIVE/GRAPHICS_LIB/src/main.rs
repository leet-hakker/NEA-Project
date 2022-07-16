#![deny(clippy::all)]
#![warn(clippy::pedantic)]
#![warn(clippy::restriction)]
#![warn(clippy::nursery)]
#![warn(clippy::cargo)]

use cgmath::{perspective, EuclideanSpace, Matrix4, Point3, Rad, Vector3};
use glfw::{Action, Context as _, Key, WindowEvent};
use luminance_derive::UniformInterface;
use luminance_front::context::GraphicsContext;
use luminance_front::pipeline::PipelineState;
use luminance_front::render_state::RenderState;
use luminance_front::shader::Uniform;
use luminance_front::tess::Mode;
//use luminance_front::Backend;
use luminance_glfw::GlfwSurface;
#[allow(deprecated)]
use luminance_windowing::{WindowDim, WindowOpt};
//use std::env;
//use std::fs::File;
//use std::io::Read as _;
//use std::path::Path;
use std::process::exit;
//use wavefront_obj::obj;

mod lib;
pub use crate::lib::{Vertex3, Vertex3Position, Vertex3Normal, Vertex3Semantics};
pub use crate::lib::{Vertex2, Vertex2Position, Vertex2Semantics};
pub use crate::lib::Obj;
pub use crate::lib::ui::{VertexIndex, button_vertex_pos, button_indices};

pub use crate::lib::input::handle_events;

const VS_STR: &str = include_str!("vs.glsl");
const FS_STR: &str = include_str!("fs.glsl");

const FOVY: Rad<f32> = Rad(std::f32::consts::FRAC_PI_2);
const Z_NEAR: f32 = 0.1;
const Z_FAR: f32 = 10.;

#[derive(Debug, UniformInterface)]
struct ShaderInterface {
  #[uniform(unbound)]
  projection: Uniform<[[f32; 4]; 4]>,
  #[uniform(unbound)]
  view: Uniform<[[f32; 4]; 4]>,
}



#[allow(deprecated)]
fn main() {
  let dim = WindowDim::Windowed {
    width: 960,
    height: 540,
  };
  let surface = GlfwSurface::new_gl33("Hello, world!", WindowOpt::default().set_dim(dim));

  match surface {
    Ok(surface) => {
      eprintln!("graphics surface created");
      main_loop(surface);
    }

    Err(e) => {
      eprintln!("cannot create graphics surface:\n{}", e);
      exit(1);
    }
  }
}


fn main_loop(surface: GlfwSurface) {
    //let path = env::args()
    //.skip(1)
    //.next()
    //.expect("first argument must be the path of the .obj file to view");
    //println!("loading {}", path);

    // TODO: This is gross.
    let vertex_positions: Vec<f32> = button_vertex_pos(&BUTTONS_ARRAY);
    let mut index: usize = 0;
    let mut vertices: Vec<Vertex2> = vec![Default::default(); (vertex_positions.len()/2) as usize];
    loop {
        vertices[index/2] = Vertex2::new(Vertex2Position::new([vertex_positions[index], vertex_positions[index+1]]));
        index += 2;

        if index == vertex_positions.len() {
        break;
        }
    }

    let indices: Vec<VertexIndex> = button_indices(BUTTONS_ARRAY.len() as u32);

    let temp_verts = &vertices;


    let mut ctxt = surface.context;
    let events = surface.events_rx;
    let back_buffer = ctxt.back_buffer().expect("back buffer");

    //let mesh = Obj::load(path).unwrap().to_tess(&mut ctxt).unwrap();


    let buttons = ctxt
        .new_tess()
        .set_vertices(vertices)
        .set_indices(indices)
        .set_mode(Mode::Triangle)
        .build()
        .unwrap();


    let mut program = ctxt
    .new_shader_program::<Vertex2Semantics, (), ()>()
    .from_strings(VS_STR, None, None, FS_STR)
    .unwrap()
    .ignore_warnings();

    let [width, height] = back_buffer.size();
    let projection = perspective(FOVY, width as f32 / height as f32, Z_NEAR, Z_FAR);

    let view = Matrix4::<f32>::look_at(Point3::new(2., 2., 2.), Point3::origin(), Vector3::unit_y());

    'app: loop {
    // handle events
    // handle_events();
    ctxt.window.glfw.poll_events();
    for (_, event) in glfw::flush_messages(&events) {
        match event {
        WindowEvent::Close | WindowEvent::Key(Key::Escape, _, Action::Release, _) => break 'app,
        _ => (),
        }
    }

    // rendering code goes here
    let color = [0.3, 0.3, 0.3, 1.];

    //let render = ctxt
    //    .new_pipeline_gate()
    //    .pipeline(
    //    &back_buffer,
    //    &PipelineState::default().set_clear_color(color),
    //    |_, mut shd_gate| {
    //        shd_gate.shade(&mut program, |mut iface, uni, mut rdr_gate| {
    //        iface.set(&uni.projection, projection.into());
    //        iface.set(&uni.view, view.into());

    //        rdr_gate.render(&RenderState::default(), |mut tess_gate| {
    //            tess_gate.render(&mesh)
    //        })
    //        })
    //    },
    //    )
    //    .assume();

    let render = ctxt
      .new_pipeline_gate()
      .pipeline(
        &back_buffer,
        &PipelineState::default().set_clear_color(color),
        |_, mut shd_gate| {
          shd_gate.shade(&mut program, |_, _, mut rdr_gate| {
            rdr_gate.render(&RenderState::default(), |mut tess_gate| {
                tess_gate.render(&buttons)
            })
          })
        },
      )
      .assume();

    // swap buffer chains
    if render.is_ok() {
        ctxt.window.swap_buffers();
    } else {
        break 'app;
    }
    }
}
