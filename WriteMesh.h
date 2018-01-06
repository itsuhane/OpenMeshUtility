#pragma once
#include <string>
#include <OpenMesh/Core/IO/Options.hh>
#include "TriangleSoup.h"

template <typename Mesh>
inline void WriteMeshPerVertex(Mesh &mesh, const std::string &path) {
    int opt = OpenMesh::IO::Options::Binary;
    if (mesh.has_vertex_colors()) {
        opt = opt | OpenMesh::IO::Options::VertexColor;
    }
    if (mesh.has_vertex_normals()) {
        opt = opt | OpenMesh::IO::Options::VertexNormal;
    }
    OpenMesh::IO::write_mesh(mesh, path, opt);
}

template <typename Mesh>
inline void WriteMeshPerFace(Mesh &mesh, const std::string &path) {
    Mesh tsoup;
    ToTriangleSoup(mesh, tsoup, true, true);
    WriteMeshPerVertex(tsoup, path);
}

template <typename Mesh>
inline void WriteMesh(Mesh &mesh, const std::string &path, bool prefer_face_color = false, bool prefer_face_normal = false) {
    bool per_face_mode = false;
    if (mesh.has_face_colors() && prefer_face_color) {
        per_face_mode = true;
    }
    if (mesh.has_face_normals() && prefer_face_normal) {
        per_face_mode = true;
    }

    if (per_face_mode) {
        Mesh tsoup;
        ToTriangleSoup(mesh, tsoup, prefer_face_color, prefer_face_normal);
        WriteMeshPerVertex(tsoup, path);
    }
    else {
        WriteMeshPerVertex(mesh, path);
    }
}
