#include <Windows.h>
#include <Xinput.h>

namespace
{
  HMODULE xinput;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
  if(fdwReason == DLL_PROCESS_ATTACH) {
    xinput = LoadLibrary(L"C:\\Windows\\System32\\xinput1_3-orig.dll");
    if(xinput == 0)
      xinput = LoadLibrary(L"C:\\Windows\\System32\\xinput1_3.dll");
  }

  return TRUE;
}

template<class T>
T set_call(T& ptr, const char* name) {
  if(ptr == 0)
    ptr = (T) GetProcAddress(xinput, name);
  return ptr;
}

template<class T>
T set_call(T& ptr, int ord) {
  if(ptr == 0)
    ptr = (T) GetProcAddress(xinput, (const char*) ord);
  return ptr;
}

void WINAPI XInputEnable(BOOL state)
{
  static void (WINAPI *orig)(BOOL state);
  return set_call(orig, __FUNCTION__)(state);
}

DWORD WINAPI XInputGetBatteryInformation(DWORD dwUserIndex, BYTE devType, XINPUT_BATTERY_INFORMATION *pBatteryInformation)
{
  static DWORD (WINAPI *orig)(DWORD dwUserIndex, BYTE devType, XINPUT_BATTERY_INFORMATION *pBatteryInformation);
  return set_call(orig, __FUNCTION__)(dwUserIndex, devType, pBatteryInformation);
}

DWORD WINAPI XInputGetCapabilities(DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES *pCapabilities)
{
  static DWORD (WINAPI *orig)(DWORD dwUserIndex, DWORD dwFlags, XINPUT_CAPABILITIES *pCapabilities);
  return set_call(orig, __FUNCTION__)(dwUserIndex, dwFlags, pCapabilities);
}

DWORD WINAPI XInputGetDSoundAudioDeviceGuids(DWORD dwUserIndex, GUID* pDSoundRenderGuid, GUID* pDSoundCaptureGuid)
{
  static DWORD (WINAPI *orig)(DWORD dwUserIndex, GUID* pDSoundRenderGuid, GUID* pDSoundCaptureGuid);
  return set_call(orig, __FUNCTION__)(dwUserIndex, pDSoundRenderGuid, pDSoundCaptureGuid);
}

DWORD WINAPI XInputGetKeystroke(DWORD dwUserIndex, DWORD dwReserved, PXINPUT_KEYSTROKE pKeystroke)
{
  static DWORD (WINAPI *orig)(DWORD dwUserIndex, DWORD dwReserved, PXINPUT_KEYSTROKE pKeystroke);
  return set_call(orig, __FUNCTION__)(dwUserIndex, dwReserved, pKeystroke);
}

DWORD WINAPI XInputGetState(DWORD dwUserIndex, XINPUT_STATE *pState)
{
  static DWORD (WINAPI *orig)(DWORD dwUserIndex, XINPUT_STATE *pState);
  return set_call(orig, __FUNCTION__)(dwUserIndex, pState);
}

DWORD WINAPI XInputSetState(DWORD dwUserIndex, XINPUT_VIBRATION *pVibration)
{
  static DWORD (WINAPI *orig)(DWORD dwUserIndex, XINPUT_VIBRATION *pVibration);
  return set_call(orig, __FUNCTION__)(dwUserIndex, pVibration);
}

DWORD WINAPI XInputOrd100(DWORD dwUserIndex, XINPUT_STATE *pState)
{
  static DWORD (WINAPI *orig)(DWORD dwUserIndex, XINPUT_STATE *pState);
  return set_call(orig, "XInputGetState")(dwUserIndex, pState);
}

DWORD WINAPI XInputOrd101(DWORD dwUserIndex, DWORD unk, void* ptr)
{
  static DWORD (WINAPI *orig)(DWORD dwUserIndex, DWORD unk, void* ptr);
  return set_call(orig, 101)(dwUserIndex, unk, ptr);
}

DWORD WINAPI XInputOrd102(DWORD dwUserIndex)
{
  static DWORD (WINAPI *orig)(DWORD dwUserIndex);
  return set_call(orig, 102)(dwUserIndex);
}

DWORD WINAPI XInputOrd103(DWORD dwUserIndex)
{
  static DWORD (WINAPI *orig)(DWORD dwUserIndex);
  return set_call(orig, 103)(dwUserIndex);
}
