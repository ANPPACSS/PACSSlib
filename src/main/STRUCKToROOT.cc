#include "../ParseGE.hh"

int main(int argc, char *argv[])
{
  string inFileName;
  string outFileName;
  bool error = false;

  // Handle the command line arguments
  switch(argc)
  {
    case 3:
      inFileName = (string)argv[1];
      outFileName = (string)argv[2];
      cout << "Beginning STRUCK data file parse." << endl;
      break;
    default:
      cout << "Usage: " << argv[0] << " [STRUCK .log file] ";
      cout << "[.root file]" << endl;
      error = true;
      return 1;
  }

  ParseGE *parseGE = new ParseGE(inFileName, outFileName);
  error = parseGE->ReadAllEvents();
  delete parseGE;

  if(error == true)
    return 1;

  return 0;
}
