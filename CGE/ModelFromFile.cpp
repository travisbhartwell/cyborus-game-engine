#include "ModelFromFile.h"

#include <iostream>

using namespace std;
using namespace CGE;

namespace CGE
{
    /**
    *   Constructor to load a resource on construction
    */
    ModelFromFile::ModelFromFile(const char* inFile)
    {
        mVBO.addField(0, 3);
        mVBO.addField(1, 2);

        string s(inFile);
        s = s.substr(s.rfind('.') + 1);

        if (s == "c3m")
        {
            loadC3M(inFile);
        }
        else
        {
            //error
        }
    }

    ModelFromFile::~ModelFromFile()
    {
    }

    void ModelFromFile::loadC3M(const char* inFile)
    {
        string file = "assets/models/";
        file += inFile;
        c3mModel* c3m = c3mOpen(file.c_str());

        if (c3mError)
        {
            cerr << "error!" << endl;
            return;
        }

        bool useColors = false;
        bool useTexture = false;
        int clusterSize = 2;

        int size = c3m->vertices.size / 3;
        GLfloat* data = c3m->vertices.array;

        size = c3m->normals.size / 3;
        data = c3m->normals.array;

        size = c3m->colors.size / 4;

        //somethings wrong, breaking colors
        //size = 0;
        if (size > 0)
        {
            ++clusterSize;
            useColors = true;
        }


        size = c3m->textureCoordinates.size / 2;
        if (size > 0)
        {
            ++clusterSize;
            useTexture = true;

            string texFile = "assets/images/models/";
            texFile += c3m->textureFile;
            cerr << texFile << endl;

            mTexture.loadImage(texFile.c_str());
        }
        else
        {
            cerr << "error, no texture" << endl;
        }

        if (useColors)
        {
        }

        if (useTexture)
        {
        }

        size_t numVertices = c3m->vertices.size / 3;
        GLfloat* buffer = (GLfloat*)malloc(numVertices * mVBO.vertexSize());
        GLfloat* b = buffer;

        for (size_t i = 0; i < numVertices; ++i)
        {
            const size_t i3 = i * 3;

            *b++ = c3m->vertices.array[i3 + 0];
            *b++ = c3m->vertices.array[i3 + 1];
            *b++ = c3m->vertices.array[i3 + 2];

            const size_t i2 = i * 2;

            *b++ = c3m->textureCoordinates.array[i2 + 0];
            *b++ = c3m->textureCoordinates.array[i2 + 1];
        }

        mVBO.loadData(buffer, numVertices);
        free(buffer);

        size = c3m->indices.size / 3;
        GLuint* indices = c3m->indices.array;
        //mVBO.loadIndexArray(GL_TRIANGLES, size, indices);
    //    CGE::IndexVBO* index = new IndexVBO();
    //    index->loadData(indices, size);
        mIVBO.loadData(indices, size, 3);
        //mClusterVBO.mount(mIVBO);

        c3mClose(c3m);
    }

    void ModelFromFile::display()
    {
        mTexture.bind();
        mVBO.display(mIVBO);
    }
}
