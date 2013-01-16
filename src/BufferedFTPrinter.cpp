#include "ftprinter/BufferedFTPrinter.h"

namespace ftprinter {

BufferedFTPrinter::BufferedFTPrinter(std::ostream* const output,
                                     const std::string& separator,
                                     const std::string& lineEnding) :
    FTPrinter(output, separator, lineEnding)
{

}
BufferedFTPrinter::~BufferedFTPrinter() { }


size_t BufferedFTPrinter::maxTableWidth() const {
  size_t maxTableWidth = separator().size();
  for (size_t i = 0; i < numberOfColumns(); ++i)
    maxTableWidth += maxColumnWidth(i) + separator().size();
  return maxTableWidth;
}

size_t BufferedFTPrinter::maxColumnWidth(const size_t col) const {
  return _maxColumnWidths[col];
}

size_t BufferedFTPrinter::numberOfPrintedRows() const {
  return FTPrinter::numberOfRows();
}
size_t BufferedFTPrinter::numberOfBufferedRows() const {
  size_t bufferedRows = 0;
  for (int i : _lines)
    if (i > 0)
      ++bufferedRows;
  return bufferedRows;
}
size_t BufferedFTPrinter::numberOfRows() const {
  return numberOfPrintedRows() + numberOfBufferedRows();
}

void BufferedFTPrinter::addColumn(const std::string& name, const size_t width,
                                  const PrintFormat& format) {
  addColumn(name, width, width, format);
}
void BufferedFTPrinter::addColumn(const std::string& name, const size_t width,
                                  const size_t maxWidth, const PrintFormat& format) {
  size_t realMaxWidth = std::max(width, maxWidth); //TODO exception

  _maxColumnWidths.push_back(realMaxWidth);
  FTPrinter::addColumn(name, std::min(realMaxWidth, name.size()), format);
}

void BufferedFTPrinter::printHeader() {
  _lines.push_back(0);
}
void BufferedFTPrinter::printFooter() {
  _lines.push_back(-1);
}

void BufferedFTPrinter::printOut(const size_t rows) {
  size_t row = rows;
  size_t column = 0;
  for (int line: _lines) {
    if (line == lineHeader) {
      FTPrinter::printFooter();
      continue;
    }
    if (line == lineFooter) {
      FTPrinter::printHeader();
      continue;
    }
    
    if (row == 0)
      break;

    for (size_t i = 0; i < (size_t)line; ++i) {
      FTPrinter::append( _columnFormats[column]).append(_columns[column]);
      ++column;
    }

    FTPrinter::append(endl());

    --row;
  }
}
void BufferedFTPrinter::flush(const size_t rows) {
  printOut(rows);
  clear(rows);
}
void BufferedFTPrinter::clear(const size_t rows) {
  _columns.clear();
  _columnFormats.clear();
  _lines.clear();
}

FTPrinter& BufferedFTPrinter::append(const PrintFormat& format) {
  const size_t numberOfFormats = _columnFormats.size();
  if (numberOfFormats >= _columns.size()) {
    if (numberOfFormats == _columns.size() + 1)
      _columnFormats[numberOfFormats - 1] = format;
    else
      _columnFormats.push_back(format);
  }
  return *this;
}
FTPrinter& BufferedFTPrinter::append(const endl input) {
  if (_lines.back() != (int)numberOfColumns() || _lines.back()==0) {
    _lines.push_back(0);
    _columnFormats.push_back(format::none);
  }
  return *this;
}
FTPrinter& BufferedFTPrinter::append(const float input) {
  return append((double) input);
}
FTPrinter& BufferedFTPrinter::append(const double input) {
  _columns.push_back(FTPrinter::decimalNumberToStr(input, maxColumnWidth(_lines.back())));
  if (_lines.back() == (int)numberOfColumns()) {
    _lines.push_back(1);
    if (_columnFormats.size() == _columns.size() - 1)
      append(format::none);
  }
  else {
    append(_columnFormats.back());
    ++(_lines.back());
  }
  return *this;
}

FTPrinter& BufferedFTPrinter::operator<<(const PrintFormat& format) {
  return append(format);
}
FTPrinter& BufferedFTPrinter::operator<<(const endl input) {
  return append(input);
}
FTPrinter& BufferedFTPrinter::operator<<(const float input) {
  return append(input);
}
FTPrinter& BufferedFTPrinter::operator<<(const double input) {
  return append(input);
}


void BufferedFTPrinter::printHorizontalLine() {

}
void BufferedFTPrinter::printEndl() {

}
void BufferedFTPrinter::printColumnStart() {

}
void BufferedFTPrinter::printColumnEnd() {

}

}// namespace ftprinter