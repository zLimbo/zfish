#include <stdio.h>
#include <stdlib.h>
#include <sys/dir.h>
#include <sys/file.h>
#include <sys/types.h>
#include <unistd.h>

void find_aux(char *path, const char *target) {
    int fd;
    struct stat st;
    struct dirent de;
    char buf[512], *p = 0;

    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "find: cannot open %s\n", path);
        return;
    }

    if (fstat(fd, &st) < 0) {
        fprintf(2, "find: cannot stat %s\n", path);
        close(fd);
        return;
    }

    if (st.type == T_DIR) {
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof(buf)) {
            printf("find: path too long\n");
            return;
        }
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        while (read(fd, &de, sizeof(de)) == sizeof(de)) {
            if (de.inum == 0)
                continue;
            memmove(p, de.name, DIRSIZ);
            if (strcmp(de.name, target) == 0) {
                printf("%s\n", buf);
            }
            find_aux(buf, target);
        }
    }
}

void find(char *path, char *target) {}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        exit(0);
    }

    find(argv[1], argv[2]);

    return 0;
}