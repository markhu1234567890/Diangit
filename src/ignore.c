#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_RULES 100
#define MAX_PATH_LENGTH 256

// 函数用于修剪字符串两端的空白字符
void trim(char *str) {
    char *end;
    while (isspace(*str)) str++;
    if (*str == 0) return;
    end = str + strlen(str) - 1;
    while (end > str && isspace(*end)) end--;
    *(end + 1) = 0;
}

// 检查文件是否被忽略
int check_ignore(const char *file_path) {
    unsigned char gitignore_path[256]; 
    sprintf(gitignore_path,".git/.gitignore",file_path);
    FILE *fp = fopen(gitignore_path, "r");
    if (!fp) {
        perror("Could not open .gitignore");
        return -1; // 错误
    }

    char *ignore_rules[MAX_RULES];
    char line[MAX_PATH_LENGTH];
    int rule_count = 0;

    // 读取 .gitignore 文件
    while (fgets(line, sizeof(line), fp) && rule_count < MAX_RULES) {
        trim(line);
        if (line[0] != '\0' && line[0] != '#') {
            ignore_rules[rule_count] = strdup(line);
            rule_count++;
        }
    }
    fclose(fp);

    // 检查是否被忽略
    for (int i = 0; i < rule_count; i++) {
        if (strstr(file_path, ignore_rules[i]) != NULL) {
            for (int j = 0; j < rule_count; j++) {
                free(ignore_rules[j]); // 释放内存
            }
            return 1; // 被忽略
        }
    }

    // 释放内存
    for (int i = 0; i < rule_count; i++) {
        free(ignore_rules[i]);
    }

    return 0; // 未被忽略
}

// 函数用于添加文件路径到 .gitignore
int add_to_gitignore(const char *file_path) {
   unsigned char gitignore_path[256]; 
   sprintf(gitignore_path,".git/.gitignore",file_path);
   
    FILE *fp = fopen(gitignore_path, "a");
    if (!fp) {
        perror("Could not open .gitignore");
        return -1; // 错误
    }

    //printf("%d\n",check_ignore(file_path));
    if(check_ignore(file_path)==1) return 0;

    // 添加文件路径到 .gitignore
    fprintf(fp, "%s\n", file_path);
    //printf("!!!!\n");
    fclose(fp);
    return 1; // 成功添加
}
