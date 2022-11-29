#include "src/LuxINI.hpp"

#include <iostream>

int
main() {
    Lux::INIParser::INI iniFile("test/Lux.ini", "test/Lux.ini", false);
    Lux::INIParser::INIStructure iniContent;

    // Generate Lux.ini
    iniFile.generate(iniContent, true);

    // Add or Update section / key-value
    iniContent["person"]["boy"] = "Lux";
    iniContent["money"]["RMB"] = "100";
    iniContent["money"]["Dollar"] = "13.87";

    // Save Lux.ini
    iniFile.write(iniContent);

    // Read Lux.ini
    iniFile.read(iniContent);
    std::cout << iniContent["person"]["boy"] << std::endl
              << iniContent["money"]["RMB"] << std::endl
              << iniContent["money"]["Dollar"] << std::endl;
}
