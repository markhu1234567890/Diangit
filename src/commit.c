#include<stdio.h>
#include<string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <zlib.h> 
#include <openssl/sha.h> 
#include <time.h> 
#include <openssl/evp.h>
#include"commit.h"
#include"add_file.h"
#define HASH_LENGTH 32 // SHA-256 produces a 32-byte hash
void update(int f,unsigned char *commit_hash, const char *message){//1表示进入log 其他表示进入文本
    char path[256];
    if(f==1){
       
    sprintf(path,".git/objects/%c%c/%s.log", commit_hash[0],commit_hash[1],commit_hash+2);
    }else{
    snprintf(path, sizeof(path), ".git/objects/%02x", commit_hash[0]);
       snprintf(path + strlen(path), sizeof(path) - strlen(path), "/%02x.log", commit_hash[1]);
    
  
    }
 
    
    
    // 创建提交文件
    //FILE *file = fopen(path, "wb");
    //printf("%s",path);
    FILE *file = fopen(path, "a");
    if (!file) {
        perror("Failed to create commit file");
        return;
    }

    // 获取当前时间并格式化
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);  // 使用 localtime 以获取本地时间
    char timestamp[256];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

    // 写入提交信息
    fprintf(file, "%s\n", message);
    //printf("---------------------");
    fprintf(file, "time %s\n\n", timestamp);
    fclose(file);
}
void commit(const char *message) {
    // 生成提交哈希
    unsigned char commit_hash[SHA_DIGEST_LENGTH];
    //create_commit_hash(message, commit_hash);
    hash_object(0,message, commit_hash);//1表示不生成obj对象 其他表示生成
    char up_message[256];
    sprintf(up_message,"commit %s",message);
    update(0,commit_hash, up_message);//1表示commit

    // 记录提交到日志
    log_commit(commit_hash, message);
}

void log_commit(unsigned char *commit_hash, const char *message) {
    FILE *log_file = fopen(".git/logs", "a");
    if (!log_file) {
        perror("Failed to open log file");
        return;
    }

    // 获取当前时间并格式化
    time_t now = time(NULL);
    struct tm *tm_info = localtime(&now);  // 使用 localtime 以获取本地时间
    char timestamp[256];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", tm_info);

    // 写入日志信息
    fprintf(log_file, "%02x%02x... %s %s\n", commit_hash[0], commit_hash[1], timestamp, message);
    fclose(log_file);
}

