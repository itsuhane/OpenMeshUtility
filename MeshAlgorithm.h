#pragma once

#include <utility>
#include <OpenMesh/Core/Utils/Property.hh>

/*
    for each (vertex_handle in mesh.valid_vertices) {
        fcn(mesh, vertex_handle);
    }
*/
template <typename Mesh, typename Fn>
inline void ForEachVertex(Mesh &mesh, Fn fcn) {
    for (Mesh::ConstVertexIter cvi = mesh.vertices_sbegin(); cvi != mesh.vertices_end(); ++cvi) {
        fcn(mesh, *cvi);
    }
}

/*
    for each (face_handle in mesh.valid_faces) {
        fcn(mesh, face_handle);
    }
*/
template <typename Mesh, typename Fn>
inline void ForEachFace(Mesh &mesh, Fn fcn) {
    for (Mesh::ConstFaceIter cfi = mesh.faces_sbegin(); cfi != mesh.faces_end(); ++cfi) {
        fcn(mesh, *cfi);
    }
}

/*
    for each (face_handle incident to mesh.vertex(vh) in CCW-order) {
        fcn(mesh, face_handle);
    }
*/
template <typename Mesh, typename Fn>
inline void ForEachVertexFaceCCW(Mesh &mesh, const typename Mesh::VertexHandle &vh, Fn fcn) {
    for (Mesh::ConstVertexFaceCCWIter cvfi = mesh.cvf_ccwbegin(vh); cvfi != mesh.cvf_ccwend(vh); ++cvfi) {
        fcn(mesh, *cvfi);
    }
}

/*
    for each (face_handle incident to mesh.vertex(vh) in CW-order) {
        fcn(mesh, face_handle);
    }
*/
template <typename Mesh, typename Fn>
inline void ForEachVertexFaceCW(Mesh &mesh, const typename Mesh::VertexHandle &vh, Fn fcn) {
    for (Mesh::ConstVertexFaceCCWIter cvfi = mesh.cvf_cwbegin(vh); cvfi != mesh.cvf_cwend(vh); ++cvfi) {
        fcn(mesh, *cvfi);
    }
}

/*
    for each (vertex_handle incident to mesh.vertex(vh) in CCW-order) {
        fcn(mesh, vertex_handle);
    }
*/
template <typename Mesh, typename Fn>
inline void ForEachVertexVertexCCW(Mesh &mesh, const typename Mesh::VertexHandle &vh, Fn fcn) {
    for (Mesh::ConstVertexVertexCCWIter cvvi = mesh.cvv_ccwbegin(vh); cvvi != mesh.cvv_ccwend(vh); ++cvvi) {
        fcn(mesh, *cvvi);
    }
}

/*
    for each (vertex_handle incident to mesh.vertex(vh) in CW-order) {
        fcn(mesh, vertex_handle);
    }
*/
template <typename Mesh, typename Fn>
inline void ForEachVertexVertexCW(Mesh &mesh, const typename Mesh::VertexHandle &vh, Fn fcn) {
    for (Mesh::ConstVertexVertexCWIter cvvi = mesh.cvv_cwbegin(vh); cvvi != mesh.cvv_cwend(vh); ++cvvi) {
        fcn(mesh, *cvvi);
    }
}

/*
    for each (vertex_handle incident to mesh.face(fh) in CCW-order) {
        fcn(mesh, vertex_handle);
    }
*/
template <typename Mesh, typename Fn>
inline void ForEachFaceVertexCCW(Mesh &mesh, const typename Mesh::FaceHandle &fh, Fn fcn) {
    for (Mesh::ConstFaceVertexCCWIter cfvi = mesh.cfv_ccwbegin(fh); cfvi != mesh.cfv_ccwend(fh); ++cfvi) {
        fcn(mesh, *cfvi);
    }
}

