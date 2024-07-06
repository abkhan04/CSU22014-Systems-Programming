// code for a huffman coder
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>

#include "huff.h"


// create a new huffcoder structure
struct huffcoder * huffcoder_new()
{
    struct huffcoder *result = calloc(1, sizeof(struct huffcoder));
    result -> tree = calloc(1, sizeof(struct huffchar));

    return result;
}

// count the frequency of characters in a file; set chars_list with zero
// frequency to one
void huffcoder_count(struct huffcoder *this, char *filename)
{
    FILE *file;
    file = fopen(filename, "r");

    int char_index = fgetc(file);

    while (!feof(file))
    {
        this -> freqs[char_index]++;
        char_index = fgetc(file);
    }

    for (int i = 0; i < NUM_CHARS; i++)
    {
        if (this -> freqs[i] == 0)
        {
            this -> freqs[i] = 1;
        }
    }

    fclose(file);
}

// using the character frequencies build the tree of compound
// and simple characters that are used to compute the Huffman codes

int find_lowest_freq(struct huffchar **chars_list, int length)
{
    int min_index = 0;
    int min_freq = chars_list[0] -> freq;

    for (int i = 1; i < length; i++)
    {
        if (chars_list[i] -> freq < min_freq)
        {
            min_freq = chars_list[i] -> freq;
            min_index = i;
        }
    }

    return min_index;
}

struct huffchar * create_compund(struct huffchar *first, struct huffchar *second)
{
    struct huffchar *result = malloc(sizeof(struct huffchar));
    result -> freq = first -> freq + second -> freq;
    result -> is_compound = 1;
    result -> u.compound.left = first;
    result -> u.compound.right = second;

    return result;
}

void write_huffman_codes(struct huffchar *node, int *path, int depth)
{
    if (node -> is_compound == 0)
    {
        // simple char
        printf("%c:", node -> u.c);

        for (int i = 0; i < depth; i++)
        {
            printf("%d", path[i]);
        }

        printf("\n");
    }
    else
    {
        // compound node
        path[depth] = 0;
        write_huffman_codes(node -> u.compound.left, path, depth + 1);

        path[depth] = 1;
        write_huffman_codes(node -> u.compound.right, path, depth + 1);
    }
}

void huffcoder_build_tree(struct huffcoder *this)
{
    struct huffchar **chars_list = malloc(sizeof(struct huffchar *) * NUM_CHARS);

    for (int i = 0; i < NUM_CHARS; i++)
    {
        chars_list[i] = malloc(sizeof(struct huffchar));
        chars_list[i] -> freq = this -> freqs[i];
        chars_list[i] -> is_compound = 0;
        chars_list[i] -> seqno = i;
        chars_list[i] -> u.c = i;
    }

    for (int chars_length = NUM_CHARS; chars_length > 1; chars_length--)
    {
        int lowest_freq = find_lowest_freq(chars_list, chars_length);

        struct huffchar *first = chars_list[lowest_freq];
        chars_list[lowest_freq] = chars_list[chars_length - 1];

        lowest_freq = find_lowest_freq(chars_list, chars_length - 1);

        struct huffchar *second = chars_list[lowest_freq];

        struct huffchar *fusion = create_compound(first, second);
        chars_list[lowest_freq = fusion];
    }
}

// using the Huffman tree, build a table of the Huffman codes
// with the huffcoder object
void huffcoder_tree2table(struct huffcoder *this)
{

}

// print the Huffman codes for each character in order;
// you should not modify this function
void huffcoder_print_codes(struct huffcoder *this)
{
    for (int i = 0; i < NUM_CHARS; i++)
    {
        // print the code
        printf("char: %d, freq: %d, code: %s\n", i, this->freqs[i], this->codes[i]);;
    }
}

// encode the input file and write the encoding to the output file
void huffcoder_encode(struct huffcoder *this, char *input_filename, char *output_filename)
{

}

// decode the input file and write the decoding to the output file
void huffcoder_decode(struct huffcoder *this, char *input_filename, char *output_filename)
{

}
