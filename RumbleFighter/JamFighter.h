#ifndef JAMFIGHTER_H
#define JAMFIGHTER_H

#include <Windows.h>


class JamFighter {
public:
	JamFighter();
	~JamFighter();

	void Close();

	void SetupVideoFlags(
		BOOL fullScreen

	);

	BOOL ReadReg(LPCSTR name, LPSTR outValue, DWORD outSize);


	void LoadConfig();
	void Tick(BOOL sleepIfNotNextFrame);
	void SetupCursor(WPARAM wParam);



private:
	BOOL m_fullScreen;         // 0x10

};

#endif // ISLEAPP_H
