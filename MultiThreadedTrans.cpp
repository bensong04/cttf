/**
 * @author Ben Song <benedics@andrew.cmu.edu>
*/

#include <thread>

#include "MultiThreadedTrans.hpp"
#include "ThreadSafeQueue.hpp"

MultiThreadedTrans::MultiThreadedTrans(const wchar_t *czi_fname, const wchar_t *tiff_fname, 
                        std::ostream &prog_log, std::ostream &err_log) : prog_log(prog_log), err_log(err_log)
{
    this->internal_filestream = libCZI::CreateStreamFromFile(czi_fname);
    this->internal_reader = libCZI::CreateCZIReader();
    this->no_threads = UNINITIALIZED;
    this->max_batch_size = UNINITIALIZED;
}

void MultiThreadedTrans::write_log(std::string msg) {
    this->prog_log << LOGGING_SYM + msg << std::endl;
}

void MultiThreadedTrans::write_err(std::string err) {
    this->err_log << ERROR_SYM + err << std::endl;
}

bool MultiThreadedTrans::configure(size_t threads, size_t max_batch_size_in_tiles) {
    if (threads < 2) {
        this->write_err("Cannot execute run with less than 2 threads");
        return false;
    }
    this->no_threads = threads;
    this->max_batch_size = max_batch_size_in_tiles;
    // write successful config to log
    this->write_log("Successfully configured run with " + 
                        std::to_string(threads) + " threads and " +
                        std::to_string(max_batch_size_in_tiles) + 
                        ".");
    return true;
}

bool MultiThreadedTrans::execute() {
    return true;
}