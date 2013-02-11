#ifndef FTPRINTER_TABLE_PRINTER_H_
#define FTPRINTER_TABLE_PRINTER_H_

#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

#include <ftprinter/PrintFormat.h>

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
  FTPrinter(const std::string& tableName, std::ostream& outStream,
            const std::string& separator = "|", const std::string& lineEnding = "");
  ~FTPrinter();

  //getter
  size_t numberOfColumns() const;
  virtual size_t tableWidth() const;
  const std::string& separator() const;
  const std::string& columnName(const size_t col) const;
  virtual size_t columnWidth(const size_t col) const;
  PrintFormat columnHeaderFormat(const size_t col) const;
  virtual size_t numberOfRows() const;
  const std::string& tableName() const; 

  void addColumn(const std::string& name, const size_t width = 25, const PrintFormat& format = format::basic);

  void printTableName();
  void printHeader();
  void printFooter();

  FTPrinter& append(const PrintFormat& format);
  FTPrinter& append(const endl input);
  FTPrinter& append(const float input);
  FTPrinter& append(const double input);

  template<typename T> FTPrinter& append(const T input) {
    if (_col == 0)
      _outStream << separator();

    _outStream << _format.formatString();

    // Leave 3 extra space: One for negative sign, one for zero, one for decimal
    std::stringstream strBuffer;
    strBuffer //<< std::setw(columnWidth(_col) - _displacement)
              << input;

    std::string str = strBuffer.str();
    size_t width = std::max<int>(str.size(), (int)columnWidth(_col) - _displacement);
    _displacement += (int)width - columnWidth(_col);

    _outStream << std::setw(width)
    		<< str
                << _format.unformatString();
    
    if (_col == numberOfColumns() - 1) {
      _outStream << separator();
      printEndl();
      _row++;
      _col = 0;
      _displacement = 0;
    }
    else {
      _outStream << separator();
      _col++;
    }

    return *this;
  }

  FTPrinter& operator<<(const PrintFormat& format);
  FTPrinter& operator<<(const endl input);
  FTPrinter& operator<<(const float input);
  FTPrinter& operator<<(const double input);

  //can't this be somewhere else? :/
  template<typename T> FTPrinter& operator<<(const T input) {
    return append(input);
  }

protected:
  void printHorizontalLine();
  void printEndl();
  void printColumnStart();
  void printColumnEnd();

  template<typename T> static std::string decimalNumberToStr(const T input, const size_t width);

  std::string _tableName;
  std::ostream& _outStream;
  std::vector<std::string> _columnNames;
  std::vector<size_t> _columnWidths;
  std::string _separator;
  std::string _lineEnding;

  PrintFormat _format;
  std::vector<PrintFormat> _headerFormats;

  size_t _row;
  size_t _col;
  size_t _displacement;
};

}// namespace ftprinter

#endif //FTPRINTER_TABLE_PRINTER_H_
