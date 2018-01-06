#pragma once

#include <utility>
#include <Eigen/Eigen>
#include "MeshAlgorithm.h"

template <typename Mesh>
std::pair<Eigen::Vector3d, Eigen::Vector3d> BoundingBox(Mesh &mesh) {
    Eigen::Vector3d lower_bound = Eigen::Vector3d::Constant(std::numeric_limits<double>::max());
    Eigen::Vector3d upper_bound = Eigen::Vector3d::Constant(-std::numeric_limits<double>::max());
    std::tie(lower_bound, upper_bound) = ReduceVertexProperty(mesh, mesh.points_pph(), std::tie(lower_bound, upper_bound), [](std::tuple<Eigen::Vector3d, Eigen::Vector3d> bb, const OpenMesh::Vec3f &p) {
        for (int i = 0; i < 3; ++i) {
            std::get<0>(bb)[i] = std::min<double>(std::get<0>(bb)[i], p[i]);
            std::get<1>(bb)[i] = std::max<double>(std::get<1>(bb)[i], p[i]);
        }
        return bb;
    });
    return{ lower_bound, upper_bound };
}
