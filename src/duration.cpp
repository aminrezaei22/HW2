#include "duration.h"

Duration::Duration(int minutes, int seconds) : m_total_seconds(minutes * 60 + seconds) {
    // A negative total would break the invariant, so it is clamped to zero.
    if (m_total_seconds < 0) {
        m_total_seconds = 0;
    }
}

int Duration::total_seconds() const {
    return m_total_seconds;
}

Duration Duration::operator+(const Duration& other) const {
    // Going through the constructor keeps the invariant check in one place.
    return Duration(0, m_total_seconds + other.m_total_seconds);
}

bool Duration::operator==(const Duration& other) const {
    return m_total_seconds == other.m_total_seconds;
}
