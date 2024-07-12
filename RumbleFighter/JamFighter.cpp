#include <iostream>
#include <cstdarg>
#include "JamFighter.h"

JamFighter* g_JamFighter = NULL;

JamFighter::JamFighter()
{
	m_fullScreen = FALSE;

}

int DisplayError(const char* message, const char* title) {
    MessageBoxA(NULL, message, title, 0);
    return 0;
}

char gInit(HINSTANCE hInstance, LPSTR lpCmdLine) {

    return 0;
}


bool FUN_00682dc0()
{
  return true;
}

char* GetSRC()
{
  return "SRCERR-FINAL";
}

DWORD GetVer()
{
    return 0x17b;
}

DWORD GetVer2()
{
    return 0x9;
}

int Log(const char* file, DWORD line, DWORD code, const char* message_format, ...) {
    static int first_launch = 1;
    FILE* log_file;

    if (first_launch) {
        // Check if the log file exists and delete it if it does
        if (fopen_s(&log_file, "RumbleFighter.Log", "r") == 0) {
            fclose(log_file);
            remove("RumbleFighter.Log");
        }
        first_launch = 0;
    }

    fopen_s(&log_file, "RumbleFighter.Log", "a");
    if (log_file == NULL) {
        perror("Failed to open log file");
        return 0;
    }

    // Get current time
    SYSTEMTIME st;
    GetLocalTime(&st);

    // Format the log message
    char buffer[100];
    va_list args;
    va_start(args, message_format);
    vsprintf_s(buffer, sizeof(buffer), message_format, args);
    va_end(args);

    // Write to log file
    fprintf(log_file, "%02d:%02d:%02d.%03d %s(%d):  %s\n",
        st.wHour, st.wMinute, st.wSecond, st.wMilliseconds,
        file, line, buffer);

    fclose(log_file);

    return 1;
}

int Logger(int a1, const char *Format)
{
    va_list ArgList;
    va_start(ArgList, Format);
    return 1;
}

void CreateReg()
{
    HKEY hKey;

    LSTATUS status = RegCreateKeyExA(
        HKEY_CURRENT_USER,
        "Software\\Nimonix\\RumbleDecomp",  // lpSubKey: Subkey path
        0,                                             // Reserved: Must be zero
        nullptr,                                       // lpClass: Class type (null)
        0,                                             // dwOptions: Options (0)
        KEY_ALL_ACCESS,                                // samDesired: Security access
        nullptr,                                       // lpSecurityAttributes: Security attributes (null)
        &hKey,                                         // phkResult: Pointer to handle
        NULL                                       // lpdwDisposition: Disposition
    );

    // Check if operation was successful
    if (status != ERROR_SUCCESS) {
        hKey = nullptr; // Set handle to null if an error occurred
    }
}

int findCharacter(char str[], char targetChar) {
    // Iterate through the string
    for (int i = 0; str[i] != '\0'; i++) {
        // Check if the current character matches the target character
        if (str[i] == targetChar) {

            return i; // Return the index where the character is found
        }

    }

    // If the character is not found, return -1
    return -1;
}

