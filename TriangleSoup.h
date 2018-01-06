#pragma once

template <typename Mesh>
inline void ToTriangleSoup(const Mesh &in, Mesh &out, bool prefer_face_color = false, bool prefer_face_normal = false) {
    out.clear();

    bool use_vertex_color = in.has_vertex_colors();
    bool use_face_color = in.has_face_colors();
    bool use_vertex_normal = in.has_vertex_normals();
    bool use_face_normal = in.has_face_normals();

    if (use_vertex_color && use_face_color) {
        use_vertex_color = !prefer_face_color;
        use_face_color = prefer_face_color;
    }
    if (use_vertex_normal && use_face_normal) {
        use_vertex_normal = !prefer_face_normal;
        use_face_normal = prefer_face_normal;
    }
    if (use_vertex_color || use_face_color) {
        out.request_vertex_colors();
    }
    if (use_vertex_normal || use_face_normal) {
        out.request_vertex_normals();
    }

    for (Mesh::ConstFaceIter cfi = in.faces_sbegin(); cfi != in.faces_end(); ++cfi) {
        Mesh::HalfedgeHandle heh_a = in.halfedge_handle(*cfi);
        Mesh::HalfedgeHandle heh_b = in.next_halfedge_handle(heh_a);
        Mesh::HalfedgeHandle heh_c = in.next_halfedge_handle(heh_b);

        Mesh::VertexHandle vh_a = in.to_vertex_handle(heh_a);
        Mesh::VertexHandle vh_b = in.to_vertex_handle(heh_b);
        Mesh::VertexHandle vh_c = in.to_vertex_handle(heh_c);

        Mesh::VertexHandle new_vh_a = out.add_vertex(in.point(vh_a));
        Mesh::VertexHandle new_vh_b = out.add_vertex(in.point(vh_b));
        Mesh::VertexHandle new_vh_c = out.add_vertex(in.point(vh_c));

        out.add_face(new_vh_a, new_vh_b, new_vh_c);

        if (use_vertex_color) {
            out.set_color(new_vh_a, in.color(vh_a));
            out.set_color(new_vh_b, in.color(vh_b));
            out.set_color(new_vh_c, in.color(vh_c));
        }
        if (use_face_color) {
            const auto &color = in.color(*cfi);
            out.set_color(new_vh_a, color);
            out.set_color(new_vh_b, color);
            out.set_color(new_vh_c, color);
        }
        if (use_vertex_normal) {
            out.set_normal(new_vh_a, in.normal(vh_a));
            out.set_normal(new_vh_b, in.normal(vh_b));
            out.set_normal(new_vh_c, in.normal(vh_c));
        }
        if (use_face_normal) {
            const auto &normal = in.normal(*cfi);
            out.set_normal(new_vh_a, normal);
            out.set_normal(new_vh_b, normal);
            out.set_normal(new_vh_c, normal);
        }
    }
}
