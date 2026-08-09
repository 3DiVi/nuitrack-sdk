// Copyright 3DiVi 2025, Inc. All Rights Reserved.
#pragma once

#include "nuitrack/cpp/ObjectData.h"

namespace tdv { namespace nuitrack {

class RGBMark : public ObjectData<RGBMark>
{
public:
    /**
     * @brief Get orientation of marker
     * @return true for succesful
     */
    virtual bool getRotationMat(float* mat, int id) const    = 0;
    virtual bool getTranslationMat(float* mat, int id) const = 0;
};

}}
