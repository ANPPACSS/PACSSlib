#include "../ParseLYSO.hh"

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
      cout << "Beginning Vertilon data file parse." << endl;
      break;
    default:
      cout << "Usage: " << argv[0] << " [Vertilon .log file] ";
      cout << "[.root file]" << endl;
      error = true;
      return 1;
  }

	ParseLYSO *parseLYSO = new ParseLYSO(inFileName, outFileName);
  error = parseLYSO->ReadAllEvents();
  delete parseLYSO;

  if(error == true)
    return 1;

  return 0;
}
