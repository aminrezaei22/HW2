#include <iostream>
#include <string>

#include "duration.h"
#include "playlist.h"
#include "track.h"

/**
 * @brief Fills a four-track playlist, then reports its size, total length,
 *        and the result of two title lookups.
 * @return 0 when the program finishes.
 */
int main() {
    const int track_count = 5;
    const Track tracks[track_count] = {
        {"Midnight Drive", Duration(3, 42)},
        {"Neon Rain", Duration(4, 5)},
        {"Static", Duration(2, 58)},
        {"Low Tide", Duration(5, 11)},
        {"Overflow", Duration(3, 30)},
    };

    // Capacity is one less than the track list so the last add is refused.
    Playlist playlist(4);
    for (int i = 0; i < track_count; i++) {
        if (playlist.add_track(tracks[i])) {
            std::cout << "Added   " << tracks[i].title << " (" << tracks[i].length << ")\n";
        } else {
            std::cout << "Refused " << tracks[i].title << " (playlist full)\n";
        }
    }

    std::cout << "Tracks: " << playlist.size() << '\n';
    std::cout << "Total length: " << playlist.total_length() << '\n';

    const int lookup_count = 2;
    const std::string lookups[lookup_count] = {"Static", "Missing"};
    for (int i = 0; i < lookup_count; i++) {
        const Track* found = playlist.find_track(lookups[i]);
        if (found != nullptr) {
            std::cout << "Found \"" << found->title << "\" at " << found->length << '\n';
        } else {
            std::cout << '"' << lookups[i] << "\" is not in the playlist.\n";
        }
    }

    return 0;
}
