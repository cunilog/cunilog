/****************************************************************************************

	File:		VectorC.c
	Why:		Implements vector types in C.
	OS:			-
	Author:		Thomas
	Created:	2019-12-09
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2019-12-09	Thomas			Created.

****************************************************************************************/

/*
	Implements vectors (variable arrays) in C. If you change this text please copy
	and paste it in the code or header file too.
	
	The code has been inspired by several different sources and changed/extended.
	
	Sources:
	https://github.com/rxi/vec
	https://eddmann.com/posts/implementing-a-dynamic-vector-array-in-c/
	https://stackoverflow.com/questions/4694401/how-to-replicate-vector-in-c
	https://github.com/Mashpoe/c-vector
	
	Most of the code comes from https://github.com/rxi/vec .
	A good introduction can be found at https://jameshfisher.com/2017/04/06/rxi-vec/ .

	This code is covered by the MIT License. See https://opensource.org/license/mit .

	Since most of the code is from the rxi implementation: Copyright (c) 2014 rxi

	Permission is hereby granted, free of charge, to any person obtaining a copy of this
	software and associated documentation files (the "Software"), to deal in the Software
	without restriction, including without limitation the rights to use, copy, modify,
	merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
	permit persons to whom the Software is furnished to do so, subject to the following
	conditions:

	The above copyright notice and this permission notice shall be included in all copies
	or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
	PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

/** 
 * Copyright (c) 2014 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */
 
#ifndef CUNILOG_USE_COMBINED_MODULE

    #include "./VectorC.h"

#endif

int vec_expand_(char **data, size_t *length, size_t *capacity, size_t memsz) {
  if (*length + 1 > *capacity) {
    void *ptr;
    size_t n = (*capacity == 0) ? 1 : *capacity << 1;
    ptr = realloc(*data, n * memsz);
    if (ptr == NULL) return -1;
    *data = ptr;
    *capacity = n;
  }
  return 0;
}


int vec_reserve_(char **data, size_t *length, size_t *capacity, size_t memsz, size_t n) {
  (void) length;
  if (n > *capacity) {
    void *ptr = realloc(*data, n * memsz);
    if (ptr == NULL) return -1;
    *data = ptr;
    *capacity = n;
  }
  return 0;
}


int vec_reserve_po2_(
  char **data, size_t *length, size_t *capacity, size_t memsz, size_t n
) {
  size_t n2 = 1;
  if (n == 0) return 0;
  while (n2 < n) n2 <<= 1;
  return vec_reserve_(data, length, capacity, memsz, n2);
}


int vec_compact_(char **data, size_t *length, size_t *capacity, size_t memsz) {
  if (*length == 0) {
    free(*data);
    *data = NULL;
    *capacity = 0;
    return 0;
  } else {
    void *ptr;
    size_t n = *length;
    ptr = realloc(*data, n * memsz);
    if (ptr == NULL) return -1;
    *capacity = n;
    *data = ptr;
  }
  return 0;
}


int vec_insert_(char **data, size_t *length, size_t *capacity, size_t memsz,
                 size_t idx
) {
  int err = vec_expand_(data, length, capacity, memsz);
  if (err) return err;
  memmove(*data + (idx + 1) * memsz,
          *data + idx * memsz,
          (size_t) ((*length - idx) * memsz));
  return 0;
}


void vec_splice_(char **data, size_t *length, size_t *capacity, size_t memsz,
                 size_t start, size_t count
) {
  (void) capacity;
  memmove(*data + start * memsz,
          *data + (start + count) * memsz,
          (size_t) ((*length - start - count) * memsz));
}


void vec_swapsplice_(char **data, size_t *length, size_t *capacity, size_t memsz,
                     size_t start, size_t count
) {
  (void) capacity;
  memmove(*data + start * memsz,
          *data + (*length - count) * memsz,
          (size_t) (count * memsz));
}


void vec_swap_(char **data, size_t *length, size_t *capacity, size_t memsz,
               size_t idx1, size_t idx2
) {
  unsigned char *a, *b, tmp;
  size_t count;
  (void) length;
  (void) capacity;
  if (idx1 == idx2) return;
  a = (unsigned char*) *data + idx1 * memsz;
  b = (unsigned char*) *data + idx2 * memsz;
  count = memsz;
  while (count--) {
    tmp = *a;
    *a = *b;
    *b = tmp;
    a++; b++;
  }
}
