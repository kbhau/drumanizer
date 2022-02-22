

#include <MidiFile.h>
#include <Options.h>

#include "Drummer.h"


using namespace std;
using namespace smf;



int main(int argc, char** argv)
{
    cout << "| ------------------------------------------------------" << endl;
    cout << "| Create options." << endl;
    cout << "| ------------------------------------------------------" << endl;
    Options options;
    options.process(argc, argv);
    if (options.getArgCount() == 0) {
        cout << "Usage: drumanize [bpm] [filename]" << endl;
        exit(0);
    }
    if (options.getArgCount() != 2) {
        cout << "Usage: drumanize [bpm] [filename]" << endl;
        cerr << "Bad arguments." << endl;
        exit(1);
    }



    cout << endl;
    cout << "| ------------------------------------------------------" << endl;
    cout << "| Read file." << endl;
    cout << "| ------------------------------------------------------" << endl;
    MidiFile midifile;
    midifile.read(options.getArg(2));
    if (!midifile.status()) {
        cerr << "Error reading MIDI file " << options.getArg(2) << endl;
        exit(1);
    }



    cout << endl;
    cout << "| ------------------------------------------------------" << endl;
    cout << "| Global settings." << endl;
    cout << "| ------------------------------------------------------" << endl;
    midifile.joinTracks();
    midifile.linkNotePairs();
    auto tpq = midifile.getTPQ();
    auto bpm = stoi(options.getArg(1));
    auto tickmult = (30000.0 / bpm) / tpq;
    cout << "TicksPerQuarterNote: " << midifile.getTicksPerQuarterNote() << endl;
    cout << "TPQ: " << tpq << endl;
    //midifile.setTPQ();




    cout << endl;
    cout << "| ------------------------------------------------------" << endl;
    cout << "| Print original event list." << endl;
    cout << "| ------------------------------------------------------" << endl;

    cout << endl;
    cout << "TICK    TRACK   MIDI MESSAGE\n";
    cout << "____________________________________\n";
    MidiEvent* mev;
    for (int event=0; event < 10; event++) {
        mev = &midifile[0][event];
        cout << dec << mev->tick;
        cout << '\t' << mev->track;
        cout << '\t' << hex;
        for (int i=0; i < mev->size(); i++)
            cout << (int)(*mev)[i] << ' ';
        cout << endl;
    }





    cout << endl;
    cout << "| ------------------------------------------------------" << endl;
    cout << "| Process notes." << endl;
    cout << "| ------------------------------------------------------" << endl;
    auto offset = 0.0;
    Drummer dummer;
    dummer.Naturalise();
    for (int event=0; event < midifile[0].size(); event++) {
        mev = &midifile[0][event];

        // Change ticks to ms.
        mev->tick *= tickmult;

        if (mev->isNoteOn()) {

            // Offset the note in time.
            offset = dummer.Get_offset(
                mev->getKeyNumber(),
                mev->tick
            );
            mev->tick += offset;
            mev->getLinkedEvent()->tick += offset;
            if (mev->tick < 0) {
                mev->tick = 0;
            }

            // Adjust the note velocity.
            mev->setVelocity(dummer.Play_note(
                mev->getVelocity(),
                mev->tick
            ));
        }
    }
    //midifile.setMillisecondTicks();




    cout << endl;
    cout << "| ------------------------------------------------------" << endl;
    cout << "| Print new event list." << endl;
    cout << "| ------------------------------------------------------" << endl;

    cout << endl;
    cout << "TICK    TRACK   MIDI MESSAGE\n";
    cout << "____________________________________\n";
    for (int event=0; event < 10; event++) {
        mev = &midifile[0][event];
        cout << dec << mev->tick;
        cout << '\t' << mev->track;
        cout << '\t' << hex;
        for (int i=0; i < mev->size(); i++)
            cout << (int)(*mev)[i] << ' ';
        cout << endl;
    }



    cout << endl;
    cout << "| ------------------------------------------------------" << endl;
    cout << "| Write file." << endl;
    cout << "| ------------------------------------------------------" << endl;
    
    midifile.sortTracks();
    midifile.setMillisecondTicks();
    midifile.setTPQ(30000.0 / bpm);
    cout << endl;
    auto path_out = options.getArg(2);
    path_out = path_out.substr(0, path_out.size() - 4) + ".humanized.mid";
    cout << "Output filename: " << path_out << endl;
    cout << "TPQ: " << midifile.getTPQ() << endl;
    midifile.write(path_out);
    if (!midifile.status()) {
        cerr << "Error writing MIDI file." << endl;
    }



    cout << endl;
    cout << "| ------------------------------------------------------" << endl;
    cout << "| Exit." << endl;
    cout << "| ------------------------------------------------------" << endl;
    return 0;
}
