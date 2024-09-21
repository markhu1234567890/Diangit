#include <stdio.h>
#include <unistd.h> 
#include <sys/stat.h> 
#include <sys/types.h>
#include "init_repository.h"

void init_repository(const char *path) { 
    char git_dir[256]; 
    sprintf(git_dir, "%s/.git", path); 
    
    if (access(git_dir, F_OK) == 0) { 
        printf("Repository already exists.\n"); 
        return; 
    } 
    
    if (mkdir(git_dir, 0755) == -1) { 
        printf("Failed to create .git directory.\n"); 
        return;  
    } 
    
    // Create the objects directory
    char objects_dir[256];
    sprintf(objects_dir, "%s/.git/objects", path);
    if (mkdir(objects_dir, 0755) == -1) {
        printf("Failed to create .git/objects directory.\n");
        return;
    }
    char temp_dir[256];
    sprintf(temp_dir, "%s/.git/temp", path);
    if (mkdir(temp_dir, 0755) == -1) {
        printf("Failed to create .git/temp directory.\n");
        return;
    }
    
    // Create the refs directory
    char refs_dir[256];
    sprintf(refs_dir, "%s/.git/refs", path);
    if (mkdir(refs_dir, 0755) == -1) {
        printf("Failed to create .git/refs directory.\n");
        return;
    }
    
    // Create the heads directory
    char heads_dir[256];
    sprintf(heads_dir, "%s/.git/refs/heads", path);
    if (mkdir(heads_dir, 0755) == -1) {
        printf("Failed to create .git/refs/heads directory.\n");
        return;
    }
    
    
    // Create the tags directory
    char tags_dir[256];
    sprintf(tags_dir, "%s/.git/refs/tags", path);
    if (mkdir(tags_dir, 0755) == -1) {
        printf("Failed to create .git/refs/tags directory.\n");
        return;
    }
    //Create the .gitignore
    char ignore_dir[256];
    sprintf(ignore_dir, "%s/.git/.gitignore", path);
    FILE *file = fopen(ignore_dir, "w"); 
    if (!file) { 
        printf("Failed to create .gitignore file.\n"); 
        return; 
    } 

    create_initial_config(path); 
    printf("Initialized empty Git repository in %s/.git/\n", path); 
} 

void create_initial_config(const char *path) { 
    char config_path[256]; 
    sprintf(config_path, "%s/.git/config", path); 
    
    FILE *file = fopen(config_path, "w"); 
    if (!file) { 
        printf("Failed to create config file.\n"); 
        return; 
    } 
    
    fprintf(file, "[core]\n\trepositoryformatversion = 0\n\tfilemode = true\n"); 
    fclose(file); 
}
