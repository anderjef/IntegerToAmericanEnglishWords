//TODO: accept commas in input
//TODO: allow for outputting in other languages


#include <iostream>
#include <sstream>
#include <string>
using std::cerr;
using std::cin;
using std::cout;
using std::istringstream;
using std::string;


constexpr unsigned int radix = 10; //TODO: allow customization of radix

const string digits[radix] = { "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
const char* AmericanAppendices[] = { "", " thousand",
							" million", " billion", " trillion", " quadrillion", " quintillion", " sextillion", " septillion", " octillion", " nonillion",
							" decillion", " undecillion", " duodecillion", " tredecillion", " quattuordecillion", " quindecillion", " sexdecillion", " septendecillion", " octodecillion", " novemdecillion",
							" vigintillion", " unvigintillion", " duovigintillion", " trevigintillion", " quattuorvigintillion", " quinvigintillion", " sexvigintillion", " septenvigintillion", " octovigintillion", " novemvigintillion",
							" trigintillion", " untrigintillion", " duotrigintillion" }; //TODO: update to scale to even larger numbers
const string theTens[radix] = { " ten", " eleven", " twelve", " thirteen", " fourteen", " fifteen", " sixteen", " seventeen", " eighteen", " nineteen" }; //ten through nineteen have unique names
const string tensPlace[radix] = { " ", " ", " twenty-", " thirty-", " forty-", " fifty-", " sixty-", " seventy-", " eighty-", " ninety-" };


string decimalNumberToAmericanEnglishWords(const string& number) { //returns an empty string on error //TODO: grammatical "and"s
	if (number.empty()) { return ""; }
	string numberAsAmericanEnglishWords = "";
	size_t index = 1; //start after any (initially assumed) sign character or leading zero
	switch (number[0]) {
	case '+':
	case '-':
		if (number.size() == 1) {
			cerr << "Error: input " << number << " rejected for not being an integer.\n";
			return "";
		}
		numberAsAmericanEnglishWords += (number[0] == '+' ? " positive" : " negative"); //adding a space at the beginning allows for easy removal once finished parsing rather than dynamically determining when to add preceding spaces
		break;
	case '0': //leading zeros such as at number[0] can be safely ignored
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
		index = 0;
		break;
	default:
		cerr << "Error: input " << number << " rejected for not being an integer.\n";
		return "";
	}

	const size_t firstNonzero = number.find_first_not_of('0', index);
	if (firstNonzero == string::npos) {
		numberAsAmericanEnglishWords += " zero";
		return numberAsAmericanEnglishWords.substr(1); //remove initial space that is guaranteed to be there instead of dynamically determining when to add it
	}
	if (!isdigit(number[firstNonzero])) {
		cerr << "Error: input " << number << " rejected for not being an integer.\n";
		return "";
	}
	if (number.size() - firstNonzero > sizeof(AmericanAppendices) / sizeof(AmericanAppendices[0]) * 3) { //each appendix can account for three digits
		cerr << "Error: input " << number << " rejected for having too great a magnitude, sorry!";
		return "";
	}

	for (index = firstNonzero; index < number.size(); index++) {
		switch ((number.size() - index) % 3) {
		case 0: //if looking at any of the hundreds-places' digits
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
				numberAsAmericanEnglishWords += theTens[number[index] - '0']; //includes a preceding space
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
					numberAsAmericanEnglishWords.erase(numberAsAmericanEnglishWords.size() - 1, 1); //remove the hyphen placed in anticipation of a nonzero right digit; corrected after the fact as (with equal probability of each digit appearing) this is anticipated to be more optimized than checking nonzero for each digit
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
				numberAsAmericanEnglishWords += theTens[number[index] - '0']; //includes a preceding space
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
					numberAsAmericanEnglishWords.erase(numberAsAmericanEnglishWords.size() - 1, 1); //remove the hyphen placed in anticipation of a nonzero right digit; corrected after the fact as (with equal probability of each digit appearing) this is anticipated to be more optimized than checking nonzero for each digit
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
			numberAsAmericanEnglishWords += string(AmericanAppendices[(number.size() - index - 1) / 3]) + ','; //adding a comma after each allows for easy removal at the end of parsing the number rather than dynamically determining when to add commas
		}
	}
	return numberAsAmericanEnglishWords.substr(1, numberAsAmericanEnglishWords.size() - 2); //remove initial space and terminal comma that are guaranteed to be there instead of dynamically determining when to add them
}


bool getNameOfNumber(const string& number) { //returns false on success and true on failure
	const string nameOfNumber = decimalNumberToAmericanEnglishWords(number);
	if (!nameOfNumber.empty()) {
		cout << nameOfNumber << '\n';
		return false;
	}
	else {
		return true;
	}
}


unsigned int main(int argc, char* argv[]) { //returns how many number interpretations had a compromising error
	unsigned int errorTally = 0;
	if (argc == 1) {
		cout << "Input integers to receive a list of their corresponding American-English names: ";
		string line;
		getline(cin, line);
		istringstream iss(line);
		while (iss >> line) {
			errorTally += getNameOfNumber(line);
		}
	}
	else {
		for (int i = 1; i < argc; i++) {
			errorTally += getNameOfNumber(argv[i]);
		}
	}
	return errorTally;
}