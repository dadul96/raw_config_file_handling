#include "../raw_config_file_handling.hpp"

//set up a structure that includes all desired config-parameters:
struct Configuration { //program configuration
	//GENERAL-Section:
	int BallCount;

	//BALL-Section:
	vector<int> BallColorRGB;
};

//inherit from the base class (RawConfigFileHandler):
class ConfigFileHandler : public RawConfigFileHandler {
public:
	Configuration ProgramConfiguration;
	//create flags if needed:
	bool SuccessfulReading;
	bool SuccessfulWriting;

	//constructor for initializing the flags:
	ConfigFileHandler() : SuccessfulReading(false), SuccessfulWriting(false) {}

	//create a method that assigns the RawConfigData (from base class) to the Configuration-struct:
	void getConfig() {
		constexpr int DesiredParameterCount = 2; //number of expected parameters (for checking if the reading was successful)
		int ParameterCount = 0;
		if (readFile()) //reading raw file and check if successful
		{
			for (size_t i = 0; i < RawConfigData.size(); i++) //looping through the RawConfigData vector array
			{
				if (RawConfigData[i].Section == "GENERAL")
				{
					if (RawConfigData[i].Key == "BALL_COUNT")
					{
						ProgramConfiguration.BallCount = stoi(RawConfigData[i].Value[0]); //assigning the value to the program configuration parameter
						ParameterCount++; //incrementing parameter count since the parameter was found
					}
				}
				else if (RawConfigData[i].Section == "BALL")
				{
					if (RawConfigData[i].Key == "BALL_RGB_COLOR")
					{
						for (size_t j = 0; j < RawConfigData[i].Value.size(); j++)
						{
							ProgramConfiguration.BallColorRGB.push_back(stoi(RawConfigData[i].Value[j])); //assigning the values to the program configuration parameter
						}
					}
					ParameterCount++; //incrementing parameter count since the parameter was found
				}

				if (DesiredParameterCount == ParameterCount)
				{
					SuccessfulReading = true;
				}
			}
		}
	}

	//create a method that assigns the Configuration-struct to the RawConfigData (in base class) in order to write a config file:
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

		if (writeFile())
		{
			SuccessfulWriting = true;
		}
	}
};

int main() {
	ConfigFileHandler ConfigHandler1;

	ConfigHandler1.setCommentChar('#'); //changing the comment character from ";" (default) to "#"

	ConfigHandler1.setFilePath("C:\\dev\\VS2019_repos\\raw_config_file_handling\\raw_config_file_handling\\example\\example_config.ini"); //setting the path of the config-file (enter your desired path)

	cout << ConfigHandler1.getCommentChar() << endl; //printing the set comment character

	cout << ConfigHandler1.getFilePath() << endl; //printing the path of the config-file

	ConfigHandler1.getConfig(); //reading config-file

	ConfigHandler1.printRawConfigData(); //printing the RawConfigData to the console

	ConfigHandler1.setFilePath("C:\\dev\\VS2019_repos\\raw_config_file_handling\\raw_config_file_handling\\example\\output_example_config.ini");

	ConfigHandler1.setConfig(); //writing config-file

	//printing the flags to the console:
	cout << "SuccessfulReading? " << std::to_string(ConfigHandler1.SuccessfulReading) << endl;
	cout << "SuccessfulWriting? " << std::to_string(ConfigHandler1.SuccessfulWriting) << endl;

	return 0;
}
