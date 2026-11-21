#include "playlist.h"

Playlist::Playlist(int capacity) : m_tracks(nullptr), m_count(0), m_capacity(capacity) {
    // A playlist with no room could never hold a track, so the smallest size is 1.
    if (m_capacity < 1) {
        m_capacity = 1;
    }
    m_tracks = new Track[m_capacity];
}

Playlist::~Playlist() {
    delete[] m_tracks;
}
