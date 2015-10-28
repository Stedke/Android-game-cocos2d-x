#ifndef __MUSICD_H__
#define __MUSICD_H__

//singleton class that determines whether the music/audio should be enabled in other classes or not

class MusicD
{
private:
	//constructors and basic operators
	MusicD():isMusicPlaying(false),isAudioPlaying(false),shouldMusicPlay(true),shouldAudioPlay(true){};
	MusicD(const MusicD&){};
	void operator = (MusicD&){};

	//static object
	static MusicD MD;

	//properties
	bool isMusicPlaying;
	bool isAudioPlaying;

	bool shouldMusicPlay;
	bool shouldAudioPlay;

public:
	//method getting a MusicD handle
	static MusicD& getHandle(){
		return MD;
	}

	//methods getting/setting properties
	bool GetIsMusicPlaying(){
		return isMusicPlaying;
	}

	bool GetIsAudioPlaying(){
		return isAudioPlaying;
	}

	bool GetShouldMusicPlay(){
		return shouldMusicPlay;
	}

	bool GetShouldAudioPlay(){
		return shouldAudioPlay;
	}

	void SetIsMusicPlaying(bool a){
		isMusicPlaying=a;
	}

	void SetIsAudioPlaying(bool a){
		isAudioPlaying=a;
	}

	void SetShouldMusicPlay(bool a){
		shouldMusicPlay=a;
	}

	void SetShouldAudioPlay(bool a){
		shouldAudioPlay=a;
	}
};

#endif // __MUSICD_H__
