#ifndef hCA3D150A_FFEA_4337_B2B6_8664012F9299
#define hCA3D150A_FFEA_4337_B2B6_8664012F9299

#include <string>
#include <vector>

namespace org
{
  namespace stdplus
  {
    namespace posix
    {
      class Run
      {
      public:
        Run(std::vector< std::string > const& commandLine);
        Run(Run const& copy) = delete;
        Run(Run const&& move) = delete;
        Run() = delete;

        void readStdout();
        std::string const& getStdout() const;
        int wait();

        ~Run();
      private:
        int m_childPid;
        int m_pipes[3];
        int m_status;
        std::string m_stdout;
        std::string m_stderr;
      };

    } // namespace stdplus
  } // namespace posix
} // namespace org

#endif
