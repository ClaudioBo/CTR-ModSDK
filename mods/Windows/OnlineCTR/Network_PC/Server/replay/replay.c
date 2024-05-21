#include "replay.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initialize_replay_data(ReplayData replay, int track_id, int num_players) {
    replay.header.track_id = track_id;
    replay.header.num_players = num_players;
    replay.header.timestamp = time(NULL);
    replay.num_positions = 0;
    replay.positions = NULL;

    for (int i = 0; i < num_players; ++i) {
        replay.players[i].player_id = i;
        snprintf(replay.players[i].name, MAX_NAME_LENGTH, "Player %d", i);
        replay.players[i].character_id = i % 10; // Example character id
        replay.players[i].num_laps = 5; // Example number of laps
        replay.players[i].lap_times = (float *)malloc(replay.players[i].num_laps * sizeof(float));
        for (int j = 0; j < replay.players[i].num_laps; ++j) {
            replay.players[i].lap_times[j] = (float)(rand() % 100);
        }
        replay.players[i].total_time = 500.0f; // Example total time
    }
}

void record_player_positions(ReplayData replay, PlayerPosition *positions, size_t num_positions) {
    replay.positions = realloc(replay.positions, (replay.num_positions + num_positions) * sizeof(PlayerPosition));
    if (replay.positions == NULL) {
        perror("Failed to reallocate memory");
        exit(EXIT_FAILURE);
    }
    memcpy(&replay.positions[replay.num_positions], positions, num_positions * sizeof(PlayerPosition));
    replay.num_positions += num_positions;
}

void write_replay_to_file(ReplayData replay, const char *filename) {
    FILE *replayFile = fopen(filename, "wb");
    if (replayFile == NULL) {
        perror("Failed to open replay file");
        exit(EXIT_FAILURE);
    }

    fwrite(&replay.header, sizeof(ReplayHeader), 1, replayFile);
    for (int i = 0; i < replay.header.num_players; ++i) {
        fwrite(&replay.players[i].player_id, sizeof(int), 1, replayFile);
        fwrite(replay.players[i].name, sizeof(char), MAX_NAME_LENGTH, replayFile);
        fwrite(&replay.players[i].character_id, sizeof(int), 1, replayFile);
        fwrite(&replay.players[i].num_laps, sizeof(int), 1, replayFile);
        fwrite(replay.players[i].lap_times, sizeof(float), replay.players[i].num_laps, replayFile);
        fwrite(&replay.players[i].total_time, sizeof(float), 1, replayFile);
    }

    fwrite(&replay.num_positions, sizeof(size_t), 1, replayFile);
    fwrite(replay.positions, sizeof(PlayerPosition), replay.num_positions, replayFile);

    fclose(replayFile);

    // Free allocated memory
    for (int i = 0; i < replay.header.num_players; ++i) {
        free(replay.players[i].lap_times);
    }
    free(replay.positions);
}
