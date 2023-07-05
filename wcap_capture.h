#define WIN32_LEAN_AND_MEAN
#include <windows.h> // For RECT and other Win32 basic types (UINT64, BOOL,...)

typedef struct IGraphicsCaptureItemInterop        IGraphicsCaptureItemInterop;
typedef struct IDirect3D11CaptureFramePoolStatics IDirect3D11CaptureFramePoolStatics;
typedef struct IDirect3DDevice                    IDirect3DDevice;
typedef struct IGraphicsCaptureItem               IGraphicsCaptureItem;
typedef struct IDirect3D11CaptureFramePool        IDirect3D11CaptureFramePool;
typedef struct IGraphicsCaptureSession            IGraphicsCaptureSession;
typedef struct ID3D11Texture2D                    ID3D11Texture2D;
typedef struct ID3D11Device                       ID3D11Device;

typedef struct ITypedEventHandler { const struct ITypedEventHandlerVtbl* vtbl; } ITypedEventHandler;


// callbacks will be called on same thread as Capture_Init call - it is assumed this thread will have message loop

#ifdef __cplusplus
extern "C" {
#endif
	typedef void CaptureCloseCallback(void);
	typedef void CaptureFrameCallback(ID3D11Texture2D* Texture, RECT Rect, UINT64 Time);
#ifdef __cplusplus
}
#endif

typedef struct Capture {
	IGraphicsCaptureItemInterop* ItemInterop;
	IDirect3D11CaptureFramePoolStatics* FramePoolStatics;
	IDirect3DDevice* Device;
	IGraphicsCaptureItem* Item;
	IDirect3D11CaptureFramePool* FramePool;
	IGraphicsCaptureSession* Session;
	ITypedEventHandler OnCloseHandler;
	ITypedEventHandler OnFrameHandler;
	UINT64 OnCloseToken;
	UINT64 OnFrameToken;
	RECT Rect;
	SIZE CurrentSize;
	BOOL OnlyClientArea;
	HWND Window;
	CaptureCloseCallback* CloseCallback;
	CaptureFrameCallback* FrameCallback;
} Capture;

#ifdef __cplusplus
extern "C" {
#endif
	BOOL Capture_IsSupported(void);
	BOOL Capture_CanHideMouseCursor(void);
	void Capture_Init(Capture* Capture, CaptureCloseCallback* CloseCallback, CaptureFrameCallback* FrameCallback);

	BOOL Capture_CreateForWindow(Capture* Capture, ID3D11Device* Device, HWND Window, BOOL OnlyClientArea);
	BOOL Capture_CreateForMonitor(Capture* Capture, ID3D11Device* Device, HMONITOR Monitor, RECT* Rect);
	void Capture_Start(Capture* Capture, BOOL WithMouseCursor);
	void Capture_Stop(Capture* Capture);
#ifdef __cplusplus
}
#endif
