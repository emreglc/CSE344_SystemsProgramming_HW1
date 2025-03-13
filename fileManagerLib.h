#ifndef FILE_MANAGER_LIB_H
#define FILE_MANAGER_LIB_H

void create_directory(const char *folder_name);
void create_file(const char *file_name);
void list_directory(const char *folder_name);
void list_files_by_extension(const char *folder_name, const char *extension);
void read_file(const char *file_name);
void append_to_file(const char *file_name, const char *content);
void delete_file(const char *file_name);
void delete_directory(const char *folder_name);

#endif // FILE_MANAGER_LIB_H