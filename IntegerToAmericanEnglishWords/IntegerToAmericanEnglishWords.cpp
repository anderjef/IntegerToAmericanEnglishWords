//This program was developed starting October 04, 2020, to take integer inputs and quickly return the numbers as American-English phrases. This program
//was designed for Windows.


//future considerations: optimize, consider accepting commas in input, consider outputting in other languages, simply update the maximum number of
//input digits supported and the appendices array to scale to even larger numbers


#include <iostream>
#include <sstream>
#include <string>
using std::cerr;
using std::cin;
using std::cout;
using std::istringstream;
using std::string;


constexpr unsigned int baseTen = 10; //the input/output base //future consideration: accept input numbers in other bases
constexpr unsigned int maxDigits = 102; //the maximum number of input digits supported

const string digits[baseTen] = { "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" }; //the appearance of the word "zero" is rather unique
const string AmericanAppendices[maxDigits / 3] = { "", " thousand",
								" million", " billion", " trillion", " quadrillion", " quintillion", " sextillion", " septillion", " octillion", " nonillion",
								" decillion", " undecillion", " duodecillion", " tredecillion", " quattuordecillion", " quindecillion", " sexdecillion", " septendecillion", " octodecillion", " novemdecillion",
								" vigintillion", " unvigintillion", " duovigintillion", " trevigintillion", " quattuorvigintillion", " quinvigintillion", " sexvigintillion", " septenvigintillion", " octovigintillion", " novemvigintillion",
								" trigintillion", " untrigintillion", " duotrigintillion" };
const string theTens[baseTen] = { " ten", " eleven", " twelve", " thirteen", " fourteen", " fifteen", " sixteen", " seventeen", " eighteen", " nineteen" }; //ten through nineteen have unique names
const string tensPlace[baseTen] = { " ", " ", " twenty-", " thirty-", " fourty-", " fifty-", " sixty-", " seventy-", " eighty-", " ninety-" };


