


//                                  LAB ASSIGNMENT                                 
// Programmer: Jason Arias        
// Class: CS 3820                                                              
                                                       


#include <iostream>
#include <iomanip>
#include "ctype.h"
#include "string.h"
#include "stdio.h"
using namespace std;

enum tokenType {
	AND, BEGIN, END, FOR, IF, NOT, OR, READ, WHILE, WRITE, COMMENT, IDENTIFIER, REAL, STRING, PLUS, MULTIPLICATION, ASSIGNMENT,
	EQUAL, GREATER_THAN, LESS_THAN, LEFT_PARENTHESIS, COMMA, RIGHT_PARENTHESIS, SEMICOLON, INVALID, DIVISION, INTEGER
};

const int buffSize = 80;
char tokenBuffer[80];

int chh;

static char message[][20] = { "and", "begin", "end","for", "if", "not","or", "read", "while","write", "comment", "identifier",
"real constant", "string", "plus","multiplication", "assignment", "equal", "greater than","less than",
"left parenthesis", "comma","right parenthesis", "semicolon", "invalid","division","integer" };

static char reservedWord[][10] = { "AND","BEGIN","END","FOR","IF","NOT","OR","READ","WHILE","WRITE" };



void skipSpaces();
void clearBuffer();
void displayToken(tokenType code);
tokenType getID();
tokenType getComment();
tokenType getReal();
tokenType getStrings();
tokenType getPlus();
tokenType getMul();
tokenType getAssign();
tokenType getEqual();
tokenType getGreater();
tokenType getLess();
tokenType getLP();
tokenType getRP();
tokenType getComma();
tokenType getSColon();

tokenType lexical_error();
tokenType scanner();

//skips over space characters in the input stream
void skipSpaces()
{
	int ch;
	ch = cin.get();
	while (isspace(ch))
		ch = cin.get();
	cin.putback(ch);

}

//reads an invalid character and returns  the code for invalid characters
tokenType lexical_error()
{
	tokenType code;
	int ch, i = 0;

	tokenBuffer[i++] = chh;
	code = INVALID;
	return code;
}

tokenType scanner()
{
	tokenType code;
	int ch;


	skipSpaces();
	ch = cin.get();

	if (ch == EOF)
	{
		cin.putback(ch);
		code = INVALID;
	}
	else if (isalpha(ch))
	{
		cin.putback(ch);
		code = getID();
	}
	else if (ch == '/')
	{
		cin.putback(ch);
		code = getComment();
	}
	else if (isdigit(ch))
	{
		cin.putback(ch);
		code = getReal();
	}
	else if (ch == '"')
	{
		cin.putback(ch);
		code = getStrings();
	}
	else if (ch == '+')
	{
		cin.putback(ch);
		code = getPlus();
	}
	else if (ch == '*')
	{
		cin.putback(ch);
		code = getMul();
	}
	else if (ch == ':')
	{
		cin.putback(ch);
		code = getAssign();
	}
	else if (ch == '=')
	{
		cin.putback(ch);
		code = getEqual();
	}
	else if (ch == '>')
	{
		cin.putback(ch);
		code = getGreater();
	}
	else if (ch == '<')
	{
		cin.putback(ch);
		code = getLess();
	}
	else if (ch == '(')
	{
		cin.putback(ch);
		code = getLP();
	}
	else if (ch == ')')
	{
		cin.putback(ch);
		code = getRP();
	}
	else if (ch == ',')
	{
		cin.putback(ch);
		code = getComma();
	}
	else if (ch == ';')
	{
		cin.putback(ch);
		code = getSColon();
	}

	else
	{

		cin.putback(chh);
		code = lexical_error();
	}
	return code;


}

//sets all the elements of the buffer to the null character
void clearBuffer()
{
	for (int i = 0; i<buffSize; i++)
		tokenBuffer[i] = '\0';

}

//displays the appropiate message, and prints the contents of the buffer
void displayToken(tokenType code)
{
	cout << setw(20) << left << message[(int)code] << "\t";
	for (int i = 0; i<buffSize; i++)
	{
		if (tokenBuffer[i] != '\0')
			cout << tokenBuffer[i];
		else
			i = buffSize;
	}
	cout << endl;

}

//if it is a reserved word, it returns its code, otherwise it returns the code of identifiers
tokenType getID()
{


	tokenType code;
	int i = 0, ch;
	ch = cin.get();

	if (isalpha(ch))
	{
		tokenBuffer[i++] = ch;
		ch = cin.get();

		while (isalnum(ch))
		{
			tokenBuffer[i++] = ch;
			ch = cin.get();
		}

		int first = 0, mid, last = 9;
		bool not_found = true;

		while (first <= last && not_found)
		{
			mid = (first + last) / 2;
			int ans = strcmp(tokenBuffer, reservedWord[mid]);

			if (ans == 0)
				not_found = false;
			else if (ans>0)
				first = mid + 1;
			else
				last = mid - 1;
		}

		if (not_found)
			code = IDENTIFIER;
		else
			code = (tokenType)mid;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}

	return code;

}

