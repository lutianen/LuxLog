/**
 * @file copyable.h
 * @brief
 *
 * @version 1.0
 * @author Tianen Lu (tianenlu957@gmail.com)
 * @date 2022-11
 */

#ifndef COPYABLE_H
#define COPYABLE_H

namespace Lux {
/// @brief A tag class emphasises the objects are copyable.
/// The empty base class optimization applies.
/// Any derived class of copyable should be a value type.
class copyable {
protected:
    copyable() = default;
    ~copyable() = default;
};
} // namespace Lux

#endif // COPYABLE_H