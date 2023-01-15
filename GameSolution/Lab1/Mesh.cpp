#include "Mesh.h"
#include <vector>

void Mesh::init(Vertex* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
	IndexedModel model;

	// Set vertices
	for (unsigned int i = 0; i < numVertices; i++)
	{
		model.positions.push_back(*vertices[i].GetPos());
		model.texCoords.push_back(*vertices[i].GetTexCoord());
		model.normals.push_back(*vertices[i].GetNormal());
	}
	// Set indices
	for (unsigned int i = 0; i < numIndices; i++)
		model.indices.push_back(indices[i]);

	// Initialise
	initModel(model);
}

void Mesh::initModel(const IndexedModel& model)
{
	// Set draw count
	drawCount = model.indices.size();

	// Generate a vertex array and store it in the VAO
	glGenVertexArrays(1, &vertexArrayObject);
	// Bind the VAO (any operation that works on a VAO will work on our bound VAO - binding)
	glBindVertexArray(vertexArrayObject);

	// Generate our buffers based of our array of data/buffers - GLuint vertexArrayBuffers[NUM_BUFFERS];
	glGenBuffers(NUM_BUFFERS, vertexArrayBuffers);

	// Tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[POSITION_VERTEXBUFFER]);
	// Move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU (determined by type)
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.positions[0]), &model.positions[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[TEXCOORD_VB]); 
	// Move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU
	glBufferData(GL_ARRAY_BUFFER, model.positions.size() * sizeof(model.texCoords[0]), &model.texCoords[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, vertexArrayBuffers[NORMAL_VB]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(model.normals[0]) * model.normals.size(), &model.normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	// Tell opengl what type of data the buffer is (GL_ARRAY_BUFFER), and pass the data
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertexArrayBuffers[INDEX_VB]);
	// Move the data to the GPU - type of data, size of data, starting address (pointer) of data, where do we store the data on the GPU
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, model.indices.size() * sizeof(model.indices[0]), &model.indices[0], GL_STATIC_DRAW);

	// Unbind our VAO
	glBindVertexArray(0);
}

Mesh::Mesh()
{
	// Reset draw count
	drawCount = NULL;
}

void Mesh::loadModel(const std::string& filename)
{
	// Load model
	IndexedModel model = OBJModel(filename).ToIndexedModel();
	// Initialise model
	initModel(model);
	Sphere meshSphere();
}

Mesh::~Mesh()
{
	// Delete arrays
	glDeleteVertexArrays(1, &vertexArrayObject);
}

void Mesh::draw()
{
	// Bind vertices
	glBindVertexArray(vertexArrayObject);
	// Draw elements
	glDrawElements(GL_TRIANGLES, drawCount, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
}

void Mesh::updateSphereData(glm::vec3 pos, float radius)
{
	// Update position
	meshSphere.SetPos(pos);
	// Update radius
	meshSphere.SetRadius(radius);
}