/*
    for each (vertex_handle incident to mesh.face(fh) in CW-order) {
        fcn(mesh, vertex_handle);
    }
*/
template <typename Mesh, typename Fn>
inline void ForEachFaceVertexCW(Mesh &mesh, const typename Mesh::FaceHandle &fh, Fn fcn) {
    for (Mesh::ConstFaceVertexCWIter cfvi = mesh.cfv_cwbegin(fh); cfvi != mesh.cfv_cwend(fh); ++cfvi) {
        fcn(mesh, *cfvi);
    }
}

/*
    for each (face_handle incident to mesh.face(fh) in CCW-order) {
        fcn(mesh, face_handle);
    }
*/
template <typename Mesh, typename Fn>
inline void ForEachFaceFaceCCW(Mesh &mesh, const typename Mesh::FaceHandle &fh, Fn fcn) {
    for (Mesh::ConstFaceFaceCCWIter cffi = mesh.cff_ccwbegin(fh); cffi != mesh.cff_ccwend(fh); ++cffi) {
        fcn(mesh, *cffi);
    }
}

/*
    for each (face_handle incident to mesh.face(fh) in CW-order) {
        fcn(mesh, face_handle);
    }
*/
template <typename Mesh, typename Fn>
inline void ForEachFaceFaceCW(Mesh &mesh, const typename Mesh::FaceHandle &fh, Fn fcn) {
    for (Mesh::ConstFaceFaceCWIter cffi = mesh.cff_cwbegin(fh); cffi != mesh.cff_cwend(fh); ++cffi) {
        fcn(mesh, *cffi);
    }
}

/*
    for each (vertex_handle in mesh.valid_vertices) {
        mesh.vph[vertex_handle] = val;
    }
*/
template <typename Mesh, typename T>
inline void FillVertexPropertyTo(Mesh &mesh, OpenMesh::VPropHandleT<T> vph, const T &val) {
    ForEachVertex(mesh, [&vph, &val](Mesh &mesh, const Mesh::VertexHandle &vh) {
        mesh.property(vph, vh) = val;
    });
}

/*
    for each (face_handle in mesh.valid_faces) {
        mesh.fph[face_handle] = val;
    }
*/
template <typename Mesh, typename T>
inline void FillFacePropertyTo(Mesh &mesh, OpenMesh::FPropHandleT<T> fph, const T &val) {
    ForEachFace(mesh, [&fph, &val](Mesh &mesh, const Mesh::FaceHandle &fh) {
        mesh.property(fph, fh) = val;
    });
}

/*
    Create new vertex property and FillVertexPropertyTo it.
*/
template <typename Mesh, typename T>
inline OpenMesh::VPropHandleT<T> FillVertexProperty(Mesh &mesh, const T &val) {
    OpenMesh::VPropHandleT<T> vph;
    mesh.add_property(vph);
    FillVertexPropertyTo(mesh, vph, val);
    return vph;
}

/*
    Create new face property and FillFacePropertyTo it.
*/
template <typename Mesh, typename T>
inline OpenMesh::FPropHandleT<T> FillFaceProperty(Mesh &mesh, const T &val) {
    OpenMesh::FPropHandleT<T> fph;
    mesh.add_property(fph);
    FillFacePropertyTo(mesh, fph, val);
    return fph;
}

/*
    for each (vertex_handle in mesh.valid_vertices) {
        mesh.vph[vertex_handle] = gen();
    }
*/
template <typename Mesh, typename T, typename Fn>
inline void GenerateVertexPropertyTo(Mesh &mesh, OpenMesh::VPropHandleT<T> vph, Fn gen) {
    ForEachVertex(mesh, [&vph, &gen](Mesh &mesh, const Mesh::VertexHandle &vh) {
        mesh.property(vph, vh) = gen();
    });
}

/*
    for each (face_handle in mesh.valid_faces) {
        mesh.fph[face_handle] = gen();
    }
*/
template <typename Mesh, typename T, typename Fn>
inline void GenerateFacePropertyTo(Mesh &mesh, OpenMesh::FPropHandleT<T> fph, Fn gen) {
    ForEachFace(mesh, [&fph, &gen](Mesh &mesh, const Mesh::FaceHandle &fh) {
        mesh.property(fph, fh) = gen();
    });
}

