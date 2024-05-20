/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ezhou <ezhou@student.42malaga.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 12:03:30 by ezhou             #+#    #+#             */
/*   Updated: 2024/03/22 16:31:15 by ezhou            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <limits.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

/**
 * @brief Sets n bytes in the pointer s to zero
 *
 * @param s Generic pointer
 * @param n Number of bytes to set to zero
 */
void				ft_bzero(void *s, size_t n);
/**
 * @brief Searches for the first occurence of the byte c
 *
 * @param s Generic pointer
 * @param c Character to find in ASCII
 * @param n Number of bytes to evaluate
 * @return Returns the pointer at the first occurrence or NULL if not found
 */
void				*ft_memchr(const void *s, int c, size_t n);
/**
 * @brief Compares n bytes from two void pointers until it finds the
 *  first difference
 *
 * @param s Generic pointer 1
 * @param s2 Generic pointer 2
 * @param n Number of bytes to compare
 * @return Returns the difference in ASCII in the first pair of
 * different characters or 0 if they are equal
 */
int					ft_memcmp(const void *s, const void *s2, size_t n);
/**
 * @brief Copies src into dest, the copy fails if the addresses
 * of memory overlap
 *
 * @param dest Pointer destination
 * @param src Pointer source
 * @param n Number of bytes to copy
 * @return The new pointer destination
 */
void				*ft_memcpy(void *dest, const void *src, size_t n);
/**
 * @brief Copies src into dest correctly even if they overlap
 *
 * @param dest Pointer destination
 * @param src Pointer source
 * @param n Number of bytes to copy
 * @return The new pointer destination
 */
void				*ft_memmove(void *dest, const void *src, size_t n);
/**
 * @brief Initializes n bytes from s to the character c
 *
 * @param s Generic pointer
 * @param c A characters value in ASCII
 * @param n Number of bytes to initialize
 * @return void*
 */
void				*ft_memset(void *s, int c, size_t n);
/**
 * @brief Makes a dinamically allocated copy of a string
 *
 * @param s String to copy
 * @return A copy of s or NULL if the allocation fails
 */
char				*ft_strdup(const char *s);
/**
 * @brief Finds the length of a given string
 *
 * @param s A string
 * @return The number of characters within the string
 */
size_t				ft_strlen(const char *s);
/**
 * @brief Concatenates src into dest as much as possible and returns
 * the length of the string it's trying to create
 *
 * @param dest String destination
 * @param src String source
 * @param size Size of dest(not to be mistaken with length of dest)
 * @return The length of the string that it tries to create
 */
unsigned int		ft_strlcat(char *dest, const char *src, unsigned int size);
/**
 * @brief Searches for the first occurence of the byte c
 *
 * @param s A string
 * @param c Character to find in ASCII
 * @return Returns the pointer at the first occurrence or NULL if not found
 */
char				*ft_strchr(const char *s, int c);
/**
 * @brief Searches for the last occurence of the byte c
 *
 * @param s A string
 * @param c Character to find in ASCII
 * @return Returns the pointer at the last occurrence or NULL if not found
 */
char				*ft_strrchr(const char *s, int c);
/**
 * @brief Checks if the character is alphabetic
 *
 * @param c The value of a character in ASCII
 * @return 1 if it's alphabetic, 0 if it's not
 */
int					ft_isalpha(int c);
/**
 * @brief Checks if the character is numeric
 *
 * @param c The value of a character in ASCII
 * @return 1 if it's numeric, 0 if it's not
 */
int					ft_isdigit(int c);
/**
 * @brief Checks if the character is alphabetic or numeric
 *
 * @param c The value of a character in ASCII
 * @return 1 if it's alphabetic or numeric, 0 if it's not
 */
int					ft_isalnum(int c);
/**
 * @brief Checks if the character is ASCII
 *
 * @param c The value of a character in ASCII
 * @return 1 if it's ASCII, 0 if it's not
 */
int					ft_isascii(int c);
/**
 * @brief Checks if the character is printable
 *
 * @param c The value of a character in ASCII
 * @return 1 if it's printable, 0 if it's not
 */
int					ft_isprint(int c);
/**
 * @brief Checks if the character is alphabetic and lowercase,
 * if it is, switch it to uppercase
 *
 * @param c The value of a character in ASCII
 * @return c if unchanged, or c - 32 if switched to uppercase
 */
int					ft_toupper(int c);
/**
 * @brief Checks if the character is alphabetic and uppercase,
 * if it is, switch it to lowercase
 *
 * @param c The value of a character in ASCII
 * @return c if unchanged, or c + 32 if switched to lowercase
 */
