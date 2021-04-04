#include "DestAppender.h"

#include <climits>

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

const char* DestAppender::getDst_current() const {
    return dst_current;
}

void DestAppender::setDstToPos(const char* pos) {
    if(pos && (pos >= dst_start) && (pos <= end)) {
        dst_current = const_cast<char*>(pos);
        *dst_current = '\0'; 
    }
}


////////////////////////////////
// Processfkt. for the Specifiers
////////////////////////////////

bool DestAppender::process_c(const int* arg) {
    const char* safePos = getDst_current();
    if(arg == nullptr) {
        return false;
    }
    // else //
    if (appendCharToDest(*arg)) {
        return true;
    } else {
        setDstToPos(safePos);
        return false;
    }
}

bool DestAppender::process_d(signed int arg) {
    const char* safePos = getDst_current();
    bool success = true;
    unsigned int abs;
    if(arg < 0) {
        success = appendCharToDest('-');
        abs = arg * (-1);
    } else {
        abs = arg;
    }

    if(!success) {
        setDstToPos(safePos);
    }
    return success && process_u(abs);
}

bool DestAppender::process_u(unsigned int arg) {
    const char* safePos = getDst_current();
    bool success = true;
    if(success) {
        const int buffer_length = 11;
        char buffer[buffer_length] = { 0 };
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

    if(!success) {
        setDstToPos(safePos);
    }
    return success;
}

bool DestAppender::process_s(char* arg) {
    const char* safePos = getDst_current();
    if(arg == nullptr) {
        return false;
    }
    // else //
    bool success;
    do {
        success = appendCharToDest(*arg);
        arg++;
    } while(success && !PrintfUtils::EOS(arg));
    
    if(!success) {
        setDstToPos(safePos);
    }
    return success;
}

const int int_length = 32; 

bool DestAppender::process_b(signed int arg) {
    const char* safePos = getDst_current();
    unsigned int uInt;
    //Handling of negative numbers
    if(arg < 0) {
        uInt = UINT_MAX + 1 + arg; // (= UINT_MAX + 1 - |arg|)
    } else {
        uInt = arg;
    }

    // write bits to out with the help of logical operators
    unsigned int mask = 1 << (int_length - 1); //highest Bit of int

    //skip 0 at front:
    while (mask > 0 && (uInt & mask) == 0) {
        mask = mask >> 1;
    }

    bool success = true;
    // write 0/1 to dst
    while (success && (mask > 0)) {
        if((uInt & mask) > 0) { //Bit set -> write 1
            success = appendCharToDest('1');
        } else { //write 0
            success = appendCharToDest('0');
        }
        mask = mask >> 1; // =: x/2
    }
    
    if(!success) {
        setDstToPos(safePos);
    }
    return success;
}

const char hexSymbols[] = { '0','1','2','3',
                            '4','5','6','7',
                            '8','9','A','B',
                            'C','D','E','F'
                        };

const int hexWidth = 4;

bool DestAppender::process_x(signed int arg) {
    const char* safePos = getDst_current();
    unsigned int uInt;
    //handle negative nr.
    if(arg < 0) {
        uInt = UINT_MAX + 1 + arg; // (= UINT_MAX + 1 - |arg|)
    } else {
        uInt = arg;
    }

    // write bits to out with the help of logical operators
    unsigned int mask = 0xF << (int_length - hexWidth); //highest 4Bits of int

    int rshifts = int_length;
    //skip 0 at front:
    while (mask > 0 && (uInt & mask) == 0) {
        mask = mask >> hexWidth;
        rshifts -= hexWidth;
    }

    bool success = true;

    // write hexSymbol to dst
    while (success && (mask > 0)) {
        rshifts -= hexWidth;
        int nr = (uInt & mask) >> rshifts;
        success = appendCharToDest(hexSymbols[nr]);
        mask = mask >> hexWidth;
    }
    
    if(!success) {
        setDstToPos(safePos);
    }
    return success;

}