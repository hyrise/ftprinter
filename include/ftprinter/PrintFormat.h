#ifndef FTPRINTER_PRINTFORMAT_H
#define FTPRINTER_PRINTFORMAT_H

#include <string>

namespace ftprinter {

enum PrintColor {c_none,
                 c_black,
                 c_red,
		 c_green,
		 c_yellow,
		 c_blue,
		 c_magenta,
		 c_cyan,
                 c_white};

class PrintFormat {
public:
  PrintFormat(PrintColor color = c_black, bool bold = false) :
    _color(color),
    _bold(bold) {}
  ~PrintFormat() {}

  inline PrintColor color() const {
    return _color;
  }
  inline bool bold() const {
    return _bold;
  }

  std::string formatString() const;
  std::string unformatString() const;

private:
  PrintColor _color;
  bool _bold;
};


//predefined formats
namespace format {
  const PrintFormat none = PrintFormat(c_none);
  const PrintFormat black = PrintFormat(c_black);
  const PrintFormat red = PrintFormat(c_red);
  const PrintFormat green = PrintFormat(c_green);
  const PrintFormat yellow = PrintFormat(c_yellow);
  const PrintFormat blue = PrintFormat(c_blue);
  const PrintFormat magenta = PrintFormat(c_magenta);
  const PrintFormat cyan = PrintFormat(c_cyan);
  const PrintFormat white = PrintFormat(c_white);
} //namespace format

} //namespace ftprinter


#endif //FTPRINTER_PRINTFORMAT_H