void ParseCmdLine(int OPTIONS[])
{
    int local_c = 1;
    LPWSTR* szArglist;
    int nArgs;

    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
    if (NULL == szArglist)
    {
        wprintf(L"CommandLineToArgvW failed\n");
        //return 0;
    }

    while (local_c < nArgs)
    {
        // Convert LPWSTR to char* for comparison
        char arg[100]; // Assuming a reasonable length for argument
        size_t convertedChars = 0;
        wcstombs_s(&convertedChars, arg, 100, szArglist[local_c], _TRUNCATE);

        if (_strnicmp(arg, "serviceid", 9) == 0)
        {
            wprintf(L"Found 'serviceid' argument: %ws\n", szArglist[local_c]);
            int iVar3 = findCharacter(arg, '=');
            if (iVar3 != -1)
            {
                char value[100]; // Adjust the size as needed
                strcpy_s(value, &arg[iVar3 + 1]);
                printf("Value:%s\n", value);
            }
        }
        else if (_strnicmp(arg, "userid", 6) == 0)
        {
            wprintf(L"Found 'userid' argument: %ws\n", szArglist[local_c]);
            int iVar3 = findCharacter(arg, '=');
            if (iVar3 != -1)
            {
                char value[100]; // Adjust the size as needed
                strcpy_s(value, &arg[iVar3 + 1]);
                printf("Value:%s\n", value);
            }
        }
        else if ((arg[0] == '/') || (arg[0] == '-'))
        {

            if (_strnicmp(arg + 1, "Windowed", 8) == 0)
            {
                printf("Windowed: %ws\n", L"true");
                *OPTIONS = 1;
            }
            else
            {
                if (_strnicmp(arg + 1, "Res", 3) == 0)
                {
                    printf("Res: %ws\n", L"true");
                    int iVar3 = findCharacter(arg, ':');
                    if (iVar3 != -1)
                    {
                        char value[100]; // Adjust the size as needed
                        strcpy_s(value, &arg[iVar3 + 1]);
                        printf("Res Value:%s\n", value);
                    }

                }
                else if (_strnicmp(arg + 1, "Single", 6) == 0)
                {
                    printf("Single: %ws\n", L"true");
                    OPTIONS[3] = 1;

                }
                else if (_strnicmp(arg + 1, "NoEdge", 6) == 0)
                {
                    printf("NoEdge: %ws\n", L"true");
                    OPTIONS[0x26] = 1;

                }
                else if (_strnicmp(arg + 1, "Ticket", 6) == 0)
                {
                    int iVar3 = findCharacter(arg, ':');
                    if (iVar3 != -1)
                    {
                        char value[100]; // Adjust the size as needed
                        strcpy_s(value, &arg[iVar3 + 1]);
                        printf("Ticket Value:%s\n", value);
                    }

                }
                else if (_strnicmp(arg + 1, "NOBGM", 5) == 0)
                {
                    printf("NOBGM: %ws\n", L"true");
                    OPTIONS[0x28] = 1;

                }
                else if (_strnicmp(arg + 1, "NoVShader", 9) == 0)
                {
                    printf("NoVShader: %ws\n", L"true");
                    OPTIONS[0x25] = 1;

                }
                else if (_strnicmp(arg + 1, "16bit", 5) == 0)
                {
                    printf("16bit: %ws\n", L"true");
                    OPTIONS[0x27] = 1;

                }
                else if (_strnicmp(arg + 1, "NETIF", 5) == 0)
                {
                    int iVar3 = findCharacter(arg, ':');
                    if (iVar3 != -1)
                    {
                        char value[100]; // Adjust the size as needed
                        strcpy_s(value, &arg[iVar3 + 1]);
                        printf("NETIF Value:%s\n", value);
                    }

                }
                else if (_strnicmp(arg + 1, "Server", 6) == 0)
                {
                    int iVar3 = findCharacter(arg, ':');
                    if (iVar3 != -1)
                    {
                        char value[100]; // Adjust the size as needed
                        strcpy_s(value, &arg[iVar3 + 1]);
                        printf("Server Value:%s\n", value);
                    }

                }
                else if (_strnicmp(arg + 1, "P2PTest", 7) == 0)
                {
                    printf("P2PTest: %ws\n", L"true");

                    OPTIONS[4] = 1;

                }
                else if (_strnicmp(arg + 1, "HOST", 4) == 0)
                {
                    printf("HOST: %ws\n", L"true");

                    OPTIONS[0x300] = 1;

                }
                else if (_strnicmp(arg + 1, "Port", 4) == 0)
                {
                    int iVar3 = findCharacter(arg, ':');
                    if (iVar3 != -1)
                    {
                        char value[100]; // Adjust the size as needed
                        strcpy_s(value, &arg[iVar3 + 1]);
                        printf("Port Value:%s\n", value);
                    }

                }
                else if (_strnicmp(arg + 1, "Sprtset", 7) == 0)
                {
                    int iVar3 = findCharacter(arg, ':');
                    if (iVar3 != -1)
                    {
                        char value[100]; // Adjust the size as needed
                        strcpy_s(value, &arg[iVar3 + 1]);
                        printf("Sprtset Value:%s\n", value);
                    }
                }
                else if (_strnicmp(arg + 1, "user_id", 7) == 0)
                {
                    int iVar3 = findCharacter(arg, ':');
                    if (iVar3 != -1)
                    {
                        char value[100]; // Adjust the size as needed
                        strcpy_s(value, &arg[iVar3 + 1]);
                        printf("user_id Value:%s\n", value);
                    }

                }
                else if (_strnicmp(arg + 1, "username", 8) == 0)
                {
                    int iVar3 = findCharacter(arg, ':');
                    if (iVar3 != -1)
                    {
                        char value[100]; // Adjust the size as needed
                        strcpy_s(value, &arg[iVar3 + 1]);
                        printf("user_id Value:%s\n", value);
                    }

                }
                else if (_strnicmp(arg + 1, "user_token", 10) == 0)
                {
                    int iVar3 = findCharacter(arg, ':');
                    if (iVar3 != -1)
                    {
                        char value[100]; // Adjust the size as needed
                        strcpy_s(value, &arg[iVar3 + 1]);
                        printf("user_id Value:%s\n", value);
                    }

                }
            }

        }

        local_c = local_c + 1;

    }

    LocalFree(szArglist);
    if (OPTIONS[4] != '\0') {
        OPTIONS[3] = 0;
    }
    return;

}


