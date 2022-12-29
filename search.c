#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>

void search(char* dir, char* search_term) {
    DIR* d = opendir(dir);
    struct dirent* entry;
    char path[1024];

    if (d == NULL) {
        perror("opendir");
        return;
    }

    while ((entry = readdir(d)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        sprintf(path, "%s/%s", dir, entry->d_name);

        if (entry->d_type == DT_DIR) {
            search(path, search_term);
        } else if (strcmp(entry->d_name, search_term) == 0) {
            printf("%s\n", path);
        }
    }

    closedir(d);
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("Usage: search [directory] [search term]\n");
        return 1;
    }

    search(argv[1], argv[2]);
    return 0;
}