//recognizes a comment and division
tokenType getComment()
{
	tokenType code;
	int ch, i = 0;
	ch = cin.get();

	if (ch == '/'&&cin.peek() == '*')
	{
		tokenBuffer[i++] = ch;
		ch = cin.get();
		tokenBuffer[i++] = ch;
		ch = cin.get();
		while (!(ch == '*' && cin.peek() == '/') && cin.peek() != EOF)
		{
			tokenBuffer[i++] = ch;
			ch = cin.get();
		}
		if (cin.peek() == EOF)
			code = INVALID;
		else
		{
			code = COMMENT;
			tokenBuffer[i++] = ch;
			ch = cin.get();
			tokenBuffer[i++] = ch;
		}
	}
	else
	{
		code = INVALID;

		cin.putback(ch);
	}

	return code;
}

//recognizes a real constant
tokenType getReal()
{
	tokenType code;
	int ch, i = 0;
	ch = cin.get();

	if (isdigit(ch))
	{
		tokenBuffer[i++] = ch;
		ch = cin.get();

		while (isdigit(ch))
		{
			tokenBuffer[i++] = ch;
			ch = cin.get();
		}

		if (ch == '.')
		{
			tokenBuffer[i++] = ch;
			ch = cin.get();

			if (isdigit(ch))
			{
				while (isdigit(ch))
				{
					tokenBuffer[i++] = ch;
					ch = cin.get();
				}

				cin.putback(ch);
				code = REAL;
			}
			else
				code = INVALID;
		}
		else
		{
			cin.putback(ch);
			code = INTEGER;
		}
	}
	else
	{
		while (ch != '\n' && i<buffSize)
		{
			tokenBuffer[i++] = ch;
			ch = cin.get();
		}
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

//recognizes a string constant
tokenType getStrings()
{
	tokenType code;
	int ch, i = 0;
	ch = cin.get();

	if (ch == '\"')
	{
		tokenBuffer[i++] = ch;
		ch = cin.get();

		while (!(ch == '\"') && ch != EOF)
		{
			tokenBuffer[i++] = ch;
			ch = cin.get();
		}

		if (ch != EOF)
		{

			tokenBuffer[i++] = ch;
			code = STRING;
		}
		else
			code = INVALID;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;

}

tokenType getPlus()
{
	tokenType code;
	int ch, i = 0;
	ch = cin.get();
	if (ch == '+')
	{
		tokenBuffer[i++] = ch;
		code = PLUS;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getMul()
{
	tokenType code;
	int ch, i = 0;
	ch = cin.get();
	if (ch == '*')
	{
		tokenBuffer[i++] = ch;
		code = MULTIPLICATION;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getAssign()
{
	tokenType code;
	int ch, i = 0;
	ch = cin.get();
	if (ch == ':')
	{
		tokenBuffer[i++] = ch;
		ch = cin.get();
		if (ch == '=')
		{
			tokenBuffer[i++] = ch;
			code = ASSIGNMENT;
		}
	}
	else
	{
		tokenBuffer[i++] = ch;
		cin.putback(ch);
		code = INVALID;
	}

	return code;
}


tokenType getEqual()
{
	tokenType code;
	int ch, i = 0;
	ch = cin.get();
	if (ch == '=')
	{
		tokenBuffer[i++] = ch;
		code = EQUAL;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getGreater()
{
	tokenType code;
	int ch, i = 0;
	ch = cin.get();
	if (ch == '>')
	{
		tokenBuffer[i++] = ch;
		code = GREATER_THAN;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getLess()
{
	tokenType code;
	int ch, i = 0;
	ch = cin.get();
	if (ch == '<')
	{
		tokenBuffer[i++] = ch;
		code = LESS_THAN;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getLP()
{
	tokenType code;
	int ch, i = 0;
	ch = cin.get();
	if (ch == '(')
	{
		tokenBuffer[i++] = ch;
		code = LEFT_PARENTHESIS;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getRP()
{
	tokenType code;
	int ch, i = 0;
	ch = cin.get();
	if (ch == ')')
	{
		tokenBuffer[i++] = ch;
		code = RIGHT_PARENTHESIS;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getComma()
{
	tokenType code;
	int ch, i = 0;
	ch = cin.get();
	if (ch == ',')
	{
		tokenBuffer[i++] = ch;
		code = COMMA;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}

tokenType getSColon()

{
	tokenType code;
	int ch, i = 0;
	ch = cin.get();
	if (ch == ';')
	{
		tokenBuffer[i++] = ch;
		code = SEMICOLON;
	}
	else
	{
		cin.putback(ch);
		code = INVALID;
	}
	return code;
}


int main()
{

	tokenType code;
	cout << setw(20) << left << "TOKEN/TYPES " << "\t" << "WORDS/LEXEMS" << endl;
	cout << setw(20) << left << "------------ " << "\t" << "-------------" << endl;
	


	code = scanner();
	displayToken(code);

		while ((int)code != EOF)
		{
			clearBuffer();
			code = scanner();
			displayToken(code);
		}
	

	system("pause");
	return 0;
}
