#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>

int main(int argc, char** argv)
{
    std::string scriptFileDescriptor;
    std::string logFileDescriptor;
    std::istream* script = NULL;
    std::ostream* log = NULL;
    std::ifstream scriptFile;
    std::ofstream logFile;
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
        scriptFile.open((specifiedOptions["script"].as<std::string>()).c_str());
        script = &scriptFile;
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
    std::string prova;
    getline(*script, prova);
    (*log) << prova << std::endl;
    getline(*script, prova);
    (*log) << prova << std::endl;
    getline(*script, prova);
    (*log) << prova << std::endl;
    getline(*script, prova);
    (*log) << prova << std::endl;
    getline(*script, prova);
    (*log) << prova << std::endl;
    return 0;
}
