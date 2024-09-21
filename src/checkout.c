#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#define MAX_PATH 256
#define MAX_CONTENT_SIZE 1024
#include <zlib.h>

/*
char* read_object(int f,const char* hash) {
    char path[MAX_PATH];
    if(f==1){
    snprintf(path, sizeof(path), ".git/objects/%c%c/%s.log", hash[0], hash[1], hash + 2);
    }else{
    snprintf(path, sizeof(path), ".git/objects/%c%c/%s", hash[0], hash[1], hash + 2);
    //printf("%s\n",path);
    }
    
    FILE* file = fopen(path, "rb");
    if (!file) {
        perror("Error opening object file");
        return NULL;
    }
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* content = (char*)malloc(size + 1);
    if (!content) {
        perror("Memory allocation error");
        fclose(file);
        return NULL;
    }
    fread(content, 1, size, file);
    content[size] = '\0';
    fclose(file);
    //printf("--------%s------\n",content);
    return content;
}*/

char* read_object(int f, const char *hash) {//1表示进入log 其他表示进入文本
    char path[256];
    if(f==1){
    snprintf(path, sizeof(path), ".git/objects/%c%c/%s.log", hash[0], hash[1], hash + 2);
    }else{
    snprintf(path, sizeof(path), ".git/objects/%c%c/%s", hash[0], hash[1], hash + 2);
    printf("%s\n",path);
    }

    gzFile file = gzopen(path, "rb");
    if (!file) {
        return NULL; 
    }

    char *content = malloc(MAX_CONTENT_SIZE);
    if (!content) {
        gzclose(file);
        return NULL; 
    }

    int bytes_read = gzread(file, content, MAX_CONTENT_SIZE - 1);
    gzclose(file);

    if (bytes_read < 0) {
        free(content);
        return NULL;  
    }

    content[bytes_read] = '\0';  // 确保内容是以 null 结尾
    return content;  // 返回读取的内容
}
void write_to_working_directory(const char* path, const char* content) {
    char dir[MAX_PATH];
    strncpy(dir, path, sizeof(dir));
    char* last_slash = strrchr(dir, '/');
    if (last_slash) {
        *last_slash = '\0';
        struct stat st = {0};
        if (stat(dir, &st) == -1) {
            if (mkdir(dir, 0700) == -1) {
                perror("Error creating directory");
                return;
            }
        }
    }
    FILE* file = fopen(path, "w");
    if (!file) {
        perror("Error opening file");
        return;
    }
    if (fprintf(file, "%s", content) < 0) {
        perror("Error writing to file");
    }
    fclose(file);
}

void print_tree(const char* tree_hash) {
    char* tree_content = read_object(1,tree_hash);//1表示进入log 其他表示进入文本
    //printf("----------------------");
    if (!tree_content) {
        printf("Error: Tree object not found.\n");
        return;
    }
   printf("%s",tree_content);
    free(tree_content);
}

void checkout(const char* commit_hash) {
    char* commit_content = read_object(0,commit_hash);//1表示进入log 其他表示进入文本
  
    
    if (!commit_content) {
        printf("Error: Commit not found.\n");
        return;
    }
    printf("%s\n",commit_content);
    char tree_hash[41];
    sscanf(commit_content, "%40s", tree_hash);
     printf("%s\n",tree_hash);
    free(commit_content);

    char* tree_content = read_object(0,tree_hash);//1表示进入log 其他表示进入文本
    if (!tree_content) {
        printf("Error: Tree object not found.\n");
        return;
    }

    char* line = strtok(tree_content, "\n");
    while (line) {
        char path[MAX_PATH];
        char content[MAX_CONTENT_SIZE];
        sscanf(line, "%s %s", path, content);
        write_to_working_directory(path, content);
        line = strtok(NULL, "\n");
    }
    printf("Switched to commit %s\n", commit_hash);
    free(tree_content);
}


