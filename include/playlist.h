#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>

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

    /**
     * @brief Releases the track array the constructor allocated.
     */
    ~Playlist();

    /**
     * @brief Copies a track onto the end of the playlist.
     * @param track Track to store. Its title must not be empty.
     * @return false, changing nothing, if the playlist is full or the title is
     *         empty; otherwise true.
     */
    bool add_track(const Track& track);

    /**
     * @brief Gets the number of tracks stored.
     * @return Track count, from 0 up to the capacity.
     */
    int size() const;

    /**
     * @brief Looks for the first stored track with an exactly matching title.
     * @param title Title to search for.
     * @return Read-only pointer to the track, or nullptr if no title matches.
     */
    const Track* find_track(const std::string& title) const;

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