/*
    Create new vertex property and GenerateVertexPropertyTo it.
*/
template <typename Mesh, typename Fn>
inline auto GenerateVertexProperty(Mesh &mesh, Fn gen) -> OpenMesh::VPropHandleT<typename std::result_of<Fn()>::type> {
    OpenMesh::VPropHandleT<typename std::result_of<Fn()>::type> vph;
    mesh.add_property(vph);
    GenerateVertexPropertyTo(mesh, vph, gen);
    return vph;
}

/*
    Create new face property and GenerateFacePropertyTo it.
*/
template <typename Mesh, typename Fn>
inline auto GenerateFaceProperty(Mesh &mesh, Fn gen) -> OpenMesh::FPropHandleT<typename std::result_of<Fn()>::type> {
    OpenMesh::FPropHandleT<typename std::result_of<Fn()>::type> fph;
    mesh.add_property(fph);
    GenerateFacePropertyTo(mesh, fph, gen);
    return fph;
}

/*
    for each (vertex_handle in mesh.valid_vertices) {
        mesh.vph_to[vertex_handle] = tfm(mesh.vph_from[vertex_handle]);
    }
*/
template <typename Mesh, typename F, typename T, typename Fn>
inline void MapVertexPropertyTo(Mesh &mesh, OpenMesh::VPropHandleT<F> vph_from, OpenMesh::VPropHandleT<T> vph_to, Fn tfm) {
    ForEachVertex(mesh, [&vph_from, &vph_to, &tfm](Mesh &mesh, const Mesh::VertexHandle &vh) {
        mesh.property(vph_to, vh) = tfm(mesh.property(vph_from, vh));
    });
}

/*
    Create new vertex property and MapVertexPropertyTo it.
*/
template <typename Mesh, typename F, typename Fn, typename T = std::decay<typename std::result_of<Fn(F)>::type>::type>
inline OpenMesh::VPropHandleT<T> MapVertexProperty(Mesh &mesh, OpenMesh::VPropHandleT<F> vph, Fn tfm) {
    OpenMesh::VPropHandleT<T> vph_to;
    mesh.add_property(vph_to);
    MapVertexPropertyTo(mesh, vph, vph_to, tfm);
    return vph_to;
}

/*
    for each (face_handle in mesh.valid_faces) {
        mesh.fph_to[face_handle] = tfm(mesh.fph_from[face_handle]);
    }
*/
template <typename Mesh, typename F, typename T, typename Fn>
inline void MapFacePropertyTo(Mesh &mesh, OpenMesh::FPropHandleT<F> fph_from, OpenMesh::FPropHandleT<T> fph_to, Fn tfm) {
    ForEachFace(mesh, [&fph_from, &fph_to, &tfm](Mesh &mesh, const Mesh::FaceHandle &fh) {
        mesh.property(fph_to, fh) = tfm(mesh.property(fph_from, fh));
    });
}

/*
    Create new face property and MapFacePropertyTo it.
*/
template <typename Mesh, typename F, typename Fn, typename T = std::decay<typename std::result_of<Fn(F)>::type>::type>
inline OpenMesh::FPropHandleT<T> MapFaceProperty(Mesh &mesh, OpenMesh::FPropHandleT<F> fph, Fn tfm) {
    OpenMesh::FPropHandleT<T> fph_to;
    mesh.add_property(fph_to);
    MapVertexPropertyTo(mesh, fph, fph_to, tfm);
    return fph_to;
}

