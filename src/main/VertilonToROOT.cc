#include "../ParseLYSO.hh"

int main(int argc, char *argv[])
{
  string inFileName;
  string outFileName;
	int numRegions;
  bool error = false;

  // Handle the command line arguments
  switch(argc)
  {
		case 4:
      inFileName = (string)argv[1];
      outFileName = (string)argv[2];
			numRegions = atoi(argv[3]);
      cout << "Beginning Vertilon data file parse." << endl;
      break;
    default:
      cout << "Usage: " << argv[0] << " [Vertilon .log file] ";
      cout << "[.root file]" << endl;
      error = true;
      return 1;
  }

	ParseLYSO *parseLYSO = new ParseLYSO(inFileName, outFileName, numRegions);
  error = parseLYSO->ReadAllEvents();
  delete parseLYSO;

  if(error == true)
    return 1;

  return 0;
}