string decimalNumberToAmericanEnglishWords(const string& number) { //returns an empty string on error //future consideration: grammatical "and"s
	if (number.empty()) { return ""; }
	string numberAsAmericanEnglishWords = "";
	if (number[0] == '+') {
		if (number.size() == 1) {
			cerr << "Error: input " << number << " rejected for not being an integer.\n";
			return "";
		}
		numberAsAmericanEnglishWords += " positive"; //adding a space at the beginning allows for easy removal once finished parsing rather than dynamically determining when to add preceding spaces
	}
	else if (number[0] == '-') {
		if (number.size() == 1) {
			cerr << "Error: input " << number << " rejected for not being an integer.\n";
			return "";
		}
		numberAsAmericanEnglishWords += " negative"; //adding a space at the beginning allows for easy removal once finished parsing rather than dynamically determining when to add preceding spaces
	}

	size_t index = !isdigit(number[0]); //start after any sign character
	if (index != 0 && numberAsAmericanEnglishWords.empty()) { //the first character is actually invalid
		cerr << "Error: input " << number << " rejected for not being an integer.\n";
		return "";
	}
	for (; number.size() - index > maxDigits; index++) { //confirm extra large digits are all zeros, or throw an error
		if (number[index] != '0') {
			cerr << "Error: input " << number << " rejected for ";
			if (!isdigit(number[index])) {
				cerr << "not being an integer.\n";
			}
			else {
				cerr << "having too great a magnitude, sorry.\n";
			}
			return "";
		}
	}
	for (; index < number.size() && number[index] == '0'; index++) {} //get to the first nonzero digit
	if (index == number.size()) { return "zero"; }

	for (; index < number.size(); index++) {
		switch ((number.size() - index) % 3) {
		case 0: //if looking at any of the "hundred"s (places') digits
			if (!isdigit(number[index])) {
				cerr << "Error: input " << number << " rejected for not being an integer.\n";
				return "";
			}
			if (number[index] != '0') {
				numberAsAmericanEnglishWords += ' ' + digits[number[index] - '0'] + " hundred";
			}
			index += 2;
			switch (number[index - 1]) { //switch on the tens-place's digit
			case '1':
				if (!isdigit(number[index])) {
					cerr << "Error: input " << number << " rejected for not being an integer.\n";
					return "";
				}
				numberAsAmericanEnglishWords += theTens[number[index] - '0']; //includes the preceding spaces
				break;
			case '0': //even zero tens gets handled appropriately by the tensPlace array
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (!isdigit(number[index])) {
					cerr << "Error: input " << number << " rejected for not being an integer.\n";
					return "";
				}
				numberAsAmericanEnglishWords += tensPlace[number[index - 1] - '0'] + digits[number[index] - '0'];
				if (number[index] == '0') {
					numberAsAmericanEnglishWords.erase(numberAsAmericanEnglishWords.size() - 1, 1); //remove the hyphen character placed in anticipation of a nonzero right digit; corrected after the fact as (with equal probability of each digit appearing) this is anticipated to be more optimized than checking nonzero for each digit
				}
				break;
			default:
				cerr << "Error: input " << number << " rejected for not being an integer.\n";
				return "";
			}
			break;
		case 2: //if looking at any of the tens-places' digits
			index++;
			switch (number[index - 1]) { //switch on the tens-place's digit
			case '1':
				if (!isdigit(number[index])) {
					cerr << "Error: input " << number << " rejected for not being an integer.\n";
					return "";
				}
				numberAsAmericanEnglishWords += theTens[number[index] - '0']; //includes the preceding spaces
				break;
			case '0': //even zero tens gets handled appropriately by the tensPlace array
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				if (!isdigit(number[index])) {
					cerr << "Error: input " << number << " rejected for not being an integer.\n";
					return "";
				}
				numberAsAmericanEnglishWords += tensPlace[number[index - 1] - '0'] + digits[number[index] - '0'];
				if (number[index] == '0') {
					numberAsAmericanEnglishWords.erase(numberAsAmericanEnglishWords.size() - 1, 1); //remove the hyphen character placed in anticipation of a nonzero right digit; corrected after the fact as (with equal probability of each digit appearing) this is anticipated to be more optimized than checking nonzero for each digit
				}
				break;
			default:
				cerr << "Error: input " << number << " rejected for not being an integer.\n";
				return "";
			}
			break;
		case 1: //if looking at any of the ones-places' digits
			switch (number[index]) {
			case '0':
				break;
			case '1':
			case '2':
			case '3':
			case '4':
			case '5':
			case '6':
			case '7':
			case '8':
			case '9':
				numberAsAmericanEnglishWords += ' ' + digits[number[index] - '0'];
				break;
			default:
				cerr << "Error: input " << number << " rejected for not being an integer.\n";
				return "";
			}
			break;
		}
		if (number[index] != '0' || (index >= 1 && number[index - 1] != '0') || (index >= 2 && number[index - 2] != '0')) {
			numberAsAmericanEnglishWords += AmericanAppendices[(number.size() - index - 1) / 3] + ','; //adding a comma after each allows for easy removal at the end of parsing the number rather than dynamically determining when to add commas
		}
	}
	return numberAsAmericanEnglishWords.substr(1, numberAsAmericanEnglishWords.size() - 2); //remove initial space and terminal comma that are guaranteed to be there instead of dynamically determining when to add them
}


int main(int argc, char* argv[]) { //returns how many number interpretations had a compromising error
	if (argc == 1) {
		cout << "Input integers to receive a list of their corresponding English phrases: ";
		string line;
		getline(cin, line);
		istringstream iss(line);
		int errorTally = 0;
		while (iss >> line) {
			const string result = decimalNumberToAmericanEnglishWords(line);
			if (!result.empty()) {
				cout << result << '\n';
			}
			else {
				errorTally++;
			}
		}
		return errorTally;
	}
	else {
		int errorTally = 0;
		for (int i = 1; i < argc; ++i) {
			const string result = decimalNumberToAmericanEnglishWords(argv[i]);
			if (!result.empty()) {
				cout << result << '\n';
			}
			else {
				errorTally++;
			}
		}
		return errorTally;
	}
}