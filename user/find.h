#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/fcntl.h"


/**
 * Reads the directory entries and upon finding a suitable directory
 * that is valid, calls itself until the file name matches or
 * there aren't any files to look at anymore
 * @param path
 *
 *
 */
void
find(char *path, char *needle)

/**
 *  Checks if the directory is "." or ".."
 *  @param path The relative path to the file
 *  @return 1 if the directory is not "." nor "..", 0 otherwise
 */
int
is_valid_dir(char *path)
