#include "../extern/httplib.h"
#include <spdlog/spdlog.h>

int main(void)
{
  using namespace httplib;

  // Initialize the logger
  spdlog::set_level(spdlog::level::debug);
  auto logger = spdlog::stdout_logger_mt("logger");

  Server svr;

  // Log that the server is starting
  logger->info("Server starting...");

  svr.Get("/hi", [&](const Request& req, Response& res) {
    res.set_content("Hello World!", "text/plain");
    logger->info("Received request at /hi");
  });

  svr.Get(R"(/numbers/(\d+))", [&](const Request& req, Response& res) {
    auto numbers = req.matches[1];
    res.set_content(numbers, "text/plain");
    logger->info("Received request at /numbers/{}", numbers);
  });

  svr.Get("/users/:id", [&](const Request& req, Response& res) {
    auto user_id = req.path_params.at("id");
    res.set_content(user_id, "text/plain");
    logger->info("Received request at /users/{}", user_id);
  });

  svr.Get("/body-header-param", [&](const Request& req, Response& res) {
    if (req.has_header("Content-Length")) {
      auto val = req.get_header_value("Content-Length");
      logger->info("Content-Length header: {}", val);
    }
    if (req.has_param("key")) {
      auto val = req.get_param_value("key");
      logger->info("Query parameter 'key': {}", val);
    }
    res.set_content(req.body, "text/plain");
    logger->info("Received request at /body-header-param");
  });

  svr.Get("/stop", [&](const Request& req, Response& res) {
    svr.stop();
    logger->info("Server stopped");
  });

  // Log that the server is listening
  logger->info("Server listening on localhost:1234");

  svr.listen("localhost", 1234);
}