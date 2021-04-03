#include "DestAppender.h"

DestAppender::DestAppender(char* dst, const void* end) 
    :blocked(false)
    ,dst_start(dst)
    ,dst_current(dst)
    ,end(end)
{
    if(!dst || !end) {
        blocked = true;
    }
}

bool DestAppender::appendCharToDest(const char& charToAppend) {
    //check if enough space for char + '\0'
    if(blocked || (dst_current + 1 > end)) {
        return false;
    }
    else
    {
        *dst_current = charToAppend;
        *(dst_current + 1) = '\0';
        dst_current++;

        return true;
    }
}

void DestAppender::resetDst() {
    dst_current = const_cast<char*>(dst_start);
    *dst_current = '\0';
}

const char* DestAppender::getDst_start() const {
    return dst_start;
}

////////////////////////////////
// Processfkt. for the Specifiers
////////////////////////////////

bool DestAppender::process_c(const int* arg) {
    if(arg == nullptr) {
        return false;
    }
    // else //
    return appendCharToDest(*arg);
}

bool DestAppender::process_d(signed int arg) {
    bool success = true;

    if(arg < 0) {
        success = appendCharToDest('-');
        arg *= (-1);
    }
    if(success) {
        const int buffer_length = 10;
        char buffer[buffer_length] = {0};
        int i = 0;

        //put arg in char-buffer
        while(success && arg > 0) {
            int nr = arg % 10;
            buffer[i] = nr;
            arg /= 10; 
            i++;       
        }

        //skip front 0
        i = buffer_length - 1;
        while(buffer[i] == 0) {
            i--;
        }

        //write rest to dest
        while(success && i >= 0) {
            success = appendCharToDest(buffer[i] + '0');
            i--;
        }
    }
    return success;
}