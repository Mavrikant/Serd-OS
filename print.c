#include "print.h"
#include "datatypes.h"
#include "stdarg.h"
#include "uart.h"

#define MAX_BUFFER_SIZE 1024U

static uint32_t read_string(char *buffer, uint32_t position, const char *string)
{
    uint32_t index = 0;

    for (index = 0; string[index] != '\0'; index++)
    {
        buffer[position++] = string[index];
    }

    return index;
}

static uint32_t hex_to_string(char *buffer, uint32_t position, uint64_t digits)
{
    const char digits_map[16] = "0123456789ABCDEF";
    char digits_buffer[25] = {0};
    uint32_t size = 0;

    do
    {
        digits_buffer[size++] = digits_map[digits % 16];
        digits /= 16;
    } while (digits != 0);

    for (int i = size - 1; i >= 0; i--)
    {
        buffer[position++] = digits_buffer[i];
    }

    return size;
}

static int udecimal_to_string(char *buffer, int position, uint64_t digits)
{
    const char digits_map[10] = "0123456789";
    char digits_buffer[25];
    int size = 0;

    do
    {
        digits_buffer[size++] = digits_map[digits % 10];
        digits /= 10;
    } while (digits != 0);

    for (int i = size - 1; i >= 0; i--)
    {
        buffer[position++] = digits_buffer[i];
    }

    return size;
}

static uint32_t decimal_to_string(char *buffer, uint32_t position, int64_t digits)
{
    uint32_t size = 0;

    if (digits < 0)
    {
        digits = -digits;
        buffer[position++] = '-';
        size = 1;
    }

    size += udecimal_to_string(buffer, position, (uint64_t)digits);
    return size;
}
uint32_t printk(const char *format, ...)
{
    char buffer[MAX_BUFFER_SIZE] = {0};
    uint32_t buffer_size = 0;
    int64_t integer = 0;
    char *string = 0;
    va_list args;

    va_start(args, format);

    for (uint32_t i = 0; format[i] != '\0'; i++)
    {
        if (format[i] != '%')
        {
            buffer[buffer_size++] = format[i];
        }
        else
        {
            switch (format[++i])
            {
            case 'x':
                integer = va_arg(args, int64_t);
                buffer_size += hex_to_string(buffer, buffer_size, (uint64_t)integer);
                break;

            case 'u':
                integer = va_arg(args, int64_t);
                buffer_size += udecimal_to_string(buffer, buffer_size, (uint64_t)integer);
                break;

            case 'd':
                integer = va_arg(args, int64_t);
                buffer_size += decimal_to_string(buffer, buffer_size, integer);
                break;

            case 's':
                string = va_arg(args, char *);
                buffer_size += read_string(buffer, buffer_size, string);
                break;

            default:
                buffer[buffer_size++] = '%';
                i--;
            }
        }
    }
    buffer[buffer_size++] = '\0';
    uart_writeArray(buffer);
    va_end(args);

    return buffer_size;
}