#include <boost/config/warning_disable.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/home/phoenix/bind/bind_member_function.hpp>
#include <iostream>
#include <string>

class Syntax :
	public
		boost::spirit::qi::grammar
			<
				std::string::const_iterator,
				boost::spirit::ascii::space_type
			>
{
	virtual void constructor() = 0;
};
