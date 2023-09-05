#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "../extern/httplib.h"
#include <spdlog/spdlog.h>

int main(void) {
  httplib::Server svr;

  svr.set_default_headers({
    {"Access-Control-Allow-Origin", "http://localhost:3000"},
    {"Access-Control-Allow-Methods", "GET, POST, OPTIONS"},
    {"Access-Control-Allow-Headers", "Origin, Content-Type, Accept"}
});

  // Initialize the logger
  spdlog::set_level(spdlog::level::debug);
  spdlog::info("Server starting...");

  // Handle "/hi" route with text/plain content
  svr.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
    res.set_content("Hello World!", "text/plain");
  });

  // Handle "/json" route with application/json content
  svr.Get("/json", [](const httplib::Request &, httplib::Response &res) {
    // Create a JSON response
    std::string json_content = "{\"message\": \"Hello JSON!\"}";

    // Set CORS headers for this specific route
    res.set_header("Access-Control-Allow-Origin", "http://localhost:3000");
    res.set_content(json_content, "application/json");
});

  svr.listen("localhost", 8080);
}