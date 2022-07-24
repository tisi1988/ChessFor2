#include "NetCfg.h"

#include <fstream>
#include <iostream>
#include <stdexcept>

namespace {
std::string parseFile() {
  std::ifstream fich("net.cfg");
  if (!fich.is_open()) {
    throw std::runtime_error("Error opening the network settings file");
  }

  std::string value;
  fich >> value;

  if (value.empty()) {
    throw std::runtime_error("Error parsing the host IP");
  }

  return value;
}
} // namespace

NetCfg::NetCfg() {
  m_hostIp = parseFile();

  if (m_hostIp == "localhost" || m_hostIp == "0.0.0.0") {
    m_role = NetCfg::HOST;
  } else {
    m_role = NetCfg::CLIENT;
  }
}

NetCfg::~NetCfg() {}

NetCfg::Role NetCfg::getRole() const { return m_role; }

std::string NetCfg::getGameHostIp() const { return m_hostIp; }
