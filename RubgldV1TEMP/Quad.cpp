#include "Quad.h"

vertexDataStream LoadQuad() {
	vertexDataStream vdata = vertexDataStream();

	GLfloat v[] = {
		-1,-1,0,
		-1,1,0,
		1,1,0,
		1,-1,0,
	};

	GLfloat u[] = {
		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f
	};

	GLuint i[] = {
		0, 2, 1,
		0, 3, 2
	};

	std::vector <GLfloat> verts(v, v + sizeof(v) / sizeof(GLfloat));
	std::vector <GLuint> ind(i, i + sizeof(i) / sizeof(GLuint));
	std::vector <GLfloat> uvs(u, u + sizeof(u) / sizeof(GLfloat));

	vdata.vertices = verts;
	vdata.indices = ind;
	vdata.uvs = uvs;

	return vdata;
}
