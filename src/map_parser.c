#include "cub3d.h"

typedef struct s_map_parser
{
    char    **lines;
    int     count;
    int     capacity;
    int     saw_empty_line;
}   t_map_parser;

static void init_map_parser(t_map_parser *parser)
{
    parser->lines = NULL;
    parser->count = 0;
    parser->capacity = 0;
    parser->saw_empty_line = 0;
}

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

static int add_line(t_map_parser *parser, char *line)
{
    if (is_empty_line(line))
    {
        if (parser->count > 0)
            parser->saw_empty_line = 1;
        free(line);
        return (0);
    }
    
    if (parser->saw_empty_line)
    {
        fprintf(stderr, "Error: Map has an empty line within it.\n");
        free(line);
        return (-1);
    }
    
    if (ensure_capacity(parser) < 0)
    {
        free(line);
        return (-1);
    }
    
    parser->lines[parser->count++] = line;
    return (0);
}

int parse_map(t_config *cfg, int fd, char *first_line)
{
    t_map_parser parser;
    char *line;
    
    init_map_parser(&parser);
    
    if (add_line(&parser, first_line) < 0)
    {
        cleanup_map_parser(&parser);
        return (-1);
    }
    
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
    
    cfg->map = parser.lines;
    cfg->map_count = parser.count;
    
    return (0);
}
