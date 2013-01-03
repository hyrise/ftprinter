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
  _col(0) {}

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

void FTPrinter::printHeader(){
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

void FTPrinter::printFooter(){
  printHorizontalLine();
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
  printDecimalNumber<float>(input);
  return *this;
}
FTPrinter& FTPrinter::operator<<(double input) {
  printDecimalNumber<double>(input);
  return *this;
}

template<typename T>
void FTPrinter::printDecimalNumber(T input) {
  *_outStream << _format.formatString();

  // If we cannot handle this number, indicate so
  if (input < 10 * (columnWidth(_col) - 1) || input > 10 * columnWidth(_col)) {
    std::stringstream string_out;
    string_out << std::setiosflags(std::ios::fixed)
               << std::setprecision(columnWidth(_col))
               << std::setw(columnWidth(_col))
               << input;

    std::string string_rep_of_number = string_out.str();

    string_rep_of_number[columnWidth(_col) - 1] = '*';
    std::string string_to_print = string_rep_of_number.substr(0, columnWidth(_col));
    *_outStream << string_to_print;
  }
  else {
    // determine what precision we need
    int precision = columnWidth(_col) - 1; // leave room for the decimal point
    if (input < 0)
      --precision; // leave room for the minus sign

    // leave room for digits before the decimal?
    if (input <= -1 || input >= 1){
      int num_digits_before_decimal = 1 + (int)log10(std::abs(input));
      precision -= num_digits_before_decimal;
    }
    else
      --precision; // e.g. 0.12345 or -0.1234

    if (precision < 0)
      precision = 0; // don't go negative with precision

    *_outStream << std::setiosflags(std::ios::fixed)
                << std::setprecision(precision)
                << std::setw(columnWidth(_col))
                << input;
  }

  *_outStream << _format.unformatString();

  *_outStream << separator();
  if (_col >= numberOfColumns() - 1) {
    printEndl();
    ++_row;
    _col = 0;
  }
  else
    ++_col;
}

} //namespace tfprinter

