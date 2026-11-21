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

std::ostream& operator<<(std::ostream& out, const Duration& d) {
    int minutes = d.total_seconds() / 60;
    int seconds = d.total_seconds() % 60;
    out << minutes << ':';
    // Seconds always take two digits, so 3:05 does not print as 3:5.
    if (seconds < 10) {
        out << '0';
    }
    out << seconds;
    return out;
}
