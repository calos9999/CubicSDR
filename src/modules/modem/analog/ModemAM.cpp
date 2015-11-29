#include "ModemAM.h"

ModemAM::ModemAM() : ModemAnalog() {
    demodAM = ampmodem_create(0.5, 0.0, LIQUID_AMPMODEM_DSB, 0);
}

Modem *ModemAM::factory() {
    return new ModemAM;
}

std::string ModemAM::getName() {
    return "AM";
}

void ModemAM::demodulate(ModemKit *kit, ModemIQData *input, AudioThreadInput *audioOut) {
    ModemKitAnalog *amkit = (ModemKitAnalog *)kit;
    
    initOutputBuffers(amkit,input);
    
    if (!bufSize) {
        input->decRefCount();
        return;
    }
    
	for (int i = 0; i < bufSize; i++) {
		ampmodem_demodulate(demodAM, input->data[i], &demodOutputData[i]);
	}
    
    buildAudioOutput(amkit,audioOut,true);
}
