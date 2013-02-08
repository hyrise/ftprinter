#include "ftprinter/PrintFormat.h"

#include <sstream>

namespace ftprinter{

PrintColor PrintFormat::color() const {
  return _color;
}
PrintAttribute PrintFormat::attribute() const {
  return _attribute;
}

std::string PrintFormat::formatString() const {
  std::stringstream buf;

  buf << "\033[";

  switch (color()) {
    case c_basic:   break;
    case c_black:   buf << "30"; break;
    case c_red:     buf << "31"; break;
    case c_green:   buf << "32"; break;
    case c_yellow:  buf << "33"; break;
    case c_blue:    buf << "34"; break;
    case c_magenta: buf << "35"; break;
    case c_cyan:    buf << "36"; break;
    case c_white:   buf << "37"; break;
  }
  
  buf << ';';

  switch (attribute()) {
    case a_none:   buf << "10"; break;
    case a_bold:   buf << '1'; break;
    case a_italic: buf << '3'; break;
  }

  buf << 'm';

  return buf.str();
}

std::string PrintFormat::unformatString() const {
  return std::string("\033[0m");
}

} //namespace ftprinter
