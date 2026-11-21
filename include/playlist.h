#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "track.h"

/**
 * @brief A fixed-capacity list of tracks that owns its own array.
 *
 * Invariants: 0 <= m_count <= m_capacity, m_capacity >= 1, m_tracks points
 * to an array of m_capacity tracks, and no stored track has an empty title.
 */
class Playlist {
public:
    /**
     * @brief Builds an empty playlist with room for a fixed number of tracks.
     * @param capacity Most tracks the playlist can hold. A value below 1 becomes 1.
     */
    explicit Playlist(int capacity);

    // Copying is not covered yet; deleting these keeps two Playlists from
    // sharing one array and freeing it twice.
    Playlist(const Playlist&) = delete;
    Playlist& operator=(const Playlist&) = delete;

private:
    Track* m_tracks;
    int m_count;
    int m_capacity;
};

#endif
