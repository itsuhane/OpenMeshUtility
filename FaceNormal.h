#pragma once

#include <cstdlib>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <Eigen/Eigen>

template <typename Mesh>
inline OpenMesh::FPropHandleT<Eigen::Vector3d> FaceNormal(Mesh &mesh) {
    OpenMesh::FPropHandleT<Eigen::Vector3d> fn;
    mesh.add_property(fn);
    if (mesh.is_trimesh()) {
        bool has_fn = mesh.has_face_normals();
        if (!has_fn) {
            mesh.request_face_normals();
        }
        mesh.update_face_normals();
        for (Mesh::ConstFaceIter cfi = mesh.faces_sbegin(); cfi != mesh.faces_end(); ++cfi) {
            const OpenMesh::Vec3f &n = mesh.normal(*cfi);
            mesh.property(fn, *cfi) = { n[0], n[1], n[2] };
        }
        if (!has_fn) {
            mesh.release_face_normals();
        }
    }
    else {
        fprintf(stderr, "Error: Currently FaceNormal can only handle triangular mesh.\n");
    }
    return fn;
}
