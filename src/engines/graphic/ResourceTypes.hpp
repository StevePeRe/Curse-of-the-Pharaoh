#pragma once

#include <engines/graphic/Resource.hpp>
#include <engines/graphic/ResourceManager.hpp>
#include <engines/graphic/RModel.hpp>
#include <engines/graphic/RShader.hpp>
#include <engines/graphic/RTexture.hpp>
#include <engines/graphic/RFont.hpp>
#include <engines/graphic/RAnimation.hpp>
#include <engines/graphic/RSkinModel.hpp>
#include <engines/graphic/RMaterial.hpp>

using ResourceManager_ = ResourceManager<RModel, RTexture, RShader, RFont, RAnimation, RSkinModel, RMaterial>;
