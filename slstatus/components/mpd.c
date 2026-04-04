#include <mpd/client.h>
#include <stdio.h>
#include <string.h>
#include "../util.h"

const char *
mpd_status(const char *unused)
{
	static char buf[256];
	struct mpd_connection *conn;
	struct mpd_status *status;
	struct mpd_song *song;
	const char *artist, *title;
	unsigned elapsed, total;

	/* Connect to local MPD (NULL defaults to localhost:6600) */
	conn = mpd_connection_new(NULL, 0, 0);
	if (mpd_connection_get_error(conn) != MPD_ERROR_SUCCESS) {
		mpd_connection_free(conn);
		return "";
	}

	/* Get status to check if playing */
	status = mpd_run_status(conn);
	if (!status || mpd_status_get_state(status) != MPD_STATE_PLAY) {
		if (status) mpd_status_free(status);
		mpd_connection_free(conn);
		return "";
	}

	/* Get elapsed/total time in seconds */
	elapsed = mpd_status_get_elapsed_time(status);
	total = mpd_status_get_total_time(status);
	mpd_status_free(status);

	/* Get current song metadata */
	song = mpd_run_current_song(conn);
	if (song) {
		artist = mpd_song_get_tag(song, MPD_TAG_ARTIST, 0);
		title = mpd_song_get_tag(song, MPD_TAG_TITLE, 0);

		snprintf(buf, sizeof(buf), " %s - %s [%u:%02u/%u:%02u] | ",
		         artist ? artist : "Unknown",
		         title ? title : "Unknown",
		         elapsed / 60, elapsed % 60,
		         total / 60, total % 60);
		mpd_song_free(song);
	}

	mpd_connection_free(conn);
	return buf;
}

