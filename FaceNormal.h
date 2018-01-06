#pragma once

#include <cstdlib>
#include <Eigen/Eigen>
#include <OpenMesh/Core/Utils/Property.hh>

template <typename Mesh>
inline OpenMesh::FPropHandleT<Eigen::Vector3d> FaceNormal(Mesh &mesh) {
    OpenMesh::FPropHandleT<Eigen::Vector3d> fn;
    mesh.add_property(fn);
    if (mesh.is_trimesh()) {
        for (Mesh::ConstFaceIter cfi = mesh.faces_sbegin(); cfi != mesh.faces_end(); ++cfi) {
            Mesh::HalfedgeHandle heh_a = mesh.halfedge_handle(*cfi);
            Mesh::HalfedgeHandle heh_b = mesh.next_halfedge_handle(heh_a);
            Mesh::HalfedgeHandle heh_c = mesh.next_halfedge_handle(heh_b);
            Mesh::Point a = mesh.point(mesh.to_vertex_handle(heh_a));
            Mesh::Point b = mesh.point(mesh.to_vertex_handle(heh_b));
            Mesh::Point c = mesh.point(mesh.to_vertex_handle(heh_c));
            Mesh::Point ab = b - a;
            Mesh::Point ac = c - a;
            Mesh::Normal n = ab % ac;
            mesh.property(fn, *cfi) = { n[0], n[1], n[2] };
            mesh.property(fn, *cfi).normalize();
        }
    }
    else {
        fprintf(stderr, "Error: Currently FaceNormal can only handle triangular mesh.\n");
    }
    return fn;
}
