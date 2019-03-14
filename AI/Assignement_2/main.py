from __future__ import print_function
import random as r
import copy
import midi


def choose(note):
    return {
        'A': 9,
        'B': 11,
        'C': 0,
        'D': 2,
        'E': 4,
        'F': 5,
        'G': 7,
        'A#': 10,
        'C#': 1,
        'D#': 3,
        'F#': 6,
        'G#': 8
    }.get(note)


def tonality():
    TONALITY = choose(raw_input("Choose a Tonality "))
    return TONALITY

# General Constants
OCTAVE = 12
NUM_OCTAVE = 3

# Note Constants
TONALITY = tonality() + 48
N_BOUND_UP = TONALITY + OCTAVE * NUM_OCTAVE+ 2
N_MAX_VEL = 1
# N_MAX_VEL_2 = 3

# Chord Constants
C_SIZE = 3
C_MAX_VEL = 1
C_BOUND_DOWN = 0
C_BOUND_UP = 2

# Buffer Constants
BUFFER_SIZE = 3
FUNCTIONS = ['T', 'S', 'D']

# PsoO Constants
POPULATION_0 = 1000
ITERATION_0 = 300

# Particle Constants
P_SIZE = 16

# Pso1 Constants
POPULATION_1 = 500
ITERATION_1 = 10

#Melody Constants
MEL_SIZE = 32

# Pso2 Constants
POPULATION_2 = 1000
ITERATION_2 = 300

class Note:
    def __init__(self):
        self.pitch = r.randint(TONALITY, N_BOUND_UP)
        self.velocity = r.uniform(-1, 1)

    # overloading operator '=='
    def __eq__(self, note):
        return self.pitch == note.pitch

    # overloading operator '+'
    def __add__(self, note):
        return self.pitch + note.pitch

    # overloading operator '-'
    def __sub__(self, note):
        return self.pitch - note.pitch

    def printNote(self):
        print(int(self.pitch), end='')

    # inputs are Notes
    # updates the pitch of the Note
    # best comes from level 3 of Particle
    def updateNoteVel(self, pos_best_g, pos_best_i):
        w = 0.7  # constant inertia weight (how much to weigh the previous velocity)
        c1 = 0.5  # cognitive constant
        c2 = 0.5  # social constant

        r1 = r.random()
        r2 = r.random()

        vel_cognitive = c1 * r1 * (pos_best_i.pitch - self.pitch)  # if pos_best_i.pitch != self.pitch % 12 else 0
        vel_social = c2 * r2 * (pos_best_g.pitch - self.pitch)  # if pos_best_g.pitch != self.pitch % 12 else 0
        self.velocity = w * self.velocity + vel_cognitive + vel_social

        # if self.velocity > N_MAX_VEL:
        #     self.velocity = N_MAX_VEL
        # elif self.velocity < -N_MAX_VEL:
        #     self.velocity = -N_MAX_VEL


    def updateNote(self):
        self.pitch += self.velocity
        # rounding the pitch
        self.pitch = round(self.pitch)

        # adjust maximum pitch if necessary (round up)
        if self.pitch > N_BOUND_UP or self.pitch < TONALITY:
            self.pitch = TONALITY + (self.pitch - TONALITY) % OCTAVE


