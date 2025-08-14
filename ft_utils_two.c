#include "utils.h"

int     ft_isalnum(int c)
{
        if ((c >= 97 && c <= 122) || (c >= 65 && c <= 90) || (c >= 48 && c <= 57))
                return (1);
        else
                return (0);
}

int     ft_isdigit(int c)
{
        if (!(c >= 48 && c <= 57))
                return (0);
        else
                return (1);
}

char    *ft_strdup(const char *s1)
{
        char    *l;
        size_t  len;

        len = ft_strlen(s1) +1;
        l = malloc (len);
        if (l == 0)
                return (0);
        ft_strlcpy(l, s1, len);
        return (l);
}
        while (src[c] != '\0' && c + 1 < destsize)
        {
                dst[c] = src[c];
                c++;
        }
        if (destsize > 0)
                dst [c] = '\0';
        return (i);
}

char    *ft_substr(char const *s, unsigned int start, size_t len)
{
        size_t  i;
        size_t  c;
        char    *p;

        i = 0;
        c = 0;
        if (start > ft_strlen(s))
                len = 0;
        else if (len > (ft_strlen(s) - start))
                len = ft_strlen(s) - start;
        p = malloc(len + 1);
        if (!p)
                return (NULL);
        while (s[i])
        {
                if (i >= start && c < len)
                {
                        p[c] = s[i];
                        c++;
                }
                i++;
        }
        p[c] = '\0';
        return (p);
}
