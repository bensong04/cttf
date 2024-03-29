/**
 * @author Ben Song <benedics@andrew.cmu.edu>
*/

#include <thread>
#include <cstdlib>
#include <iostream>
#include <filesystem>

#include "MultiThreadedTrans.hpp"
#include "ThreadSafeQueue.hpp"
#include "tinytiffwriter.h"

MultiThreadedTrans::MultiThreadedTrans(const wchar_t *czi_fname, const wchar_t *tiff_fname, 
                        std::ostream &prog_log, std::ostream &err_log) : prog_log(prog_log), err_log(err_log)
{
    this->internal_filestream = libCZI::CreateStreamFromFile(czi_fname);
    this->internal_reader = libCZI::CreateCZIReader();
    this->no_threads = UNINITIALIZED;
    this->max_batch_size = UNINITIALIZED;
    this->out_fname = MultiThreadedTrans::w_to_cstring(tiff_fname);
}

std::string MultiThreadedTrans::w_to_cstring(const wchar_t *w) {
    // This performs a naive conversion. It is very bad.
    char *buf = (char *) std::calloc(sizeof(wchar_t), wcslen(w));
    if (!buf) {
        return "";
    }
    for (size_t w_idx = 0; w_idx < wcslen(w); w_idx++) {
        buf[w_idx] = (char) w[w_idx];
    }
    std::string res = buf;
    std::free(buf);
    return res;
}

void MultiThreadedTrans::write_log(std::string msg) {
    this->prog_log << LOGGING_SYM + msg << std::endl;
}

void MultiThreadedTrans::write_err(std::string err) {
    this->err_log << ERROR_SYM + err << std::endl;
}

bool MultiThreadedTrans::configure(size_t threads, size_t max_batch_size_in_tiles) {
    if (threads < 1) {
        this->write_err("Cannot execute run with less than 1 thread");
        return false;
    }
    this->no_threads = threads;
    this->max_batch_size = max_batch_size_in_tiles;
    if (threads == 1) {
        this->write_log("Successfully configured sequential run using 1 thread");
        return true;
    }
    // write successful config to log
    this->write_log("Successfully configured run with " + 
                        std::to_string(threads) + " threads and " +
                        std::to_string(max_batch_size_in_tiles) + 
                        ".");
    return true;
}

bool MultiThreadedTrans::execute_concurrent() {

}

bool MultiThreadedTrans::execute_sequential() {
    using namespace std;
    auto reader = internal_reader;
    this->write_log("Beginning sequential run");
    // Hardcoding constants as a test
    TinyTIFFWriterFile *tiff = TinyTIFFWriter_open(this->out_fname.c_str(), 16, TinyTIFFWriter_UInt, 
                                                    0, 2048, 2048, TinyTIFFWriter_Greyscale);
    if (!tiff) {
        this->write_err("Could not open TIFF file " + this->out_fname + "!");
    }
    reader->Open(this->internal_filestream);
    if (!reader) {
        this->write_err("Could not open CZI file!");
        TinyTIFFWriter_close(tiff);
    }
    int no_sbs = reader->GetStatistics().subBlockCount;
    for (int sb_idx = 0; sb_idx < no_sbs; sb_idx++) {
        auto sblock = reader->ReadSubBlock(sb_idx);
        auto bitmap = sblock->CreateBitmap();
        auto data = bitmap->Lock();
        TinyTIFFWriter_writeImage(tiff, data.ptrDataRoi);
        bitmap->Unlock();
    }
    TinyTIFFWriter_close(tiff);
    return true;
}

bool MultiThreadedTrans::execute() {
    if (this->no_threads == 1) {
        this->write_log("One thread");
        this->execute_sequential();
    } else {
        this->write_log("Not one thread");
    }
    return true;
}