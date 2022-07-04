
#include <filesystem>
#include <iostream>

void testSymLink(std::filesystem::path top)
{
  top = absolute(top);      // use absolute paths as we change current path
  create_directory(top);    // make sure top exists
  current_path(top);        // so that we can change the directory to it
  std::cout << std::filesystem::current_path() << '\n'; // print path of top

  // define our sub-directories (without creating them):
  std::filesystem::path px{top / "a/x"};
  std::filesystem::path py{top / "a/y"};
  std::filesystem::path ps{top / "a/s"};

  // print some relative paths (for non-existing files):
  std::cout << px.relative_path() << '\n';        // relative path from top
  std::cout << px.lexically_relative(py) << '\n'; // to px from py: "../x"
  std::cout << relative(px, py) << '\n';          // to px from py: "../x"
  std::cout << relative(px) << '\n';              // to px from curr. path: "a/x"

  std::cout << px.lexically_relative(ps) << '\n'; // to px from ps: "../x"
  std::cout << relative(px, ps) << '\n';          // to px from ps: "../x"

  // now create all sub-directories and the symbolic link:
  create_directories(px);                         // create "top/a/x"
  create_directories(py);                         // create "top/a/y"
  if (!is_symlink(ps)) {
    create_directory_symlink(top, ps);            // create "top/a/s" -> "top" 
  }
  std::cout << "ps: " << ps << '\n'
            << " -> " << read_symlink(ps) << '\n';

  // and see the difference between lexically and filesystem relative:
  std::cout << px.lexically_relative(ps) << '\n'; // to px from ps: "../x"
  std::cout << relative(px, ps) << '\n';          // to px from ps: "a/x"
}


