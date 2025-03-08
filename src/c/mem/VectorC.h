/****************************************************************************************

	File:		VectorC.h
	Why:		Implements vector types in C.
	OS:			-
	Author:		Thomas
	Created:	2019-12-09
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2019-12-09	Thomas			Created.
2020-01-17	Thomas			Documentation from https://github.com/rxi/vec partly
							 added here for convenience.
							 
****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

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
	The project itself at https://github.com/rxi/vec contains the basics.

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

#ifndef VECTORC_H
#define VECTORC_H

#ifndef CUNILOG_USE_COMBINED_MODULE

	#ifdef UBF_USE_FLAT_FOLDER_STRUCTURE
		#include "./externC.h"
	#else
		#include "./../pre/externC.h"
	#endif

#endif

BEGIN_C_DECLS

/** 
 * Copyright (c) 2014 rxi
 *
 * This library is free software; you can redistribute it and/or modify it
 * under the terms of the MIT license. See LICENSE for details.
 */
 
#ifndef _CRT_RAND_S
#define _CRT_RAND_S
#endif

#include <stdlib.h>
#include <string.h>

#define VEC_VERSION "0.2.1"

/*
	vec
	
	A type-safe dynamic array implementation for C.
	Installation
	
	The vec.c and vec.h files can be dropped into an existing C project and compiled along with it.
	Usage
	
	Before using a vector it should first be initialised using the vec_init() function.
	
	vec_int_t v;
	vec_init(&v);
	vec_push(&v, 123);
	vec_push(&v, 456);
	
	To access the elements of the vector directly the vector's data field can be used.
	
	printf("%d\n", v.data[1]); // Prints the value at index 1
	
	The current length of the vector is stored in the length field of the vector
	
	printf("%d\n", v.length); // Prints the length of the vector
	
	When you are done with the vector the vec_deinit() function should be called on it.
	This will free any memory the vector allocated during use.
	
	vec_deinit(&v);
	
	Types
	
	vec.h provides the following predefined vector types:
	Contained Type 	Type name
	void* 	vec_void_t
	char* 	vec_str_t
	int 	vec_int_t
	char 	vec_char_t
	float 	vec_float_t
	double 	vec_double_t
	
	To define a new vector type the vec_t() macro should be used:
	
	/// Creates the type uint_vec_t for storing unsigned ints
	typedef vec_t(unsigned int) uint_vec_t;
	
	Functions
	
	All vector functions are macro functions. The parameter v in each function should be
	a pointer to the vec struct which the operation is to be performed on.
	vec_t(T)
	
	Creates a vec struct for containing values of type T.
	
	// Typedefs the struct `fp_vec_t` as a container for type FILE*
	typedef vec_t(FILE*) fp_vec_t;
	
*/

#define vec_unpack_(v)\
  (char**)&(v)->data, &(v)->length, &(v)->capacity, sizeof(*(v)->data)


#define vec_t(T)\
  struct { T *data; size_t length, capacity; }

/*
	vec_init(v)
	
	Initialises the vector, this must be called before the vector can be used.
*/
#define vec_init(v)\
  memset((v), 0, sizeof(*(v)))

/*
	vec_deinit(v)
	
	Deinitialises the vector, freeing the memory the vector allocated during use;
	this should be called when we're finished with a vector.
*/
#define vec_deinit(v)\
  ( free((v)->data),\
    vec_init(v) ) 

/*
	vec_push(v, val)
	
	Pushes a value to the end of the vector. Returns 0 if the operation was successful,
	otherwise -1 is returned and the vector remains unchanged.
*/
#define vec_push(v, val)\
  ( vec_expand_(vec_unpack_(v)) ? -1 :\
    ((v)->data[(v)->length++] = (val), 0), 0 )

/*
	vec_pop(v)
	
	Removes and returns the value at the end of the vector.
*/
#define vec_pop(v)\
  (v)->data[--(v)->length]

/*
	vec_splice(v, start, count)
	
	Removes the number of values specified by count, starting at the index start.
	
	vec_splice(&v, 2, 4); // Removes the values at indices 2, 3, 4 and 5
*/
#define vec_splice(v, start, count)\
  ( vec_splice_(vec_unpack_(v), start, count),\
    (v)->length -= (count) )

