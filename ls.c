#include "ls.h"

void ls(char dir_paths[][INT_MAX], int show_hidden_files, int detailed_view, int num_paths)
{
    if (detailed_view == 0)
    {
        for (int i = 0; i < num_paths; i++)
        {
            DIR *dir;
            struct dirent *d;
            char *path = dir_paths[i];
            dir = opendir(path);
            // Check if an error has occured
            if (dir == 0)
            {
                perror(path);
                continue;
            }

            // Normal execution of code
            // Reading contents of the directory
            if (num_paths > 1)
            {
                printf("%s:\n", dir_paths[i]);
            }
            while ((d = readdir(dir)) != NULL)
            {
                if (show_hidden_files == 0 && d->d_name[0] == '.')
                    continue;
                printf("%s\n", d->d_name);
            }
            if (num_paths > 1 && i != num_paths - 1)
            {
                printf("\n");
            }
            closedir(dir);
        }
    }
    else
    {
        for (int i = 0; i < num_paths; i++)
        {
            DIR *dir;
            struct dirent *d;
            char *path = dir_paths[i];
            dir = opendir(path);

            // Detailed view info
            struct stat directory;
            struct tm *time;
            char date[INT_MAX], final_date[13];
            long long int total;

            if (dir == 0)
            {
                perror(path);
                continue;
            }
            // Normal execution of code
            // Reading contents of the directory
            if (num_paths > 1)
            {
                printf("%s:\n", dir_paths[i]);
            }
            while ((d = readdir(dir)) != NULL)
            {
                char current_path[INT_MAX];

                strcpy(current_path, path);
                strcat(current_path, "/");
                strcat(current_path, d->d_name);
                stat(current_path, &directory);

                if (show_hidden_files == 0 && d->d_name[0] == '.')
                    continue;
                total += directory.st_blocks;
            }
            printf("total %lld\n", total / 2);
            closedir(dir);

            dir = opendir(path);
            while ((d = readdir(dir)) != NULL)
            {
                char current_path[INT_MAX];

                strcpy(current_path, path);
                strcat(current_path, "/");
                strcat(current_path, d->d_name);
                stat(current_path, &directory);

                if (show_hidden_files == 0 && d->d_name[0] == '.')
                    continue;

                // For filetype
                char file_type;

                file_type = S_ISDIR(directory.st_mode) ? 'd' : S_ISBLK(directory.st_mode) ? 'b'
                                                           : S_ISCHR(directory.st_mode)   ? 'c'
                                                           : S_ISFIFO(directory.st_mode)  ? 'f'
                                                           : S_ISLNK(directory.st_mode)   ? 'l'
                                                           : S_ISSOCK(directory.st_mode)  ? 's'
                                                                                          : '-';

                printf("%c", file_type);
                // Permissions
                printf((directory.st_mode & S_IRUSR) ? "r" : "-");
                printf((directory.st_mode & S_IWUSR) ? "w" : "-");
                printf((directory.st_mode & S_IXUSR) ? "x" : "-");
                printf((directory.st_mode & S_IRGRP) ? "r" : "-");
                printf((directory.st_mode & S_IWGRP) ? "w" : "-");
                printf((directory.st_mode & S_IXGRP) ? "x" : "-");
                printf((directory.st_mode & S_IROTH) ? "r" : "-");
                printf((directory.st_mode & S_IWOTH) ? "w" : "-");
                printf((directory.st_mode & S_IXOTH) ? "x" : "-");
                // Other Info
                int num_links;
                long long int file_size;
                char *user_name, *group_name;
                num_links = directory.st_nlink;
                file_size = directory.st_size;
                user_name = getpwuid(directory.st_uid)->pw_name;
                group_name = getgrgid(directory.st_gid)->gr_name;
                time = localtime(&directory.st_mtime);
                strftime(date, INT_MAX, nl_langinfo(D_T_FMT), time);
                int k = 0;
                for (int i = 4; i <= 15; i++)
                {
                    final_date[k++] = date[i];
                }
                final_date[k] = '\0';

                printf(" %2d", num_links);
                printf(" %8.8s", user_name);
                printf(" %8.8s", group_name);
                printf(" %10lld", file_size);
                printf(" %s %s\n", final_date, d->d_name);
            }
            closedir(dir);
            if (num_paths > 1 && i != num_paths - 1)
            {
                printf("\n");
            }
        }
    }
}

void exec_ls(char input_tokens[][INT_MAX], int size)
{
    int show_hidden_files = 0;
    int detailed_view = 0;
    int no_dir_address_given = 0;
    for (int i = 1; i < size; i++)
    {
        if (strcmp(input_tokens[i], "-a") == 0)
            show_hidden_files = 1;
        if (strcmp(input_tokens[i], "-l") == 0)
            detailed_view = 1;
        if (strcmp(input_tokens[i], "-la") == 0 || strcmp(input_tokens[i], "-al") == 0)
        {
            show_hidden_files = 1;
            detailed_view = 1;
        }
    }

    // for all directory paths
    int num_paths = 0;
    char dir_paths[100][INT_MAX];
    for (int i = 1; i < size; i++)
    {
        // printf("extra arguments: %s\n", input_tokens[i]);
        if (input_tokens[i][0] != '-')
        {
            if (input_tokens[i][0] == '~')
            {
                strcpy(dir_paths[num_paths], home_path);
                strcat(dir_paths[num_paths], input_tokens[i] + 1);
            }
            else
            {
                strcpy(dir_paths[num_paths], input_tokens[i]);
            }
            num_paths++;
            no_dir_address_given++;
        }
    }
    if (no_dir_address_given == 0)
    {
        char cur_dir[INT_MAX];
        getcwd(cur_dir, INT_MAX);
        strcpy(dir_paths[num_paths], cur_dir);
        num_paths++;
    }
    ls(dir_paths, show_hidden_files, detailed_view, num_paths);
    // for (int i = 1; i <= num_paths; i++)
    //     printf("%s\n", dir_paths[i]);
}