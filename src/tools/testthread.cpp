#include <iostream>
#include "thread.h"

class A : public Tools::IThread
{
  public:
    A() { }
    ~A() { }
    void Run()
    {
      for(int i=10; --i;)
      {
        std::cout << "A ";
        sleep(1);
      }
    }
};

class B : public Tools::IThread
{
  public:
    B() { }
    ~B() { }
    void Run()
    {
      while(fRunning)
      {
        std::cout << "B ";
        sleep(1);
      }
    }
};

int main(int, char**)
{
  A CA;
  B CB;
  std::cout << "A started \247\n";
  std::cout << "B started !\n";
  CA.Start();
  CB.Start();
  sleep(2);
  CB.Stop();
  std::cout << "\nB stoped \n";
  std::cout << "Waiting end of threads ..." << '\n';
  return EXIT_SUCCESS;
}
