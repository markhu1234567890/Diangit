#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include"create_tag.h"
#include"commit.h"
void create_tag(const char *tag_name, const char *commit_hash) { 
char check_path[256];
    snprintf(check_path, sizeof(check_path), "%s/%c%c/%s", ".git/objects", commit_hash[0], commit_hash[1], commit_hash + 2);

    FILE *check_file = fopen(check_path, "rb");
    if (!check_file) {
        printf("Cannot find commit file: %s\n", check_path);
        return;
    }
    fclose(check_file);
 char path[256]; 
 sprintf(path, ".git/refs/tags/%s", tag_name); 
 
 FILE *file = fopen(path, "w"); 
 if (!file) { 
 printf("Failed to create tag: %s\n", tag_name); 
 return; 
 } 
 
 fprintf(file, "%s\n", commit_hash); 
 fclose(file); 
 

 char up_message[256];
 sprintf(up_message,"Tag '%s' created pointing to commit %s.\n", tag_name, commit_hash); 
 printf("%s\n",up_message);
 update(0,(unsigned char*)commit_hash,up_message);
} 
void list_tags() {
    DIR* dir = opendir(".git/refs/tags");
    if (!dir) {
        perror("Error opening tags directory");
        return;
    }
    struct dirent* entry;
    printf("Tags:\n");
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            printf("  %s\n", entry->d_name);
        }
    }
    closedir(dir);
}


void delete_tag(const char *tag_name) {
    char path[256];
    snprintf(path, sizeof(path), "%s/%s",".git/refs/tags", tag_name);
    if (remove(path) == 0) {
        printf("Tag '%s' deleted.\n", tag_name);
    }else{
     printf("Failed to delete tag");
     }
}





void rename_tag(const char *old_name, const char *new_name) {
    char old_path[256], new_path[256];
    snprintf(old_path, sizeof(old_path), "%s/%s", ".git/refs/tags", old_name);
    snprintf(new_path, sizeof(new_path), "%s/%s", ".git/refs/tags", new_name);

    if (rename(old_path, new_path) != 0) {
        perror("Error renaming tag");
        return;
    }
    printf("Tag '%s' renamed to '%s'.\n", old_name, new_name);
}




void update_tag(const char *tag_name, const char *new_commit_hash) {
    char check_path[256];
    snprintf(check_path, sizeof(check_path), "%s/%c%c/%s", ".git/objects", new_commit_hash[0], new_commit_hash[1], new_commit_hash + 2);

    FILE *check_file = fopen(check_path, "rb");
    if (!check_file) {
        printf("Cannot find commit file: %s\n", check_path);
        return;
    }
    fclose(check_file);

    char path[256];
    snprintf(path, sizeof(path), "%s/%s", ".git/refs/tags" ,tag_name);

    FILE *file = fopen(path, "w");
    if (!file) {
        perror("Failed to update tag");
        return;
    }

    fprintf(file, "%s\n", new_commit_hash);
    fclose(file);

    printf("Tag '%s' updated to commit %s.\n", tag_name, new_commit_hash);
}

