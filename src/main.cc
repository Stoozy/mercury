#include <clue.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include <string>

#include <backtest.h>
#include <config.h>
#include <util.h>

using namespace std;

int main(int argc, char *argv[]) {

  if (argc <= 1) {
    cout << USAGE << endl;
  }

  if (argc <= 3) {

    if (strcmp(argv[1], "-c") == 0) {
      // TODO: actually run the main program here
      if (argc < 3) {
        cout << USAGE << endl;
        return 0;
      }

      LOG_INFO("Config file at " << argv[2]);

      string path = char_ptr_to_string(argv[2]);
      Config conf(path);

      if (!conf.exists()) {
        LOG_CRITICAL(argv[2] << " does not exist.");
        return -1;
      }

      // load config
      if (!conf.load()) {
        LOG_CRITICAL("Invalid config file. Please make sure it's properly "
                     "formatted and contains all the data needed.");
        return -1;
      }

      json config_data = conf.getJson();

      // create and run the actual backtest
      Backtest bt(config_data);
      bt.run();
    }

    if (strcmp(argv[1], "-h") == 0)
      cout << USAGE << endl;

    if (strcmp(argv[1], "-v") == 0)
      cout << VERSION << endl;
  }

  return 0;
}