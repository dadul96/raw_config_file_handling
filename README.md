# raw_config_file_handling
This small single header library allows handling of ini-style config-files. In addition to the standard ini-format, this library allows values with more than one parameter (separation with commas). Comments in the config-file are getting ignored. The standard comment-character is the semicolon (;), but also custom characters could be set.
Example of this config-file format:
```ini
;Comment1
[GENERAL];Comment2
BALL_COUNT=2;Comment3

[BALL]
BALL_RGB_COLOR=0,0,255
...
```
### Installation
1. Include the **raw_config_file_handling.hpp** file in your project.
2. Set up a struct that contains all possible configuration parameters:
```cpp
struct Configuration { //program configuration
  //GENERAL-Section:
  int BallCount;

  //BALL-Section:
  vector<int> BallColorRGB;
};
```
3. Inherit from the base class (RawConfigFileHandler) and implement setConfig/getConfig Methods and optional features (for a more advanced use, see the example folder):
```cpp
class ConfigFileHandler : public RawConfigFileHandler {
public:
  Configuration ProgramConfiguration;

  //empty constructor:
  ConfigFileHandler() {}

  //create a method that assigns the RawConfigData (from base class) to the Configuration-struct:
  void getConfig() {
    if (readFile()) //reading raw file and check if successful
    {
      //looping through the RawConfigData vector array:
      for (size_t i = 0; i < RawConfigData.size(); i++) 
      {
        if (RawConfigData[i].Section == "GENERAL")
        {
          if (RawConfigData[i].Key == "BALL_COUNT")
          {
            //assigning the value to the program configuration parameter:
            ProgramConfiguration.BallCount = stoi(RawConfigData[i].Value[0]); 
          }
        }
        else if (RawConfigData[i].Section == "BALL")
        {
          if (RawConfigData[i].Key == "BALL_RGB_COLOR")
          {
            for (size_t j = 0; j < RawConfigData[i].Value.size(); j++)
            {
              ProgramConfiguration.BallColorRGB.push_back(stoi(RawConfigData[i].Value[j]));
            }
          }
        }
      }
    }
  }

  //create a method that assigns the Configuration-struct to the RawConfigData (in base class):
  void setConfig() {
    int i = 0;
    RawConfigData.clear();

    RawConfigData.push_back(ConfigDataStruct());
    RawConfigData[i].Section = "GENERAL";
    RawConfigData[i].Key = "BALL_COUNT";
    RawConfigData[i].Value.push_back(std::to_string((ProgramConfiguration.BallCount)));
    i++; //increment the vector array iterator of RawConfigData 

    RawConfigData.push_back(ConfigDataStruct());
    RawConfigData[i].Section = "BALL";
    RawConfigData[i].Key = "COLOR_RGB";
    for (size_t j = 0; j < ProgramConfiguration.BallColorRGB.size(); j++)
    {
      RawConfigData[i].Value.push_back(std::to_string(ProgramConfiguration.BallColorRGB[j]));
    }

    writeFile();
  }
};
```

### Built With
* [Visual Studio 2019](https://visualstudio.microsoft.com/)

### Author
**Daniel Duller** - [dadul96](https://github.com/dadul96)

### License
This project/library is licensed under the MIT License - see the [LICENSE](LICENSE) file for details

