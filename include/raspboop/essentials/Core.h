#ifndef RASPBOOP_ESSENTIALS_CORE_H
#define RASPBOOP_ESSENTIALS_CORE_H

#include "raspboop/Raspboop.h"
#include <cstring>

namespace raspboop
{

/*! \brief Initializes Raspboop and its dependencies
 *
 * Initializes raspboop and wiringPi. The pin numbering
 * scheme used depends on the value passed into the
 * Scheme parameter.
 *
 * see PinScheme for the available schemes, and visit
 * the [wiringPi reference](http://wiringpi.com/reference/
 * setup/) for a detailed description of the implications
 * of a pin scheme. The default pin scheme is Wiring.
 *
 * \param Scheme The pin scheme to use.
 */
int Init(PinScheme Scheme = PinScheme::WIRING);

/*! \todo Implement Deinit() method */
int Deinit();

/** \brief Advances the dest pointer by size */
static void* rbpbufset(unsigned char*& dest, const void* source, size_t size)
{
    void* v = std::memcpy(dest, source, size);
    dest += size;
    return v;
}

/** \brief Advances the source pointer by size */
static void* rbpbufget(void* dest, unsigned char* source, size_t size)
{
    void* v = std::memcpy(dest, source, size);
    source += size;
    return v;
}

} /* raspboop */

#endif /* RASPBOOP_ESSENTIALS_CORE_H */
