#ifndef REPLAY_H
#define REPLAY_H

#include <time.h>

#define MAX_PLAYERS 8
#define MAX_NAME_LENGTH 32

typedef struct {
    int player_id;
    char name[MAX_NAME_LENGTH];
    int character_id;
    int num_laps;
    float *lap_times;
    float total_time;
} PlayerData;

typedef struct {
    int track_id;
    int num_players;
    time_t timestamp;
} ReplayHeader;

typedef struct {
    int player_id;
    float x, y, z;
} PlayerPosition;

typedef struct {
    ReplayHeader header;
    PlayerData players[MAX_PLAYERS];
    size_t num_positions;
    PlayerPosition *positions;
} ReplayData;

void initialize_replay_data(int track_id, int num_players);
void record_player_positions(PlayerPosition *positions, size_t num_positions);
void write_replay_to_file(const char *filename);

#endif