/*
	vec_swapsplice(v, start, count)
	
	Removes the number of values specified by count, starting at the index start;
	the removed values are replaced with the last count values of the vector. This
	does not preserve ordering but is O(1).
*/
#define vec_swapsplice(v, start, count)\
  ( vec_swapsplice_(vec_unpack_(v), start, count),\
    (v)->length -= (count) )

/*
	vec_insert(v, idx, val)
	
	Inserts the value val at index idx shifting the elements after the index to make
	room for the new value.
	
	// Inserts the value 123 at the beginning of the vec
	vec_insert(&v, 0, 123);
	
	Returns 0 if the operation was successful, otherwise -1 is returned and the
	vector remains unchanged.
*/
#define vec_insert(v, idx, val)\
  ( vec_insert_(vec_unpack_(v), idx) ? -1 :\
    ((v)->data[idx] = (val), 0), (v)->length++, 0 )
    
/*
	vec_sort(v, fn)
	
	Sorts the values of the vector; fn should be a qsort-compatible compare function.
*/
#define vec_sort(v, fn)\
  qsort((v)->data, (size_t) (v)->length, sizeof(*(v)->data), fn)

/*
	vec_swap(v, idx1, idx2)
	
	Swaps the values at the indices idx1 and idx2 with one another.
*/
#define vec_swap(v, idx1, idx2)\
  vec_swap_(vec_unpack_(v), idx1, idx2)

/*
	vec_truncate(v, len)
	
	Truncates the vector's length to len. If len is greater than the vector's current
	length then no change is made.
*/
#define vec_truncate(v, len)\
  ((v)->length = (len) < (v)->length ? (len) : (v)->length)

/*
	vec_clear(v)
	
	Clears all values from the vector reducing the vector's length to 0.
*/
#define vec_clear(v)\
  ((v)->length = 0)

/*
	vec_first(v)
	
	Returns the first value in the vector. This should not be used on an empty vector.
*/
#define vec_first(v)\
  (v)->data[0]

/*
	vec_last(v)
	
	Returns the last value in the vector. This should not be used on an empty vector.
*/
#define vec_last(v)\
  (v)->data[(v)->length - 1]

/*
	vec_reserve(v, n)
	
	Reserves capacity for at least n elements in the given vector; if n is less than
	the current capacity then vec_reserve() does nothing. Returns 0 if the operation
	was successful, otherwise -1 is returned and the vector remains unchanged.
*/
#define vec_reserve(v, n)\
  vec_reserve_(vec_unpack_(v), n)

/*
	vec_compact(v)
	
	Reduces the vector's capacity to the smallest size required to store its current
	number of values. Returns 0 if the operation is successful, otherwise -1 is
	returned and the vector remains unchanged.
*/
#define vec_compact(v)\
  vec_compact_(vec_unpack_(v))

/*
	vec_pusharr(v, arr, count)
	
	Pushes the contents of the array arr to the end of the vector. count should be the
	number of elements in the array.
*/
#define vec_pusharr(v, arr, count)\
  do {\
    int i__, n__ = (count);\
    if (vec_reserve_po2_(vec_unpack_(v), (v)->length + n__) != 0) break;\
    for (i__ = 0; i__ < n__; i__++) {\
      (v)->data[(v)->length++] = (arr)[i__];\
    }\
  } while (0)

/*
	vec_extend(v, v2)
	
	Appends the contents of the v2 vector to the v vector.
*/
#define vec_extend(v, v2)\
  vec_pusharr((v), (v2)->data, (v2)->length)

/*
	vec_find(v, val, idx)
	
	Finds the first occurrence of the value val in the vector. idx should be an int
	where the value's index will be written; idx is set to -1 if val could not be
	found in the vector.
*/
#define vec_find(v, val, idx)\
  do {\
    for ((idx) = 0; (idx) < (v)->length; (idx)++) {\
      if ((v)->data[(idx)] == (val)) break;\
    }\
    if ((idx) == (v)->length) (idx) = -1;\
  } while (0)

