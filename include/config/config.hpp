#pragma once

class Config {
public:
  Config();

  int getPort() const;
  void setPort(int port);

private:
  int port;
};