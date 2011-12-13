#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>
#include "../lib/CommandInterpreter/CommandInterpreter.h"
#include "Controller/PantaReiLanguage/PantaReiLanguage.h"

int main(int argc, char** argv)
{
    std::string scriptFileDescriptor;
    std::string logFileDescriptor;
    std::istream* script = NULL;
    std::ostream* log = NULL;
    std::ifstream scriptFile;
    scriptFile.exceptions(std::ifstream::failbit);
    std::ofstream logFile;
    boost::program_options::options_description options("Panta Rei options");
    options.add_options()
        ("help,h", "Produce this help message")
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
                    &scriptFileDescriptor
                )
                ->default_value("stdout"),
            "Specify a log file."
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
            std::cout << "\nStream error" << std::endl;
        }
    }
    return 0;
}
