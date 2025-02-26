#include "cub3d.h"

/**
 * Simple structure to track map parsing state
 */
typedef struct s_map_parser
{
    char    **lines;         // Array of map lines
    int     count;           // Current count of lines
    int     capacity;        // Total capacity of lines array
    int     saw_empty_line;  // Flag for if we've seen an empty line
}   t_map_parser;

/**
 * Initialize a new map parser with default values
 */
static void init_map_parser(t_map_parser *parser)
{
    parser->lines = NULL;
    parser->count = 0;
    parser->capacity = 0;
    parser->saw_empty_line = 0;
}

/**
 * Clean up map parser and free all allocated memory
 */
static void cleanup_map_parser(t_map_parser *parser)
{
    int i;
    
    if (parser->lines)
    {
        i = 0;
        while (i < parser->count)
        {
            if (parser->lines[i])
                free(parser->lines[i]);
            i++;
        }
        free(parser->lines);
        parser->lines = NULL;
    }
    parser->count = 0;
    parser->capacity = 0;
}

/**
 * Ensure the map parser has enough capacity for more lines
 * Returns 0 on success, -1 on failure
 */
static int ensure_capacity(t_map_parser *parser)
{
    char **new_lines;
    int new_capacity;
    
    if (parser->count >= parser->capacity)
    {
        new_capacity = parser->capacity == 0 ? 32 : parser->capacity * 2;
        new_lines = malloc(sizeof(char *) * new_capacity);
        if (!new_lines)
            return (-1);
            
        // Copy existing pointers to new array
        if (parser->lines)
        {
            for (int i = 0; i < parser->count; i++)
                new_lines[i] = parser->lines[i];
            free(parser->lines);
        }
        
        parser->lines = new_lines;
        parser->capacity = new_capacity;
    }
    return (0);
}

/**
 * Check if a line is empty or just whitespace
 */
static int is_empty_line(const char *line)
{
    int i;

    i = 0;
    while (line[i])
    {
        if (line[i] != ' ' && line[i] != '\t' && line[i] != '\n')
            return (0);
        i++;
    }
    return (1);
}

/**
 * Add a line to the map parser
 * Returns 0 on success, -1 on failure
 */
static int add_line(t_map_parser *parser, char *line)
{
    // Check for empty lines
    if (is_empty_line(line))
    {
        if (parser->count > 0)
            parser->saw_empty_line = 1;
        free(line); // We don't store empty lines
        return (0);
    }
    
    // Check if we've seen an empty line already
    if (parser->saw_empty_line)
    {
        fprintf(stderr, "Error: Map has an empty line within it.\n");
        free(line);
        return (-1);
    }
    
    // Ensure we have space
    if (ensure_capacity(parser) < 0)
    {
        free(line);
        return (-1);
    }
    
    // Add the line
    parser->lines[parser->count++] = line;
    return (0);
}

/**
 * Parse the map from file and store in config
 * The first_line parameter is the first line of the map
 */
int parse_map(t_config *cfg, int fd, char *first_line)
{
    t_map_parser parser;
    char *line;
    
    init_map_parser(&parser);
    
    // Add the first line
    if (add_line(&parser, first_line) < 0)
    {
        cleanup_map_parser(&parser);
        return (-1);
    }
    
    // Read and add the rest of the lines
    while (1)
    {
        line = ft_getline(fd);
        if (!line)
            break;
            
        if (add_line(&parser, line) < 0)
        {
            cleanup_map_parser(&parser);
            return (-1);
        }
    }
    
    // Copy the map to the config
    cfg->map = parser.lines;
    cfg->map_count = parser.count;
    
    return (0);
}
