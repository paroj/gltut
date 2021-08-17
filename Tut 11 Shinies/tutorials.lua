
SetupProject("Tut11PhongLighting", "PhongLighting.cpp",
	"data/PCN.vert",
	"data/PN.vert",
	"data/PosTransform.vert",
	"data/UniformColor.frag",
	"data/NoPhong.frag",
	"data/PhongOnly.frag",
	"data/PhongLighting.frag")

SetupProject("Tut11BlinnVsPhongLighting", "BlinnVsPhongLighting.cpp",
	"data/PCN.vert",
	"data/PN.vert",
	"data/PosTransform.vert",
	"data/UniformColor.frag",
	"data/PhongLighting.frag",
	"data/BlinnLighting.frag",
	"data/PhongOnly.frag",
	"data/BlinnOnly.frag")

SetupProject("Tut11GaussianSpecularLighting", "GaussianSpecularLighting.cpp",
	"data/PCN.vert",
	"data/PN.vert",
	"data/PosTransform.vert",
	"data/UniformColor.frag",
	"data/PhongLighting.frag",
	"data/GaussianLighting.frag",
	"data/BlinnLighting.frag",
	"data/PhongOnly.frag",
	"data/GaussianOnly.frag",
	"data/BlinnOnly.frag")

