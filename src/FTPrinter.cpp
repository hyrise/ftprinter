#include "ftprinter/FTPrinter.h"

#include <stdexcept>
#include <iomanip>
#include <stdexcept>

#include "ftprinter/PrintFormat.h"


namespace ftprinter {

FTPrinter::FTPrinter(const std::string& tableName, std::ostream* const output,
                     const std::string& separator, const std::string& lineEnding) :
  _tableName(tableName),
  _outStream(output),
  _separator(separator),
  _lineEnding(lineEnding),
  _format(format::basic),
  _row(0),
  _col(0),
  _displacement(0) {}

FTPrinter::~FTPrinter() {}

//getter
size_t FTPrinter::numberOfColumns() const {
  return _columnNames.size();
}
size_t FTPrinter::tableWidth() const {
  size_t tableWidth = separator().size();
  for (size_t i = 0; i < numberOfColumns(); ++i)
    tableWidth += columnWidth(i) + separator().size();
  return tableWidth;
}
const std::string& FTPrinter::separator() const {
  return _separator;
}
const std::string& FTPrinter::columnName(const size_t col) const {
  return _columnNames[col];
}
size_t FTPrinter::columnWidth(const size_t col) const {
  return _columnWidths[col];
}
PrintFormat FTPrinter::columnHeaderFormat(const size_t col) const {
  return _headerFormats[col];
}
size_t FTPrinter::numberOfRows() const {
  return _row;
}
const std::string& FTPrinter::tableName() const {
  return _tableName;
}

/** \brief Add a column to our table
 ** 
 ** \param name Name to be print for the header
 ** \param width the width of the column (has to be >=5)
 ** \param format the format of the header cell
 ** */
void FTPrinter::addColumn(const std::string& name, const size_t width, const PrintFormat& format){
  if (width <= 0)
    throw std::invalid_argument("Column width has to be 0");
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

  //*_outStream << "+"; // the right bar
  for (size_t col = 0; col < numberOfColumns(); ++col) {
    //line for the column space
    for (size_t i = 0; i < columnWidth(col); ++i)
      *_outStream << "-";

    //for the seperator
    const size_t seperatorWidth = separator().size();
    for (size_t i = 0; i < seperatorWidth; ++i)
      *_outStream << "+";
  }
  
  printEndl();
}

void FTPrinter::printEndl() {
  if (_lineEnding.size() != 0)
    *_outStream << _lineEnding;
  else
    *_outStream << std::endl;

  _format = format::basic;
}

void FTPrinter::printTableName() {
  const int space = (int)tableWidth() - (tableName().size() + 2);
  const int spaceFront = space / 2;
  const int  spaceBack = space - spaceFront;

  *_outStream << "+";
  for (int i = 0; i < spaceFront; ++i)
    *_outStream << "-";

*_outStream << format::basic_b.formatString();
  *_outStream << tableName();
  *_outStream << format::basic_b.unformatString();

  for (int i = 0; i < spaceBack; ++i)
    *_outStream << "-";
  *_outStream << "+";
  printEndl();
}

void FTPrinter::printHeader() {
  printHorizontalLine();
  *_outStream << separator();

  for (size_t i = 0; i < numberOfColumns(); ++i) {
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


FTPrinter& FTPrinter::append(const PrintFormat& format) {
  _format = format;
  return *this;
}
FTPrinter& FTPrinter::append(endl input) {
  while (_col > 0){
    *this << "";
  }
  return *this;
}
FTPrinter& FTPrinter::append(float input) {
  return *this << (double) input;
}
FTPrinter& FTPrinter::append(double input) {
  printColumnStart();

  *_outStream << decimalNumberToStr<double>(input, columnWidth(_col));

  printColumnEnd();
  return *this;
}

FTPrinter& FTPrinter::operator<<(const PrintFormat& format) {
  return append(format);
}
FTPrinter& FTPrinter::operator<<(endl input) {
  return append(input);
}
FTPrinter& FTPrinter::operator<<(float input) {
  return append(input);
}
FTPrinter& FTPrinter::operator<<(double input) {
  return append(input);
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

