#include "../headers/normalize_link.h"
#include <regex>
#include <stdexcept>

std::pair<double, double> NormalizeLink(const std::string &url) {
  if (url.empty()) {
    throw std::invalid_argument("Link tidak boleh kosong");
  }

  if (url.find("google.com/maps") == std::string::npos) {
    throw std::invalid_argument("Link bukan Google Maps");
  }

  std::regex pattern(R"(/@(-?\d+(?:\.\d+)?),(-?\d+(?:\.\d+)?))");
  std::smatch match;

  if (!std::regex_search(url, match, pattern)) {
    throw std::invalid_argument("Format link Google Maps tidak valid");
  }

  double latitude = std::stod(match[1].str());
  double longitude = std::stod(match[2].str());

  if (latitude < -90 || latitude > 90) {
    throw std::invalid_argument(
        "Latitude harus berada di antara -90 sampai 90");
  }

  if (longitude < -180 || longitude > 180) {
    throw std::invalid_argument(
        "Longitude harus berada di antara -180 sampai 180");
  }

  return {latitude, longitude};
}