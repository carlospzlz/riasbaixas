#ifndef MODELS_H
#define MODELS_H

#include <vector>
#include <string>
#include <ngl/Obj.h>


/***********************************
 * N_MODELS is the number of models
 * SPEEDBOAT mesh stored in index 0
 *
 ***********************************/
#define N_MODELS 1
#define SPEEDBOAT 0


class Models
{

private:
    std::vector<ngl::Obj*> m_models;

public:
    Models() {};
    ~Models();
    void addModel(const int _index, const std::string _modelPath);
    void addModel(const int _index, const std::string _meshPath, const std::string _texturePath);
    ngl::Obj *getModel(const int _index);
    std::string getModelName(const int _index);
    void draw(const int _index);

};


#endif // MODELS_H
