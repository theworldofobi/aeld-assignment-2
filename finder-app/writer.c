#include <syslog.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>

int cleanup(int fd, int rc) {
  if (fd != -1) { close(fd); }
  closelog();
  return rc;
}

int main(int argc, char* argv[]) {
  openlog("writer.c", 0, LOG_USER);
  
  if (argc != 3) 
  {
    syslog(LOG_ERR, "ERROR (1) writer.c: please include writefile then writestr");
    return cleanup(-1, 1);
  }

  int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 
                S_IWUSR | S_IRUSR | S_IWGRP | S_IRGRP | S_IROTH);
  if (fd == -1) 
  {
    syslog(LOG_ERR, "ERROR (1) writer.c: cannot open file");
    return cleanup(fd, 1);
  }
  
  size_t str_length = strlen(argv[2]);
  ssize_t write_bytes = write(fd, argv[2], str_length);
  if (write_bytes == -1) 
  {
    syslog(LOG_ERR, "ERROR (1) writer.c: cannot write to file");
    return cleanup(fd, 1);
  } else if (write_bytes != str_length) 
  {
    syslog(LOG_ERR, "ERROR (1) writer.c: write to file incomplete");
    return cleanup(fd, 1);
  }
  
  syslog(LOG_DEBUG, "Writing %s to %s\n", argv[2], argv[1]);

  return cleanup(fd, 0);
}


