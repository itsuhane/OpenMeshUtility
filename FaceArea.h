#pragma once

#include <cstdlib>
#include <OpenMesh/Core/Mesh/TriMesh_ArrayKernelT.hh>

template <typename Mesh>
inline OpenMesh::FPropHandleT<double> FaceArea(Mesh &mesh) {
    OpenMesh::FPropHandleT<double> fa;
    mesh.add_property(fa);
    if (mesh.is_trimesh()) {
        for (Mesh::ConstFaceIter cfi = mesh.faces_sbegin(); cfi != mesh.faces_end(); ++cfi) {
            Mesh::HalfedgeHandle heh = mesh.halfedge_handle(*cfi);
            mesh.property(fa, *cfi) = mesh.calc_sector_area(heh);
        }
    }
    else {
        fprintf(stderr, "Error: Currently FaceArea can only handle triangular mesh.\n");
    }
    return fa;
}
