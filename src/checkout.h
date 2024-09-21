void checkout(const char *commit_hash);
char* read_object(int f,const char* hash);//1表示进入log 其他表示进入文本
void print_tree(const char* tree_hash);
void write_to_working_directory(const char* path, const char* content);
