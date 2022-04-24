use luminance_derive::{Vertex, Semantics};
use luminance_front::tess::{Interleaved, Mode, Tess, TessError};
use luminance_front::context::GraphicsContext;
use luminance_front::Backend;
use std::collections::HashMap;
use std::path::Path;
use std::fs::File;
use std::io::Read;
use try_guard::verify;
use wavefront_obj::obj;

pub mod ui;

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq, Semantics)]
pub enum Vertex3Semantics {
  #[sem(name = "position", repr = "[f32; 3]", wrapper = "Vertex3Position")]
  Position,
  #[sem(name = "normal", repr = "[f32; 3]", wrapper = "Vertex3Normal")]
  Normal,
}

#[derive(Clone, Copy, Debug, Vertex)]
#[vertex(sem = "Vertex3Semantics")]
pub struct Vertex3 {
  pub position: Vertex3Position,
  pub normal: Vertex3Normal,
}

#[derive(Clone, Copy, Debug, Eq, Hash, PartialEq, Semantics)]
pub enum Vertex2Semantics {
  #[sem(name = "position", repr = "[f32; 2]", wrapper = "Vertex2Position")]
  Position,
}

#[derive(Clone, Copy, Debug, Vertex)]
#[vertex(sem = "Vertex2Semantics")]
pub struct Vertex2 {
  pub position: Vertex2Position,
}

impl Default for Vertex2 {
    fn default() -> Self {Vertex2 {position: Vertex2Position::new([0., 0.])}}
}

type VertexIndex = u32;


pub struct Obj {
  vertices: Vec<Vertex3>,
  indices: Vec<VertexIndex>,
}

impl Obj {
  pub fn to_tess<C>(self, ctxt: &mut C) -> Result<Tess<Vertex3, VertexIndex, (), Interleaved>, TessError>
  where
    C: GraphicsContext<Backend = Backend>,
  {
    ctxt
      .new_tess()
      .set_mode(Mode::Triangle)
      .set_vertices(self.vertices)
      .set_indices(self.indices)
      .build()
  }

  pub fn load<P>(path: P) -> Result<Self, String>
  where
    P: AsRef<Path>,
  {
    let file_content = {
      let mut file = File::open(path).map_err(|e| format!("cannot open file: {}", e))?;
      let mut content = String::new();
      file.read_to_string(&mut content).unwrap();
      content
    };
    let obj_set = obj::parse(file_content).map_err(|e| format!("cannot parse: {:?}", e))?;
    let objects = obj_set.objects;

    verify!(objects.len() == 1).ok_or("expecting a single object".to_owned())?;

    let object = objects.into_iter().next().unwrap();

    verify!(object.geometry.len() == 1).ok_or("expecting a single geometry".to_owned())?;

    let geometry = object.geometry.into_iter().next().unwrap();

    println!("loading {}", object.name);
    println!("{} vertices", object.vertices.len());
    println!("{} shapes", geometry.shapes.len());

    // build up vertices; for this to work, we remove duplicated vertices by putting them in a
    // map associating the vertex with its ID
    let mut vertex_cache: HashMap<obj::VTNIndex, VertexIndex> = HashMap::new();
    let mut vertices: Vec<Vertex3> = Vec::new();
    let mut indices: Vec<VertexIndex> = Vec::new();

    for shape in geometry.shapes {
      if let obj::Primitive::Triangle(a, b, c) = shape.primitive {
        for key in &[a, b, c] {
          if let Some(vertex_index) = vertex_cache.get(key) {
            indices.push(*vertex_index);
          } else {
            let p = object.vertices[key.0];
            let n = object.normals[key.2.ok_or("missing normal for a vertex".to_owned())?];
            let position = Vertex3Position::new([p.x as f32, p.y as f32, p.z as f32]);
            let normal = Vertex3Normal::new([n.x as f32, n.y as f32, n.z as f32]);
            let vertex = Vertex3 { position, normal };
            let vertex_index = vertices.len() as VertexIndex;

            vertex_cache.insert(*key, vertex_index);
            vertices.push(vertex);
            indices.push(vertex_index);
          }
        }
      } else {
        return Err("unsupported non-triangle shape".to_owned());
      }
    }

    Ok(Obj { vertices, indices })
  }
}
