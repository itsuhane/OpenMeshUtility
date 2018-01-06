#pragma once

#include <Eigen/Eigen>
#include <OpenMesh/Core/Utils/Property.hh>
#include "MeshAlgorithm.h"

template <typename Mesh>
OpenMesh::VPropHandleT<Eigen::Vector3d> NormalTensorVoting(Mesh &mesh, double sigma) {
    OpenMesh::VPropHandleT<Eigen::Matrix3d> vnt = FillVertexProperty(mesh, Eigen::Matrix3d(Eigen::Matrix3d::Zero()));

    OpenMesh::FPropHandleT<Eigen::Vector3d> fn = FaceNormal(mesh);
    OpenMesh::FPropHandleT<Eigen::Vector3d> fc = FaceBaryCenter(mesh);
    OpenMesh::FPropHandleT<double> fa = FaceArea(mesh);
    OpenMesh::VPropHandleT<double> vfa_max = ReduceVertexFaceProperty(mesh, fa, 1.0e-7, [](const double &a, const double &b) {
        return std::max(a, b);
    });

    ForEachVertex(mesh, [&vnt, &fn, &fc, &fa, &vfa_max, sigma](Mesh &mesh, const Mesh::VertexHandle &vh) {
        Eigen::Matrix3d &normal_tensor = mesh.property(vnt, vh);
        const OpenMesh::Vec3f &op = mesh.point(vh);
        const Eigen::Vector3d p = { op[0], op[1], op[2] };
        const double &area_max = mesh.property(vfa_max, vh);
        std::set<Mesh::FaceHandle> faces = FaceInRadius(mesh, vh, sigma);
        for (const Mesh::FaceHandle &fh : faces) {
            const Eigen::Vector3d &n = mesh.property(fn, fh);
            const Eigen::Vector3d &bc = mesh.property(fc, fh);
            const double &area = mesh.property(fa, fh);
            double weight = area / area_max * std::exp(-((p - bc).squaredNorm() * 3 / sigma));
            normal_tensor += (weight*n)*n.transpose();
        }
        if (faces.size() > 0) {
            normal_tensor /= double(faces.size());
        }
    });

    OpenMesh::VPropHandleT<Eigen::Vector3d> spectrum = MapVertexProperty(mesh, vnt, [](const Eigen::Matrix3d &nt) {
        return Eigen::SelfAdjointEigenSolver<Eigen::Matrix3d>(nt).eigenvalues().normalized();
    });

    mesh.remove_property(vnt);
    mesh.remove_property(fn);
    mesh.remove_property(fc);
    mesh.remove_property(fa);
    mesh.remove_property(vfa_max);

    return spectrum;
}
