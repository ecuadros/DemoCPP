
#include <iostream>
#include <fstream>
#include <filesystem>
#include <cstdlib>    // for std::exit() and EXIT_FAILURE

int main ()
{
  namespace fs = std::filesystem;
  try {
    // create directories tmp/test/ (if they don't exist yet):
    fs::path testDir{"tmp/test"};
    create_directories(testDir);
     
    // create data file tmp/test/data.txt:
    auto testFile = testDir / "data.txt";
    std::ofstream dataFile{testFile};
    if (!dataFile) {
      std::cerr << "OOPS, can't open \"" << testFile.string() << "\"\n";
      std::exit(EXIT_FAILURE);  // exit program with failure
    }
    dataFile << "The answer is 42\n";

    // create symbolic link from tmp/slink/ to tmp/test/:
    create_directory_symlink("test", testDir.parent_path() / "slink");
  } 
  catch (const fs::filesystem_error& e) {
    std::cerr << "EXCEPTION: " << e.what() << '\n';
    std::cerr << "    path1: \"" << e.path1().string() << "\"\n";
  }

  // recursively list all files (also following symlinks)
  std::cout << fs::current_path().string() << ":\n";
  auto iterOpts{fs::directory_options::follow_directory_symlink};
  for (const auto& e : fs::recursive_directory_iterator(".", iterOpts)) {
    std::cout << "  " << e.path().lexically_normal().string() << '\n'; 
  }
}

