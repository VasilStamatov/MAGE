
#include <iostream>

#include "SandboxApplication.h"

#include <exceptions/RuntimeError.h>

int main(int argc, const char** argv)
{
  try
  {
    std::unique_ptr<SandboxApplication> app =
        std::make_unique<SandboxApplication>();
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