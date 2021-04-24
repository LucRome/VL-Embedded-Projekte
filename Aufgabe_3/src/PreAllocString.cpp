#include "PreAllocString.h"

#include <stdio.h>
#include <iostream>
// size: size without \0
// PreAllocString::PreAllocString(int N, const size_t& size, char* buffer) 
//     :buffer_start(buffer), buffer_end(buffer + size + 1), buffer_cur(buffer)
//     ,size(size)
// {
//     // check if buffer Pointer valid
//     if(!buffer) {
//         return;
//     }
//     // else
//     *buffer_cur = '\0';
// }

// bool PreAllocString<k>::writeChar(const char& chr) {
//     printf("write char: %c \n", chr);
//     if(buffer_cur == buffer_end || GetLength() + 1 > size) {
//         return false;
//     } 
//     // Else
//     *buffer_cur = chr;
//     ++buffer_cur;
//     *buffer_cur='\0';

//     return true;
// }

// PreAllocString::operator const char *() const {
//     return buffer_start;
// }

// PreAllocString::operator const void *() const {
//     return buffer_start;
// }

// const char& PreAllocString::operator[] (const int idx) {
//     size_t idx_d = idx;
//     std::cout << "operator[idx], idx=" << idx_d << std::endl;
//     if(idx_d > this->size - 1) {
//         // Error -> return '\0'
//         return *buffer_cur;
//     }
//     // else
//     return *(buffer_start + idx_d);
// }

// size_t PreAllocString::GetLength() const {
//     return (buffer_cur - buffer_start);
// }

// constexpr size_t SizeOf() {
//     return size;
// }

// void PreAllocString::Empty() {
//     // Empty string
//     while(buffer_cur > buffer_start) {
//         *buffer_cur = '\0';
//         buffer_cur--;
//         printf("buffer empty: size = %i", GetLength());
//     }
//     // also reset start
//     *buffer_cur = '\0';
// }

// PreAllocString& PreAllocString::operator=(char rhs) {
//     this->Empty();
//     if(!writeChar(rhs)) {
//         //Error
//         this->Empty();
//     }
//     return *this;
// }

// PreAllocString& PreAllocString::operator=(const char* rhs) {
//     this->Empty();
//     if(rhs)
//     {
//         while(*rhs != '\0') {
//             if(!writeChar(*rhs)) {
//                 // Error
//                 this->Empty();
//                 return *this;
//             }
//             rhs++;
//         }
//     }
//     return *this;
// }

// PreAllocString& PreAllocString::operator=(char * const rhs) {
//     this->Empty();
//     if(rhs)
//     {   
//         const char* rhs_mut = const_cast<const char*>(rhs);
//         this->operator=(rhs_mut);
//     }
//     return *this;
// }

// PreAllocString& PreAllocString::operator+=(char rhs) {
//     if(!writeChar(rhs)) {
//         //Error
//         this->Empty();
//     }
//     // else
//     return *this;
// }

// PreAllocString& PreAllocString::operator+=(char const* rhs) {
//     if(!rhs) {
//         //error
//         printf("Empty Pointer!! \n");
//         this->Empty();
//         return *this;
//     }
//     // Else
//     const char* rhs_mov = const_cast<const char*>(rhs);
//     while (*rhs_mov != '\0') {
//         if(!writeChar(*rhs_mov)) {
//             // Error
//             this->Empty();
//             return *this;
//         }
//         rhs_mov++;
//     }
//     return *this;
// }

// void PreAllocString::AddFormat(const char*, ...) {
//     // TODO
// }

// void PreAllocString::AddWhiteSpace() {
//     // no possibility to communicate Error -> no need to catch
//     writeChar(' ');
// }