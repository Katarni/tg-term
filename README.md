# tg-term
Treminal telegram client builded with td json client and ncurces(probably)

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

## Starting
+ get you api key on [telegram site](https://my.telegram.org/)
+ create td-api-key.env and write keys in format:
  ```
    api_id
    api_hash
  ```
