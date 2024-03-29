#include <cstdlib>
#include <wchar.h>
#include "libCZI.h"
#include "MultiThreadedTrans.hpp"
#include "CTTFUtils.hpp"

int main(int argc, char** argv) {
    std::string f_in = argv[1];
    // std::string f_out = argv[2];
    std::wstring wide_f_in(f_in.begin(), f_in.end());
    wchar_t *filler = L"test.tif";
    auto trans = MultiThreadedTrans(
        wide_f_in.data(), filler, std::cout, std::cerr
    );
    trans.configure(1, 1);
    trans.execute();
}