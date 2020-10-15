#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <memory>

#include "soloud/soloud.h"
#include "soloud/soloud_wav.h"


//----------------------------------------------------------------------------------------------
void print_dialogue(const char *dialogue, int time = 2, bool newLine = true)
{
	newLine ? printf("%s\n\n", dialogue) : printf("%s", dialogue);
	Sleep(time * 1000); //ms -> s
}

//----------------------------------------------------------------------------------------------
void startDialogue(bool on)
{
	if (!on)
	{
		print_dialogue("Press enter to stop.", 0);
		char input[512];
		fgets(input, 511, stdin);
		return;
	}
	
	print_dialogue("Hi, friend...");
	print_dialogue("Do you have a cigarette per chance?");
	print_dialogue("...", 3);
	print_dialogue("Nevermind, I'm trying to quit.");
	print_dialogue("So, uh... The sky is so black tonight. Uh...");
	print_dialogue("Oh look, the party is about to start.", 5);

	print_dialogue("What was your name again?", 0);
	char name[512];
	fgets(name, 511, stdin);

	print_dialogue("\nIt was lovely to meet you ", 0, false);
	print_dialogue(name);
	print_dialogue("Goodnight.");
}

//----------------------------------------------------------------------------------------------
int main(int argc, char *argv[])
{
	auto soloud = std::make_unique<SoLoud::Soloud>(); // Engine core
	auto wav	= std::make_unique<SoLoud::Wav>(); // One sample source

	soloud->init(); // Initialize SoLoud (automatic back-end selection)
	
	SoLoud::result loaded = wav->load("../res/wav/la-fete-triste.wav");  // Load a wave file
	print_dialogue("(wav file was loaded)", 0);

	if (loaded != SoLoud::SO_NO_ERROR)
	{
		print_dialogue("There's no music at this party...");
		print_dialogue("(wav file not loaded properly)");
		soloud->deinit(); // Clean up SoLoud
		return 1;
	}

	wav->setLooping(1);                         // Tell SoLoud to loop the sound
	int handle = soloud->play(*wav);             // Play it
	print_dialogue("(wav file was played)", 0);
	soloud->setVolume(handle, 0.8f);            // Set volume; 1.0f is "normal"
	soloud->setPan(handle, -0.2f);              // Set pan; -1 is left, 1 is right
	soloud->setRelativePlaySpeed(handle, 0.9f); // Play a bit slower; 1.0f is normal

	startDialogue(true); // Optional...

	soloud->stop(handle); // Stop the sound

	soloud->deinit(); // Clean up SoLoud

	return 0; // All done.
}
