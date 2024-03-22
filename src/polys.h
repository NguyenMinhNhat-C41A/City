#pragma once
#include <string>
#include <vector>
#include <map>
#include "../wolf/wolf.h"
#include "lighting.h"

struct PolyVertex
{
    GLfloat x, y, z, u, v, nx, ny, nz;
};

class Polys
{
public:
    Polys();
    virtual ~Polys();

    void update(const float dt);
    void render(const glm::mat4 &mProj, const glm::mat4 &mView);
    void render(const glm::mat4 &mProj, const glm::mat4 &mView, const glm::vec3 &lightDir, const glm::vec3 &lightCol, const glm::vec3 &lightAmbCol);
    void render(const glm::mat4 &mProj, const glm::mat4 &mView, Lighting *lighting);
    void endInitialisation();
    void addTexture(const std::string tex, const int mapIndex);

    void addPoly04(const float width, const float height, const glm::vec3 coords, const glm::vec3 angles);
    void addPoly03(const float width, const float height, const glm::vec3 coords, const glm::vec3 angles, const int normSide, const int slantSide);

    void beginConstructingVertices();
    void endConstructingVertices();

private:
    wolf::VertexBuffer *m_pVB = nullptr;
    wolf::VertexDeclaration *m_pDecl = nullptr;
    wolf::Program *m_pProgram = nullptr;

    std::vector<PolyVertex> vertices;
    std::vector<wolf::Texture *> textures;
    std::vector<int> texIndices;

    bool isConstructingVertices = false;
    void addLighting(const glm::vec3 &lightDiffDir, const glm::vec3 &lightDiffCol);
};