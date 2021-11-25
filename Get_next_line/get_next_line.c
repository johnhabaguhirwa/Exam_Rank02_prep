#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

int ft_strlen(const char *str)
{
    int i;

    while (str[i])
        i++;
    return (i);
}

char    *ft_substr(const char *str, int start, int len)
{
    char    *substr;
    int     i = 0;
    int     j = 0;

    substr = (char *)malloc(sizeof(char) * len + 1);
    if (!substr)
        return (NULL);
    while (str[i])
    {
        if (i >= start && i < len)
            substr[j++] = str[i];
        i++;
    }
    substr[j] ='\0';
    return (substr);
}

char    *ft_strjoin(const char *s1, const char *s2)
{
    char    *str;
    int     i = 0;
    int     j = 0;

    str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
    if (!str)
        return (NULL);
    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    while (s2[j])
    {
        str[i + j] = s2[j];
        j++;
    }
    str[i + j] = '\0';
    return (str);
 }

char    *ft_strdup(char *str)
{
    char    *strdup;
    int     i = 0;

    strdup = (char *)malloc(sizeof(char) * ft_strlen(str) + 1);
    if (!strdup)
        return (NULL);
    while (str[i])
    {
        strdup[i] = str[i];
        i++;
    }
    strdup[i] = '\0';
    return (strdup);
}

char    *ft_strchr(const char *str, int c)
{
    if (!c)
        return ((char *)str);
    while (*str)
    {
        if (*str == c)
            return ((char *)str);
        str++;
    }
    return (NULL);
}

static char *read_and_append(int fd, char *buffer, char *remainder)
{
    int     bytes_read = 1;
    char    *temp;
    
    while (bytes_read != 0)
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read == -1)
            return (NULL);
        if (bytes_read == 0)
            break ;
        buffer[bytes_read] = '\0';
        if (!remainder)
            remainder = ft_strdup("");
        temp = remainder;
        remainder = ft_strjoin(temp, buffer);
        free(temp);
        temp = NULL;
        if (ft_strchr(buffer, '\n'))
            break ;
    }
    return (remainder);
}

char    *update_next_line(char *line)
{
    char    *remainder;
    int     idx;

    while (line[idx] != '\0' && line[idx] != '\n')
        idx++;
    if (line[idx] == '\0' || line[1] == '\0')
        return (NULL);
    remainder = ft_substr(line, idx + 1, ft_strlen(line) - idx);
    if (!(*remainder))
    {
        free(remainder);
        remainder = NULL;
    }
    line[idx + 1] = '\0';
    return (remainder);
}

char    *get_next_line(int fd)
{
    char        *line;
    char        *buffer;
    static char *remainder;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (0);
    buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
    if (!buffer)
        return (NULL);
    line = read_and_append(fd, buffer, remainder);
    free(buffer);
    buffer = NULL;
    if (!line)
        return (NULL);
    remainder = update_next_line(line);
    return (line);
}

int main(void)
{
    int fd;

    fd = open("test.txt", O_RDWR);
    printf("Next line:  %s\n", get_next_line(fd));
    printf("Next line:  %s\n", get_next_line(fd));
    printf("Next line:  %s\n", get_next_line(fd));
    printf("Next line:  %s\n", get_next_line(fd));
    return (0);
}