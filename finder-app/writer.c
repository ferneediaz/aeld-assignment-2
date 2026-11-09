/*
 * writer.c - write a string to a file (C replacement for writer.sh)
 * Usage: writer <writefile> <writestr>
 *
 * The directory containing <writefile> is assumed to already exist.
 * Logs to syslog using the LOG_USER facility.
 */
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <syslog.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    openlog("writer", LOG_PID | LOG_PERROR, LOG_USER);

    if (argc != 3) {
        syslog(LOG_ERR, "Invalid number of arguments: expected 2, got %d. "
               "Usage: %s <writefile> <writestr>", argc - 1, argv[0]);
        closelog();
        return 1;
    }

    const char *writefile = argv[1];
    const char *writestr = argv[2];

    int fd = open(writefile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        syslog(LOG_ERR, "Could not open file %s: %s", writefile, strerror(errno));
        closelog();
        return 1;
    }

    syslog(LOG_DEBUG, "Writing %s to %s", writestr, writefile);

    size_t len = strlen(writestr);
    const char *p = writestr;
    while (len > 0) {
        ssize_t n = write(fd, p, len);
        if (n == -1) {
            if (errno == EINTR)
                continue;
            syslog(LOG_ERR, "Could not write to file %s: %s", writefile, strerror(errno));
            close(fd);
            closelog();
            return 1;
        }
        p += n;
        len -= (size_t)n;
    }

    if (close(fd) == -1) {
        syslog(LOG_ERR, "Could not close file %s: %s", writefile, strerror(errno));
        closelog();
        return 1;
    }

    closelog();
    return 0;
}
