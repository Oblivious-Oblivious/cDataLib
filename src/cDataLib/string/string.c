#include "headers/string.h"

static void string_ensure_space(string *sb, size_t add_len) {
    if(sb == NULL || add_len == 0) return;

    /* If out allocated space is big enough */
    if(sb->alloced >= sb->length+add_len + 1) return;

    while (sb->alloced < sb->length+add_len + 1) {
        /* Doubling growth strategy */
        sb->alloced <<= 1;
        if(sb->alloced == 0) {
            /* Left shift of max bits will go to 0. An unsigned type set to
             * -1 will return the maximum possible size. However, we should
             *  have run out of memory well before we need to do this. Since
             *  this is the theoretical maximum total system memory we don't
             *  have a flag saying we can't grow any more because it should
             *  be impossible to get to this point */
            sb->alloced--;
        }
    }
    sb->str = (char*)realloc(sb->str, sb->alloced);
}

string *new_string(char *initial_string) {
    string *sb = (string*)calloc(1, sizeof(*sb));
    sb->str = (char*)malloc(string_init_capacity);

    /* NULL terminate the string */
    *sb->str = '\0';

    sb->alloced = string_init_capacity;
    sb->length = 0;

    string_add_str(sb, initial_string);
    return sb;
}

void string_add_str(string *sb, const char *str) {
    if(sb == NULL || str == NULL || *str == '\0') return;

    size_t len = strlen(str);
    string_ensure_space(sb, len);

    /* Copy the value into memory */
    memmove(sb->str+sb->length, str, len);

    /* Reset length and NULL terminate */
    sb->length += len;
    sb->str[sb->length] = '\0';
}

void string_add_char(string *sb, char c) {
    if(sb == NULL) return;

    string_ensure_space(sb, 1);

    sb->str[sb->length] = c;
    sb->length++;
    sb->str[sb->length] = '\0';
}

void string_add_int(string *sb, int val) {
    char str[1024];

    if(sb == NULL) return;

    snprintf(str, sizeof(str), "%d", val);
    string_add_str(sb, str);
}

void string_add_double_precision(string *sb, double val) {
    char str[1024];

    if(sb == NULL) return;

    /* Use %g for minimum precision on printing floats */
    snprintf(str, sizeof(str), "%g", val);
    string_add_str(sb, str);
}

char *string_get(string *sb) {
    if(sb == NULL) return NULL;
    return sb->str;
}

char string_get_char_at_index(string *sb, size_t index) {
    if(sb == NULL) return '\0';
    return sb->str[index];
}

void string_shorten(string *sb, size_t len) {
    if(sb == NULL || len >= sb->length) return;

    /* Reset the length and NULL terminate, ingoring
        all values right to the NULL from memory */
    sb->length = len;
    sb->str[sb->length] = '\0';
}

void string_delete(string *sb) {
    if(sb == NULL) return;

    /* Call truncate with 0, clearing out the string */
    string_shorten(sb, 0);
}

void string_skip(string *sb, size_t len) {
    if(sb == NULL || len == 0) return;

    if(len >= sb->length) {
        /* If we choose to drop more bytes than the
            string has simply clear the string */
        string_delete(sb);
        return;
    }

    sb->length -= len;

    /* +1 to move the NULL. */
    memmove(sb->str, sb->str + len, sb->length + 1);
}

size_t string_length(string *sb) {
    if(sb == NULL) return 0;
    return sb->length;
}

unsigned char string_equals(string *sb, string *other) {
    return strcmp(string_get(sb), string_get(other)) == 0;
}

char *string_identifier(string *sb) {
    if(sb == NULL) return NULL;

    string *output = new_string("");

    unsigned char add_underscore = 0;
    char buf[32];
    size_t i;

    for(i = 0; i < string_length(sb); i++) {
        char c = string_get(sb)[i];

        if((c > 47 && c < 58)
        || (c > 64 && c < 91)
        || (c > 96 && c != 95 && c < 123))
            string_add_char(output, c);
        else if(c == 32)
            string_add_char(output, '_');
        else {
            if(i == 0) add_underscore = 1;
            sprintf(buf, "%02x", c & 0xff);
            string_add_str(output, buf);
        }
    }

    string *ret_value;
    if(add_underscore)
        ret_value = new_string("_");
    else
        ret_value = new_string("");
    string_add_str(ret_value, string_get(output));

    return string_get(ret_value);
}