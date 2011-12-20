/**
 * @file PantaRei.cpp
 * @author Cosimo Sacco <cosimosacco@gmail.com>
 *
 * @section LICENSE
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/

#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include "../lib/CommandInterpreter/CommandInterpreter.h"
#include "../lib/StaticLog/StaticLog.h"
#include "Controller/PantaReiLanguage/PantaReiLanguage.h"

void printLogo()
{
/*                      __                                         
                       /\ \__                                __    
 _____      __      ___\ \ ,_\    __             _ __    __ /\_\   
/\ '__`\  /'__`\  /' _ `\ \ \/  /'__`\   _______/\`'__\/'__`\/\ \  
\ \ \_\ \/\ \_\.\_/\ \/\ \ \ \_/\ \_\.\_/\______\ \ \//\  __/\ \ \ 
 \ \ ,__/\ \__/.\_\ \_\ \_\ \__\ \__/.\_\/______/\ \_\\ \____\\ \_\
  \ \ \/  \/__/\/_/\/_/\/_/\/__/\/__/\/_/         \/_/ \/____/ \/_/
   \ \_\                                                           
    \/_/ 
*/
    std::cout << "                        __                                         " << std::endl;
    std::cout << "                       /\\ \\__                                __    " << std::endl;
    std::cout << " _____      __      ___\\ \\ ,_\\    __             _ __    __ /\\_\\   " << std::endl;
    std::cout << "/\\ '__`\\  /'__`\\  /' _ `\\ \\ \\/  /'__`\\   _______/\\`'__\\/'__`\\/\\ \\  " << std::endl;
    std::cout << "\\ \\ \\_\\ \\/\\ \\_\\.\\_/\\ \\/\\ \\ \\ \\_/\\ \\_\\.\\_/\\______\\ \\ \\//\\  __/\\ \\ \\ " << std::endl;
    std::cout << " \\ \\ ,__/\\ \\__/.\\_\\ \\_\\ \\_\\ \\__\\ \\__/.\\_\\/______/\\ \\_\\\\ \\____\\\\ \\_\\" << std::endl;
    std::cout << "  \\ \\ \\/  \\/__/\\/_/\\/_/\\/_/\\/__/\\/__/\\/_/         \\/_/ \\/____/ \\/_/" << std::endl;
    std::cout << "   \\ \\_\\                                                           " << std::endl;
    std::cout << "    \\/_/ " << std::endl;
    std::cout << std::endl;
}

int main(int argc, char** argv)
{
    std::string scriptFileDescriptor;
    std::string logFileDescriptor;
    //std::string xmlFileDescriptor; TODO XML OUTPUT
    std::string errorLogFileDescriptor;
    std::istream* script = NULL;
    std::ostream* log = NULL;
    //std::ostream* xml = NULL; TODO XML OUTPUT
    std::ostream* errorLog = NULL;
    std::ifstream scriptFile;
    scriptFile.exceptions(std::ifstream::failbit);
    std::ofstream logFile;
    //std::ofstream xmlFile; TODO XML OUTPUT
    std::ofstream errorLogFile;
    boost::program_options::options_description options("Panta Rei options");
    options.add_options()
        ("help,h", "Produce this help message")
        (
            "script,s",
            boost::program_options::value<std::string>
                (
                    &scriptFileDescriptor
                )
                ->default_value("stdin"),
            "Specify a script file."
        )
        (
            "log,l",
            boost::program_options::value<std::string>
                (
                    &logFileDescriptor
                )
                ->default_value("stdout"),
            "Specify a log file."
        )
        /*(
            "xml,x",
            boost::program_options::value<std::string>
                (
                    &xmlFileDescriptor
                )
            "Specify a XML output file."
        ) TODO XML OUTPUT
        */
        (
            "errorLog,e",
            boost::program_options::value<std::string>
                (
                    &errorLogFileDescriptor
                )
                ->default_value("stderr"),
            "Specify a error log file."
        )
    ;
    boost::program_options::variables_map specifiedOptions;
    try
    {
        boost::program_options::store
            (
                boost::program_options::parse_command_line
                    (
                        argc, argv, options
                    ),
                specifiedOptions
            );
    }
    catch(...)
    {
        std::cout << "The specified options are invalid" << std::endl;
        std::cout << options << std::endl;
        return 1;
    }
    boost::program_options::notify(specifiedOptions);
    if (specifiedOptions.count("help"))
    {
        std::cout << options << std::endl;
        return 0;
    }
    if
        (
            specifiedOptions.count("script")
            &&
            !
            (
                (
                    specifiedOptions["script"].as<std::string>()
                )
                .compare("stdin") == 0
            )
        )
    {
        try
        {
            scriptFile.open
                (
                    (
                        specifiedOptions["script"].as<std::string>()
                    ).c_str()
                )
            ;
            script = &scriptFile;
        }
        catch(std::ifstream::failure)
        {
            std::cout
                << specifiedOptions["script"].as<std::string>()
                << ": The specified script does not exist" << std::endl;
            return 1;
        }
    }
    else
    {
        script = &std::cin;
    }
    if
        (
            specifiedOptions.count("log")
            &&
            !
            (
                (
                    specifiedOptions["log"].as<std::string>()
                )
                .compare("stdout") == 0
            )
        )
    {
        logFile.open((specifiedOptions["log"].as<std::string>()).c_str());
        log = &logFile;
    }
    else
    {
        log = &std::cout;
    }
    /*if
        (
            specifiedOptions.count("xml")
            &&
        )
    {
        xmlFile.open((specifiedOptions["xml"].as<std::string>()).c_str());
        xml = &xmlFile;
    }
    else
    {
        xmlFile.open("/dev/null"); TODO portability AND standardization
        xml = &xmlFile;
    } TODO XML OUTPUT */
    if
        (
            specifiedOptions.count("errorLog")
            &&
            !
            (
                (
                    specifiedOptions["errorLog"].as<std::string>()
                )
                .compare("stderr") == 0
            )
        )
    {
        errorLogFile.open((specifiedOptions["errorLog"].as<std::string>()).c_str());
        errorLog = &errorLogFile;
    }
    else
    {
        errorLog = &std::cerr;
    }
    StaticLog::log["general"] = log;
    //StaticLog::log["xml"] = xml; TODO XML OUTPUT
    StaticLog::log["error"] = errorLog;
    if(log == &std::cout) //That is, the output is on screen
    {
        printLogo();
    }
    else
    {
        (*log) << "Panta Rei - log" << std::endl << std::endl;
    }
    std::string welcomeMessage("Panta Rei - Real time scheduling simulator");
    CommandInterpreter<PantaReiLanguage>
        pantaReiRuntimeEnvironment(welcomeMessage, script);
    try
    {
        pantaReiRuntimeEnvironment.run();
    }
    catch(std::ifstream::failure)
    {
        if((script->fail() || script->bad()) && !script->eof())
        {
            (*errorLog) << "\nStream error" << std::endl;
        }
    }
    return 0;
}
