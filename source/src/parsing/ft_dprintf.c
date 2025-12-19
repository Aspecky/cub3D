/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaneddam <kaneddam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 20:51:56 by kaneddam          #+#    #+#             */
/*   Updated: 2025/12/01 20:52:11 by kaneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

static void ft_putchar_fd(char c, int fd)
{
    write(fd, &c, 1);
}

static void ft_putstr_fd(char *s, int fd)
{
    if (!s)
        return;
    while (*s)
        write(fd, s++, 1);
}

static void ft_putnbr_fd(int n, int fd)
{
    if (n == -2147483648)
    {
        ft_putstr_fd("-2147483648", fd);
        return;
    }
    if (n < 0)
    {
        ft_putchar_fd('-', fd);
        n = -n;
    }
    if (n >= 10)
        ft_putnbr_fd(n / 10, fd);
    ft_putchar_fd((n % 10) + '0', fd);
}

void ft_dprintf(int fd, const char *format, ...)
{
    va_list args;
    va_start(args, format);
    
    while (*format)
    {
        if (*format == '%' && *(format + 1))
        {
            format++;
            if (*format == 's')
                ft_putstr_fd(va_arg(args, char *), fd);
            else if (*format == 'd')
                ft_putnbr_fd(va_arg(args, int), fd);
            else if (*format == 'c')
                ft_putchar_fd(va_arg(args, int), fd);
        }
        else
            ft_putchar_fd(*format, fd);
        format++;
    }
    
    va_end(args);
}
