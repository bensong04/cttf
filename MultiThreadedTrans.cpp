#include "MultiThreadedTrans.hpp"

MultiThreadedTrans::MultiThreadedTrans(const wchar_t *czi_fname, const wchar_t *tiff_fname) {
    std::shared_ptr<libCZI::IStream> internal_filestream;
    std::shared_ptr<libCZI::ICZIReader> internal_reader;
}

void MultiThreadedTrans::configure(size_t threads, size_t max_batch_size_in_tiles) {

}

bool MultiThreadedTrans::execute() {

}