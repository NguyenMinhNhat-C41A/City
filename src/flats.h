#pragma once
#include <string>
#include <vector>
#include <map>
#include "../wolf/wolf.h"

struct Vertex
{
    GLfloat x, y, z, u, v;
};

class Flats
{
public:
    Flats();
    virtual ~Flats();

    void update(const float dt);
    void render(const glm::mat4 &mProj, const glm::mat4 &mView);

    void addTexture(const std::string tex, const int mapIndex);

    void addFlat(const float width, const float height, const glm::vec3 coords, const float angle, const glm::vec3 axes);
    void addFlat(const float width, const float height, const glm::vec3 coords, const glm::vec3 angles);
    void addHalfFlat(const float width, const float height, const glm::vec3 coords, const glm::vec3 angles, const int norm);
    void addFlatTextureFit(const float width, const float height, const glm::vec3 coords, const float angle, const glm::vec3 axes);
    void addFlatTextureFitHeight(const float width, const float height, const glm::vec3 coords, const float angle, const glm::vec3 axes);
    void addFlatTextureFitWidth(const float width, const float height, const glm::vec3 coords, const float angle, const glm::vec3 axes);

    void endInit();
    void endInitialisation();

    void beginConstructingVertices();
    void endConstructingVertices();

private:
    wolf::VertexBuffer *m_pVB = nullptr;
    wolf::VertexDeclaration *m_pDecl = nullptr;
    wolf::Program *m_pProgram = nullptr;

    std::vector<Vertex> vertices;
    std::vector<wolf::Texture *> textures;
    std::vector<int> texIndices;

    bool isConstructingVertices = false;
};