class Chord:
    def __init__(self):
        self.position = None
        self.chromo = [Note() for i in range(C_SIZE)]

        self.fitness = 0

        self.velocity = r.uniform(-1, 1)
        self.function = None

    # overloading index operator '[]'
    def __getitem__(self, indx):
        return self.chromo[indx]

    # overloading operator '=='
    # comparing chords means comparing their respective note pitchs
    def __eq__(self, chord):
        count = 0
        for i in range(C_SIZE):
            if self[i].pitch == chord.chromo[i].pitch:
                count += 1

        return count == C_SIZE


    def printChord(self):
        print('( ', end='')
        for note in self.chromo:
            note.printNote()
            print(' ', end='')
        print(')', end='')

    def printChordFit(self):
        print(self.fitness)

    ######################################### USED FOR 1ST PSO ###################################################

    def checkRep(self):
        if len(self.chromo) == len(set([i.pitch for i in self.chromo])):
            self.fitness -= 2

    # checks relationship between notes
    def evaluateChord(self):
        self.fitness = 0
        self.fitness += abs((self[1].pitch - self[0].pitch - 4))
        self.fitness += abs((self[2].pitch - self[0].pitch - 7))

    # inputs are chords chromo
    # updates each note
    def updateChord(self, best_g, best_i):
        for i in range(C_SIZE):
            self[i].updateNoteVel(best_g[i], best_i[i])
            self[i].updateNote()

    ######################################### USED FOR 2ND PSO ###################################################

    # inputs are chords
    # updates the position of the chord
    # best comes from Particle
    def updateChordVel(self, pos_best_g, pos_best_i):
        w = 0.3  # constant inertia weight (how much to weigh the previous velocity)
        c1 = 0.6  # cognitive constant
        c2 = 0.4  # social constant

        r1 = r.random()
        r2 = r.random()

        vel_cognitive = c1 * r1 * (pos_best_i.position - self.position)
        vel_social = c2 * r2 * (pos_best_g.position - self.position)
        self.velocity = w * self.velocity + vel_cognitive + vel_social

    def updateChordPos(self):
        self.position += self.velocity
        # rounding the position
        self.position = int(round(self.position))

        # adjust maximum position if necessary (round up)
        if self.position > C_BOUND_UP:
            self.position = C_BOUND_UP
        elif self.position < C_BOUND_DOWN:
            self.position = C_BOUND_DOWN

# Array of chords
class Buffer:
    def __init__(self):
        self.chromo = [Chord() for i in range(BUFFER_SIZE)]
        for i in range(BUFFER_SIZE):
            self.chromo[i].position = i
            self.chromo[i].function = FUNCTIONS[i]
        self.fitness = 0
        self.err_best_i = -1
        self.best_i = -1

    # overloading index operator '[]'
    def __getitem__(self, indx):
        return self.chromo[indx]

    def printBuffer(self):
        print('{ ')
        for chord in self.chromo:
            chord.printChord()
            print(' ')
        print('}')

    def printBuffer2(self):
        for c in self.chromo:
            print(c.position, c.function)

    # --------------------------------------------------------------------------------------
    def checkBases(self):
        # check bases of chords
        self.fitness += self[0][0].pitch % (OCTAVE + TONALITY - 48) * 10
        self.fitness += abs((self[1][0].pitch - self[0][0].pitch - 5)) * 10
        self.fitness += abs((self[2][0].pitch - self[0][0].pitch - 7)) * 10

    # checks for base repetition in buffer
    def checkRep(self):
        if len(self[0].chromo) != len(set([i[0].pitch for i in self.chromo])):
            self.fitness += 5
    # --------------------------------------------------------------------------------------

    # checks Fitness of all chords and their relationship to one another
    def evaluateBuffer(self):
        self.fitness = 0
        self.checkBases()
        for i in range(BUFFER_SIZE):
            self[i].evaluateChord()
            self.fitness += self.chromo[i].fitness
        self.checkRep()

        # check to see if the current pitch is an individual best
        if self.fitness < self.err_best_i or self.err_best_i == -1:
            # save its fitness as best individual fitness
            self.err_best_i = self.fitness
            # save its pitch (notes) as best individual pitch
            self.best_i = copy.deepcopy(self.chromo)

    # inputs are buffer chromo
    # updates each chord
    def updateBuffer(self, best_g):
        for i in range(BUFFER_SIZE):
            self[i].updateChord(best_g[i], self.best_i[i])


