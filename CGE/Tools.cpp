#include "Tools.h"

#include <cstdlib>
#include <cstdio>
#include <cctype>

namespace CGE
{
    bool caseInsensitiveEquals(const char* inA, const char* inB)
    {
        if (!inA || !inB) return false;

        while (true)
        {
            char a = tolower(*inA);
            char b = tolower(*inB);

            if (a != b)
                return false;
            else if (!a)
                return true;

            ++inA;
            ++inB;
        }
    }

    char* fileToBuffer(const char* inFile)
    {
        FILE *f;

        if (!(f = fopen(inFile, "r"))) return NULL;

        fseek(f, 0, SEEK_END);
        size_t length = ftell(f);

        fseek(f, 0, SEEK_SET);

        char* outBuffer = static_cast<char*>(calloc(length + 1, sizeof(char)));

        if (!outBuffer) return NULL;

        size_t r = fread(outBuffer, sizeof(char), length, f);

        if (!r)
        {
            free(outBuffer);
            return NULL;
        }

        outBuffer[length] = '\0';
        fclose(f);

        return outBuffer;
    }


}
