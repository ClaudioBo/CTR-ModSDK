#ifndef REPLAY_H
#define REPLAY_H

#include <time.h>

#define MAX_PLAYERS 8
#define MAX_NAME_LENGTH 32
#define MAX_FRAME_LIMIT 1200 // 1 frame each 0.5 secs, limit to 10 mins

typedef struct {
    int player_id;
    char name[MAX_NAME_LENGTH];
    unsigned char character_id;
    int num_laps;
    float *lap_times;
    float total_time;
} RecordPlayerData;

typedef struct {
    int track_id;
    int num_players;
	int num_laps;
    time_t timestamp;
	char replay_version;
} ReplayHeader;

typedef struct {
    int player_id;
    unsigned char x, y, z;
    unsigned char button_hold, rotation1, rotation2;

} RecordPlayerPosition;

typedef struct {
	int frameIndex;
	RecordPlayerPosition *positions;
} ReplayFrames;

typedef struct {
    ReplayHeader header;
	RecordPlayerData *player_datas;
	size_t total_frames;
    ReplayFrames *frames;
} ReplayData;

ReplayData* initialize_replay_data(int track_id, int num_players, int num_laps);
void register_player_to_replay(ReplayData *replay, int player_id, const char *player_name, unsigned char character_id);
void store_player_new_laptime(ReplayData *replay, int player_id, float lap_time);
int find_replayplayer_by_id(ReplayData *replay, int player_id);
void advance_next_frame(ReplayData *replay);
void record_player_positions(ReplayData *replay, RecordPlayerPosition frameInfo);
int write_replay_to_file(ReplayData *replay, const char* filename);

#endif
