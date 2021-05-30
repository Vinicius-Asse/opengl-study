#include<core/mesh.hpp>

Mesh::Mesh(GLint indices[], unsigned int _indicesCount, Vertex *vertex, unsigned int vertexCount, Shader *shader) {

    indicesCount = _indicesCount;
    
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    std::cout << "[" << std::to_string(VBO) << "] * Mesh Buffer Created * " << std::endl;
    
    bind();
    shader->enable();

    // Setting Up Data Buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertexCount, vertex, GL_STATIC_DRAW);

    // Setting Up Index Buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLint) * indicesCount, indices, GL_STATIC_DRAW);

    // Setting Positions Attribute
    addAttribute(GL_FLOAT, 3);

    // Setting Collor Attribute
    addAttribute(GL_FLOAT, 3);

    unbind();
}
 
Mesh::~Mesh() {
    std::cout << "[" << std::to_string(VBO) << "] ~ Deleting Mesh Data" << std::endl;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

void Mesh::draw() {
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indicesCount, GL_UNSIGNED_INT, 0);
}

void Mesh::bind() {
    std::cout << "[" << std::to_string(VBO) << "] Mesh Buffer Binded" << std::endl;
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
}

void Mesh::unbind() {
    std::cout << "[" << std::to_string(VBO) << "] Mesh Buffer Unbinded" << std::endl;
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::addAttribute(GLenum type, int count, bool normalized)
{
    glVertexAttribPointer(currAttr, count, type, normalized? GL_FALSE : GL_TRUE, sizeof(Vertex), (void*) nxtAttr);
    glEnableVertexAttribArray(currAttr);

    nxtAttr += sizeof(float) * count;
    currAttr++;
}