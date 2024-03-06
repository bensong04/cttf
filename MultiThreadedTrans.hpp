#pragma once
#include <stdlib.h>
#include "libCZI.h"

class MultiThreadedTrans {
    private:
        std::shared_ptr<libCZI::IStream> internal_filestream;
        std::shared_ptr<libCZI::ICZIReader> internal_reader;
    public: 
        /** 
         * @brief Constructor for a multi-threaded CZI -> tiff converter 
         * 
         * @param czi_fname
         * @param tiff_fname
         */
        MultiThreadedTrans(const wchar_t *czi_fname, const wchar_t *tiff_fname);
        /**
         * @brief Configures the converter for a particular run
        */
        void configure(size_t threads, size_t max_batch_size_in_tiles);
        /**
         * @brief
         * 
         * @returns false if unable to finish, true if successful.
        */
        bool execute();
};