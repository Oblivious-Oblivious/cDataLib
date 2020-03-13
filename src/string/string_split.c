#include "../../headers/_data_structures.h"

vectorT *string_split(stringT *str, stringT *delimeter) {
	vectorT *str_tokens = new_vectorT();
	stringT *token_str = new_stringT("");

	/* Iterate through the chars constructing a string and
		reseting the value once we find the delimeter */
	for(size_t i = 0; (i <= string_length(str)
	&& string_get_char_at_index(str, i) != '\0'); i++) {
		if(string_get_char_at_index(str, i) == string_get(delimeter)[0]) {
			/* We found a character matching the delimeter */
			vector_add(str_tokens, token_str);

			/* Reset the temp string */
			token_str = new_stringT("");
			continue;
		}

		string_add_char(token_str, string_get_char_at_index(str, i));
	}

	/* We add the last collected characters */
	vector_add(str_tokens, token_str);
	return str_tokens;
}