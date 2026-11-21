# Class Sketch

## Duration

A length of time, like the length of one song.

Private data:

- `int m_total_seconds` - the whole duration in seconds.

Invariant:

- The stored total is never negative. If the minutes and seconds add up to
  less than zero, the constructor stores 0 instead.

Public functions:

- `Duration(int minutes = 0, int seconds = 0)` - turns minutes and seconds
  into one total. Seconds past 59 carry into minutes on their own because
  only the total is kept.
- `int total_seconds() const` - returns the total.
- `Duration operator+(const Duration& other) const` - returns a new Duration
  with both totals added. Neither side changes.
- `bool operator==(const Duration& other) const` - true when the totals match.
- `operator<<` (free function, not a member) - prints the duration as `m:ss`
  using `total_seconds()`, so it does not need to be a friend.

## Track

A plain struct with a `std::string title` and a `Duration length`. It has no
invariant of its own, so its members are public.

## Playlist

A list of tracks with a fixed capacity. It owns the array the tracks live in.

Private data:

- `Track* m_tracks` - the array, allocated with `new Track[m_capacity]`.
- `int m_count` - how many tracks are stored right now.
- `int m_capacity` - how many tracks the array can hold.

Invariants:

- `0 <= m_count <= m_capacity`. The count only goes up in `add_track`, and
  only when there is room.
- `m_capacity >= 1`. The constructor changes anything smaller to 1.
- `m_tracks` always points to an array of `m_capacity` tracks, from the end of
  the constructor until the destructor runs.
- No stored track has an empty title. `add_track` refuses those.

Public functions:

- `explicit Playlist(int capacity)` - fixes the capacity, allocates the array,
  and starts with zero tracks.
- `~Playlist()` - releases the array with `delete[]`.
- `bool add_track(const Track& track)` - copies the track onto the end and
  returns true, or returns false and changes nothing if the playlist is full
  or the title is empty.
- `int size() const` - returns the number of tracks stored.
- `Duration total_length() const` - adds every track's length with
  `operator+`. An empty playlist gives 0:00.
- `const Track* find_track(const std::string& title) const` - pointer to the
  first track with that exact title, or `nullptr`. The pointer is const so the
  caller cannot change the track.
- Copy constructor and copy assignment are deleted so two playlists can never
  share one array.
