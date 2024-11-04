Texture2D texture;

int vertexCount = 20;

float vertex[20*7] =
{
    // Positions       BoneIds       Weights
     1,  0,  1,        0, -1,        1.0f,  0.0f,
     1,  0, -1,        0, -1,        1.0f,  0.0f,
    -1,  0, -1,        0, -1,        1.0f,  0.0f,
    -1,  0,  1,        0, -1,        1.0f,  0.0f,
     1,  2,  1,        0,  1,        0.5f,  0.5f,
     1,  2, -1,        0,  1,        0.5f,  0.5f,
    -1,  2, -1,        0,  1,        0.5f,  0.5f,
    -1,  2,  1,        0,  1,        0.5f,  0.5f,
     1,  4,  1,        1, -1,        1.0f,  0.0f,
     1,  4, -1,        1, -1,        1.0f,  0.0f,
    -1,  4, -1,        1, -1,        1.0f,  0.0f,
    -1,  4,  1,        1, -1,        1.0f,  0.0f,
     1,  6,  1,        2,  1,        0.5f,  0.5f,
     1,  6, -1,        2,  1,        0.5f,  0.5f,
    -1,  6, -1,        2,  1,        0.5f,  0.5f,
    -1,  6,  1,        2,  1,        0.5f,  0.5f,
     1,  8,  1,        2, -1,        1.0f,  0.0f,
     1,  8, -1,        2, -1,        1.0f,  0.0f,
    -1,  8, -1,        2, -1,        1.0f,  0.0f,
    -1,  8,  1,        2, -1,        1.0f,  0.0f,
};
int modelIndeces[64]
{
     0,  1,  5,  4,
     1,  2,  6,  5,
     2,  3,  7,  6,
     3,  0,  4,  7,

     4,  5,  9,  8,
     5,  6, 10,  9,
     6,  7, 11, 10,
     7,  4,  8, 11,

     8,  9, 13, 12,
     9, 10, 14, 13,
    10, 11, 15, 14,
    11,  8, 12, 15,

    12, 13, 17, 16,
    13, 14, 18, 17,
    14, 15, 19, 18,
    15, 12, 16, 19,
};
int parentsChildren[6]
{
     1,  2,
     2, -1,
    -1, -1,
};
Matrix bonesInitInvert[3];
Matrix bonesInit[3] =
{
    {
        1,0,0,0,
        0,1,0,0,
        0,0,1,0,
        0,0,0,1,
    },
    {
        1,0,0,0,
        0,1,0,4,
        0,0,1,0,
        0,0,0,1,
    },
    {
        1,0,0,0,
        0,1,0,8,
        0,0,1,0,
        0,0,0,1,
    },
};

void Model1Init()
{
    texture = LoadTexture("models/duno1.png");

    ModelInfo modelInfo = {};

    int vertexCount = 20;
    int boneCount = 3;
    int indexCount = 64;

    modelInfo.vertexCount = vertexCount;
    modelInfo.boneCount = boneCount;
    modelInfo.indexCount = indexCount;

    modelInfo.vertexInfos = new VertexInfo[vertexCount];
    modelInfo.boneInfos = new BoneData[boneCount];
    modelInfo.indeces = new int[indexCount];

    for (int i = 0; i < vertexCount; i++)
    {
        int offset = i*7;

        float x       = vertex[offset+0];
        float y       = vertex[offset+1];
        float z       = vertex[offset+2];
        int boneId1   = vertex[offset+3];
        int boneId2   = vertex[offset+4];
        float weight1 = vertex[offset+5];
        float weight2 = vertex[offset+6];

        VertexInfo vertexInfos = {};
        vertexInfos.position = { x, y, z };
        vertexInfos.boneIds[0] = boneId1;
        vertexInfos.boneIds[1] = boneId2;
        vertexInfos.weights[0] = weight1;
        vertexInfos.weights[1] = weight2;

        modelInfo.vertexInfos[i] = vertexInfos;
    }

    for (int i = 0; i < boneCount; i++)
    {
        // BoneData boneData;
        // boneData
        bonesInitInvert[i] = MatrixInvert(bonesInit[i]);
    }
}