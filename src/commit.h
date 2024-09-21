//void store_object(const char *filename, unsigned char *hash);
void update(int f,unsigned char *commit_hash, const char *message);//1表示进入log 其他表示进入文本
void commit(const char *message);
void log_commit(unsigned char *commit_hash, const char *message) ;
//int create_commit_hash(const char *filename, unsigned char *file_hash);
