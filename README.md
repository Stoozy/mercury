# Mercury

Event Driven Backtesting Framework

![](snapshot.png)

Visualizing a mean reversion.

### Building

This is a cmake project. Make sure you have some sort of c++ compiler that is detected by cmake.
Steps :-
1. git clone https://github.com/Stoozy/mercury.git
2. `cd mercury`
3. mkdir build
4. `cd build`
5. Run `cmake ..`. Makefile will be created in build directory.
6. Run `make`. Now, the executable `build/mercury` should be created.

### Running

Mercury requires a config.json file to run. Here is a sample one:

```json
{
  "historical_data": "AAPL.csv",
  "strategy": {
    "name": "MEAN_REVERSION",
    "moving_average": "EMA",
    "days": {
      "short_term": 10,
      "long_term": 30
    },
    "smoothing": 2,
    "output": "output.csv"
  },
  "capital": 10000,
  "positions": [
    {
      "symbol": "AAPL",
      "quantity": 0,
      "price": 0
    }
  ],
  "slippage": 0.005,
  "transaction_cost": 0.001,
  "start_date": "2018-10-12",
  "end_date": "2023-10-11"
}
```

1. Download historical data from internet. You can use [Yahoo Finance](https://finance.yahoo.com/quote/AAPL/history).
2. Put the csv file in the same directory as `config.json`. In `config.json`, change the following fields
     - `historical_data` to the file-name.csv
     - `start_date` to the start date in your file
     - `end_date` to the end date in your file.
3. Go to the parent directory. Run `build/mercury -c config.json`. The file output.csv will be created.
4. Now, run `python visualize.py` to view plot of the output graphs. Note that you need pandas and matplotlib installed in your system.
