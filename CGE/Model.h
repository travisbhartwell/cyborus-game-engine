#ifndef MODEL_H
#define MODEL_H

namespace CGE
{
    class Model
    {
        public:
            Model() {}
            virtual ~Model() {}

            virtual void display() = 0;
    };
}

#endif
