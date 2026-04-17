#ifndef LIBFT_H
# define LIBFT_H

# include <stddef.h>
# include <stdlib.h>

/* ── str.c (already implemented) ─────────────────── */
size_t  ft_strlen(const char *s);
int     ft_strcmp(char *s1, const char *s2);
size_t  ft_strlcat(char *dst, const char *src, size_t size);

/* ── still needed — add to str.c ─────────────────── */
char    *ft_strdup(const char *s);
char    *ft_strjoin(const char *s1, const char *s2);
char    *ft_strchr(const char *s, int c);
char    **ft_split(const char *s, char c);
void    ft_free_split(char **arr);
char    *ft_strndup(const char *s, size_t n);

char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_isalpha(int c);
int		ft_isalnum(int c);
int		ft_isdigit(int c);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *s);

/* ── mem.c ────────────────────────────────────────── */
void    *ft_calloc(size_t count, size_t size);
void    ft_bzero(void *s, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t n);

#endif
