#include <org.stdplus/posix/popen3.hpp>

#include <unistd.h>
#include <errno.h>

#include <cassert>
#include <cstdio>

namespace org
{
  namespace stdplus
  {
    namespace posix
    {
      // from https://sites.google.com/site/williamedwardscoder/popen3
      int popen3(int fd[3],const char **const cmd)
      {
        int i, e;
        int p[3][2];
        pid_t pid;

        assert(STDIN_FILENO==0);
        assert(STDOUT_FILENO==1);
        assert(STDERR_FILENO==2);

        // set all the FDs to invalid
        for(i=0; i<3; i++)
          p[i][0] = p[i][1] = -1;
        // create the pipes
        for(int i=0; i<3; i++)
          if(pipe(p[i]))
            goto error;
        // and fork
        pid = fork();
        if(-1 == pid)
          goto error;
        // in the parent?
        if(pid) {
          // parent
          fd[STDIN_FILENO] = p[STDIN_FILENO][1];
          fd[STDOUT_FILENO] = p[STDOUT_FILENO][0];
          fd[STDERR_FILENO] = p[STDERR_FILENO][0];
          close(p[STDIN_FILENO][0]);
          close(p[STDOUT_FILENO][1]);
          close(p[STDERR_FILENO][1]);
          // success
          return pid;
        } else {
          // child
          dup2(p[STDIN_FILENO][0],STDIN_FILENO);
          close(p[STDIN_FILENO][1]);
          dup2(p[STDOUT_FILENO][1],STDOUT_FILENO);
          close(p[STDOUT_FILENO][0]);
          dup2(p[STDERR_FILENO][1],STDERR_FILENO);
          close(p[STDERR_FILENO][0]);
          // here we try and run it
          execv(*cmd,const_cast<char*const*>(cmd));
          // if we are there, then we failed to launch our program
          perror("Could not launch");
          fprintf(stderr," \"%s\"\n",*cmd);
          _exit(EXIT_FAILURE);
        }
      error:
        // preserve original error
        e = errno;
        for(i=0; i<3; i++) {
          close(p[i][0]);
          close(p[i][1]);
        }
        errno = e;
        return -1;
      }

    } // namespace posix
  } // namespace stdplus
} // namespace org
