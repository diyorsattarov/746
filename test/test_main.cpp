#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "../extern/httplib.h"
#include <spdlog/spdlog.h>

int main(void)
{
  httplib::Server svr;
  // Initialize the logger
  spdlog::set_level(spdlog::level::debug);
  spdlog::info("Server starting...");

  svr.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
    res.set_content("Hello World!", "text/plain");
  });

  svr.listen("localhost", 8080);
}
