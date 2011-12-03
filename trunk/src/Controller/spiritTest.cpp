#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <string>
#include <iostream>
#include <exception>
#include <boost/spirit/include/phoenix_core.hpp>
#include <boost/spirit/include/phoenix_operator.hpp>
#include <boost/spirit/home/phoenix/bind/bind_member_function.hpp>

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
		const std::string welcomeMessage;
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

/*template <Visitor>*/ class PantaReiCommandInterpreter : public CommandInterpreter
{
	private:
		//SchedulingSimulation simulation;
		//Visitor simulationVisitor;
		void exit()
        {
			ExitException e;
			throw e;
		}
	public:
		PantaReiCommandInterpreter() : CommandInterpreter("Welcome!"){}
		void execute(std::string command)
    	{
    		bool validCommand =
    			boost::spirit::qi::phrase_parse
    				(
                        command.begin(),
    					command.end(),
            			//  Begin grammar
            			(
                            //<command name="exit">
            				(
                                (
                                    (
                                        (
                                            boost::spirit::qi::string("e")
                                            |
                                            boost::spirit::qi::string("E")
                                        )
                                        >>
                                        -
                                        (boost::spirit::qi::string("xit"))
                                    )
                                    |
                                    (
                                        boost::spirit::qi::string("q")
                                        |
                                        boost::spirit::qi::string("Q")
                                    )
                                    >>
                                    -
                                    (boost::spirit::qi::string("uit"))
                                )
                            )
                            [boost::phoenix::bind(&PantaReiCommandInterpreter::exit, *this)]
                            //</command>
                            |
                            //<command name="create">
                    		boost::spirit::qi::string("create") 
                            >>
                            (
                                boost::spirit::qi::string("periodictask")[f] |
                                boost::spirit::qi::string("task")[g]
                            )
                            //</command">
                            |
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

//OK, IT WORKS!F

int main()
{
    PantaReiCommandInterpreter C;
    C.prompt();
    return 0;
}
