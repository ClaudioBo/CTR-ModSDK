#define _CRT_SECURE_NO_WARNINGS

#include "replay.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ReplayData initialize_replay_data(int track_id, int num_players, int num_laps) {
	ReplayData replay;

	// Header
    replay.header.track_id = track_id;
    replay.header.num_players = num_players;
    replay.header.timestamp = time(NULL);
	replay.header.replay_version = 1;
	replay.header.num_laps = num_laps;

	// Allocate memory for frames
	replay.frames = (ReplayFrames*)malloc(MAX_FRAME_LIMIT * sizeof(ReplayFrames));
	for (int i = 0; i < MAX_FRAME_LIMIT; i++) {
		replay.frames[i].positions = NULL;
	}

	replay.total_frames = 0;

	return replay;
}

void register_player_to_replay(ReplayData replay, int player_id, char player_name, unsigned char character_id) {
	int recordplayer_new_index = replay.header.num_players++;
	replay.player_datas[recordplayer_new_index].player_id = player_id;
	strncpy(replay.player_datas[recordplayer_new_index].name, player_name, MAX_NAME_LENGTH);
	replay.player_datas[recordplayer_new_index].character_id = character_id;
	replay.player_datas[recordplayer_new_index].num_laps = 0;
	replay.player_datas[recordplayer_new_index].lap_times = (float*)malloc(replay.header.num_laps * sizeof(float));
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

void advance_next_frame(ReplayData replay) {
	replay.total_frames += 1;
}

void record_player_positions(ReplayData *replay, RecordPlayerPosition frameInfo) {
	int currentFrame = replay->total_frames;

	if (currentFrame >= MAX_FRAME_LIMIT) {
		printf("Reached maximum frame limit!\n");
		return;
	}

	// Allocate memory for positions if not already allocated
	if (replay->frames[currentFrame].positions == NULL) {
		replay->frames[currentFrame].positions = (RecordPlayerPosition*)malloc(MAX_PLAYERS * sizeof(RecordPlayerPosition));
	}

	// Set the frame info directly at the current position index
	replay->frames[currentFrame].positions[frameInfo.player_id] = frameInfo;
}

void write_replay_to_file(ReplayData *replay) {
	time_t now = time(NULL);
	struct tm* t = localtime(&now);
	char timestamp[20];
	strftime(timestamp, sizeof(timestamp), "%m-%d-%Y_%H-%M-%S", t);

	// Create the filename with the timestamp
	char filename[40];

	FILE* replayFile = fopen(filename, "wb");
	if (replayFile == NULL) {
		perror("Failed to open replay file");
		exit(EXIT_FAILURE);
	}

	fwrite(&replay->header, sizeof(ReplayHeader), 1, replayFile);
	for (int i = 0; i < replay->header.num_players; ++i) {
		fwrite(&replay->player_datas[i].player_id, sizeof(int), 1, replayFile);
		fwrite(&replay->player_datas[i].name, sizeof(char), MAX_NAME_LENGTH, replayFile);
		fwrite(&replay->player_datas[i].character_id, sizeof(int), 1, replayFile);
		fwrite(&replay->player_datas[i].num_laps, sizeof(int), 1, replayFile);
		fwrite(&replay->player_datas[i].lap_times, sizeof(float), replay->player_datas[i].num_laps, replayFile);
		fwrite(&replay->player_datas[i].total_time, sizeof(float), 1, replayFile);
	}

	fwrite(&replay->total_frames, sizeof(size_t), 1, replayFile);
	for (size_t i = 0; i < replay->total_frames; ++i) {
		fwrite(&replay->frames[i], sizeof(ReplayFrames), 1, replayFile);
		fwrite(replay->frames[i].positions, sizeof(RecordPlayerPosition), replay->header.num_players, replayFile);
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
}

