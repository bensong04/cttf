#pragma once
#include <stdlib.h>
#include <ostream>
#include "libCZI.h"

#define LOGGING_SYM "[LOG] "
#define ERROR_SYM "[ERROR] "
#define UNINITIALIZED 0

class MultiThreadedTrans {
    private:
        std::shared_ptr<libCZI::IStream> internal_filestream;
        std::shared_ptr<libCZI::ICZIReader> internal_reader;
        size_t no_threads;
        size_t max_batch_size;
        std::ostream &prog_log;
        std::ostream &err_log;
        void write_log(std::string msg);
        void write_err(std::string err);
        bool execute_concurrent();
        bool execute_sequential();
    public: 
        /** 
         * @brief Constructor for a multi-threaded CZI -> tiff converter 
         * 
         * @param czi_fname
         * @param tiff_fname
         */
        MultiThreadedTrans(const wchar_t *czi_fname, const wchar_t *tiff_fname, 
                                    std::ostream &prog_log, std::ostream &err_log);
        /**
         * @brief Configures the converter for a particular run.
         * 
         * At most max_batch_size_in_tiles tiles will be loaded into memory at once.
         * The distribution of tiles across threads is not guaranteed.
         * One thread is reserved for reading chunks from the czi file. As such, 
         * the number of threads should be at least 2 if any work is to be done.
         * 
         * @param threads
         * @param max_batch_size_in_tiles
         * @pre threads > 2
         * @return false if configuration is invalid, true otherwise
        */
        bool configure(size_t threads, size_t max_batch_size_in_tiles);
        /**
         * @brief
         * 
         * @returns false if unable to finish, true if successful.
        */
        bool execute();
};