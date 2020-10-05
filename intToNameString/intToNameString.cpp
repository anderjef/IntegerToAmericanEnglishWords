//This program was developed starting October 04, 2020, to take integer inputs and quickly return the numbers as American-English phrases. This program
//was designed for Windows.

//future considerations: optimize further, accept numbers in other bases, consider accepting commas in input, consider outputting in other languages,
//only the maximum number of input digits supported and the appendices array need be updated to scale to even larger numbers

#include <iostream>
#include <string>
#include <sstream>
using namespace std;

constexpr unsigned int baseTen = 10; //the output base
constexpr unsigned int maxDigits = 102; //the maximum number of input digits supported
const string digits[baseTen] = { "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
const string AmericanAppendices[maxDigits / 3] = { "", " thousand",
                " million", " billion", " trillion", " quadrillion", " quintillion", " sextillion", " septillion", " octillion", " nonillion",
                " decillion", " undecillion", " duodecillion", " tredecillion", " quattuordecillion", " quindecillion", " sexdecillion", " septendecillion", " octodecillion", " novemdecillion",
                " vigintillion", " unvigintillion", " duovigintillion", " trevigintillion", " quattuorvigintillion", " quinvigintillion", " sexvigintillion", " septenvigintillion", " octovigintillion", " novemvigintillion",
                " trigintillion", " untrigintillion", " duotrigintillion" };

string decimalNumberToEnglishWords(const string number) { //returns an empty string on error
    if (number.size() < 1) { return ""; }
    string numberAsEnglishWords = "";
    bool hasSignChar = false;
    if (number[0] == '-') {
        if (number.size() < 2) {
            cerr << "Error: rejected the input " << number << " for not being an integer.";
            return "";
        }
        hasSignChar = true;
        numberAsEnglishWords += " negative"; //adding a space at the beginning allows for easy removal once finished parsing rather than dynamically determining when to add preceding spaces
    }
    else if (number[0] == '+') {
        if (number.size() < 2) {
            cerr << "Error: rejected the input " << number << " for not being an integer.";
            return "";
        }
        hasSignChar = true;
    }

    const size_t numberSize = number.size();
    size_t index = hasSignChar;
    for (; numberSize - index > maxDigits; ++index) {
        if (number[index] != '0') {
            cerr << "Error: rejected the input " << number << " for having too great a magnitude, sorry.";
            return "";
        }
    }

    bool hadHundredsPlace = false, hadLessThanHundredsPlace = false, sawAnyNonzeroDigit = false;
    for (; index < numberSize; ++index) {
        if (isdigit(number[index])) { //future consideration: accept input numbers in other bases
            if ((numberSize - index) % 3 == 0) { //if looking at any of the "hundred"s digits
                hadHundredsPlace = (number[index] != '0');
                if (hadHundredsPlace) {
                    numberAsEnglishWords += ' ' + digits[number[index] - '0'] + " hundred";
                }
            }
            else {
                hadLessThanHundredsPlace = true; //reset
                if ((numberSize - index) % 3 == 2) { //handle the two non-"hundred"s digits at the same time
                    index++;
                    switch (number[index - 1]) { //switch on left digit
                    case '0':
                        numberAsEnglishWords += ' ' + digits[number[index] - '0'];
                        break;
                    case '1':
                        switch (number[index]) { //switch on right digit
                        case '0':
                            numberAsEnglishWords += " ten";
                            break;
                        case '1':
                            numberAsEnglishWords += " eleven";
                            break;
                        case '2':
                            numberAsEnglishWords += " twelve";
                            break;
                        case '3':
                            numberAsEnglishWords += " thirteen";
                            break;
                        case '4':
                            numberAsEnglishWords += " fourteen";
                            break;
                        case '5':
                            numberAsEnglishWords += " fifteen";
                            break;
                        case '6':
                            numberAsEnglishWords += " sixteen";
                            break;
                        case '7':
                            numberAsEnglishWords += " seventeen";
                            break;
                        case '8':
                            numberAsEnglishWords += " eighteen";
                            break;
                        case '9':
                            numberAsEnglishWords += " nineteen";
                            break;
                        }
                        break;
                    case '2':
                        numberAsEnglishWords += " twenty-" + digits[number[index] - '0'];
                        break;
                    case '3':
                        numberAsEnglishWords += " thirty-" + digits[number[index] - '0'];
                        break;
                    case '4':
                        numberAsEnglishWords += " forty-" + digits[number[index] - '0'];
                        break;
                    case '5':
                        numberAsEnglishWords += " fifty-" + digits[number[index] - '0'];
                        break;
                    case '6':
                        numberAsEnglishWords += " sixty-" + digits[number[index] - '0'];
                        break;
                    case '7':
                        numberAsEnglishWords += " seventy-" + digits[number[index] - '0'];
                        break;
                    case '8':
                        numberAsEnglishWords += " eighty-" + digits[number[index] - '0'];
                        break;
                    case '9':
                        numberAsEnglishWords += " ninety-" + digits[number[index] - '0'];
                        break;
                    }

                    if (number[index - 1] != '1' && number[index] == '0') {
                        if (number[index - 1] == '0') {
                            if (numberSize - index == 1 && !sawAnyNonzeroDigit) {
                                return "zero";
                            }
                            hadLessThanHundredsPlace = false;
                        }
                        numberAsEnglishWords = numberAsEnglishWords.substr(0, numberAsEnglishWords.size() - 1); //remove the character placed in anticipation of a nonzero right digit
                    }
                }
                else { //there was no tens-place digit, so only handle the ones-place digit
                    numberAsEnglishWords += ' ' + digits[number[index] - '0'];

                    if (number[index] == '0') { //need to undo the operation just done
                        if (numberSize - index == 1 && !sawAnyNonzeroDigit) {
                            return "zero";
                        }
                        numberAsEnglishWords = numberAsEnglishWords.substr(0, numberAsEnglishWords.size() - 1); //remove the character placed in anticipation of a nonzero right digit
                        hadLessThanHundredsPlace = false;
                    }
                }
                if (hadHundredsPlace || hadLessThanHundredsPlace) { //if appendix is needed
                    sawAnyNonzeroDigit = true;
                    numberAsEnglishWords += AmericanAppendices[(numberSize - index - 1) / 3] + ','; //adding a comma after each allows for easy removal at the end of parsing the number rather than dynamically determining when to add commas
                }
            }
        }
        else {
            cerr << "Error: rejected the input " << number << " for not being an integer.";
            return "";
        }
    }

    return numberAsEnglishWords.substr(1, numberAsEnglishWords.size() - 2); //remove initial space and terminal comma that are guaranteed to be there instead of dynamically determining when to add them
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        cout << "Input integers to receive a list of their corresponding English phrases: ";
        string line;
        getline(cin, line);
        istringstream iss(line);
        //string n;
        while (iss >> line || !iss.eof()) { //future consideration: accept numbers in other bases
            if (iss.fail()) {
                iss.clear();
                cerr << "Error: rejected an input for not being an integer or having too great a magnitude.\n";
            }
            else {
                cout << decimalNumberToEnglishWords(line) << '\n';
            }
        }
    }
    else {
        for (int i = 1; i < argc; ++i) {
            cout << decimalNumberToEnglishWords(argv[i]) << '\n'; //future consideration: accept numbers in other bases
        }
    }
}