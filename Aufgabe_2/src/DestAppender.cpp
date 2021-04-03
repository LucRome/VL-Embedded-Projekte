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