# libopus/test

## Create new files

```bash
arecord -t raw -f FLOAT_LE -r 8000 -c 1 --duration 6 > test/f32le_8000_1_6.bin
```

## Format

```
$format-$sampleRate-$channelCount-$duration
```

-   duration - in seconds
-   format - f32le or int16le
-   sampleRate - i.e. 48000
-   channelCount - channel count
