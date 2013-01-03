#include "ftprinter/PrintFormat.h"

#include <sstream>

namespace ftprinter{

std::string PrintFormat::formatString() const {
  std::stringstream buf;

  buf << "\033[";
  if (bold())
    buf << '1';
  else
    buf << '0';
  buf << ';';

  switch(color()){
    case c_none: return "";
    case c_black: buf << "30"; break;
    case c_red: buf << "31"; break;
    case c_green: buf << "32"; break;
    case c_yellow: buf << "33"; break;
    case c_blue: buf << "34"; break;
    case c_magenta: buf << "35"; break;
    case c_cyan: buf << "36"; break;
    case c_white: buf << "37"; break;
  }
  buf << 'm';

  return buf.str();
}

std::string PrintFormat::unformatString() const {
  if (color() == c_none)
    return "";
  return std::string("\033[0m");
}

} //namespace ftprinter
