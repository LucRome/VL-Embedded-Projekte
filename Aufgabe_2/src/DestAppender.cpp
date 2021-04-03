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

bool DestAppender::processSpecifier(const PrintfUtils::SpecifierType specType, void* arg) {
    using namespace PrintfUtils;
    switch (specType)
    {
    case SpecifierType::Binary: {
        
        break;
    }
    case SpecifierType::Char: {

        break;
    }
    case SpecifierType::Hexa: {

        break;
    }
    case SpecifierType::None: {

        break;
    }
    case SpecifierType::SignedInt: {

        break;
    }
    case SpecifierType::SkipFormat: {

        break;
    }
    case SpecifierType::String: {

        break;
    }
    case SpecifierType::UnsignedInt: {

        break;
    }
    default:
        break;
    }
}

void DestAppender::resetDst() {
    dst_current = const_cast<char*>(dst_start);
    *dst_current = '\0';
}

const char* DestAppender::getDst_start() const {
    return dst_start;
}