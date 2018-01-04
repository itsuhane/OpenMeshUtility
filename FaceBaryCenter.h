#pragma once

#include <cstdlib>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>
#include <Eigen/Eigen>

template <typename Mesh>
inline OpenMesh::FPropHandleT<Eigen::Vector3d> FaceBaryCenter(Mesh &mesh) {
    OpenMesh::FPropHandleT<Eigen::Vector3d> fbc;
    mesh.add_property(fbc);
    if (mesh.is_trimesh()) {
        for (Mesh::ConstFaceIter cfi = mesh.faces_sbegin(); cfi != mesh.faces_end(); ++cfi) {
            mesh.property(fbc, *cfi) = Eigen::Vector3d::Zero();
        }
        for (Mesh::ConstVertexIter cvi = mesh.vertices_sbegin(); cvi != mesh.vertices_end(); ++cvi) {
            const OpenMesh::Vec3f &p = mesh.point(*cvi);
            for (Mesh::ConstVertexFaceCCWIter cvfi = mesh.cvf_ccwbegin(*cvi); cvfi != mesh.cvf_ccwend(*cvi); ++cvfi) {
                mesh.property(fbc, *cvfi) += Eigen::Vector3d(p[0], p[1], p[2]);
            }
        }
        for (Mesh::ConstFaceIter cfi = mesh.faces_sbegin(); cfi != mesh.faces_end(); ++cfi) {
            mesh.property(fbc, *cfi) /= 3.0;
        }
    }
    else {
        fprintf(stderr, "Error: Currently FaceNormal can only handle triangular mesh.\n");
    }
    return fbc;
}
