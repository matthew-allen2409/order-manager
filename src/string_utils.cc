#include <cctype>
#include <cstring>
#include "string_utils.h"

void stripWhitespace(char buffer[]) {
    int length = strlen(buffer);
    int start = 0, end = length - 1;

    while(start <= end && std::isspace(buffer[start])) {
        start++;
    }

    while(end >= start && std::isspace(buffer[end])) {
        end--;
    }

    if (end < start) {
        buffer[0] = '\0';
        return;
    }

    for (int i = start; i <= end; i++) {
        buffer[i - start] = buffer[i];
    }

    buffer[end - start + 1] = '\0';
}
