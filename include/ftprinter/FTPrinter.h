#ifndef FTPRINTER_TABLE_PRINTER_H_
#define FTPRINTER_TABLE_PRINTER_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

#include "PrintFormat.h"

namespace ftprinter {

class endl{};
/** \class FTPrinter
 **
 **Print a pretty table into your output of choice.
 **
 **Usage:
 ** FTPrinter tp(&std::cout);
 ** tp.addColumn("Name", 25);
 ** tp.addColumn("Age", 3);
 ** tp.addColumn("Position", 30);

 ** tp.printHeader();
 ** tp << "Dat Chu" << 25 << "Research Assistant";
 ** tp << "John Doe" << 26 << "Professional Anonymity";
 ** tp << "Jane Doe" << tp.SkipToNextLine();
 ** tp << "Tom Doe" << 7 << "Student";
 ** tp.printFooter();
 */
class FTPrinter{
public:
  FTPrinter(std::ostream* output = &std::cout, const std::string& separator = "|", const std::string& lineEnding = "");
  ~FTPrinter();

  //getter
  unsigned int numberOfColumns() const;
  unsigned int tableWidth() const;
  std::string separator() const;
  std::string columnName(const unsigned int i) const;
  unsigned int columnWidth(const unsigned int i) const;
  PrintFormat columnHeaderFormat(const unsigned int i) const;
  unsigned int numberOfRows() const;

  void addColumn(const std::string& name, const unsigned int width = 25, const PrintFormat& format = format::none);

  void printHeader();
  void printFooter();

  FTPrinter& operator<<(const PrintFormat& format);
  FTPrinter& operator<<(endl input);
  FTPrinter& operator<<(float input);
  FTPrinter& operator<<(double input);

  //can't this be somewhere else? :/
  template<typename T> FTPrinter& operator<<(T input) {
    if (_col == 0)
      *_outStream << separator();

    *_outStream << _format.formatString();

    // Leave 3 extra space: One for negative sign, one for zero, one for decimal
    std::stringstream strBuffer;
    strBuffer //<< std::setw(columnWidth(_col) - _displacement)
              << input;

    std::string str = strBuffer.str();
    size_t width = std::max<int>(str.size(), (int)columnWidth(_col) - _displacement);
    //std::cout << "(" << _displacement << ", " << (int)width - columnWidth(_col);
    _displacement += (int)width - columnWidth(_col);
    //std::cout << "=>" << _displacement << ")" << std::endl;

    *_outStream << std::setw(width)
    		<< str
                << _format.unformatString();
    
    if (_col == numberOfColumns() - 1) {
      *_outStream << separator();
      printEndl();
      _row++;
      _col = 0;
      _displacement = 0;
    }
    else {
      *_outStream << separator();
      _col++;
    }

    return *this;
  }

private:
  void printHorizontalLine();
  void printEndl();
  void printColumnStart();
  void printColumnEnd();

  template<typename T> static std::string decimalNumberToStr(const T input, const size_t width);

  std::ostream* _outStream;
  std::vector<std::string> _columnNames;
  std::vector<unsigned int> _columnWidths;
  std::string _separator;
  std::string _lineEnding;

  PrintFormat _format;
  std::vector<PrintFormat> _headerFormats;

  unsigned int _row;
  unsigned int _col;
  unsigned int _displacement;
};

}// namespace ftprinter

#endif //FTPRINTER_TABLE_PRINTER_H_