/*
	vec_remove(v, val)
	
	Removes the first occurrence of the value val from the vector. If the val is not
	contained in the vector then vec_remove() does nothing.
*/
#define vec_remove(v, val)\
  do {\
    int idx__;\
    vec_find(v, val, idx__);\
    if (idx__ != -1) vec_splice(v, idx__, 1);\
  } while (0)

/*
	vec_reverse(v)
	
	Reverses the order of the vector's values in place. For example, a vector
	containing 4, 5, 6 would contain 6, 5, 4 after reversing.
*/
#define vec_reverse(v)\
  do {\
    int i__ = (v)->length / 2;\
    while (i__--) {\
      vec_swap((v), i__, (v)->length - (i__ + 1));\
    }\
  } while (0)

/*
	vec_foreach(v, var, iter)
	
	Iterates the values of the vector from the first to the last. var should be a
	variable of the vector's contained type where the value will be stored with each
	iteration. iter should be an int used to store the index during iteration.
	
	// Iterates and prints the value and index of each value in the float vec
	int i; float val;
	vec_foreach(&v, val, i) {
	  printf("%d : %f\n", i, val);
	}
*/
#define vec_foreach(v, var, iter)\
  if  ( (v)->length > 0 )\
  for ( (iter) = 0;\
        (iter) < (v)->length && (((var) = (v)->data[(iter)]), 1);\
        ++(iter))

/*
	vec_foreach_rev(v, var, iter)
	
	Iterates the values of the vector from the last to the first. See vec_foreach()
*/
#define vec_foreach_rev(v, var, iter)\
  if  ( (v)->length > 0 )\
  for ( (iter) = (v)->length - 1;\
        (iter) >= 0 && (((var) = (v)->data[(iter)]), 1);\
        --(iter))

/*
	vec_foreach_ptr(v, var, iter)
	
	Iterates the value pointers of the vector from first to last. var should be a
	variable of the vector's contained type's pointer. See vec_foreach().
	
	// Iterates and prints the value and index of each value in the float vector
	int i; float *val;
	vec_foreach_ptr(&v, val, i) {
	  printf("%d : %f\n", i, *val);
}
*/
#define vec_foreach_ptr(v, var, iter)\
  if  ( (v)->length > 0 )\
  for ( (iter) = 0;\
        (iter) < (v)->length && (((var) = &(v)->data[(iter)]), 1);\
        ++(iter))

/*
	vec_foreach_ptr_rev(v, var, iter)
	
	Iterates the value pointers of the vector from last to first. See vec_foreach_ptr()
*/
#define vec_foreach_ptr_rev(v, var, iter)\
  if  ( (v)->length > 0 )\
  for ( (iter) = (v)->length - 1;\
        (iter) >= 0 && (((var) = &(v)->data[(iter)]), 1);\
        --(iter))

/*
	License
	
	This library is free software; you can redistribute it and/or modify it under the
	terms of the MIT license. See LICENSE for details.
*/

int vec_expand_(char **data, size_t *length, size_t *capacity, size_t memsz);
int vec_reserve_(char **data, size_t *length, size_t *capacity, size_t memsz, size_t n);
int vec_reserve_po2_(char **data, size_t *length, size_t *capacity, size_t memsz,
                     size_t n);
int vec_compact_(char **data, size_t *length, size_t *capacity, size_t memsz);
int vec_insert_(char **data, size_t *length, size_t *capacity, size_t memsz,
                size_t idx);
void vec_splice_(char **data, size_t *length, size_t *capacity, size_t memsz,
	size_t start, size_t count);
void vec_swapsplice_(char **data, size_t *length, size_t *capacity, size_t memsz,
                     size_t start, size_t count);
void vec_swap_(char **data, size_t *length, size_t *capacity, size_t memsz,
               size_t idx1, size_t idx2);

typedef vec_t(void*) vec_void_t;
typedef vec_t(char*) vec_str_t;
typedef vec_t(int) vec_int_t;
typedef vec_t(char) vec_char_t;
typedef vec_t(float) vec_float_t;
typedef vec_t(double) vec_double_t;
// More type definitions can be found in VectorCtypes.h.

END_C_DECLS

#endif															// End of VECTORC_H.
