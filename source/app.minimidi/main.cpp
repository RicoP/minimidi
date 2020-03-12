#include <Windows.h>
#include <iostream>
#include <conio.h> // _getch

#pragma comment(lib, "winmm.lib")

HMIDIOUT omidi;
HMIDIIN imidi;

void CALLBACK MidiInProc(HMIDIIN hMidiIn, UINT wMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)
{
	if (wMsg == MIM_DATA) {
		printf("wMsg=MIM_DATA, dwInstance=%08x, dwParam1=%08x, dwParam2=%08x\n", dwInstance, dwParam1, dwParam2);
		midiOutShortMsg(omidi, dwParam1);
	}
}

int main() {
	if (midiOutOpen(&omidi, 0, 0, 0, CALLBACK_NULL) == MMSYSERR_NOERROR) {
		printf("successfully opened default MIDI device \n");
	}
	else {
		printf("error opening default MIDI device \n");
		return -1;
	}

	if (midiInGetNumDevs() == 0) {
		fprintf(stderr, "midiInGetNumDevs() return 0...");
		return -1;
	}

	if (midiInOpen(&imidi, 0, (DWORD_PTR)(void*)MidiInProc, 0, CALLBACK_FUNCTION) != MMSYSERR_NOERROR) {
		fprintf(stderr, "midiInOpen() failed...");
		return -1;
	}

	midiInStart(imidi);

	while (_getch() != VK_ESCAPE) {
	}

	midiInStop(imidi);
	midiInClose(imidi);
	midiOutClose(omidi);

	imidi = nullptr;
	omidi = nullptr;

	return 0;
}