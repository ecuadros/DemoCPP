
#include <exception>
#include <iostream>
#include <string>

class Request {
  private:
    std::string name;
     int initialExceptions = std::uncaught_exceptions();
  public:
    Request(const std::string& n) 
     : name{n} {
    }
    //...
    ~Request() {
      if (std::uncaught_exceptions() > initialExceptions) {
        rollback();  // destruction caused by stack unwinding
      }
      else {
        commit();    // destruction NOT caused by stack unwinding
      }
    }
    //...
    void commit() {
        std::cout << "  commit() for " << name << "\n";
    }
    void rollback() {
        std::cout << "  rollback() for " << name << "\n";
    }
};

int main()
{
  try {
    Request r1{"r1"};
    //...
    throw std::out_of_range{"dummy exception"};
  } // will rollback r1 due to exception
  catch (...) {
    Request r2{"r2"};
    //...
  } // will commit r2 without another unhandled exception
}

