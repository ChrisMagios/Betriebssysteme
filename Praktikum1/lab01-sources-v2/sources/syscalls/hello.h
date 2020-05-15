#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/stat.h>      
#include <unistd.h>

#include <string.h>

#include <fcntl.h>

int writeToFile(char* name, const char* content);

int writeToFileILA(char* name, const char* content);
