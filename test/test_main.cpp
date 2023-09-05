#include <Windows.h>
#include "../extern/httplib.h"
#include "../extern/json.hpp"
#include <spdlog/spdlog.h>
#include <string>
#include <vector>
#include <unordered_map>

// Define a struct to represent a user
struct User {
    std::string id;
    std::string username;
    std::string password;
    std::string email;
};

// In-memory user database (for demonstration purposes)
std::unordered_map<std::string, User> users = {
    {"user1", {"user1", "John", "password123", "john@example.com"}},
    {"user2", {"user2", "Alice", "secret456", "alice@example.com"}}
};

// Function to parse URL path into components
std::vector<std::string> parse_url_path(const std::string& path) {
    std::vector<std::string> components;
    std::istringstream iss(path);
    std::string component;
    
    while (std::getline(iss, component, '/')) {
        if (!component.empty()) {
            components.push_back(component);
        }
    }
    
    return components;
}

int main(void) {
    httplib::Server svr;

    // Initialize the logger
    spdlog::set_level(spdlog::level::debug);
    spdlog::info("Server starting...");

    // Handle "/hi" route with text/plain content
    svr.Get("/hi", [](const httplib::Request&, httplib::Response& res) {
        res.set_content("Hello World!", "text/plain");
    });

    // Handle "/json/user/id" route
    svr.Get(R"(/json/user/(\d+))", [&](const httplib::Request& req, httplib::Response& res) {
        // Parse the user ID from the URL
        std::vector<std::string> components = parse_url_path(req.path);
        if (components.size() != 4) {
            res.status = 400; // Bad Request
            return;
        }

        int user_id = std::stoi(components[3]); // Convert the user ID to an integer

        // Check if the user ID exists in the database
        auto it = users.find("user" + std::to_string(user_id));
        if (it != users.end()) {
            // Return user data as JSON
            const User& user = it->second;
            nlohmann::json user_json;
            user_json["id"] = user.id;
            user_json["username"] = user.username;
            user_json["password"] = user.password;
            user_json["email"] = user.email;
            res.set_header("Access-Control-Allow-Origin", "http://localhost:3000");
            res.set_content(user_json.dump(), "application/json");
        } else {
            res.status = 404; // Not Found
        }
    });


    // Handle "/json/users" route
    svr.Get("/json/users", [&](const httplib::Request&, httplib::Response& res) {
        // Return a list of all users as JSON
        nlohmann::json user_array;
        for (const auto& pair : users) {
            const User& user = pair.second;
            nlohmann::json user_json;
            user_json["id"] = user.id;
            user_json["username"] = user.username;
            user_json["password"] = user.password;
            user_json["email"] = user.email;
            user_array.push_back(user_json);
        }

        res.set_header("Access-Control-Allow-Origin", "http://localhost:3000");
        res.set_content(user_array.dump(), "application/json");
    });

    // Catch-all route for handling non-existent routes
    svr.Get(R"(/.*)", [](const httplib::Request&, httplib::Response& res) {
      res.status = 404;
      res.set_content("Not Found", "text/plain");
    });

    svr.listen("localhost", 8080);
}
