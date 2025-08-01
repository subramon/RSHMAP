//START_INCLUDES
#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "q_macros.h"
//STOP_INCLUDES
#include "rs_mmap.h"
//START_FUNC_DECL
int
rs_mmap(
	const char *file_name,
	char **ptr_mmapped_file,
	size_t *ptr_file_size,
	bool is_write
	)
//STOP_FUNC_DECL
{
  int status = 0;
  int fd = -1;
  struct stat filestat;
  size_t len = 0;
#define MAX_LEN_DIR_NAME 255

  if ( is_write ) { 
    fd = open(file_name, O_RDWR);
  }
  else {
    fd = open(file_name, O_RDONLY);
  }
  if ( fd < 0 ) {
    char cwd[MAX_LEN_DIR_NAME+1];
    if ( getcwd(cwd, MAX_LEN_DIR_NAME) == NULL ) { go_BYE(-1); }
    fprintf(stderr, "Could not open file [%s] \n", file_name); 
    fprintf(stderr, "Currently in dir    [%s] \n", cwd); 
    go_BYE(-1); 
  }
  // henceforth, fd >= 0
  status = fstat(fd, &filestat); cBYE(status);
  len = filestat.st_size;
  /* It is okay for file size to be 0 */
  *ptr_file_size = -1;
  if ( len == 0 ) { 
    *ptr_mmapped_file = NULL;
    *ptr_file_size = 0;
    goto BYE;
  }
  //-----------------------------------------
  if ( is_write ) { 
    *ptr_mmapped_file = (void *)mmap(NULL, (size_t) len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
  }
  else {
    *ptr_mmapped_file = (void *)mmap(NULL, (size_t) len, PROT_READ, MAP_SHARED, fd, 0);
  }
  *ptr_file_size = filestat.st_size;
BYE:
  if ( fd >= 0 ) { close(fd); fd = -1; }
  return(status);
}
