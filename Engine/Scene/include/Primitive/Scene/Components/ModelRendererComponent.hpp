#pragma once

#include <memory>
#include <utility>

namespace primitive
{
    class Model;
    class Material;

    struct ModelRendererComponent
    {
        std::shared_ptr<Model> model;
        std::shared_ptr<Material> material;

        ModelRendererComponent(
            std::shared_ptr<Model> modelValue,
            std::shared_ptr<Material> materialValue)
            : model(std::move(modelValue)),
              material(std::move(materialValue))
        {
        }
    };
}