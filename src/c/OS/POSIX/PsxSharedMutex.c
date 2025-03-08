/****************************************************************************************

	File:		PsxSharedMutex.c
	Why:		Implements a mutex for interprocess-locking.
	OS:			C99
	Author:		Thomas
	Created:	2021-02-23
  
History
-------

When		Who				What
-----------------------------------------------------------------------------------------
2021-02-23	Thomas			Created. See
							 https://gist.github.com/marcetcheverry/d2f62672ee98bf54bfad7b8bc0840616
							 and
							 https://gist.github.com/yamnikov-oleg/abf61cf96b4867cbf72d .

****************************************************************************************/

/*
	This file is maintained as part of Cunilog. See https://github.com/cunilog .
*/

/*
MIT License

Copyright (c) 2018 Oleg Yamnikov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef CUNILOG_USE_COMBINED_MODULE

	#include "./PsxSharedMutex.h"

#endif

#ifdef PLATFORM_IS_POSIX

#include <errno.h> // errno, ENOENT
#include <fcntl.h> // O_RDWR, O_CREATE
#include <linux/limits.h> // NAME_MAX
#include <sys/mman.h> // shm_open, shm_unlink, mmap, munmap,
					  // PROT_READ, PROT_WRITE, MAP_SHARED, MAP_FAILED
#include <sys/stat.h> /* For mode constants */
#include <unistd.h> // ftruncate, close
#include <stdio.h> // perror
#include <stdlib.h> // malloc, free
#include <string.h> // strcpy

shared_mutex_t PsxInitSharedMutex(const char *name, mode_t mode) {
  shared_mutex_t mutex = {NULL, 0, NULL, 0};
  errno = 0;

  // Open existing shared memory object, or create one.
  // Two separate calls are needed here, to mark fact of creation
  // for later initialization of pthread mutex.
  mutex.shm_fd = shm_open(name, O_RDWR, mode);
  if (errno == ENOENT) {
	mutex.shm_fd = shm_open(name, O_RDWR|O_CREAT, mode);
	mutex.created = 1;
	// Change permissions of shared memory, so every body can access it. Avoiding the umask of shm_open
	if (fchmod(mutex.shm_fd, mode) != 0) {
	  //perror("fchmod");
	}
  }
  if (mutex.shm_fd == -1) {
	//perror("shm_open");
	return mutex;
  }

  // Truncate shared memory segment so it would contain
  // pthread_mutex_t.
  if (ftruncate(mutex.shm_fd, sizeof(pthread_mutex_t)) != 0) {
	//perror("ftruncate");
	return mutex;
  }

  // Map pthread mutex into the shared memory.
  void *addr = mmap(
	NULL,
	sizeof(pthread_mutex_t),
	PROT_READ|PROT_WRITE,
	MAP_SHARED,
	mutex.shm_fd,
	0
  );
  if (addr == MAP_FAILED) {
	//perror("mmap");
	return mutex;
  }
  pthread_mutex_t *mutex_ptr = (pthread_mutex_t *)addr;

  // If shared memory was just initialized -
  // initialize the mutex as well.
  if (mutex.created) {
	pthread_mutexattr_t attr;
	if (pthread_mutexattr_init(&attr)) {
	  //perror("pthread_mutexattr_init");
	  return mutex;
	}
	if (pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED)) {
	  //perror("pthread_mutexattr_setpshared");
	  return mutex;
	}
	if (pthread_mutex_init(mutex_ptr, &attr)) {
	  //perror("pthread_mutex_init");
	  return mutex;
	}
  }
  mutex.ptr = mutex_ptr;
  mutex.name = (char *)malloc(NAME_MAX+1);
  strcpy(mutex.name, name);
  return mutex;
}

int PsxCloseSharedMutex(shared_mutex_t mutex) {
  if (munmap((void *)mutex.ptr, sizeof(pthread_mutex_t))) {
	//perror("munmap");
	return -1;
  }
  mutex.ptr = NULL;
  if (close(mutex.shm_fd)) {
	//perror("close");
	return -1;
  }
  mutex.shm_fd = 0;
  free(mutex.name);
  return 0;
}

int PsxDestroySharedMutex(shared_mutex_t mutex) {
  if ((errno = pthread_mutex_destroy(mutex.ptr))) {
	//perror("pthread_mutex_destroy");
	return -1;
  }
  if (munmap((void *)mutex.ptr, sizeof(pthread_mutex_t))) {
	//perror("munmap");
	return -1;
  }
  mutex.ptr = NULL;
  if (close(mutex.shm_fd)) {
	//perror("close");
	return -1;
  }
  mutex.shm_fd = 0;
  if (shm_unlink(mutex.name)) {
	//perror("shm_unlink");
	return -1;
  }
  free(mutex.name);
  return 0;
}

#endif															// Of #ifdef UBF_LINUX.