/*
    result = init;
    for each (vertex_handle in mesh.valid_vertices) {
        result = op(result, mesh.vph[vertex_handle]);
    }
*/
template <typename Mesh, typename T, typename Fn, typename R = T>
inline R ReduceVertexProperty(Mesh &mesh, OpenMesh::VPropHandleT<T> vph, R init, Fn op) {
    ForEachVertex(mesh, [&init, &vph, &op](Mesh &mesh, const Mesh::VertexHandle &vh) {
        init = op(init, mesh.property(vph, vh));
    });
    return init;
}

/*
    result = init;
    for each (face_handle in mesh.valid_faces) {
        result = op(result, mesh.fph[face_handle]);
    }
*/
template <typename Mesh, typename T, typename Fn, typename R = T>
inline R ReduceFaceProperty(Mesh &mesh, OpenMesh::FPropHandleT<T> fph, R init, Fn op) {
    ForEachFace(mesh, [&init, &fph, &op](Mesh &mesh, const Mesh::FaceHandle &vh) {
        init = op(init, mesh.property(fph, vh));
    });
    return init;
}

template <typename F, typename T, typename Fn>
inline void ReduceVertexFacePropertyTo(Mesh &mesh, OpenMesh::FPropHandleT<F> fph_from, OpenMesh::VPropHandleT<T> vph_to, const T &init, Fn op) {
    ForEachVertex(mesh, [&fph_from, &vph_to, &init, &op](Mesh &mesh, const Mesh::VertexHandle &vh) {
        mesh.property(vph_to, vh) = init;
        ForEachVertexFaceCCW(mesh, vh, [&vh, &fph_from, &vph_to, &op](Mesh &mesh, const Mesh::FaceHandle &fh) {
            mesh.property(vph_to, vh) = op(mesh.property(vph_to, vh), mesh.property(fph_from, fh));
        });
    });
}

template <typename F, typename T, typename Fn>
inline void ReduceVertexVertexPropertyTo(Mesh &mesh, OpenMesh::VPropHandleT<F> vph_from, OpenMesh::VPropHandleT<T> vph_to, const T &init, Fn op) {
    ForEachVertex(mesh, [&vph_from, &vph_to, &init, &op](Mesh &mesh, const Mesh::VertexHandle &vh) {
        mesh.property(vph_to, vh) = init;
        ForEachVertexVertexCCW(mesh, vh, [&vh, &vph_from, &vph_to, &op](Mesh &mesh, const Mesh::VertexHandle &vh_from) {
            mesh.property(vph_to, vh) = op(mesh.property(vph_to, vh), mesh.property(vph_from, vh_from));
        });
    });
}

template <typename F, typename T, typename Fn>
inline void ReduceFaceVertexPropertyTo(Mesh &mesh, OpenMesh::VPropHandleT<F> vph_from, OpenMesh::FPropHandleT<T> fph_to, const T &init, Fn op) {
    ForEachFace(mesh, [&vph_from, &fph_to, &init, &op](Mesh &mesh, const Mesh::FaceHandle &fh) {
        mesh.property(fph_to, fh) = init;
        ForEachFaceVertexCCW(mesh, fh, [&fh, &vph_from, &fph_to, &op](Mesh &mesh, const Mesh::VertexHandle &vh) {
            mesh.property(fph_to, fh) = op(mesh.property(fph_to, fh), mesh.property(vph_from, vh));
        });
    });
}

template <typename F, typename T, typename Fn>
inline void ReduceFaceFacePropertyTo(Mesh &mesh, OpenMesh::VPropHandleT<F> fph_from, OpenMesh::FPropHandleT<T> fph_to, const T &init, Fn op) {
    ForEachFace(mesh, [&fph_from, &fph_to, &init, &op](Mesh &mesh, const Mesh::FaceHandle &fh) {
        mesh.property(fph_to, fh) = init;
        ForEachFaceFaceCCW(mesh, fh, [&fh, &fph_from, &fph_to, &op](Mesh &mesh, const Mesh::FaceHandle &fh_from) {
            mesh.property(fph_to, fh) = op(mesh.property(fph_to, fh), mesh.property(fph_from, fh_from));
        });
    });
}
