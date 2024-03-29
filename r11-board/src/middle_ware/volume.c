#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "common.h"

static unsigned int vol;

#define CONFIG_BANJO

struct amixer_control {
    char *name;
    unsigned int value;
};

struct amixer_control controls[] =
{
#ifdef CONFIG_AZALEA
    /*azalea*/
    {"Left Output Mixer DACL Switch", 1},
    {"Right Output Mixer DACR Switch", 1},
    {"HPL Mux", 1},
    {"HPR Mux", 1},
    {"Headphone Switch", 1}
#endif

#ifdef CONFIG_ASTAR
    /*astar*/
    {"AIF1IN0L Mux", 0},
    {"AIF1IN0R Mux", 0},
    {"DACL Mixer AIF1DA0L Switch", 1},
    {"DACR Mixer AIF1DA0R Switch", 1},
    {"Left Output Mixer DACL Switch", 1},
    {"Right Output Mixer DACR Switch", 1},
    {"HP_L Mux", 1},
    {"HP_R Mux", 1},
    {"Headphone Switch", 1}
#endif

#ifdef CONFIG_SITAR
    /*sitar*/
    {"head phone power", 1},
    {"ADC MIC Boost AMP en", 1},
    {"ADC mixer mute for mic", 1},
#endif

#ifdef CONFIG_BANJO
    /*banjo*/
    {"Speaker Function", 1},
    {"Audio speaker out", 1}
#endif
};

static int audio_mixer_cset(char *mixer_name,int value)
{
    char cmd[128] = {0};
    sprintf(cmd,"amixer cset name='%s' %d",mixer_name,value);
    system(cmd);
    return TINAL_OK;
}

int audio_mixer_get(const char* shell,const char* name)
{
    int bytes;
    char buf[10] = {0};
    char cmd[500] = {0};
    sprintf(cmd,shell,name);
    FILE   *stream;
    printf("%s\n",cmd);
    stream = popen( cmd, "r" );
    if(!stream)
		return -1;
    bytes = fread( buf, sizeof(char), sizeof(buf), stream);
    pclose(stream);
    if(bytes > 0){
            return atoi(buf);
    }else {
            printf("%s --> failed\n",cmd);
            return -1;
    }
}

/*0~31*/
int volume_set_volume(int volume)
{
#ifdef CONFIG_BANJO
    char *name = "Master Playback Volume";/*banjo*/
#endif

#ifdef CONFIG_SITAR
    char *name = "head phone volume"; /*sitar*/
#endif

#ifdef CONFIG_AZALEA
    char *name = "Headphone volume"; /*azalea*/
#endif

#ifdef CONFIG_ASTAR
    char *name = "headphone volume"; /*astar*/
#endif
    audio_mixer_cset(name,volume);
	vol = volume;
	return TINAL_OK;
}

int volume_get_volume(void)
{
	return vol;
}
/*0~7 */
int volume_set_mic_AMP_gain_value(int val)
{
#ifdef CONFIG_BANJO
    char *name = "MIC1 boost AMP gain control";/*banjo*/
#endif

#ifdef CONFIG_ASTAR
    char *name = "MIC1 boost amplifier gain";/*astar*/
#endif

#ifdef CONFIG_AZALEA
    char *name = "MIC1 boost volume";/*azalea*/
#endif

#ifdef CONFIG_SITAR
    char *name = "MICIN GAIN control";/*sitar*/
#endif

    audio_mixer_cset(name,val);
	return TINAL_OK;
}
/*0~7*/
int volume_set_mic_mixer_value(int val)
{
	char *name = "MIC1_G boost stage output mixer control";
    char cmd[100] = {0};

	audio_mixer_cset(name,val);
	return  TINAL_OK;
}

int volume_get_mic_AMP_gain_value(int val)
{
#ifdef CONFIG_BANJO
    char *name = "MIC1 boost AMP gain control";/*banjo*/
#endif

#ifdef CONFIG_ASTAR
    char *name = "MIC1 boost amplifier gain";/*astar*/
#endif

#ifdef CONFIG_AZALEA
    char *name = "MIC1 boost volume";/*azalea*/
#endif

#ifdef CONFIG_SITAR
    char *name = "MICIN GAIN control";/*sitar*/
#endif

    const char* shell = "volume=`amixer cget name='%s' | grep ': values='`;volume=${volume#*=};echo $volume";
    return audio_mixer_get(shell,name);
}

int volume_get_mic_mixer_value(int val)
{
	char *name = "MIC1_G boost stage output mixer control";
    const char* shell = "volume=`amixer cget name='%s' | grep ': values='`;volume=${volume#*=};echo $volume";
    return audio_mixer_get(shell,name);
}

int volume_init(void)
{
    int i = 0;
    int num = sizeof(controls)/sizeof(controls[0]);
    for(i = 0;i < num;i++)
    {
        audio_mixer_cset(controls[i].name,controls[i].value);
    }

    return  TINAL_OK;
}
