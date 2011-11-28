#ifndef TOOLS_H
#define TOOLS_H
#define PI 3.141592653589793238462643383
#define TO_RADIANS(n)((n) * PI / 180.0)
namespace CGE
{
    bool caseInsensitiveEquals(const char* inA, const char* inB);

    char* fileToBuffer(const char* inFile);

    template<class T>
    T linearInterpolate(const T& inMin, const T& inMax, double inT)
    {
        return (inMin * (1.0 - inT)) + (inMax * inT);
    }

    template<typename T>
    inline void readBytes(void* inData, T& outResult)
    {
        outResult = *reinterpret_cast<T*>(inData);
    }
}

#endif

