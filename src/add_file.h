void add_file(const char *filename) ;
int hash_object(const char *filename, unsigned char *file_hash);
void store_object(const char *filename, unsigned char *hash);
void cat_file(const char *hash);
