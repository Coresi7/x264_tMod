#ifndef FILTERS_AUDIO_AUDIO_FILTERS_H_
#define FILTERS_AUDIO_AUDIO_FILTERS_H_

#include <stdint.h>
#include "filters/common.h"

#define hnd_t void*

typedef struct audio_filter_t
{
    enum AudioResult (*init)( const struct audio_filter_t *self, hnd_t previous, hnd_t *handle, const char *opts );
    struct AVPacket *(*get_samples)( hnd_t handle, int64_t first_sample, int64_t last_sample );
    int (*free_packet)( hnd_t handle, struct AVPacket *frame );
    enum AudioResult (*close)( hnd_t handle );
    char *name, *longname, *description, *help;
    void (*help_callback)( int longhelp );
} audio_filter_t;

/* NOTE: this enum must be synchronized with audio_internal.c:register_all */
enum AudioFilter
{
    AUDIO_SOURCE_LAVF = 0,
    AUDIO_MUXER_RAW
};

#include "audio/audio.h"

audio_filter_t *af_get_filter( enum AudioFilter filterid );
enum AudioResult af_add( hnd_t base, audio_filter_t *filter, const char *options );
enum AudioResult af_get_samples( audio_samples_t *samples, hnd_t handle, int64_t first_sample, int64_t last_sample );
void af_free_samples( audio_samples_t *samples );
int af_close( hnd_t chain );

#endif /* AUDIO_H_ */
