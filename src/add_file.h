void add_file(const char *filename) ;
int hash_object(int f,const char *filename, unsigned char *file_hash);//f 1表示不生成obj对象 其他表示生成
void store_object(const char *filename, unsigned char *hash);
void cat_file(const char *hash);
void rm(const char *filename);
