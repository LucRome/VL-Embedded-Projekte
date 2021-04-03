#pragma once

/**
 * @brief own implementation of printf
 * 
 * @param dst Destination to write to
 * @param end End of Destionation
 * @param fmt Format-String
 * @param ... Additional parameters
 * @return char* the next char that can be written to dst (from fmt) (correct ???)
 */
char* Printf(char* dst, const void* end, const char* fmt, ...);