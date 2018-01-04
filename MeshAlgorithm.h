#pragma once

#include <OpenMesh/Core/Utils/Property.hh>

template <typename Mesh, typename Fn>
inline auto GenerateVertexProperty(Mesh &mesh, Fn gen) -> OpenMesh::VPropHandleT<decltype(gen())> {
    OpenMesh::VPropHandleT<decltype(gen())> ret;
    mesh.add_property(ret);
    for (Mesh::ConstVertexIter cvi = mesh.vertices_sbegin(); cvi != mesh.vertices_end(); ++cvi) {
        mesh.property(ret, *cvi) = gen();
    }
    return ret;
}

template <typename Mesh, typename Fn>
inline auto GenerateFaceProperty(Mesh &mesh, Fn gen) -> OpenMesh::FPropHandleT<decltype(gen())> {
    OpenMesh::FPropHandleT<decltype(gen())> ret;
    mesh.add_property(ret);
    for (Mesh::ConstFaceIter cfi = mesh.faces_sbegin(); cfi != mesh.faces_end(); ++cfi) {
        mesh.property(ret, *cfi) = gen();
    }
    return ret;
}

template <typename Mesh, typename T, typename Fn>
inline auto MapVertexProperty(Mesh &mesh, OpenMesh::VPropHandleT<T> vph, Fn tfm) -> OpenMesh::VPropHandleT<decltype(tfm(T()))> {
    OpenMesh::VPropHandleT<decltype(tfm(T()))> ret;
    mesh.add_property(ret);
    for (Mesh::ConstVertexIter cvi = mesh.vertices_sbegin(); cvi != mesh.vertices_end(); ++cvi) {
        mesh.property(ret, *cvi) = tfm(mesh.property(vph, *cvi));
    }
    return ret;
}

template <typename Mesh, typename T, typename Fn>
inline auto MapFaceProperty(Mesh &mesh, OpenMesh::FPropHandleT<T> fph, Fn tfm) -> OpenMesh::FPropHandleT<decltype(tfm(T()))> {
    OpenMesh::FPropHandleT<decltype(tfm(T()))> ret;
    mesh.add_property(ret);
    for (Mesh::ConstFaceIter cfi = mesh.faces_sbegin(); cfi != mesh.faces_end(); ++cfi) {
        mesh.property(ret, *cfi) = tfm(mesh.property(fph, *cfi));
    }
    return ret;
}

template <typename Mesh, typename T, typename Fn, typename Ret = T>
inline auto ReduceVertexFaceProperty(Mesh &mesh, OpenMesh::FPropHandleT<T> fph, Fn op, const Ret &init = {}) -> OpenMesh::VPropHandleT<Ret> {
    OpenMesh::VPropHandleT<Ret> ret = GenerateVertexProperty(mesh, [&init]() { return init; });
    for (Mesh::ConstFaceIter cfi = mesh.faces_sbegin(); cfi != mesh.faces_end(); ++cfi) {
        const T & fval = mesh.property(fph, *cfi);
        for (Mesh::ConstFaceVertexCCWIter cfvi = mesh.cfv_ccwbegin(*cfi); cfvi != mesh.cfv_ccwend(*cfi); ++cfvi) {
            Ret & val = mesh.property(ret, *cfvi);
            val = op(val, fval);
        }
    }
    return ret;
}
