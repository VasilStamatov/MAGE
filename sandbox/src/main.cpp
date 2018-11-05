#include <iostream>

#include "SandboxApplication.h"

#include <exceptions/RuntimeError.h>

int main(int argc, char const* argv[])
{
  std::cout << "Argc: " << argc << " /--/ Argv: " << argv << std::endl;

  try
  {
    std::unique_ptr<mage::core::Application> app =
        std::make_unique<SandboxApplication>();
    app->Run();
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