# Produces correct Buffer
class Pso0:
    def __init__(self):
        self.err_best_g = -1
        # Best saved as buffer to get access to the printBuffer method
        # Its chromo will be updated with the '=' operator if a new best is found
        self.best_g = Buffer()

    def solver(self):
        # establish the swarm
        swarm = [Buffer() for i in range(POPULATION_0)]

        # begin optimization loop
        for i in range(ITERATION_0):
            # cycle through particles in swarm and evaluate fitness
            for j in range(POPULATION_0):
                # max fitness == 104
                swarm[j].evaluateBuffer()

                # determine if current particle is the best (globally)
                if swarm[j].err_best_i < self.err_best_g or self.err_best_g == -1:
                    # save its fitness as best individual fitness
                    self.err_best_g = copy.deepcopy(swarm[j].err_best_i)
                    # save this particle as best global particle
                    self.best_g = copy.deepcopy(swarm[j])

                # cycle through swarm and update velocities and pitch
                swarm[j].updateBuffer(self.best_g)

            if self.err_best_g == 0:
                print("BUFFER DONE")
                return self.best_g


class Particle:
    def __init__(self, buffer):
        # chords are taken at random from buffer
        self.chromo = [copy.deepcopy(buffer[r.randint(0, 2)]) for i in range(P_SIZE)]
        # Setting all chord velocities to 0
        for i in range(P_SIZE):
            self.chromo[i].velocity = 0
        self.fitness = 0
        self.err_best_i = -1
        self.best_i = -1

    # overloading index operator '[]'
    def __getitem__(self, indx):
        return self.chromo[indx]

    def printParticle(self):
        for i in range(C_SIZE):
            for j in range(P_SIZE):
                self[j][i].printNote()
                print('    ', end='')
            print()

    def checkConsistency(self, indx, buffer):
        buffer.printBuffer2()
        print()
        if self[indx].position == 0 and self[indx].function != 'T':
            print("\nPROBLEM\n")
        if self[indx].position == 1 and self[indx].function != 'S':
            print("\nPROBLEM\n")
        if self[indx].position == 2 and self[indx].function !='D':
            print("\nPROBLEM\n")

    # Particle Fitness Check
    # --------------------------------------------------------------------------------
    def tonic_first_last(self):
        if self[0].position == 0:
            self.fitness += 10
        elif self[P_SIZE - 1].position == 0:
            self.fitness += 10

    def no_d_s(self):
        for i in range(0, P_SIZE - 1):
            if self[i].position == 2 and self[i + 1].position == 1:
                self.fitness -= 2

    def no_3_s(self):
        for i in range(2, P_SIZE, 4):
            if self[i].position == 1:
                self.fitness -= 1

    def no_prolong(self):
        for i in range(3, P_SIZE - 4, 4):
            if self[i].position == self[i + 1].position:
                self.fitness -= 2

    def diversity(self):
        pos = []
        for i in range(P_SIZE):
            pos.append(self[i].position)
        if 1 not in pos:
            self.fitness -= 3

    # ---------------------------------------------------------------------------------

    # checks Fitness of each Sequence and their relationship to oneanother
    def evaluateParticle(self):
        self.fitness = 0

        self.tonic_first_last()
        self.no_3_s()
        self.no_d_s()
        self.no_prolong()
        self.diversity()

        # check to see if the current position is an individual best
        if self.fitness > self.err_best_i or self.err_best_i == -1:
            # save its fitness as best individual fitness
            self.err_best_i = self.fitness
            # save its position (notes) as best individual position
            self.best_i = copy.deepcopy(self.chromo)

    # inputs are particle chromo
    # updates each chord position
    def updateParticle(self, best_g, buffer):
        for i in range(P_SIZE):
            self[i].updateChordVel(best_g[i], self.best_i[i])
            self[i].updateChordPos()
            # Chord Redefinition
            self.chromo[i] = copy.deepcopy(buffer[self[i].position])


