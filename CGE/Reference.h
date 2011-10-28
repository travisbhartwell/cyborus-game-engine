#ifndef REFERENCE_H
#define REFERENCE_H

#include <cstdlib>

namespace CGE
{
    template<class T>
    class Reference
    {
        class Container
        {
            public:
                Container(T* inPointer) : mPointer(inPointer), mCount(1)
                {
                }

                inline void Acquire() { ++mCount; }
                inline void Release() { if (!--mCount) delete this; }

                inline T* pointer() { return mPointer; }
                inline const T* pointer () const { return mPointer; }

            private:
                ~Container() { delete mPointer; }

                T* mPointer;
                size_t mCount;
        };

        public:
            Reference(T* inPointer = NULL) : mContainer(NULL)
            {
                if (inPointer) mContainer = new Container(inPointer);
            }

            Reference(const Reference& inReference)
            {
                mContainer = inReference.mContainer;
                if (mContainer) mContainer->Acquire();
            }

            ~Reference()
            {
                if (mContainer) mContainer->Release();
            }

            inline T* operator->() { return mContainer->pointer(); }
            inline const T* operator->() const { return mContainer->pointer(); }

            inline T& operator*() { return *mContainer->pointer(); }
            inline const T& operator*() const { return *mContainer->pointer(); }

            Reference& operator=(const Reference& inReference)
            {
                if (mContainer) mContainer->Release();
                mContainer = inReference.mContainer;
                if (mContainer) mContainer->Acquire();
                return *this;
            }

        private:
            Container* mContainer;
    };
}

#endif
