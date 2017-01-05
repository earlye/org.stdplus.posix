#include <org.stdplus/posix/basename.hpp>

#include <libgen.h>

namespace org
{
  namespace stdplus
  {
    namespace posix
    {
      std::string basename(std::string const& path)
      {
        std::string result = path;
        result = ::basename((char*)result.data());
        return result;
      }
    } // namespace posix
  } // namespace stdplus
} // namespace org
