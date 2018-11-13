
#include <iostream>

#include "demo/DemoApplication.h"

#include <exceptions/RuntimeError.h>

int main(int argc, const char** argv)
{
  try
  {
    std::unique_ptr<DemoApplication> app = std::make_unique<DemoApplication>();
    app->Run(argc, argv);
  }
  catch (const mage::exceptions::RuntimeError& e)
  {
    std::cerr << e.GetFullMessage() << '\n';
    return -1;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return -1;
  }

  return 0;
}