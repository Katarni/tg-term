# tg-term
Treminal telegram client builded with td json client and ncurces(probably)

## Starting
+ get your api key on [telegram site](https://my.telegram.org/)
+ create tg-term config file in project dir (tg-term-config.json) and set params like this:
  ```
    {
      "api-id" : your api id as int,
      "api-hash" : your hash as string,
      "log-file" : your log file as string, "../logs.dat" is default,
      "log-lvl" : your log level, 1 is default;
    }
  ```

## Building
### Dependencies
  + TdLib (build and install)
  + Json-c
  + Curces
### Build with cmake
  Just 
  ```
    cmake ..
    make
  ```
  in build dir
