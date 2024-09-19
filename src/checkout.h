void checkout(const char *commit_hash);
char* read_object(int f,const char* hash);
void print_tree(const char* tree_hash);
void write_to_working_directory(const char* path, const char* content);
