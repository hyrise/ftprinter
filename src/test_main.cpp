#include "ftprinter/FTPrinter.h"
#include "ftprinter/BufferedFTPrinter.h"
#include "ftprinter/PrintFormat.h"

#define _USE_MATH_DEFINES
#include <math.h>

using ftprinter::FTPrinter;
using ftprinter::BufferedFTPrinter;

int main(int argc, char** argv){
  FTPrinter tp("test table 1: unformated output", std::cout);
  tp.addColumn("Name", 25);
  tp.addColumn("Age", 5);
  tp.addColumn("Position", 30);
  tp.addColumn("Allowance", 9);

  tp.printTableName();
  tp.printHeader();
  tp << "Dat Chu" << 25 << "Research Assistant" << -0.00000000001337;
  tp << "John Doe" << 26 << "Too much float" << 125456789.123456789;
  tp << "John Doe" << 26 << "Typical Int" << 1254;
  tp << "John Doe" << 26 << "Typical float" << 1254.36;
  tp << "John Doe" << 26 << "Too much negative" << -125456789.123456789;
  tp << "John Doe" << 26 << "Exact size int" << 125456789;
  tp << "John Doe" << 26 << "Exact size int" << -12545678;
  tp << "John Doe" << 26 << "Exact size int" << -125456789;
  tp << "John Doe" << 26 << "Exact size float" << -1254567.8f;
  tp << "John Doe" << 26 << "Negative Int" << -1254;
  tp << "Jane Doe" << ftprinter::endl();
  tp << "Tom Doe" << 7 << "Student" << -M_PI;
  tp.printFooter();


  FTPrinter tp2("test table 2: formated output", std::cout, "||", "\n");
  tp2.addColumn("red",     8, ftprinter::format::red);
  tp2.addColumn("green",   8, ftprinter::format::green);
  tp2.addColumn("yellow",  8, ftprinter::format::yellow);
  tp2.addColumn("blue",    8, ftprinter::format::blue);
  tp2.addColumn("cyan",    8, ftprinter::format::cyan);
  tp2.addColumn("magenta", 8, ftprinter::format::magenta);
  tp2.addColumn("white",   8, ftprinter::format::white);
  tp2.addColumn("black",   8, ftprinter::format::black);
  tp2.addColumn("nothing", 8, ftprinter::format::basic);

  tp2.printTableName();
  tp2.printHeader();
  
  tp2 << "asdfsdf" << ftprinter::format::red << 2 << 3 << 4 << 5 << ftprinter::endl();
  tp2 << ftprinter::format::blue << 6 << 7 << ftprinter::endl();
  tp2 << ftprinter::format::red << 1
      << ftprinter::format::blue << 2
      << ftprinter::format::red << 3
      << ftprinter::format::blue << 4
      << ftprinter::format::red << 5
      << ftprinter::format::blue << 6
      << ftprinter::format::red << 7
      << ftprinter::format::blue << 8
      << ftprinter::format::green << 9
      << "neue zeile";
  tp2.printHeader();


  FTPrinter tp3("test table 3: column width adjustment", std::cout);
  tp3.addColumn("too short column",  8);
  tp3.addColumn("long enough column", 20);
  tp3.addColumn("long enough column", 50);

  tp3.printTableName();
  tp3.printHeader();

  tp3 << "asdhfjahsddfjhasdlkfjhasdklfjasdkfjhasdklfj" << "asdfasdfasdfasdfasdfasdfasdfasdfasdfasdf" << "bbbbb";
  tp3 << 66666666666.5 << "asdf" << "asdfasdf";
  tp3 << 123456789 << "a";
  tp3.printFooter();
  tp3.printTableName();


  BufferedFTPrinter btp("test table 4: buffered output", std::cout);
  btp.addColumn("Name", 0, 25);
  btp.addColumn("Age", 0, 5);
  btp.addColumn("Position", 0, 30);
  btp.addColumn("Allowance", 0, 9);

  btp.printTableName();
  btp.printHeader();
  btp.printOut();

  btp << "Dat Chu" << 25 << "Research Assistant" << -0.00000000001337;
  btp << "John Doe" << 26 << "Too much float" << 125456789.123456789;
  btp << "John Doe" << 26 << "Typical Int" << 1254;
  btp << "John Doe" << 26 << "Typical float" << 1254.36;
  btp << "John Doe" << 26 << "Too much negative" << -125456789.123456789;
  btp << "John Doe" << 26 << "Exact size int" << 125456789;
  btp << "John Doe" << 26 << "Exact size int" << -12545678;
  btp << "John Doe" << 26 << "Exact size int" << -125456789;
  btp << "John Doe" << 26 << "Exact size float" << -1254567.8f;
  btp << "John Doe" << 26 << "Negative Int" << -1254;
  btp << "Jane Doe" << ftprinter::endl();
  btp << "Tom Doe" << 7 << "Student" << -M_PI;
  btp.printFooter();

  btp.printHeader();
  btp.flush();

  btp << ftprinter::format::red_b << "!!THIS SHOULD NOT BE PRINTED!!";

  return 0;
}
