//
// Created by vladl on 06/07/2020.
//

#include "Array.h"

[[nodiscard]] const char* EngineUtility::EngineArrayOutOfBounds::what() const noexcept {
    return "Access of memory outside array bounds";
}

