#ifndef hD4B43BBF_598D_43CE_9616_95E0B6385DF2
#define hD4B43BBF_598D_43CE_9616_95E0B6385DF2

namespace org
{
  namespace stdplus
  {
    namespace posix
    {
      /**
       * Open a process, with stdin,stdout, and stderr redirected.
       *
       * preconditions:
       *
       *   cmd is a null-terminated list of null-terminated strings representing the command to execute.
       *
       * postconditions:
       *
       *   fd[STDIN_FILENO] is the write-side of the child STDIN pipe
       *   fd[STDOUT_FILENO] is the read-side of the child's STDOUT pipe
       *   fd[STDERR_FILENO] is the read-side of the child's STDERR pipe
       *
       *   result is child's pid.
       */
      int popen3(int fd[3],const char **const cmd);

    } // namespace stdplus
  } // namespace posix
} // namespace org

#endif
