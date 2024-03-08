#pragma once

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <memory>
#include "libCZI.h"

namespace TSVUtils {
    bool write_to_file(std::wstring in_fname, std::string out_fname);
}