int					ft_tolower(int c);
/**
 * @brief Compares n bytes from two strings until it finds the
 *  first different pair of characters
 *
 * @param s String 1
 * @param s2 String 2
 * @param n Number of bytes to compare
 * @return Returns the difference in ASCII in the first pair of
 * different characters or 0 if they are equal
 */

int					ft_strcmp(const char *s1, const char *s2);

int					ft_strncmp(const char *s1, const char *s2, size_t n);
/**
 * @brief Finds the first occurrence of the little string in the big string
 * in len bytes
 *
 * @param big String to search in
 * @param little String to find
 * @param len Amount of bytes to evaluate
 * @return A pointer to the beggining of the little string in the big
 * string if found or NULL otherwise
 */
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
/**
 * @brief Returns the int value of the number that is represented in a string
 *
 * @param nptr A number represented by a string
 * @return The number value of the string or 0 if any error happens
 */
int				ft_atoi(const char *nptr);
/**
 * @brief Applies the function f to every byte in the string s
 *
 * @param s A string
 * @param f Pointer to a function f that takes an unsigned int and a char*
 * as parameters
 */
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
/**
 * @brief Applies the function f to every bite in the string s and returns
 * a new string with the values returned from applying f to each character
 *
 * @param s A string
 * @param f Pointer to a function f that takes an unsigned int and a char*
 * as parameters
 * @return The new string
 */
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
/**
 * @brief Returns the substr from a given start index from the string s,
 * and len bytes
 *
 * @param s A string
 * @param start Starter index
 * @param len Length of the string
 * @return A pointer to the substring if found or NULL otherwise
 */
char				*ft_substr(char const *s, unsigned int start, size_t len);
/**
 * @brief Returns a new string that concatenates s1 and s2 that is also
 * dinamically allocated
 *
 * @param s1 String 1
 * @param s2 String 2
 * @return Returns the new string or NULL if the allocation fails
 */
char				*ft_strjoin(char const *s1, char const *s2);
/**
 * @brief Returns a new string that concatenates s1 and s2 that is also
 * dinamically allocated but only up to length - 1
 *
 * @param s1 String 1
 * @param s2 String 2
 * @param length Maximum size of the string
 * @return Returns the new string or NULL if the allocation fails
 */
char				*ft_strjoin_alt(char *s1, char *s2, int length);
/**
 * @brief Removes all the characters that are in the string
 * set at the beggining and at the end of the string s
 *
 * @param s A string
 * @param set Set of characters to remove
 * @return The new "trimmed" string
 */
char				*ft_strtrim(char const *s, char const *set);
/**
 * @brief Splits the string in smallers substrings that are separated
 * by the character c
 *
 * @param s String to split
 * @param c Character separator
 * @return Double pointer that con
 */
char				**ft_split(char const *s, char c);
/**
 * @brief Takes a numeric value and transforms it into its string representation
 *
 * @param n A number
 * @return It's string representation
 */
char				*ft_itoa(long ln);
/**
 * @brief Writes the character c into the output fd and returns the number of
bytes printed
 *
 * @param c Character to print on file descriptor
 * @param fd File descriptor
 */
void				ft_putchar_fd(char c, int fd);
/**
 * @brief Writes the string s into the output fd
 *
 * @param s String to print to the file descriptor
 * @param fd File descriptor
 */
void				ft_putstr_fd(char const *s, int fd);
/**
 * @brief Writes the string s into the output fd and terminates with end line
 *
 * @param s String to print to the file descriptor
 * @param fd File descriptor
 */
void				ft_putendl_fd(char const *s, int fd);
/**
 * @brief Writes the number n into the output fd
 *
 * @param n Number to write
 * @param fd File descriptor
 */
void				ft_putnbr_fd(int n, int fd);
/**
 * @brief Copies src into dst up to size - 1, NULL terminating if size is not 0
 *
 * @param dst Destination string
 * @param src Source string
 * @param size Maximum size of the string
 * @return The new destination string
 */
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
/**
 * @brief Initializes a pointer with count elements of size bytes and 
 * initializes all elements to zero
 *
 * @param count Number of elements
 * @param size Size of each individual elements
 * @return The pointer initialized
 */
void				*ft_calloc(size_t count, size_t size);
/**
 * @brief Creates a new node with a given content passed by arguments
 *
 * @param content Content to add to the node
 * @return The new node with its content
 */
t_list				*ft_lstnew(void *content);
/**
 * @brief Adds the node new to the front of the list lst
 *
 * @param lst The initial list
 * @param new The node to add to the front of the list
 * @return The list with the new node added to the front
 */
void				ft_lstadd_front(t_list **lst, t_list *new);
/**
 * @brief Returns the amount of nodes in the list lst
 *
 * @param lst The list
 * @return The number of nodes
 */
