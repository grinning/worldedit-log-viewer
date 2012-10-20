#include "timestamp.h"
std::string ts2str(Timestamp ts) {
  std::stringstream ss;
  ss << ts.year << '-' << ts.month << '-' << ts.day << ' ' << ts.hour << ':' << ts.min << ':' << ts.sec;
  return ss.str();
}
