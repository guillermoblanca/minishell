int     ft_atoi(const char *str)
{
        int     i;
        int     s;
        int     c;

        i = 0;
        s = 1;
        c = 0;
        while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
                i++;
        if (str[i] == 43 || str[i] == 45)
        {
                if (str[i] == 45)
                        s = -s;
                i++;
        }
        while (str[i] >= 48 && str[i] <= 57)
        {
                c = (str[i] - 48) + 10 * c;
                i++;
        }
        c = c * s;
        return (c);
}

int     ft_strncmp(const char *s1, const char *s2, size_t n)
{
        size_t  i;

        i = 0;
        while ((s1[i] == s2 [i]) && (s1[i] && s2[i] != '\0') && (i < n))
                i++;
        {
                if (i != n)
                        return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
                return (0);
        }
}

size_t  ft_strlen(const char *s)
{
        size_t  i;

        i = 0;
        while (((char *)s)[i] != '\0')
        {
                i++;
        }
        return (i);
}

size_t  ft_strlcat(char *dst, const char *src, size_t destsize)
{
        size_t  lensrc;
        size_t  lendst;
        size_t  i;
        size_t  c;

        i = 0;
        c = 0;
        lendst = ft_strlen (dst);
        lensrc = ft_strlen (src);
        if (destsize > 0 && lendst < destsize - 1)
        {
                while (dst[i] != '\0')
                        i++;
                while (src[c] != '\0' && c + i < destsize - 1)
                {
                        dst[i + c] = src[c];
                        c++;
                }
                dst [i + c] = '\0';
        }
        if (lendst >= destsize)
                lendst = destsize;
        return (lendst + lensrc);
}

char    *ft_strjoin(char const *s1, char const *s2)
{
        char    *c;
        int             i;
        size_t  size;

        if (!s1 || !s2)
                return (NULL);
        size = ft_strlen(s1) + ft_strlen(s2) + 1;
        c = (char *)malloc(size);
        if (!c)
                return (NULL);
        i = 0;
        while (s1[i] != '\0')
        {
                c[i] = s1[i];
                i++;
        }
        c[i] = '\0';
        ft_strlcat(c, s2, size);
        return (c);
}
