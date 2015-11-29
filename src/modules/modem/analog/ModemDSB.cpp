#include "ModemDSB.h"

ModemDSB::ModemDSB() : ModemAnalog() {
    demodAM_DSB = ampmodem_create(0.5, 0.0, LIQUID_AMPMODEM_DSB, 1);
}

Modem *ModemDSB::factory() {
    return new ModemDSB;
}

std::string ModemDSB::getName() {
    return "DSB";
}

void ModemDSB::demodulate(ModemKit *kit, ModemIQData *input, AudioThreadInput *audioOut) {
    ModemKitAnalog *amkit = (ModemKitAnalog *)kit;

    initOutputBuffers(amkit, input);
    
    if (!bufSize) {
        input->decRefCount();
        return;
    }
    
	for (int i = 0; i < bufSize; i++) {
		ampmodem_demodulate(demodAM_DSB, input->data[i], &demodOutputData[i]);
	}
    
    buildAudioOutput(amkit, audioOut, true);
}
