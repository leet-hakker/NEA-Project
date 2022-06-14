fn f() {
    ();
}

type VertexIndex = u32;

#[derive(Copy, Clone, Debug)]
pub struct Button {
    pub position: [f32; 2],
    pub dimensions: [f32; 2],
    pub colour: [f32; 4],
    pub action: fn(),
}


impl Default for Button {
    fn default() -> Self {
        Button {
            position: [0., 0.,],
            dimensions: [1., 1.],
            colour: [0., 0., 0., 1.],
            action: f,
        }
    }
}


impl Button {
    pub fn vertex_positions(self) -> [f32; 8] {
        [
            self.position[0], self.position[1],
            self.position[0]+self.dimensions[0], self.position[1],
            self.position[0], self.position[1]+self.dimensions[1],
            self.position[0]+self.dimensions[0], self.position[1]+self.dimensions[1],
        ]
    }
}

pub fn button_vertex_pos(buttons: &[Button]) -> Vec<f32> {
    let mut vertex_positions: Vec<f32> = vec![Default::default(); 4*buttons.len()];

    let mut index = 0;
    for i in 0..buttons.len() {
        let verts = buttons[i].vertex_positions();
        for vert in verts {
            vertex_positions[index] = vert;
            index += 1;
        }
    }
    vertex_positions
}


pub fn button_indices(n_buttons: u32) -> Vec<VertexIndex> {
    let mut indices: Vec<u32> = vec![Default::default(); (6*n_buttons).try_into().unwrap()];
    let mut array_index = 0;
    for i in 0..n_buttons {
        indices[array_index] = 0 + 4*i;
        indices[array_index+1] = 1 + 4*i;
        indices[array_index+2] = 2 + 4*i;
        indices[array_index+3] = 1 + 4*i;
        indices[array_index+4] = 2 + 4*i;
        indices[array_index+5] = 3 + 4*i;
        array_index += 6
    }

    indices
}

