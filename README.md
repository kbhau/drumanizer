# DRUMANIZER

This app provides humanizer functionality for drum MIDI files meant for MT Power Drum Kit 2 plugin, written purely to satisfy author's needs.

The aim is to simulate some basic parameters that affect the performance in a slightly more interesting way than just a basic humanizer.

## Usage

My workflow is as follows:

1. Write drum track in Zynewave Podium Free.
2. Export MIDI file with drum notes and put it in the folder with the app exe.
3. Run in command line: `[exe name] [bpm] [filename]` Example: `Drumanizer_standalone 134 soundtest.mid`
4. Import to Reaper track as input for MT Power Drum Kit 2.
5. Adjust item playback speed.

## Dependencies

[Midifile](https://github.com/craigsapp/midifile) - working with MIDI files in C++.

## Known bugs

1. Due to conversion of ticks to milliseconds, notes get desynchrinozed from the grid. This can be countered by adjusting playback speed on the MIDI item in the DAW. For me it's usually about 1.003, but it will vary from project to project.

## Roadmap

1. Config file for input / output directory and drummer sim parameters.
2. Fixing the desync bug.

Note: This is a very low-priority project for me and any further development is more a matter of _if_ rather than _when_.
