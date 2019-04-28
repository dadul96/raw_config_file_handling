# raw_config_file_handling
This small single header library allows handling of ini-style config-files. In addition to the standard ini-format, this library allows values with more than one parameter (separation with commas).
Example of this config-file format:
```
[SECTION]
KEY=VALUE
KEY=VALUE1,VALUE2

[RGB_COLOR_CODES]
BACKGROUND=255,255,255
...
```
