//void store_object(const char *filename, unsigned char *hash);
void update(int f,unsigned char *commit_hash, const char *message);
void commit(const char *message);
void log_commit(unsigned char *commit_hash, const char *message) ;
//int create_commit_hash(const char *filename, unsigned char *file_hash);
