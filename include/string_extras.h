/* ================================== *\
 @file     string_extras.h
 @project  string
 @author   moosm
 @date     11/20/2025
*\ ================================== */


#ifndef STRING_STRING_EXTRAS_H
#define STRING_STRING_EXTRAS_H
//////////////////////////////////////
// string extras declaration
//////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "string.h"

// ------------------------------------
// output character array
// ------------------------------------
void string_output_ca(
    FILE* stream,       // file to output to -> stdin (can be null)
    const char* ca,     // char array
    int size,           // char array size
    const char* c,      // spacing string -> ", " / " " (can be null)
    int as_char         // as char or as int -> ['h', 'e', 'l', 'l', 'o'] /
    );

void string_output_pretty(
    FILE* stream,       // file to output to -> stdin (can be null)
    string_t s,         // string to output
    int as_char         // as char or as int -> ['h', 'e', 'l', 'l', 'o'] /
    );


#ifdef STRING_EXTRAS_IMPLEMENTATION
//////////////////////////////////////
// string extras implementations
//////////////////////////////////////

void string_output_ca(FILE* stream, const char* ca, const int size, const char* c, const int as_char)
{
    if (stream == NULL) stream = stdout;
    if (c == NULL) c = ", ";
    if (ca == NULL) return;

    for (int i = 0; i < size; i++)
    {
        if (as_char != 1) fprintf(stream,"%d", (int)ca[i]);
        if (as_char == 1)
        {
            if (isprint((unsigned char)ca[i]))
            {
                fprintf(stream,"'%c'", ca[i]);
            } else
            {
                fprintf(stream,"0x%02X", (unsigned char)ca[i]);
            }
        }
        if (i != size - 1) fprintf(stream,"%s",c);
    }
}

void string_output_pretty(FILE* stream, const string_t s, const int as_char)
{
    if (stream == NULL) stream = stdout;
    printf("{\n");
    printf("    .data= [");
    string_output_ca(stream, s.data, s.capacity, ", ", 1);
    printf("]\n");
    printf("    .size= %d\n",s.size);
    printf("    .capacity= %d\n",s.capacity);
    printf("}\n");
}

#endif


#endif //STRING_STRING_EXTRAS_H