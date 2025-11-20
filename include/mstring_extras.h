/* ================================== *\
 @file     mstring_extras.h
 @project  mstring
 @author   moosm
 @date     11/20/2025
*\ ================================== */


#ifndef STRING_STRING_EXTRAS_H
#define STRING_STRING_EXTRAS_H
//////////////////////////////////////
// mstring extras declaration
//////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "mstring.h"

// ------------------------------------
// output character array
// ------------------------------------
void mstring_output_ca(
    FILE* stream,       // file to output to -> stdin (can be null)
    const char* ca,     // char array
    int size,           // char array size
    const char* c,      // spacing string -> ", " / " " (can be null)
    int as_char         // as char or as int -> ['h', 'e', 'l', 'l', 'o', 0x00] / [104, 101, 108, 108, 111, 0]
    );

// ------------------------------------
// pretty print output
// ------------------------------------
void mstring_output_pretty(
    FILE* stream,       // file to output to -> stdin (can be null)
    mstring s          // mstring to output
    );

//#define MSTRING_EXTRAS_IMPLEMENTATION
#ifdef MSTRING_EXTRAS_IMPLEMENTATION
//////////////////////////////////////
// string extras implementations
//////////////////////////////////////

void mstring_output_ca(FILE* stream, const char* ca, const int size, const char* c, const int as_char)
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

void mstring_output_pretty(FILE* stream, mstring s)
{
    if (stream == NULL) stream = stdout;
    fprintf(stream,"{\n");
    if (s != NULL)
    {
        fprintf(stream,"    .data= %p [", mstring_get(s));
        mstring_output_ca(stream, mstring_get(s), mstring_capacity(s), ", ", 1);
        fprintf(stream,"]\n");
        fprintf(stream,"    .size= %d\n",mstring_size(s));
        fprintf(stream,"    .capacity= %d\n",mstring_capacity(s));
    } else
    {
        fprintf(stream,"    [null]\n");
    }
    fprintf(stream,"}\n");
}

#endif


#endif //STRING_STRING_EXTRAS_H