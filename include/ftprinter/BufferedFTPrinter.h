#ifndef FTPRINTER_BUFFEREDFTPRINTER_H_
#define FTPRINTER_BUFFEREDFTPRINTER_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

#include "FTPrinter.h"

namespace ftprinter {

/**\class BufferedFTPrinter
 *
 * Print a pretty table into your output of choice.
 *
 * Usage:
 * BufferedFTPrinter tp(&std::cout);
 * tp.addColumn("Name", 25);
 * tp.addColumn("Age", 3);
 * tp.addColumn("Position", 30);

 * tp.printHeader();
 * tp << "Dat Chu" << 25 << "Research Assistant";
 * tp << "John Doe" << 26 << "Professional Anonymity";
 * tp << "Jane Doe" << tp.SkipToNextLine();
 * tp << "Tom Doe" << 7 << "Student";
 * tp.printFooter();
 *
 */
class BufferedFTPrinter : public FTPrinter{
public:
  BufferedFTPrinter(const std::string& tableName, std::ostream* const output = &std::cout,
                    const std::string& separator = "|", const std::string& lineEnding = "");
  ~BufferedFTPrinter();

  //getter
  size_t maxTableWidth() const;
  size_t maxColumnWidth(const size_t col) const;
  size_t numberOfPrintedRows() const;
  size_t numberOfBufferedRows() const;
  size_t numberOfRows() const;

  void addColumn(const std::string& name, const size_t width = 25, const PrintFormat& format = format::basic);
  void addColumn(const std::string& name, const size_t width = 15,
                 const size_t maxWidth = 40, const PrintFormat& format = format::basic);

  void printTableName();
  void printHeader();
  void printFooter();

  void printOut(const size_t rows = (size_t) -1);
  void flush(const size_t rows = (size_t) -1);
  void clear(const size_t rows = (size_t) -1);
  
  FTPrinter& append(const PrintFormat& format);
  FTPrinter& append(const endl input);
  FTPrinter& append(const float input);
  FTPrinter& append(const double input);

  FTPrinter& operator<<(const PrintFormat& format);
  FTPrinter& operator<<(const endl input);
  FTPrinter& operator<<(const float input);
  FTPrinter& operator<<(const double input);

  template<typename T> FTPrinter& operator<<(const T input) {
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

protected:
  void printHorizontalLine();
  void printEndl();
  void printColumnStart();
  void printColumnEnd();

  enum SpecialLines {lineFooter = -1, lineHeader = - 2, lineTableName = -3};

  //vectores that contain the buffered data
  std::vector<int> _lines;
  std::vector<PrintFormat> _columnFormats;
  std::vector<std::string> _columns;

  std::vector<size_t> _maxColumnWidths;
};

}// namespace ftprinter

#endif //FTPRINTER_BUFFEREDTFPRINTER_H_
