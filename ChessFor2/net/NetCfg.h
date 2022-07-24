#pragma once

#include <string>

class NetCfg {
public:
  enum Role { HOST, CLIENT };

  NetCfg();

  ~NetCfg();

  Role getRole() const;

  std::string getGameHostIp() const;

private:
  Role m_role;
  std::string m_hostIp;
};
