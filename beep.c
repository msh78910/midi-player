#include <soundio/soundio.h>
#include <math.h>
#include <stdlib.h>

# define M_PI		3.14159265358979323846	/* pi */

int beep(float freq, int len_ms) {
    struct SoundIo *soundio = soundio_create();
    if (!soundio) return -1;

    if (soundio_connect(soundio) != 0) return -2;
    soundio_flush_events(soundio);

    int dev_index = soundio_default_output_device_index(soundio);
    if (dev_index < 0) return -3;

    struct SoundIoDevice *device =
        soundio_get_output_device(soundio, dev_index);
    if (!device) return -4;

    struct SoundIoOutStream *out =
        soundio_outstream_create(device);
    if (!out) return -5;

    out->format = SoundIoFormatFloat32NE;
    out->sample_rate = 44100;

    /* ✅ SAFE layout selection */
    // soundio_channel_layout_init_stereo(&out->layout);
    out->layout = *soundio_channel_layout_get_builtin(SoundIoChannelLayoutIdStereo);

    if (soundio_outstream_open(out) != 0) return -6;
    if (soundio_outstream_start(out) != 0) return -7;

    int frames_total = (out->sample_rate * len_ms) / 1000;
    int frames_left = frames_total;

    double phase = 0.0;
    double step = 2.0 * M_PI * freq / out->sample_rate;

    while (frames_left > 0) {
        int frame_count = frames_left;
        struct SoundIoChannelArea *areas;

        if (soundio_outstream_begin_write(out, &areas, &frame_count) != 0)
            break;

        for (int f = 0; f < frame_count; f++) {
            float sample = 0.3f * sin(phase);
            phase += step;

            for (int ch = 0; ch < out->layout.channel_count; ch++) {
                *(float *)(areas[ch].ptr) = sample;
                areas[ch].ptr += areas[ch].step;
            }
        }

        soundio_outstream_end_write(out);
        frames_left -= frame_count;
    }

    soundio_outstream_destroy(out);
    soundio_device_unref(device);
    soundio_destroy(soundio);
    return 0;
}
