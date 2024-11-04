struct BoneData
{
    Matrix init;
    Matrix initInvert;
    int childs[2];
};

struct VertexInfo
{
    Vector3 position;
    int boneIds[2];
    int weights[2];
};

struct ModelInfo
{
    int vertexCount;
    int boneCount;
    int indexCount;
    VertexInfo* vertexInfos;
    BoneData* boneInfos;
    int* indeces;
};