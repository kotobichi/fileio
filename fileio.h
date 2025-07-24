#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef enum {
    FIO_SUCCESS,
    FIO_INVALID_ARGS,
    FIO_FILE_NOT_FOUND,
    FIO_EMPTY_FILE,
    FIO_ALLOCATION_FAILED,
    FIO_READ_FAILED,
} FIO_status_e;

/**
 * @param filepath path to file.
 * @param dst file data.
 * @param length of the file data.
 * @return `1` on success (`FIO_SUCCESS`), a negative value otherwise, 
 * consulte the  `FIO_status_e` enumerator.
 * @attention remember to free `dst`.
 * @author kotobichi
 */
FIO_status_e FIO_read(const char *filepath, char **dst, size_t *length);

#ifdef FIO_IMPLEMENTATION

FIO_status_e FIO_read(const char *filepath, char **dst, size_t *length) {
    if (!filepath || !dst || !length) 
    return FIO_INVALID_ARGS;

    *dst = NULL;
    *length = 0;

    FILE *file = fopen(filepath, "rb");
    if (!file) return FIO_FILE_NOT_FOUND;
    
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return FIO_READ_FAILED;
    }
    
    long file_size_long = ftell(file);
    if (file_size_long < 0) {
        fclose(file);
        return FIO_READ_FAILED;
    }
    
    if (fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return FIO_READ_FAILED;
    }
    
    if (file_size_long == 0) {
        fclose(file);
        return FIO_EMPTY_FILE;
    }
    
    size_t file_size = (size_t) file_size_long;
    
    *dst = (char *) malloc(file_size + 1);
    if (!*dst) {
        fclose(file);
        return FIO_ALLOCATION_FAILED;
    }
    
    size_t bytes_read = fread(*dst, 1, file_size, file);
    fclose(file);
    
    if (bytes_read != (size_t) file_size) {
        free(*dst);
        *dst = NULL;
        return FIO_READ_FAILED;
    }
    
    (*dst)[file_size] = '\0';
    *length = file_size;
    return FIO_SUCCESS;
}

#endif