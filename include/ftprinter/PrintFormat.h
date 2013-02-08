#ifndef FTPRINTER_PRINTFORMAT_H
#define FTPRINTER_PRINTFORMAT_H

#include <string>

namespace ftprinter {

enum PrintColor { c_basic,
                  c_black,
                  c_red,
		  c_green,
		  c_yellow,
		  c_blue,
		  c_magenta,
		  c_cyan,
                  c_white };

enum PrintAttribute { a_none,
                      a_bold,
		      a_italic };


class PrintFormat {
public:
  PrintFormat(PrintColor color = c_black, PrintAttribute attribute = a_none) :
    _color(color),
    _attribute(attribute) {}
  ~PrintFormat() {}

  PrintAttribute attribute() const;
  PrintColor color() const;

  std::string formatString() const;
  std::string unformatString() const;

private:
  PrintColor _color;
  PrintAttribute _attribute;
};


//predefined formats
namespace format {
//normal formats
  const PrintFormat basic = PrintFormat  (c_basic,   a_none);
  const PrintFormat black = PrintFormat  (c_black,   a_none);
  const PrintFormat red = PrintFormat    (c_red,     a_none);
  const PrintFormat green = PrintFormat  (c_green,   a_none);
  const PrintFormat yellow = PrintFormat (c_yellow,  a_none);
  const PrintFormat blue = PrintFormat   (c_blue,    a_none);
  const PrintFormat magenta = PrintFormat(c_magenta, a_none);
  const PrintFormat cyan = PrintFormat   (c_cyan,    a_none);
  const PrintFormat white = PrintFormat  (c_white,   a_none);

//bold formats
  const PrintFormat basic_b = PrintFormat  (c_basic,   a_bold);
  const PrintFormat black_b = PrintFormat  (c_black,   a_bold);
  const PrintFormat red_b = PrintFormat    (c_red,     a_bold);
  const PrintFormat green_b = PrintFormat  (c_green,   a_bold);
  const PrintFormat yellow_b = PrintFormat (c_yellow,  a_bold);
  const PrintFormat blue_b = PrintFormat   (c_blue,    a_bold);
  const PrintFormat magenta_b = PrintFormat(c_magenta, a_bold);
  const PrintFormat cyan_b = PrintFormat   (c_cyan,    a_bold);
  const PrintFormat white_b = PrintFormat  (c_white,   a_bold);

//italic formats
  const PrintFormat basic_i = PrintFormat  (c_basic,   a_italic);
  const PrintFormat black_i = PrintFormat  (c_black,   a_italic);
  const PrintFormat red_i = PrintFormat    (c_red,     a_italic);
  const PrintFormat green_i = PrintFormat  (c_green,   a_italic);
  const PrintFormat yellow_i = PrintFormat (c_yellow,  a_italic);
  const PrintFormat blue_i = PrintFormat   (c_blue,    a_italic);
  const PrintFormat magenta_i = PrintFormat(c_magenta, a_italic);
  const PrintFormat cyan_i = PrintFormat   (c_cyan,    a_italic);
  const PrintFormat white_i = PrintFormat  (c_white,   a_italic);
} //namespace format

} //namespace ftprinter


#endif //FTPRINTER_PRINTFORMAT_H

