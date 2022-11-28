/**
 * @file Exception.cc
 * @brief
 *
 * @version 1.0
 * @author Tianen Lu (tianenlu957@gmail.com)
 * @date 2022-11
 */

#include "Exception.h"
#include "CurrentThread.h"

Lux::Exception::Exception(std::string msg)
    : message_(msg), stack_(CurrentThread::stackTrace(false)) {}
