/**
 * @file noncopyable.h
 * @brief
 *
 * @version 1.0
 * @author Tianen Lu (tianenlu957@gmail.com)
 * @date 2022-11
 */


#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

namespace Lux {
/// @brief Private copy constructor and copy assignment
/// ensure classes derived from class noncopyable cannot be copied.
class noncopyable {
public:
    /// copy constructor
    noncopyable(const noncopyable&) = delete;

    /// copy assignment
    noncopyable& operator=(const noncopyable&) = delete;

protected:
    noncopyable() = default;
    ~noncopyable() = default;
};
} // namespace Lux

#endif // NONCOPYABLE_H