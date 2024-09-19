
#include"add_file.h"
#include<stdio.h>
#include<string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <zlib.h> 
#include <openssl/sha.h> 
#include <time.h> 
#include <openssl/evp.h>

#define HASH_LENGTH 32
#define CHUNK_SIZE 1024
#define PATH_SIZE 512


void add_file(const char *filename) { 
 unsigned char file_hash[SHA_DIGEST_LENGTH]; 
 // Assume hash_object() calculates file hash 
 if(hash_object(filename, file_hash)!=1){
 return;
 } 
 
 FILE *index_file = fopen(".git/index", "a"); 
 if (!index_file) { 
 printf("Failed to open index file.\n"); 
 return; 
 } 
 
 fprintf(index_file, "%s %02x%02x...\n", filename, file_hash[0], file_hash[1]); // Simplified hash 
 fclose(index_file); 
 printf("Added '%s' to the staging area.\n", filename); 
}
/*
int hash_object(const char *filename, unsigned char *file_hash) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Cannot open file: %s\n", filename);
        return 0;
    }

    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    char buffer[1024];
    size_t bytes_read;

    // Create and initialize a new message digest context
    mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        fclose(file);
        printf("Failed to create context\n");
        return 0;
    }

    // Use SHA-256 for hashing
    md = EVP_sha256();
    if (EVP_DigestInit_ex(mdctx, md, NULL) <= 0) {
        EVP_MD_CTX_free(mdctx);
        fclose(file);
        printf("Failed to initialize digest\n");
        return 0;
    }

    // Read the file in chunks and update the hash
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        if (EVP_DigestUpdate(mdctx, buffer, bytes_read) <= 0) {
            EVP_MD_CTX_free(mdctx);
            fclose(file);
            printf("Failed to update digest\n");
            return 0; 
        }
    }

    // Finalize the hash
    if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) <= 0) {
        EVP_MD_CTX_free(mdctx);
        fclose(file);
        printf("Failed to finalize digest\n");
        return 0;
    }

    // Clean up
    EVP_MD_CTX_free(mdctx);
    fclose(file);

    // Copy the hash to file_hash
    if (hash_len <= SHA256_DIGEST_LENGTH) {
        memcpy(file_hash, hash, hash_len);
    } else {
        printf("Hash length is longer than expected\n");
    }
    char path[256];
    snprintf(path, sizeof(path), ".git/objects/%02x", hash[0]);
    mkdir(path, 0755);
    snprintf(path + strlen(path), sizeof(path) - strlen(path), "/%02x", hash[1]);
    store_object(filename, hash);
    return 1;
}*/
int hash_object(const char *filename, unsigned char *file_hash) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len;
    FILE *file = fopen(filename, "rb");
    if (!file) {
        printf("Cannot open file: %s\n", filename);
        return 0;
    }
    // Create and initialize a new message digest context
    mdctx = EVP_MD_CTX_new();
    if (!mdctx) {
        printf("Failed to create context\n");
        return 0;
    }

    // Use SHA-256 for hashing
    md = EVP_sha256();
    if (EVP_DigestInit_ex(mdctx, md, NULL) <= 0) {
        EVP_MD_CTX_free(mdctx);
        printf("Failed to initialize digest\n");
        return 0;
    }

    // Update the digest with the filename
    if (EVP_DigestUpdate(mdctx, filename, strlen(filename)) <= 0) {
        EVP_MD_CTX_free(mdctx);
        printf("Failed to update digest\n");
        return 0;
    }

    // Finalize the hash
    if (EVP_DigestFinal_ex(mdctx, hash, &hash_len) <= 0) {
        EVP_MD_CTX_free(mdctx);
        printf("Failed to finalize digest\n");
        return 0;
    }

    // Clean up
    EVP_MD_CTX_free(mdctx);

    // Copy the hash to file_hash
    if (hash_len <= SHA256_DIGEST_LENGTH) {
        memcpy(file_hash, hash, hash_len);
    } else {
        printf("Hash length is longer than expected\n");
        return 0;
    }

    // Example of using the hash, replace with your own logic
    char path[256];
    snprintf(path, sizeof(path), ".git/objects/%02x", hash[0]);
    mkdir(path, 0755);
    snprintf(path + strlen(path), sizeof(path) - strlen(path), "/%02x", hash[1]);
    // Assuming store_object is a function you have that takes a filename and hash
    store_object(filename, hash);

    return 1;
}

void cat_file(const char *hash) { 
 char path[256]; 
 sprintf(path, ".git/objects/%c%c/%s", hash[0], hash[1], hash + 2); 
 
 gzFile file = gzopen(path, "rb"); 
 if (!file) { 
 printf("Cannot open object file: %s\n", path); 
 return; 
 }  
 
 char buffer[1024]; 
 int bytes_read;
    while ((bytes_read = gzread(file, buffer, sizeof(buffer))) > 0) {
        fwrite(buffer, 1, bytes_read, stdout);
  }
 
 gzclose(file); 
} 


void store_object(const char *filename, unsigned char *hash) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        
        perror("Cannot open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *file_content = malloc(file_size);
    if (!file_content) {
        fclose(file);
        fprintf(stderr, "Memory allocation failed\n");
        return;
    }

    fread(file_content, 1, file_size, file);
    fclose(file);
    // printf("%s",file_content);
    char header[64];
    int header_length = snprintf(header, sizeof(header), "blob %ld\0", file_size);
    if (header_length < 0 || header_length >= sizeof(header)) {
        free(file_content);
        fprintf(stderr, "Failed to format header\n");
        return;
    }

    char path[PATH_SIZE];
    snprintf(path, sizeof(path), ".git/objects/%02x/%02x", hash[0], hash[1]);
    
    //printf("%s",path);
    //snprintf(path + strlen(path), sizeof(path) - strlen(path), "/%02x%02x", hash[2], hash[3]);
    //printf("%s",path);
    FILE *obj_file = fopen(path, "wb");
    if (!obj_file) {
       
        free(file_content);
        perror("Cannot create object file");
        return;
    }

    gzFile gz = gzdopen(fileno(obj_file), "wb");
    if (!gz) {
        free(file_content);
        fclose(obj_file);
        perror("Failed to open gz file");
        return;
    }

    gzwrite(gz, header, header_length);
    gzwrite(gz, file_content, file_size);
    gzclose(gz);

    free(file_content);
    fclose(obj_file);
}



