#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <string>
#include <iostream>
#include <exception>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>

void f()
{
    std::cout << "f()" << std::endl;
}

void g()
{
    std::cout << "g()" << std::endl;
}


class ExitException {};
class InvalidCommandException : public std::exception
{
	private:
		std::string message;
	public:
		InvalidCommandException(std::string invalidCommand)
		{
			message = "Invalid command: ";
			message.append("\"").append(invalidCommand).append("\"");
		}
		~InvalidCommandException() throw(){}
		const char* what() const throw()
		{
			return message.c_str();
		}
};

class CommandInterpreter
{
	private:
		std::string welcomeMessage;
    public:
    	CommandInterpreter(std::string welcomeMessageToSet)
    		: welcomeMessage(welcomeMessageToSet)
    	{}
    	void prompt()
    	{
    		std::cout << welcomeMessage << std::endl;
    		std::string command;
    		while(true)
    		{
    			std::cout << ">> ";
    			std::cin >> command;
    			try
    			{
    				execute(command);
    			}
    			catch(ExitException& exit)
    			{
    				break;
    			}
    			catch(std::exception& caughtException)
    			{
    				std::cout << caughtException.what() << std::endl;
    			}
    		}
    	}
    	virtual void execute(std::string command) = 0;
};

class PantaReiCommandInterpreter : public CommandInterpreter
{
	public:
		PantaReiCommandInterpreter() : CommandInterpreter("Welcome!"){}
		void execute(std::string command)
    	{
    		if(command.compare("exit") == 0)
    		{
    			ExitException e;
    			throw e;
    		}
    		bool validCommand =
    			boost::spirit::qi::phrase_parse
    				(
    					command.begin(),
    					command.end(),
            			//  Begin grammar
            			(
                    	boost::spirit::qi::string("f")[f] |
                    	boost::spirit::qi::string("g")[g]
            			),
            			//  End grammar
            			boost::spirit::ascii::space
            		);
            if(!validCommand)
            {
    			InvalidCommandException invalidCommand(command);
    			throw invalidCommand;
    		}
    	}

};

template <typename Iterator>
    int parse_integer(Iterator first, Iterator last)
    {
        using boost::spirit::qi::double_;
        using boost::spirit::qi::_1;
        using boost::spirit::qi::phrase_parse;
        using boost::spirit::ascii::space;
        using boost::phoenix::ref;
        int rN = 0;
        bool r = phrase_parse(first, last,
            //  Begin grammar
            (
                    "(" >> boost::spirit::qi::int_[ref(rN) = _1] >> ')' |
                    boost::spirit::qi::string("ciao")[f]
            ),
            //  End grammar
            space);

        if (!r || first != last) // fail if we did not get a full match
            return -1;
        
        return rN;
    }

//OK, IT WORKS!F

int main()
{
    std::string s;
    std::cin >> s;
    std::cout << parse_integer(s.begin(), s.end()) << std::endl;
    PantaReiCommandInterpreter C;
    C.prompt();
    return 0;
}