int					ft_lstsize(t_list *lst);
/**
 * @brief Returns the last node in the list lst
 *
 * @param lst The list
 * @return The last node of the list
 */
t_list				*ft_lstlast(t_list *lst);
/**
 * @brief Adds the node new to the back of the list lst
 *
 * @param lst The list
 * @param new The new node to add at the back
 * @return The new list with the node added at the back
 */
void				ft_lstadd_back(t_list **lst, t_list *new);
/**
 * @brief Deletes and frees the node by using an auxiliary function del
 *
 * @param lst The list
 * @param del Pointer to a function that deletes the content
 * and frees the memory
 */
void				ft_lstdelone(t_list *lst, void (*del)(void *));
/**
 * @brief Deletes and frees the entire list by using an
 * auxiliary function del
 *
 * @param lst The list
 * @param del Pointer to a function that deletes the content
 * and frees the memory
 */
void				ft_lstclear(t_list **lst, void (*del)(void *));
/**
 * @brief Goes through the whole list and applies the function f to
the content of each node
 *
 * @param lst The list
 * @param f Pointer to a function f
 */
void				ft_lstiter(t_list *lst, void (*f)(void *));
/**
 * @brief Goes through the whole list and applies the function f to
 * the content of each node and generates a new list with them
 *
 * @param lst The list
 * @param f Pointer to the function f to apply to the contents
 * @param del Pointer to the function del to free and delete nodes
 * @return t_list*
 */
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
/**
 * @brief Prints the number lnbr in the specified base
 *
 * @param lnbr Numeric value of a number
 * @param base Base in which you would like to print the number
 * @return The number of bytes printed
 */
int					ft_putnbr_base(long lnbr, char *base);
/**
 * @brief Prints the character c in stdout
 *
 * @param c A character
 * @return The number of bytes printed
 */
int					ft_putchar(char c);
/**
 * @brief Prints string s in stdoutput
 *
 * @param s The string
 * @return The number of bytes printed
 */
int					ft_putstr(char *s);
/**
 * @brief  Returns 1 if c is included in s
 *
 * @param s The string
 * @param c The character to search for
 * @return 1 if found, 0 otherwise
 */
int					ft_strcontains(char *s, int c);
/**
 * @brief Frees a pointers and sets it to NULL
 *
 * @param pointer Pointer to free and reset
 * @return NULL in all cases
 */
char				*ft_clean(char *pointer);
/**
 * @brief Prints the next line in the given fd
 *
 *
 * @param fd File descriptor from where to read
 * @return The next line in the fd,
 * NULL if there are no more lines to read
 */
char				*get_next_line(int fd);
/**
 * @brief Function that prints on screen a string with variables, such as a
 * digit, string, number or hexadecimal numbers.
 *
 * @param str String with the words
 * @param ... Variadic arguments
 * @return Number of bytes printed
 */
int					ft_printf(char const *str, ...);
/**
 * @brief Prints in standard output all lines contained in fd
 *
 * @param fd
 */
void				print_all_lines(int fd);
/**
 * @brief Functions that finds the first ocurrence of character c in string s
 * and returns its index
 *
 * @param s A string
 * @param c A character's value in ASCII
 * @return Its index or 0 if not found
 */
int					ft_strchrindex(char *s, int c);
/**
 * @brief Functions that finds the last ocurrence of character c in string s
 * and returns its index
 *
 * @param s A string
 * @param c A character's value in ASCII
 * @return Its index or 0 if not found
 */
int					ft_strrchrindex(const char *s, int c);
/**
 * @brief Finds the number of pointers contained in the double pointer,
 * considering that the double pointer is NULL terminated
 *
 * @param pointer The double pointer
 * @return int The number of char * contained inside.
 */
int					ft_dpointer_size(char **pointer);
/**
 * @brief Frees a double char pointer and all of the char * located
 * within
 * 
 * @param array The double pointer to free
 */
void				ft_free_char(char **array);
/**
 * @brief Frees a triple pointer, all the double pointers contained and
 * the single pointers. 
 * 
 * @param array The triple pointer to free
 */
void				ft_free_tpointer(char ***array);
/**
 * @brief Resize a dynamically allocated double pointer allowing to either:
 * increase the memory or shrink it
 * 
 * @param ptr The double pointer to modify
 * @param size The desired size 
 * @return char** The new double pointer
 */
char				**ft_realloc_doublep_char(char **ptr, size_t size);
char				**ft_dpointer_dupe(char **original);
int					ft_dpointer_size(char **args);
/**
 * @brief Returns the long value of the number that is represented in a string
 *
 * @param nptr A number represented by a string
 * @return The number value of the string or 0 if any error happens
 */
long				ft_atol(const char *nptr);

#endif