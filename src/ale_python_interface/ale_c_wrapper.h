#ifndef __ALE_C_WRAPPER_H__
#define __ALE_C_WRAPPER_H__

// Declare var for __declspec(dllexport)
#define EXPORT __declspec(dllexport)

#include <ale_interface.hpp>

extern "C" {
    //declares int rgb_palette[256]
    #include "atari_ntsc_rgb_palette.h"
    EXPORT ALEInterface *ALE_new(bool displayScreen = false){return new ALEInterface(displayScreen);}

	EXPORT void ALE_del(ALEInterface *ale){ delete ale; }

	EXPORT const char *getString(ALEInterface *ale, const char *key){ return ale->theOSystem->settings().getString(key).c_str(); }
	EXPORT int getInt(ALEInterface *ale, const char *key){ return ale->theOSystem->settings().getInt(key); }
	EXPORT bool getBool(ALEInterface *ale, const char *key){ return ale->theOSystem->settings().getBool(key); }
	EXPORT float getFloat(ALEInterface *ale, const char *key){ return ale->theOSystem->settings().getFloat(key); }

	EXPORT void setString(ALEInterface *ale, const char *key, const char *value){ ale->theOSystem->settings().setString(key, value); }
	EXPORT void setInt(ALEInterface *ale, const char *key, int value){ ale->theOSystem->settings().setInt(key, value); }
	EXPORT void setBool(ALEInterface *ale, const char *key, bool value){ ale->theOSystem->settings().setBool(key, value); }
	EXPORT void setFloat(ALEInterface *ale, const char *key, float value){ ale->theOSystem->settings().setFloat(key, value); }

	EXPORT void loadROM(ALEInterface *ale, const char *rom_file){ ale->loadROM(rom_file); }
	EXPORT int  getLegalActionSize(ALEInterface *ale){ return ale->getLegalActionSet().size(); }

	EXPORT void getLegalActionSet(ALEInterface *ale, int *actions){
        ActionVect action_vect = ale->getLegalActionSet();
        const int sz = (int)ale->getLegalActionSet().size();
        for(int i = 0;i < ale->getLegalActionSet().size();i++){
            actions[i] = action_vect[i];
        }
    }

	EXPORT int getMinimalActionSize(ALEInterface *ale){ return ale->getMinimalActionSet().size(); }

	EXPORT void getMinimalActionSet(ALEInterface *ale, int *actions){
        ActionVect action_vect = ale->getMinimalActionSet();
        const int sz = (int)ale->getMinimalActionSet().size();
        for(int i = 0;i < ale->getMinimalActionSet().size();i++){
            actions[i] = action_vect[i];
        }
    }

	EXPORT int getFrameNumber(ALEInterface *ale){ return ale->getFrameNumber(); }
	EXPORT int getEpisodeFrameNumber(ALEInterface *ale){ return ale->getEpisodeFrameNumber(); }

	EXPORT int getScreenWidth(ALEInterface *ale){ return ale->getScreen().width(); }
	EXPORT int getScreenHeight(ALEInterface *ale){ return ale->getScreen().height(); }

	EXPORT int getScreen(ALEInterface *ale, unsigned char *screen_data){
        int w = ale->getScreen().width(); 
        int h = ale->getScreen().height(); 
        pixel_t *ale_screen_data = (pixel_t *)ale->getScreen().getArray();
        memcpy(screen_data,ale_screen_data,w*h*sizeof(pixel_t));
		return 1;
    }

	EXPORT int getScreenRGB(ALEInterface *ale, int *screen_data){
        int w = ale->getScreen().width(); 
        int h = ale->getScreen().height(); 
        pixel_t *ale_screen_data = (pixel_t *)ale->getScreen().getArray();
        for(int i = 0;i < w*h;i++){
            screen_data[i] = rgb_palette[ale_screen_data[i]];
        }
		return 1;
    }

	EXPORT int getRAMSize(ALEInterface *ale){ return ale->getRAM().size(); }

	EXPORT void getRAM(ALEInterface *ale, unsigned char *ram){
        unsigned char *ale_ram = ale->getRAM().array();
        int size = ale->getRAM().size();
        memcpy(ram,ale_ram,size*sizeof(unsigned char));
    }

	EXPORT int act(ALEInterface *ale, int action){ return ale->act((Action)action); }
	EXPORT bool game_over(ALEInterface *ale){ return ale->game_over(); }
	EXPORT void reset_game(ALEInterface *ale){ ale->reset_game(); }
}

#endif
