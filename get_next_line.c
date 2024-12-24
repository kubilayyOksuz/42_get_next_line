#include "get_next_line.h"
#include <unistd.h>

static char	*ft_substr(char *s, int start, int len)
{
	char	*str;
    int  index;

    index = 0;
	if (start > ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) - start < len)
    {
        len = ft_strlen(s) - start;
		str = (char *)malloc((len + 1) * sizeof(char));
    }
	else
        str = (char *)malloc((len + 1) * sizeof(char));
	if (!str || !s)
		return (0);
    while (start < ft_strlen(s) && index < len)
        str[index++] = s[start++];
    str[index] = '\0';
	return (str);
}

char *read_line(char *str)
{
    int index;

    index = 0;
    if (!str || !str[index])
        return (NULL);
    while (str[index] && str[index] != '\n')
        index++;
    if (str[index] == '\n')
        index++;
    return (ft_substr(str, 0, index));
}

char *add_line(int fd, char *buffer)
{
    char *temp;
    int bytes_read;
    char *new_buffer;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    temp = (char *)malloc(BUFFER_SIZE + 1);
    if (!temp)
        return (NULL);
    if (!buffer)
        buffer = ft_strdup("");
    bytes_read = 1;
    while (!ft_strchr(buffer, '\n') && bytes_read != 0)
    {
        bytes_read = read(fd, temp, BUFFER_SIZE);
        if (bytes_read < 0)
            return (free(buffer), free(temp), NULL);
        temp[bytes_read] = '\0';
        new_buffer = ft_strjoin(buffer, temp);
        free(buffer);
        buffer = new_buffer;
    }
    free(temp);
    return (buffer);
}

char *after_newline(char *str)
{
    int index;
    int index2;
    char *result;

    index = 0;
    index2 = 0;
    if (!str)
        return (NULL);
    while (str[index] && str[index] != '\n')
        index++;
    if (!str[index] || !str[index + 1])
    {
        free(str);
        return (NULL);
    }
    result = (char *)malloc(ft_strlen(str) - index);
    if (!result)
        return (NULL);
    index++;
    while (str[index])
        result[index2++] = str[index++];
    result[index2] = '\0';
    free(str);
    return (result);
}

char *get_next_line(int fd)
{
    static char *buf = NULL;
    char *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buf = add_line(fd, buf);
    if (!buf)
    {
        free(buf);
        buf = NULL;
        return (NULL);
    }
    line = read_line(buf);
    buf = after_newline(buf);
    return (line);
}
