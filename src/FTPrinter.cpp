#include "ftprinter/FTPrinter.h"

#include <stdexcept>
#include <iomanip>
#include <stdexcept>

#include "ftprinter/PrintFormat.h"


namespace ftprinter {

FTPrinter::FTPrinter(std::ostream* output, const std::string& separator, const std::string& lineEnding) :
  _outStream(output),
  _separator(separator),
  _lineEnding(lineEnding),
  _format(format::none),
  _row(0),
  _col(0),
  _displacement(0) {}

FTPrinter::~FTPrinter() {}

//getter
unsigned int FTPrinter::numberOfColumns() const {
  return _columnNames.size();
}
unsigned int FTPrinter::tableWidth() const {
  unsigned int tableWidth = separator().size();
  for (unsigned int i = 0; i < numberOfColumns(); ++i)
    tableWidth += columnWidth(i) + separator().size();
  return tableWidth;
}
std::string FTPrinter::separator() const {
  return _separator;
}
std::string FTPrinter::columnName(const unsigned int i) const {
  return _columnNames[i];
}
unsigned int FTPrinter::columnWidth(const unsigned int i) const {
  return _columnWidths[i];
}
PrintFormat FTPrinter::columnHeaderFormat(const unsigned int i) const {
  return _headerFormats[i];
}
unsigned int FTPrinter::numberOfRows() const {
  return _row;
}


/** \brief Add a column to our table
 ** 
 ** \param name Name to be print for the header
 ** \param width the width of the column (has to be >=5)
 ** \param format the format of the header cell
 ** */
void FTPrinter::addColumn(const std::string& name, unsigned int width, const PrintFormat& format){
  if (width < 4)
    throw std::invalid_argument("Column width has to be >= 4");
  if (name.size() == 0)
    throw std::invalid_argument("Column name cannot be \"\"");

  _columnNames.push_back(name);
  _columnWidths.push_back(width);
  _headerFormats.push_back(format);
}

void FTPrinter::printHorizontalLine() {
  if (_col > 0)
    *this << endl();

  *_outStream << "+"; // the left bar

  for (unsigned int i = 0; i < tableWidth() - 2; ++i)
    *_outStream << "-";

  *_outStream << "+"; // the right bar
  printEndl();
}

void FTPrinter::printEndl() {
  if (_lineEnding.size() != 0)
    *_outStream << _lineEnding;
  else
    *_outStream << std::endl;

  _format = format::none;
}

void FTPrinter::printHeader() {
  printHorizontalLine();
  *_outStream << separator();

  for (unsigned int i = 0; i < numberOfColumns(); ++i) {
    *_outStream << columnHeaderFormat(i).formatString();
    *_outStream << std::setw(columnWidth(i)) << columnName(i).substr(0, columnWidth(i));
    *_outStream << columnHeaderFormat(i).unformatString();
    if (i < numberOfColumns()){
      *_outStream << separator();
    }
  }

  //*_outStream << separator();
  printEndl();
  printHorizontalLine();
}

void FTPrinter::printFooter() {
  printHorizontalLine();
}

void FTPrinter::printColumnStart() {
  if (_col == 0)
    *_outStream << separator();
  *_outStream << _format.formatString();
}

void FTPrinter::printColumnEnd() {
  *_outStream << _format.unformatString();

  *_outStream << separator();

  ++_col;
  if (_col >= numberOfColumns() - 1) {
    printEndl();
    ++_row;
    _col = 0;
    _displacement = 0;
  }
}


FTPrinter& FTPrinter::operator<<(const PrintFormat& format) {
  _format = format;
  return *this;
}
FTPrinter& FTPrinter::operator<<(endl input) {
  while (_col > 0){
    *this << "";
  }
  return *this;
}
FTPrinter& FTPrinter::operator<<(float input) {
  return *this << (double) input;
}
FTPrinter& FTPrinter::operator<<(double input) {
  printColumnStart();

  *_outStream << decimalNumberToStr<double>(input, columnWidth(_col));

  printColumnEnd();
  return *this;
}

template<typename T>
std::string FTPrinter::decimalNumberToStr(const T input, const size_t width) {
//  *_outStream << _format.formatString();


  std::string str;

  // If we cannot handle this number, indicate so
  if (input < 10 * (width - 1) || input > 10 * width) {
    std::stringstream strBuffer;
    strBuffer << std::setiosflags(std::ios::fixed)
              << std::setprecision(width)
              << std::setw(width)
              << input;

    str = strBuffer.str();

    str[width - 1] = '*';
    return str.substr(0, width);
   // *_outStream << string_to_print;
  }
  else {
    // determine what precision we need
    int precision = width - 1; // leave room for the decimal point
    if (input < 0)
      --precision; // leave room for the minus sign

    // leave room for digits before the decimal?
    if (input <= -1 || input >= 1){
      int digitsBeforePoint = 1 + (int)log10(std::abs(input));
      precision -= digitsBeforePoint;
    }
    else
      --precision; // e.g. 0.12345 or -0.1234

    if (precision < 0)
      precision = 0; // don't go negative with precision

    std::stringstream strBuffer;
    strBuffer << std::setiosflags(std::ios::fixed)
              << std::setprecision(width)
              << std::setw(width)
              << input;

    str = strBuffer.str();
  }

  //*_outStream << _format.unformatString();

  //*_outStream << separator();
  //if (_col >= numberOfColumns() - 1) {
  //  printEndl();
  //  ++_row;
  //  _col = 0;
  //  _displacement = 0;
  //}
  //else
  //  ++_col;

  return str;
}

} //namespace tfprinter