int InitNetwork(float a, int a2, void *Src) {
    printf("Network");
    int result  = 0;
    HANDLE mutexHandle;
    mutexHandle = HINSTANCE(a2);

    if (result == 0)
    {
        DisplayError("System Error", "GEM Fighter");
    }
    if (result == '\0')
    {
        DisplayError("InitNetwork fail", "GEM Fighter");
    }

    mutexHandle = CreateMutexA(NULL, FALSE, "wpavkdlxjabxprtm2");
    DWORD singleobj = WaitForSingleObject(mutexHandle, 100);
    if (singleobj != 0)
    {
        //return 0;
    }

    while (result != '\1')
    {
        DWORD Version = GetVersion();

        if (Version < (DWORD)0x80000000)
        {

            if (4 < (byte)Version)
            {
                STICKYKEYS sk;
                sk.cbSize = sizeof(STICKYKEYS);

                TOGGLEKEYS tk;
                tk.cbSize = sizeof(TOGGLEKEYS);

                FILTERKEYS fk;
                fk.cbSize = sizeof(FILTERKEYS);

                SystemParametersInfoA(SPI_GETSTICKYKEYS, sizeof(STICKYKEYS), &sk, 0);
                SystemParametersInfoA(SPI_GETTOGGLEKEYS, sizeof(TOGGLEKEYS), &tk, 0);
                SystemParametersInfoA(SPI_GETFILTERKEYS, sizeof(FILTERKEYS), &fk, 0);

                int priority = 1;
                mutexHandle = GetCurrentThread();
                SetThreadPriority(mutexHandle, priority);
                CreateReg();
                int OPTIONS[100] = { 0 };
                ParseCmdLine(OPTIONS);

                bool bLauncher = true;

                if (bLauncher)
                {
                    const char* src = "JamFighter.cpp";
                    DWORD code = 1698;
                    DWORD anothercode = 256;
                    Log(src, code, anothercode, "LAUNCHER User!!");

                }

                auto v11 = operator new(0x90u);


                break;
            }

        }

        HANDLE pvVar = OpenEventA(0x1f0003, 0, "slahslrtm");
        if (pvVar != (HANDLE)0x0)
        {
            DisplayError("Is Not A Handle", "RF");
            SetEvent(pvVar);
            CloseHandle(pvVar);
        }

    }


    return 4;
}


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    
	bool cVar1;
	bool BVar3;
	int* puVar6;
	int DAT1 = 0;
	int DAT2 = 0;
	int DAT3 = 0;
	char* uVar4;
	DWORD uVar00;
	DWORD uVar2;

	HANDLE hHandle;
	LPCSTR lpParameters;
	LPCSTR lpDirectory;
	LPVOID pvReserved;

    cVar1 = FUN_00682dc0();

    if (cVar1 == true) {

        BVar3 = IsDebuggerPresent();
        if (BVar3 == false) {
            puVar6 = &DAT1;
        }
        else {
            puVar6 = &DAT2;
        }
    }
    else {
        puVar6 = &DAT3;
    }

    hHandle = CreateMutexA((LPSECURITY_ATTRIBUTES)0x0, 0, "wpavkdlxjabxprtm");

    if (!WaitForSingleObject(hHandle, 0x64u))
    {
            CoInitialize(0);
        pvReserved = (LPVOID)WaitForSingleObject(hHandle, 100);
        uVar4 = GetSRC();
        uVar00 = GetVer();
        uVar2 = GetVer2();

        char buffer[100];
        sprintf(buffer, "GemVer%d.%d_%05d_%s", 0, uVar2, uVar00, uVar4);
        //printf(buffer);

        const char* src = "JamFighter.cpp";
        DWORD code = 878;
        DWORD anothercode = 256;

        Log(src, code, anothercode, buffer);
        //Rumfus();
        //auto v10 = 0;

        //if (v10 == 1877)
        //{

        //}
        //TaskManager(108);
        char conditionResult;
        char anotherResult;
        //conditionResult = AnotherCheckFunction(hInstance, lpCmdLine);
        conditionResult = '\0';
        if (conditionResult == '\0') {
            anotherResult = InitNetwork(0, int(hInstance), lpCmdLine);
            if (anotherResult == 1) {
                ShellExecuteA(0, 0, 0, 0, 0, 1);
            }
            else if (anotherResult == 2) {
                ShellExecuteA(0, 0, "https://www.playredfox.com/rumble_fighter", 0, 0, 1);
            }
            else if (anotherResult == 3) {
                //DisplayError("can not connect to game server", "Rumble Fighter");
            }
            else {
                ShellExecuteA(0, 0, "RumbleLauncher.exe", 0, 0, 1);

            }
        }

        //FUN_00401e90(&local_114, &DAT_007d17d8);

        const char* errorMessage;
        const char* browserUrl;
        int errorCode;
        std::string formattedMessage;

        errorCode = 0;

        switch (errorCode) {
        case 0x6e:
            errorMessage = "GameGuard is already running.";
            break;
        case 0x70:
            errorMessage = "Failed to load virus and hacking protection.";
            break;
        case 0x72:
            errorMessage = "GameGuard initialization error.";
            break;
        case 0x73:
            errorMessage = "There are multiple instances of the game running.";
            break;
        case 0x78:
        case 0x7c:
        case 0x96:
        case 0x99:
            errorMessage = "GameGuard file does not exist or is corrupted.";
            break;
        case 0x9b:
            errorMessage = "Windows system files might be corrupted.";
            break;
        case 0xaa:
            errorMessage = "Fail to run GameGuard. Please retry.";
            break;
        case 200:
            errorMessage = "Illegal program detected. Close all unnecessary programs and try again.";
            break;
        case 0xe6:
            errorMessage = "GameGuard initialization error or GameGuard was already running.";
            break;
        case 0x140:
            errorMessage = "INI file does not exist or has been corrupted.";
            break;
        case 0x14a:
            errorMessage = "npgmup.des initialization error.";
            break;
        case 0x154:
            errorMessage = "Failed to connect to the GameGuard update server.";
            break;
        case 0x15e:
            errorMessage = "GameGuard update has been aborted.";
            break;
        case 0x168:
            errorMessage = "Failed to complete GameGuard update.";
            break;
        default:
            errorMessage = "Failed to connect to the GameGuard server.";
            break;
        }

        //formattedMessage = "GameGuard execute error: " + std::to_string(errorCode);
        MessageBoxA(nullptr, errorMessage, formattedMessage.c_str(), 0);

        return 0;

}
    
}
