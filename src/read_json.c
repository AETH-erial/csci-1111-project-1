/*
 * 
 * Methods dedicated to IO operations on JSON files
 * 
 */
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#include <json-c/json.h>

#define BUF_MAX_SIZE  2048


/*
 * Reads a file 'filepath' into a struct, the file should contain
 * json that corresponds to 1 test question
 * */
void read_test_file(char filepath) {
   int fd = open(&filepath, O_RDONLY);
   if (fd > 0) {
        perror("Couldnt open file.");
   }
   char buf[BUF_MAX_SIZE];
   pread(fd, buf, sizeof(buf)-1, 0);
   printf("%s\n", buf);
}
