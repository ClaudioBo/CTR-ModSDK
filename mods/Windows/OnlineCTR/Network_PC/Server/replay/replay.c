#define _CRT_SECURE_NO_WARNINGS

#include "replay.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double lastTime = 0.0;

ReplayData* initialize_replay_data(int track_id, int num_players, int num_laps) {
	ReplayData* replay = (ReplayData*)malloc(sizeof(ReplayData));

	// Header
    replay->header.track_id = track_id;
    replay->header.num_players = 0;
    replay->header.timestamp = time(NULL);
	replay->header.replay_version = 1;
	replay->header.num_laps = num_laps;

	// Allocate memory for frames
	replay->frames = (ReplayFrames*)malloc(MAX_FRAME_LIMIT * sizeof(ReplayFrames));
	if (replay->frames == NULL) {
		printf("Error: Memory allocation for frames failed.\n");
		free(replay);
		return NULL;
	}

	for (int i = 0; i < MAX_FRAME_LIMIT; i++) {
		replay->frames[i].positions = NULL;
	}

	// Allocate memory for player data
	replay->player_datas = (RecordPlayerData*)malloc(MAX_PLAYERS * sizeof(RecordPlayerData));
	if (replay->player_datas == NULL) {
		printf("Error: Memory allocation for player_data failed.\n");
		free(replay);
		return NULL;
	}

	replay->total_frames = 0;

	return replay;
}

void register_player_to_replay(ReplayData *replay, int player_id, const char *player_name, unsigned char character_id) {
	int recordplayer_new_index = replay->header.num_players++;
	if (recordplayer_new_index >= MAX_PLAYERS) {
		printf("Error: Exceeded maximum number of players.\n");
		return;
	}
	replay->player_datas[recordplayer_new_index].player_id = player_id;
	strncpy(replay->player_datas[recordplayer_new_index].name, player_name, MAX_NAME_LENGTH - 1);
	replay->player_datas[recordplayer_new_index].name[MAX_NAME_LENGTH - 1] = '\0'; // Ensure null-termination
	replay->player_datas[recordplayer_new_index].character_id = character_id;
	replay->player_datas[recordplayer_new_index].num_laps = 0;
	replay->player_datas[recordplayer_new_index].lap_times = (float*)malloc(replay->header.num_laps * sizeof(float));
	if (replay->player_datas[recordplayer_new_index].lap_times == NULL) {
		printf("Error: Memory allocation for lap_times failed.\n");
	}
}

void store_player_new_laptime(ReplayData *replay, int player_id, float lap_time) {
	int replay_player_id = find_replayplayer_by_id(replay, player_id);
	if (replay_player_id == -1) {
		return;
	}

	int new_laptime_idx = replay->player_datas[replay_player_id].num_laps++;
	replay->player_datas[replay_player_id].lap_times[new_laptime_idx] = lap_time;
}

int find_replayplayer_by_id(ReplayData *replay, int player_id) {
	for (int i = 0; i < MAX_PLAYERS; i++) {
		if (replay->player_datas[i].player_id == player_id) {
			return i;
		}
	}
	return NULL;
}

void advance_next_frame(ReplayData* replay) {
	double currentTime = (double)clock() / CLOCKS_PER_SEC;

	if (currentTime - lastTime >= 0.1) {
		replay->total_frames++;
		printf("Advanced to frame %d\n", replay->total_frames);
		lastTime = currentTime;
	}
}


void record_player_positions(ReplayData* replay, RecordPlayerPosition frameInfo) {
	int currentFrame = replay->total_frames;

	if (currentFrame >= MAX_FRAME_LIMIT) {
		printf("Reached maximum frame limit!\n");
		return;
	}

	// Allocate memory for the frame if not already allocated
	if (replay->frames[currentFrame].positions == NULL) {
		replay->frames[currentFrame].positions = (RecordPlayerPosition*)malloc(MAX_PLAYERS * sizeof(RecordPlayerPosition));
		if (replay->frames[currentFrame].positions == NULL) {
			printf("Memory allocation failed!\n");
			return; // Exit if memory allocation failed
		}
		// Initialize the allocated memory to avoid garbage values
		memset(replay->frames[currentFrame].positions, 0, MAX_PLAYERS * sizeof(RecordPlayerPosition));
	}

	// Allocate memory for positions of the current player in the current frame
	replay->frames[currentFrame].positions[frameInfo.player_id] = frameInfo;
}


int write_replay_to_file(ReplayData* replay, const char* filename) {
	FILE* replayFile = fopen(filename, "wb");
	if (replayFile == NULL) {
		perror("Failed to open replay file");
		return 1;
	}

	fwrite(&replay->header, sizeof(ReplayHeader), 1, replayFile);
	for (int i = 0; i < replay->header.num_players; ++i) {
		fwrite(&replay->player_datas[i].player_id, sizeof(int), 1, replayFile);
		size_t items_written = fwrite(replay->player_datas[i].name, sizeof(char), MAX_NAME_LENGTH, replayFile);
		if (items_written != MAX_NAME_LENGTH) {
			perror("Error writing player name to file");
			// Handle the error or return/exit as appropriate
		}
		fwrite(&replay->player_datas[i].character_id, sizeof(int), 1, replayFile);
		fwrite(&replay->player_datas[i].num_laps, sizeof(int), 1, replayFile);
		fwrite(replay->player_datas[i].lap_times, sizeof(float), replay->player_datas[i].num_laps, replayFile);
	}

	size_t written = fwrite(&replay->total_frames, sizeof(size_t), 1, replayFile);
	if (written != 1) {
		// Manejo de error
		fprintf(stderr, "Error escribiendo total_frames\n");
		fclose(replayFile); // Close the file before returning
		return 1;
	}

	for (size_t i = 0; i < replay->total_frames; ++i) {
		size_t written = fwrite(&replay->frames[i], sizeof(ReplayFrames), 1, replayFile);
		if (written != 1) {
			fprintf(stderr, "Error escribiendo frame %zu\n", i);
			fclose(replayFile); // Close the file before returning
			return 1;
		}

		if (&replay->frames[i].positions == NULL) {
			fprintf(stderr, "Error: positions es NULL en el frame %zu\n", i);
			fclose(replayFile); // Close the file before returning
			return 1;
		}

		if (replay->header.num_players <= 0) {
			fprintf(stderr, "Error: num_players es <= 0\n");
			fclose(replayFile); // Close the file before returning
			return 1;
		}

		written = fwrite(&replay->frames[i].positions, sizeof(RecordPlayerPosition), replay->header.num_players, replayFile);
		if (written != replay->header.num_players) {
			fprintf(stderr, "Error escribiendo posiciones del frame %zu\n", i);
			fclose(replayFile); // Close the file before returning
			return 1;
		}
	}

	fclose(replayFile);

	// Free allocated memory
	for (int i = 0; i < replay->header.num_players; ++i) {
		free(replay->player_datas[i].lap_times);
	}
	for (size_t i = 0; i < replay->total_frames; ++i) {
		free(replay->frames[i].positions);
	}
	free(replay->frames);
	free(replay->player_datas); // Added to free player_datas
	return 0;
}


