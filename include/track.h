#ifndef TRACK_H
#define TRACK_H

#include <string>

#include "duration.h"

/**
 * @brief One song: a title paired with its length.
 *
 * A plain record with no invariant of its own, so it stays a struct.
 */
struct Track {
    std::string title; ///< Name of the track.
    Duration length;   ///< How long the track plays.
};

#endif
