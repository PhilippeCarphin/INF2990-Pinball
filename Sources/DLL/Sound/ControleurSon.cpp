#include "ControleurSon.h"
ControleurSon::ControleurSon()
{
	FMOD::System_Create(&system_);
	system_->init(1024, FMOD_INIT_NORMAL, 0);
	maxBGM_ = 1;
	maxSFX_ = 1;

	TCHAR buffer[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring wBuffer(buffer);
	std::string currentFolder(wBuffer.begin(), wBuffer.end());
	std::string::size_type position = currentFolder.find_last_of("\\/");
	std::string targetPath = std::string(currentFolder).substr(0, position);
	targetPath += "\\media\\SFX\\";
	const char* d = targetPath.c_str();
	std::vector<std::string> f;

	FILE* pipe = NULL;
	std::string pCmd = "dir /B /S " + std::string(d);
	char buf[256];

	if (NULL == (pipe = _popen(pCmd.c_str(), "rt")))
	{
		return;
	}

	while (!feof(pipe))
	{
		if (fgets(buf, 256, pipe) != NULL)
		{
			f.push_back(std::string(buf));
		}
	}
	_pclose(pipe);
	for (unsigned int i = 0; i < f.size(); i++)
	{
		std::string name = f[i];
		name.erase(0, targetPath.length());
		name.erase(name.length() - 1);
		creeSon((char*)name.c_str());
	}
}

ControleurSon::~ControleurSon()
{
	for (unsigned int i = 0; i < soundTable_.size(); i++)
		soundTable_[i].second.second->stop();
	system_->release();
	system_->close();
}

void ControleurSon::creeSon(char* sName)
{
	std::string name(sName);

	// Check if already created
	for (unsigned int i = 0; i < soundTable_.size(); i++)
		if (soundTable_[i].first == name)
			return;

	std::string path = getPath(sName);
	const char* sPath = path.c_str();
	std::cout << "\tAdding " << name << "..." << std::setw(40 - name.length());

	std::pair< std::string, std::pair< FMOD::Sound *, FMOD::Channel* > > apair;
	apair.first = std::string(sName);
	apair.second.first = NULL;
	apair.second.second = NULL;
	soundTable_.push_back(apair);
	std::cout << ((system_->createSound(sPath, FMOD_DEFAULT, 0, &soundTable_[soundTable_.size()-1].second.first)
				 == FMOD_OK) ? "OK" : "FAILED") << std::endl;
	specialEffectSounds_.push_back(soundTable_.size() - 1);
}

void ControleurSon::jouerSon(char* sName, bool pause)
{
	int i = lookUp(std::string(sName));
	if (i == -1)
		return;
	system_->playSound(FMOD_CHANNEL_FREE, soundTable_[i].second.first, pause, &soundTable_[i].second.second);
	setVolumeLimiter();
}

void ControleurSon::bouclerSon(char* sName, bool loop)
{
	int i = lookUp(std::string(sName));
		if (i == -1)
			return;
	soundTable_[i].second.first->setMode(sName ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);

	for (unsigned int j = 0; j < backGroundMusic_.size(); j++)
		if (backGroundMusic_[j] == i)
			backGroundMusic_.erase(backGroundMusic_.begin() + i);
	for (unsigned int j = 0; j < specialEffectSounds_.size(); j++)
		if (specialEffectSounds_[j] == i)
			specialEffectSounds_.erase(specialEffectSounds_.begin() + i);

	if (loop)
		backGroundMusic_.push_back(i);
	else
		specialEffectSounds_.push_back(i);

}

void ControleurSon::arreterSon(char* sName)
{
	int i = lookUp(std::string(sName));
	if (i == -1)
		return;
	soundTable_[i].second.second->stop();
}

void ControleurSon::sourdine(bool mute)
{
	FMOD::ChannelGroup *canal;
	system_->getMasterChannelGroup(&canal);
	canal->setMute(mute);
}

unsigned int ControleurSon::lookUp(std::string fileName)
{
	for (unsigned int i = 0; i < soundTable_.size(); i++)
		if (soundTable_[i].first == fileName)
			return i;
	
	creeSon((char*)fileName.c_str());

	for (unsigned int i = 0; i < soundTable_.size(); i++)
		if (soundTable_[i].first == fileName)
			return i;	

	std::cout << "ERROR: " << fileName << " not found !";
	return -1;
}

void ControleurSon::ajusterBGM(float percent)
{
	// Si n'Est pas entre 0 et 1 mais plus tot entre 0 et 100
	if (percent > 1.0)
		percent /= 100;
	if (percent > 1 || percent < 0)
		percent = -1;
	maxBGM_ = percent;
}

void ControleurSon::ajusterSFX(float percent)
{
	// Si n'Est pas entre 0 et 1 mais plus tot entre 0 et 100
	if (percent > 1.0)
		percent /= 100;
	if (percent > 1 || percent < 0)
		percent = -1;
	maxSFX_ = percent;
}

void ControleurSon::setVolumeLimiter()
{
	setVolumeBGM();
	setVolumeSFX();
}

void ControleurSon::setVolumeBGM()
{
	if (maxBGM_ == -1) return;
	for (unsigned int i = 0; i < backGroundMusic_.size(); i++)
		soundTable_[backGroundMusic_[i]].second.second->setVolume(maxBGM_);
}

void ControleurSon::setVolumeSFX()
{
	if (maxSFX_ == -1) return;
	for (unsigned int i = 0; i < specialEffectSounds_.size(); i++)
		soundTable_[specialEffectSounds_[i]].second.second->setVolume(maxSFX_);
}

std::string ControleurSon::getPath(char* sName)
{
	std::string soundPath = "media/SFX/" + std::string(sName);
	return soundPath;
}