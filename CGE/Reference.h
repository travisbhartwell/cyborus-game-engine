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

                inline void acquire() { ++mCount; }
                inline void release() { if (!--mCount) delete this; }

                inline T* pointer() { return mPointer; }
                inline const T* pointer () const { return mPointer; }

            private:
                inline ~Container() { delete mPointer; }

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
                if (mContainer) mContainer->acquire();
            }

            inline ~Reference()
            {
                if (mContainer) mContainer->release();
            }

            inline bool isNull() { return !mContainer; }

            inline T* operator->() { return mContainer->pointer(); }
            inline const T* operator->() const { return mContainer->pointer(); }

            inline T& operator*() { return *mContainer->pointer(); }
            inline const T& operator*() const { return *mContainer->pointer(); }

            Reference& operator=(T* inPointer)
            {
                if (mContainer) mContainer->release();
                mContainer = inPointer ? new Container(inPointer) : NULL;
                return *this;
            }

            Reference& operator=(const Reference& inReference)
            {
                if (mContainer) mContainer->release();
                mContainer = inReference.mContainer;
                if (mContainer) mContainer->acquire();
                return *this;
            }

            inline bool operator==(const Reference& inReference) const
            {
                return this == &inReference
                    || mContainer == inReference.mContainer;
            }

            inline bool operator!=(const Reference& inReference) const
            {
                return this != &inReference
                    && mContainer != inReference.mContainer;
            }

            inline bool operator==(const T* inPointer) const
            {
                return mContainer && mContainer->pointer() == inPointer;
            }

            inline bool operator!=(const T* inPointer) const
            {
                return !mContainer || mContainer->pointer() != inPointer;
            }

        private:
            Container* mContainer;
    };
}

#endif
