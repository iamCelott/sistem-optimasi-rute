
#include "../headers/normalize_coordinate.h"
#include <regex>
#include <sstream>
#include <stdexcept>

std::pair<double, double> NormalizeCoordinate(const std::string &input) {
  if (input.empty()) {
    throw std::invalid_argument("Input tidak boleh kosong!");
  }

  double latitude, longitude;

  std::regex coordinatePattern(
      R"(^\s*(-?\d+(?:\.\d+)?)\s*,\s*(-?\d+(?:\.\d+)?)\s*$)");
  std::smatch match;

  if (std::regex_match(input, match, coordinatePattern)) {
    latitude = std::stod(match[1].str());
    longitude = std::stod(match[2].str());
  } else {
    if (input.find("google.com/maps") == std::string::npos) {
      throw std::invalid_argument(
          "Input harus berupa koordinat atau link Google Maps!");
    }

    std::regex linkPattern(R"(/@(-?\d+(?:\.\d+)?),(-?\d+(?:\.\d+)?))");

    if (!std::regex_search(input, match, linkPattern)) {
      throw std::invalid_argument("Format link Google Maps tidak valid!");
    }

    latitude = std::stod(match[1].str());
    longitude = std::stod(match[2].str());
  }

  if (latitude < -90 || latitude > 90) {
    throw std::invalid_argument(
        "Latitude harus berada di antara -90 sampai 90!");
  }

  if (longitude < -180 || longitude > 180) {
    throw std::invalid_argument(
        "Longitude harus berada di antara -180 sampai 180!");
  }

  return {latitude, longitude};
}
