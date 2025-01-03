#include <cctype> 
#include "utils.h"

string lowerCaseString(const string& value) {
    string result;
    result.resize(value.size());
    transform(value.begin(), value.end(), result.begin(), [](unsigned char c) {
        return std::tolower(c);
    });
    return result;
}