void create_branch(const char *branch_name, const char *commit_hash);
void list_branches();
void delete_branch(const char *branch_name);
void rename_branch(const char *old_name, const char *new_name); 
void update_branch(const char *branch_name, const char *new_commit_hash);
