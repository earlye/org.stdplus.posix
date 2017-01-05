#include <org.stdplus/posix/Run.hpp>

#include <org.stdplus/posix/popen3.hpp>

#include <unistd.h>
#include <sys/wait.h>

namespace org
{
  namespace stdplus
  {
    namespace posix
    {
      Run::Run(std::vector<std::string> const& commandLine)
        : m_status(-1)
      {
        // convert to something popen3 can use.
        std::vector<char const*> command;
        for( std::string const& arg:commandLine )
          {
            command.push_back(arg.c_str());
          }
        command.push_back(NULL);

        m_childPid = popen3(m_pipes,command.data());
        if (m_childPid == -1)
          throw std::runtime_error("Couldn't launch process");
      }

      Run::~Run()
      {
        if (m_pipes[STDIN_FILENO])
          close(m_pipes[STDIN_FILENO]);
        if (m_pipes[STDOUT_FILENO])
          close(m_pipes[STDOUT_FILENO]);
        if (m_pipes[STDERR_FILENO])
          close(m_pipes[STDERR_FILENO]);
      }

      int Run::wait()
      {
        if (m_status <0)
          waitpid(m_childPid,&m_status,0);
        return m_status;
      }

      void Run::readStdout()
      {
        char buffer[1024];
        ssize_t bytes_read;
        do
          {
            bytes_read = read(m_pipes[STDOUT_FILENO],buffer, sizeof(buffer));
            buffer[bytes_read]='\0';
            m_stdout += buffer;
          }
        while(bytes_read);
      }

      std::string const& Run::getStdout() const
      {
        return m_stdout;
      }
    } // namespace stdplus
  } // namespace posix
} // namespace org
