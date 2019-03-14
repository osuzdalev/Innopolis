import midi

# creating background music
MUSIC = builder.Builder()
BACK = MUSIC.back
BACK.printParticle()
MELODY = MUSIC.melody
MELODY.printMelody()

TICK = 100
VELOCITY = 40
# Instantiate a MIDI Pattern (contains a list of tracks)
pattern = midi.Pattern()
# Instantiate a MIDI Track (contains a list of MIDI events)
track = midi.Track()
# Append the track to the pattern
pattern.append(track)

# melody note indx
k = 0

for i in range(builder.P_SIZE):
    for j in range(builder.C_SIZE):
        # first note of chord
        if j == 0:
            on = midi.NoteOnEvent(tick=TICK, data=[int(BACK[i][j].pitch), VELOCITY])
            track.append(on)
            # first melody note
            on = midi.NoteOnEvent(tick=0, data=[int(MELODY[k].pitch), VELOCITY])
            track.append(on)
            k += 1
        else:
            on = midi.NoteOnEvent(tick=0, data=[int(BACK[i][j].pitch), VELOCITY])
            track.append(on)

    # 2nd melody note
    on = midi.NoteOnEvent(tick=TICK, data=[int(MELODY[k].pitch), VELOCITY])
    track.append(on)
    k += 1

# Add the end of track event, append it to the track
eot = midi.EndOfTrackEvent(tick=1)
track.append(eot)
# Print out the pattern
print(pattern)
# Save the pattern to disk
midi.write_midifile("back.mid", pattern)