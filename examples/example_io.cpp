
#include <cstdlib>

 #include "../src/tools/InChannel.cpp"
#include "../src/tools/OutChannel.cpp"

bool		example_io(void) {
  OutChannel	stdout;
  InChannel	stdin;

 stdout.put("Type a name for the file you want to create: ");
  std::string filename;
  if (!stdin.getNextLine(filename))
    return stdout.putError("Error: Empty filename!");

  OutChannel	file;
  if (!(file.setOutFile(filename)))
    return stdout.putError("Error: Opening file permission denied!");

  file.put("Hello world!", OutChannel::ENDLINE);
  file << "meow meow~ " << 5 << " " << 1.5 << " liter\n";
  file.put("the end of the file", OutChannel::ENDLINE);

  InChannel infile;
  if (!(infile.setInFile("toto")))
    return stdout.putError("Error: Opening file permission denied!");
  
  std::string str;
  while (infile.getNextLine(str))
    stdout << str << "\n";
	
  return true;
}

int		main(void) {
  return example_io() ? EXIT_SUCCESS : EXIT_FAILURE;
}

