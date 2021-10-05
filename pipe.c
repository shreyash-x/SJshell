#include "pipe.h"
#include "execute.h"

// int pipe(int fds[2]);

// Parameters :
// fd[0] will be the fd(file descriptor) for the
// read end of pipe.
// fd[1] will be the fd for the write end of pipe.
// Returns : 0 on Success.
// -1 on error.

int check_syntax(char input_tokens[][INT_MAX], int size)
{
    int x = 0;
    for (int i = 0; i < size - 1; i++)
    {
        if (strcmp(input_tokens[i], input_tokens[i + 1]) == 0)
        {
            x = -1;
            break;
        }
    }

    if (strcmp(input_tokens[0], "|") == 0 || strcmp(input_tokens[size - 1], "|") == 0)
        x = -1;

    return x;
}

void exec_pipe(char input_tokens[][INT_MAX], int size, char command[])
{
    if (check_syntax(input_tokens, size) == -1)
    {
        fprintf(stderr, "Invalid Syntax\n");
        return;
    }
    char pipe_commands[30][INT_MAX];
    int num_cmds = 0;
    char *Token;
    Token = strtok(command, "|");
    while (Token != NULL)
    {
        strcpy(pipe_commands[num_cmds], Token);
        num_cmds++;
        Token = strtok(NULL, "|");
    }

    int fd[num_cmds][2];
    for (int i = 0; i < num_cmds; i++)
    {
        if (i != num_cmds - 1)
        {
            if (pipe(fd[i]) == -1)
            {
                fprintf(stderr, "Failed to pipe\n");
                continue;
            }
        }

        // Case (1) : No read, only write
        if (i == 0)
        {
            int write_fd = dup(STDOUT_FILENO);
            dup2(fd[0][1], STDOUT_FILENO);
            // dup2 opens the fd, we must close it
            close(fd[0][1]);

            // tokenizing
            char tokens[30][INT_MAX];
            int itr = 0;
            char delimiter[5] = " \t";
            char *token;
            token = strtok(pipe_commands[i], delimiter);
            while (token != NULL)
            {
                strcpy(tokens[itr], token);
                itr++;
                token = strtok(NULL, delimiter);
            }
            execute(tokens, itr, pipe_commands[i]);
            dup2(write_fd, STDOUT_FILENO);
            close(write_fd);
        }
        else if (i == num_cmds - 1) // Case(2) : No write, only read
        {
            int read_fd = dup(STDIN_FILENO);
            dup2(fd[num_cmds - 2][0], STDIN_FILENO);
            // dup2 opens the fd, we must close it
            close(fd[num_cmds - 2][0]);

            // tokenizing
            char tokens[30][INT_MAX];
            int itr = 0;
            char delimiter[5] = " \t";
            char *token;
            token = strtok(pipe_commands[i], delimiter);
            while (token != NULL)
            {
                strcpy(tokens[itr], token);
                itr++;
                token = strtok(NULL, delimiter);
            }

            execute(tokens, itr, pipe_commands[i]);
            dup2(read_fd, STDIN_FILENO);
            close(read_fd);
        }
        else // Case(3) : Both read and write
        {
            int write_fd = dup(STDOUT_FILENO);
            int read_fd = dup(STDIN_FILENO);
            dup2(fd[i][1], STDOUT_FILENO);
            dup2(fd[i - 1][0], STDIN_FILENO);
            // dup2 opens the fd, we must close it
            close(fd[i][1]);
            close(fd[i - 1][0]);

            // tokenizing
            char tokens[30][INT_MAX];
            int itr = 0;
            char delimiter[5] = " \t";
            char *token;
            token = strtok(pipe_commands[i], delimiter);
            while (token != NULL)
            {
                strcpy(tokens[itr], token);
                itr++;
                token = strtok(NULL, delimiter);
            }

            execute(tokens, itr, pipe_commands[i]);
            dup2(write_fd, STDOUT_FILENO);
            dup2(read_fd, STDIN_FILENO);
            close(write_fd);
            close(read_fd);
        }
    }
}
