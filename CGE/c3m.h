/**
 *  This file is part of c3mloader.
 *
 *  c3mloader is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  c3mloader is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with c3mloader.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  For more information and full access to the source code, visit the project
 *  page at <http://code.google.com/p/c3mloader/>.
 */

#ifndef CYBORUS_C3MREADER
#define CYBORUS_C3MREADER


#ifdef __cplusplus
extern "C" {
#endif

#define C3ML_MAJOR_VERSION 1
#define C3ML_MINOR_VERSION 1

#define C3M_NO_ERRORS 0
#define C3M_MISSING_FILE 1
#define C3M_INVALID_HEADER 2
#define C3M_FAILED_ALLOCATION 3
#define C3M_STRUCTURE_ERROR 4
#define C3M_UNSUPPORTED_SPEC 5

    typedef struct {
        float* array;
        unsigned int size;
    } c3mFloatBlock;

    typedef struct {
        unsigned int* array;
        unsigned int size;
    } c3mIndexBlock;

    typedef struct {
        unsigned short* array;
        unsigned int size;
    } c3mShortIndexBlock;

    typedef struct {
        c3mFloatBlock vertices;
        c3mFloatBlock normals;
        c3mFloatBlock colors;
        c3mFloatBlock secondaryColors;
        c3mFloatBlock textureCoordinates;
        c3mIndexBlock indices;
        c3mShortIndexBlock shortIndices;
        char* textureFile;
    } c3mModel;

    extern unsigned int c3mError;
    extern c3mModel* c3mOpen(const char* inFile);
    extern void c3mClose(c3mModel* inModel);

#ifdef __cplusplus
}
#endif

#endif
