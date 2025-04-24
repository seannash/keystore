#include "oauthmiddleware.h"

#include <cpr/cpr.h>
#include <crow/json.h>
#include <sstream>
#include <iomanip>

namespace framework {

OAuthMiddleware::OAuthMiddleware(const OAuthConfig& config)
    : config_(config) {
}

void OAuthMiddleware::before_handle(crow::request& req, crow::response& res, context& ctx) {
    // Skip OAuth for the callback endpoint
    if (req.url == "/oauth/callback") {
        return;
    }

    // Check for Authorization header
    auto auth_header = req.get_header_value("Authorization");
    if (!auth_header.empty()) {
        // Extract token from "Bearer <token>"
        if (auth_header.find("Bearer ") == 0) {
            std::string token = auth_header.substr(7);
            if (validate_token(token)) {
                return; // Token is valid, allow request to proceed
            }
        }
    }

    // No valid token found, redirect to OAuth login
    res.redirect(get_auth_url());
    res.end();
}

void OAuthMiddleware::after_handle(crow::request& req, crow::response& res, context& ctx) {
    // Handle OAuth callback
    if (req.url == "/oauth/callback") {
        auto code = req.url_params.get("code");
        if (code) {
            std::string token = exchange_code_for_token(code);
            if (!token.empty()) {
                // Store token in cache
                token_cache_[token] = "valid";
                // Set token in response cookie
                res.add_header("Set-Cookie", "token=" + token + "; HttpOnly; Secure");
                // Redirect back to original URL
                res.redirect("/");
                res.end();
                return;
            }
        }
        res.code = 400;
        res.body = "Invalid OAuth callback";
        res.end();
    }
}

bool OAuthMiddleware::validate_token(const std::string& token) {
    // Check token cache first
    if (token_cache_.find(token) != token_cache_.end()) {
        return true;
    }

    // TODO: Implement actual token validation with OAuth provider
    // This is a placeholder implementation
    return false;
}

std::string OAuthMiddleware::get_auth_url() const {
    std::stringstream ss;
    ss << config_.auth_endpoint
       << "?client_id=" << config_.client_id
       << "&redirect_uri=" << config_.redirect_uri
       << "&response_type=code"
       << "&scope=" << config_.scope;
    return ss.str();
}

std::string OAuthMiddleware::exchange_code_for_token(const std::string& code) {
    auto response = cpr::Post(
        cpr::Url{config_.token_endpoint},
        cpr::Payload{
            {"client_id", config_.client_id},
            {"client_secret", config_.client_secret},
            {"code", code},
            {"redirect_uri", config_.redirect_uri},
            {"grant_type", "authorization_code"}
        }
    );

    if (response.status_code == 200) {
        auto json = crow::json::load(response.text);
        if (json && json.has("access_token")) {
            return json["access_token"].s();
        }
    }
    return "";
}

} // namespace framework
