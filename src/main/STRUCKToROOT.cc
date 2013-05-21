#include "../ParseGE.hh"

int main(int argc, char *argv[])
{
  string inFileName;
  string outFileName;
	int clockFreq;
  bool error = false;
	ParseGE *parseGE;

  // Handle the command line arguments
  switch(argc)
  {
    case 4:
      inFileName = (string)argv[1];
      outFileName = (string)argv[2];
			clockFreq = atoi(argv[3]);
      cout << "Beginning STRUCK data file parse." << endl;
  		parseGE = new ParseGE(inFileName, outFileName, clockFreq);
      break;
		case 3:
			inFileName = (string)argv[1];
			outFileName = (string)argv[2];
			cout << "Beginning STRUCK data file parse." << endl;
  		parseGE = new ParseGE(inFileName, outFileName);
			break;
    default:
      cout << "Usage: " << argv[0] << " [STRUCK .log file] ";
      cout << "[.root file] [clock frequency (default=100MHz)]" << endl;
      error = true;
      return 1;
  }

  error = parseGE->ReadAllEvents();
  delete parseGE;

  if(error == true)
    return 1;

  return 0;
}
