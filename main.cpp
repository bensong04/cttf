#include <stdlib.h>
#include "libCZI.h"
#include "MultiThreadedTrans.hpp"
#include "CTTFUtils.hpp"

int main(int argc, char** argv) {
    std::string f_in = argv[1];
    std::string f_out = argv[2];
    std::wstring wide_f_in(f_in.begin(), f_in.end());
    return !TSVUtils::write_to_file(wide_f_in, f_out);
}