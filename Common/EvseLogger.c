#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include "EvseLogger.h"

#define RX_LOG_PREFIX        "RX_LOG\\>"
#define RX_LOG_POSTFIX       "\n"

#define ESC_SEQ_HEX                 "\x1b["
#define ESC_SEQ_UNICODE             "\u001b["
#define ESC_SEQ_OCT                 "\033["
#define ESC_SEQ                     ESC_SEQ_OCT

#define TEXT_STYLE_NORMAL           "0"
#define TEXT_STYLE_BOLD             "1"
#define TEXT_STYLE_TONE             "2"
#define TEXT_STYLE_ITALIC           "3"
#define TEXT_STYLE_UNDERLINE        "4"
#define TEXT_STYLE_BLINK            "5"

#define TEXT_COLOR_BLACK            "30"
#define TEXT_COLOR_RED              "31"
#define TEXT_COLOR_GREEN            "32"
#define TEXT_COLOR_YELLO            "33"
#define TEXT_COLOR_BLUE             "34"
#define TEXT_COLOR_PURPLE           "35"
#define TEXT_COLOR_TURQUOISE        "36"
#define TEXT_COLOR_WHITE            "37"

#define BACK_GROUND_COLOR_BLACK     "40"
#define BACK_GROUND_COLOR_RED       "41"
#define BACK_GROUND_COLOR_GREEN     "42"
#define BACK_GROUND_COLOR_YELLO     "43"
#define BACK_GROUND_COLOR_BLUE      "44"
#define BACK_GROUND_COLOR_PURPLE    "45"
#define BACK_GROUND_COLOR_TURQUOISE "46"
#define BACK_GROUND_COLOR_WHITE     "47"

#define END_STRING                  "m"

#define RX_LOG_RESET_COLOR   (ESC_SEQ TEXT_STYLE_NORMAL END_STRING)


#define FONT_STYLE(text_style, text_color, bg_color) (ESC_SEQ text_style ";" text_color ";" bg_color END_STRING)
#define FONT_NORMAL(text_color, bg_color)            FONT_STYLE(TEXT_STYLE_NORMAL, text_color, bg_color)
#define FONT_ITALIC(text_color, bg_color)            FONT_STYLE(TEXT_STYLE_ITALIC, text_color, bg_color)

#define RX_LOG_COLOR_I       FONT_ITALIC(TEXT_COLOR_GREEN, BACK_GROUND_COLOR_BLACK)
#define RX_LOG_COLOR_W       FONT_ITALIC(TEXT_COLOR_YELLO, BACK_GROUND_COLOR_BLACK)
#define RX_LOG_COLOR_E       FONT_ITALIC(TEXT_COLOR_RED, BACK_GROUND_COLOR_BLACK)
#define RX_LOG_COLOR_D       FONT_ITALIC(TEXT_COLOR_WHITE, BACK_GROUND_COLOR_BLACK)
#define RX_LOG_COLOR_V       FONT_ITALIC(TEXT_COLOR_PURPLE, BACK_GROUND_COLOR_BLACK)

#define RX_VA_LIST              va_list
#define RX_VA_START             va_start
#define RX_VA_END               va_end
#define RX_PRINTF(args)         printf(args);
#define RX_VPRINTF(format, args)   vprintf(format, args);

static bool LogEnable = false;
static timeLogStampGetter_t TimeLogStampGetter = NULL;

void LOG_ENABLE(bool on)
{
    LogEnable = on;
}

void LOG_ADD_TIME_STAMP_GETTER(timeLogStampGetter_t timeLogStampGetter)
{
    TimeLogStampGetter = timeLogStampGetter;
}

static void LOG_PREFIX(const char * color, char letter, const char * tag)
{
    RX_PRINTF(color);
    printf("%s %c (%d) %s: ", 
                    RX_LOG_PREFIX,
                    letter, 
                    (TimeLogStampGetter==NULL)?(0):(TimeLogStampGetter()), 
                    tag);
}

static void LOG_POSTFIX(void)
{
    RX_PRINTF(RX_LOG_RESET_COLOR);
    RX_PRINTF(RX_LOG_POSTFIX);
}


void LOG_ERROR(const char * tag, const char * _fmt, ...)
{
    if(!LogEnable)
        return;
    LOG_PREFIX(RX_LOG_COLOR_E, 'E', tag);

    RX_VA_LIST argptr;
    RX_VA_START(argptr, _fmt);
    RX_VPRINTF(_fmt, argptr);//RX_VPRINTF(_fmt, argptr);
    RX_VA_END(argptr);

    LOG_POSTFIX(); // printf(RX_LOG_RESET_COLOR);
}

void LOG_WARNING(const char * tag, const char * _fmt, ...) // (const char * tag, const char * format, ...)
{
    if(!LogEnable)
        return;
    LOG_PREFIX(RX_LOG_COLOR_W, 'W', tag);

    RX_VA_LIST argptr;
    RX_VA_START(argptr, _fmt);
    RX_VPRINTF(_fmt, argptr);
    RX_VA_END(argptr);

    LOG_POSTFIX(); // printf(RX_LOG_RESET_COLOR);
}

void LOG_INFO(const char * tag, const char * _fmt, ...) // (const char * tag, const char * format, ...)
{
    if(!LogEnable)
        return;
    LOG_PREFIX(RX_LOG_COLOR_I, 'I', tag);

    RX_VA_LIST argptr;
    RX_VA_START(argptr, _fmt);
    RX_VPRINTF(_fmt, argptr);
    RX_VA_END(argptr);

    LOG_POSTFIX(); // printf(RX_LOG_RESET_COLOR);
}

void LOG_DEBUG(const char * tag, const char * _fmt, ...) // (const char * tag, const char * format, ...)
{
    if(!LogEnable)
        return;
    LOG_PREFIX(RX_LOG_COLOR_D, 'D', tag);

    RX_VA_LIST argptr;
    RX_VA_START(argptr, _fmt);
    RX_VPRINTF(_fmt, argptr);
    RX_VA_END(argptr);

    LOG_POSTFIX(); // 
}

void LOG_VERBOSE(const char * tag, const char * _fmt, ...) // (const char * tag, const char * format, ...)
{
    if(!LogEnable)
        return;
    LOG_PREFIX(RX_LOG_COLOR_V, 'V', tag);

    RX_VA_LIST argptr;
    RX_VA_START(argptr, _fmt);
    RX_VPRINTF(_fmt, argptr);
    RX_VA_END(argptr);

    LOG_POSTFIX(); // 
}


