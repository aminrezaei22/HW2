#ifndef DURATION_H
#define DURATION_H

#include <ostream>

/**
 * @brief A length of time stored as whole seconds.
 *
 * Invariant: the stored total is never negative.
 */
class Duration {
public:
    /**
     * @brief Builds a duration from minutes and seconds.
     *
     * Seconds past 59 carry into minutes. A negative total becomes 0.
     * @param minutes Whole minutes, may be negative.
     * @param seconds Extra seconds, may be negative or above 59.
     */
    Duration(int minutes = 0, int seconds = 0);

    /**
     * @brief Gets the whole duration in seconds.
     * @return Total seconds, never negative.
     */
    int total_seconds() const;

    /**
     * @brief Adds two durations without changing either one.
     * @param other Duration to add to this one.
     * @return A new Duration holding the combined time.
     */
    Duration operator+(const Duration& other) const;

    /**
     * @brief Compares two durations by their total seconds.
     * @param other Duration to compare against.
     * @return true when both hold the same total seconds.
     */
    bool operator==(const Duration& other) const;

private:
    int m_total_seconds;
};

/**
 * @brief Writes a duration as m:ss, for example 3:05.
 * @param out Stream to write to.
 * @param d Duration to print.
 * @return The same stream, so calls can chain.
 */
std::ostream& operator<<(std::ostream& out, const Duration& d);

#endif
