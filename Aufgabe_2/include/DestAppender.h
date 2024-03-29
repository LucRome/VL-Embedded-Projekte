#pragma once

#include "PrintfUtils.h"

/**
 * @brief abstraction for the Destionation
 * (handles the Writing of chars to dst)
 */
class DestAppender
{
public:
    /**
     * @brief Construct a new Dest Appender object
     * 
     * @param dst Destination
     * @param end End of Destination
     */
    DestAppender(char *dst, const void *end);

    /**
     * @brief appends a single char to the dst
     * 
     * @param charToAppend 
     * @return true char is appended
     * @return false char can't be appended
     */
    bool appendCharToDest(const char &charToAppend);
    /**
     * @brief to catch errors (e.g. in constructor) 
     */
    bool blocked;
    /**
     * @brief resets current position to start of dst
     * 
     */
    void resetDst();
    /**
     * @brief Get the pointer to the start of dst
     */
    const char *getDst_start() const;
    const char *getDst_current() const;

    void setDstToPos(const char *pos);

    /////////////// Functions for specifiers /////////////////
    bool process_c(const int *arg);
    bool process_d(signed int arg);
    bool process_u(unsigned int arg);
    bool process_s(char *arg);
    bool process_b(signed int arg);
    bool process_x(signed int arg);

private:
    /**
     * @brief start of dst
     * 
     */
    const char *dst_start;
    /**
     * @brief always points to current '\0' of dst
     * 
     */
    char *dst_current;
    const void *end;
};