class Pso1:
    def __init__(self):
        self.buffer = Pso0().solver()
        self.err_best_g = -1
        # Best saved as particle to get access to the printParticle method
        # Its chromo will be updated with the '=' operator if a new best is found
        self.best_g = -1

    def checkConsistency(self, swarm, buffer):
        for i in range(POPULATION_1):
            for j in range(P_SIZE):
                swarm[i].checkConsistency(j, buffer)
        print()

    def solver(self):
        # establish the swarm
        swarm = [Particle(self.buffer) for i in range(POPULATION_1)]

        # begin optimization loop
        for i in range(ITERATION_1):
            # cycle through particles in swarm and evaluate fitness
            for j in range(POPULATION_1):
                swarm[j].evaluateParticle()

                # determine if current particle is the best (globally)
                if swarm[j].err_best_i > self.err_best_g or self.err_best_g == -1:
                    # save its fitness as best individual fitness
                    self.err_best_g = copy.deepcopy(swarm[j].err_best_i)
                    # save this particle as best global particle
                    self.best_g = copy.deepcopy(swarm[j])

                # cycle through swarm and update velocities and position
                swarm[j].updateParticle(self.best_g, self.buffer)

        print("BACK DONE")
        return self.best_g


class Melody:
    def __init__(self, back):
        self.chromo = [Note() for i in range(MEL_SIZE)]
        # Pso1().solver()
        self.back = back
        self.fitness = 0
        self.err_best_i = -1
        self.best_i = -1

    # overloading index operator '[]'
    def __getitem__(self, indx):
        return self.chromo[indx]

    def printMelody(self):
        for note in self.chromo:
            note.printNote()
            print(' ', end='')
        print()

    def printMelodyFit(self):
        print(self.fitness)

    # -----------------------------------------------------------------------------
    def fitfunc(self):
        j = 0
        for i in range(MEL_SIZE):
            goals = [self.back[j][k].pitch + 12 for k in range(C_SIZE)]
            dists = [abs(self[i].pitch - goals[k]) for k in range(C_SIZE) ]
            self.fitness += min(dists)
            if i % 2:
                j += 1
    # -----------------------------------------------------------------------------

    def evaluateMelody(self):
        self.fitness = 0

        # self.noteOctaveDif()
        # self.checkDivPrevNote()
        self.fitfunc()

        # check to see if the current position is an individual best
        if self.fitness < self.err_best_i or self.err_best_i == -1:
            # save its fitness as best individual fitness
            self.err_best_i = self.fitness
            # save its position (notes) as best individual position
            self.best_i = copy.deepcopy(self.chromo)

    # inputs are melody chromo
    # updates each note
    def updateMelody(self, best_g):
        for i in range(MEL_SIZE):
            self[i].updateNoteVel(best_g[i], self.best_i[i])
            self[i].updateNote()


class Pso2:
    def __init__(self, back):
        self.back = back
        self.err_best_g = -1
        # Best saved as buffer to get access to the printBuffer method
        # Its chromo will be updated with the '=' operator if a new best is found
        self.best_g = Melody(self.back)

    def solver(self):
        # establish the swarm
        swarm = [Melody(self.back) for i in range(POPULATION_2)]

        # begin optimization loop
        for i in range(ITERATION_2):
            #print("ITERATION ", i)
            # cycle through particles in swarm and evaluate fitness
            for j in range(POPULATION_2):
                # max fitness == 104
                swarm[j].evaluateMelody()

                # determine if current particle is the best (globally)
                if swarm[j].err_best_i < self.err_best_g or self.err_best_g == -1:
                    # save its fitness as best individual fitness
                    self.err_best_g = copy.deepcopy(swarm[j].err_best_i)
                    #print(self.err_best_g)
                    # save this particle as best global particle
                    self.best_g = copy.deepcopy(swarm[j])
                    #self.best_g.printMelody()

                # cycle through swarm and update velocities and pitch
                swarm[j].updateMelody(self.best_g)

        print("MELODY DONE")
        return self.best_g


class Builder:
    def __init__(self):
        self.back = Pso1().solver()
        self.melody = Pso2(self.back).solver()


if __name__ == "__main__":
    # creating background music
    MUSIC = Builder()
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

    for i in range(P_SIZE):
        for j in range(C_SIZE):
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
